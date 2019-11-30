#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "AllHeader.h"
#include "Vector3.h"
#include "Color.h"
#include "ColorDeclaration.h"
#include "GameObject.h"
#include "TicTacToe.h"
#include "DataPacker.h"
#include "GUI.h"

const int RESOLUTION_X = 800;
const int RESOLUTION_Y = 600;
bool ShowConsoleWindow;

void Stealth(int cmdShow)
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, cmdShow);
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	
	glViewport(0.0f, 0.0f, width, height);				// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
	
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		ShowConsoleWindow = !ShowConsoleWindow;
	}
}

int main(void)
{
	//Stealth(0);
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{
		return -1;
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "Multiplayer TicTacToe by Teena 0118856", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, key_callback);
	onWindowResized(window, RESOLUTION_X, RESOLUTION_Y);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
	glfwSwapInterval(1); //enable/disable vsync

	TransferData transferData;
	PlayerData playerData;
	PlayerData enemyData;
	GameData gameData;

	TicTacToe ticTacToe = TicTacToe(window);
	ticTacToe.SetTransferData(&transferData);
	ticTacToe.SetPlayerData(&playerData);
	ticTacToe.SetEnemyData(&enemyData);
	ticTacToe.SetGameData(&gameData);

	MyPhoton::getInstance().SetTransferData(&transferData);
	MyPhoton::getInstance().SetPlayerData(&playerData);
	MyPhoton::getInstance().SetEnemyData(&enemyData);
	MyPhoton::getInstance().SetGameData(&gameData);

	MyPhoton::getInstance().connect();

	GUI gui = GUI(window);
	gui.SetPlayerData(&playerData);
	gui.SetEnemyData(&enemyData);
	gui.SetGameData(&gameData);

	ticTacToe.Start();
	srand(time(NULL));

	float deltaTime = 0.0f;
	int width;
	int height;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			break;
		}

		if (ShowConsoleWindow == true)
		{
			HWND hWnd = GetConsoleWindow();
			ShowWindow(hWnd, SW_SHOW);
		}
		else if(ShowConsoleWindow == false)
		{
			HWND hWnd = GetConsoleWindow();
			ShowWindow(hWnd, SW_HIDE);
		}

		/* Render here */
		MyPhoton::getInstance().run();
		ticTacToe.Update();
		gui.DrawGameGUI();
		ticTacToe.Draw();
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}