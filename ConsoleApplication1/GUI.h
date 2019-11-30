#pragma once
#include "AllHeader.h"
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL2_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl2.h"
#include "PlayerData.h"
#include "Sprite.h"
#include "GUIStyle.h"

class GUI
{
protected:
	GLFWwindow* window;
	struct nk_context *ctx;
	int m_width;
	int m_height;

	PlayerData* playerData;
	PlayerData* enemyData;
	GameData* gameData;
	ColorTable colorTable;

	Texture oWinSprite = Texture("../Media/O Win.png");
	Texture xWinSprite = Texture("../Media/X Win.png");
	struct nk_image oWinImage = nk_image_id(oWinSprite.m_textureID);
	struct nk_image xWinImage = nk_image_id(xWinSprite.m_textureID);

public:

	GUI() {};

	GUI(GLFWwindow* win)
	{
		window = win;
		/* GUI */
		ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
		{
			struct nk_font_atlas *atlas;
			nk_glfw3_font_stash_begin(&atlas);
			//struct nk_font* font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 20.0f, 0); */
			struct nk_font* font = nk_font_atlas_add_default(atlas, 20.0f, 0);
			nk_glfw3_font_stash_end();
			nk_style_set_font(ctx, &font->handle);
		}
		set_style(ctx, Theme::THEME_RED_CUSTOM);
		ctx->style.button.text_normal = nk_rgba(0, 0, 0, 255);
		ctx->style.button.text_active = nk_rgba(0, 0, 0, 255);
	}

	~GUI()
	{
		nk_glfw3_shutdown();
	}

	void SetPlayerData(PlayerData* data)
	{
		playerData = data;
	}

	void SetEnemyData(PlayerData* data)
	{
		enemyData = data;
	}

	void SetGameData(GameData* data)
	{
		gameData = data;
	}

	void DrawGameGUI()
	{
		nk_glfw3_new_frame();
		glfwGetFramebufferSize(window, &m_width, &m_height);
		/* GUI */
		if (nk_begin(ctx, "", nk_rect(0, 0, m_width, m_height), NK_WINDOW_NO_SCROLLBAR))
		{
			DrawData();
		}
		
		nk_end(ctx);
		nk_glfw3_render(NK_ANTI_ALIASING_ON);
	}

	void DrawData()
	{
		static struct nk_color red = { 242,109,125,255 };
		static struct nk_color green = { 28,187,180,255 };
		static struct nk_color white = { 255,255,255,255 };
		
		nk_layout_row_dynamic(ctx, 1, 1);
		nk_layout_row_dynamic(ctx, 30, 1);
		int playerInt = (int)playerData->playerType + 1;
		int enemyInt = (int)enemyData->playerType + 1;
		if (playerInt > 2)
		{
			playerInt = -1;
		}
		if (enemyInt > 2)
		{
			enemyInt = -1;
		}
		nk_label(ctx, TextCombiner("You are Player: ", playerInt, "").c_str(), NK_TEXT_ALIGN_CENTERED);
		nk_layout_row_dynamic(ctx, 30, 3);
		nk_label(ctx, TextCombiner("Player: ", playerInt, "").c_str(), NK_TEXT_ALIGN_LEFT);

		if (nk_button_label(ctx, "Restart"))
		{
			gameData->doReset = true;
			UIntPacker::getInstance().pack((int)gameData->doReset, 1);
			MyPhoton::getInstance().sendMyData(UIntPacker::getInstance().GetData());
		}
		nk_label(ctx, TextCombiner("Player: ", enemyInt, "").c_str(), NK_TEXT_ALIGN_RIGHT);


		nk_layout_row_dynamic(ctx, 20, 3);
		nk_label(ctx, TextCombiner("Score: ", playerData->score, "").c_str(), NK_TEXT_ALIGN_LEFT);
		
		if (gameData->canPlay == true)
		{
			if (gameData->matchResult == MatchResult::NONE)
			{
				if (gameData->curPlayer == PlayerType::PLAYER_1)
				{
					nk_label_colored(ctx, TextCombiner("Player: ", gameData->curPlayer + 1, " turn").c_str(), NK_TEXT_ALIGN_CENTERED, green);
				}
				else if (gameData->curPlayer == PlayerType::PLAYER_2)
				{
					nk_label_colored(ctx, TextCombiner("Player: ", gameData->curPlayer + 1, " turn").c_str(), NK_TEXT_ALIGN_CENTERED, red);
				}
			}
			else if (gameData->matchResult != MatchResult::NONE)
			{
				if (gameData->winner == PlayerType::PLAYER_1)
				{
					nk_label_colored(ctx, TextCombiner("Player: ", gameData->curPlayer + 1, " Wins").c_str(), NK_TEXT_ALIGN_CENTERED, green);
				}
				else if (gameData->winner == PlayerType::PLAYER_2)
				{
					nk_label_colored(ctx, TextCombiner("Player: ", gameData->curPlayer + 1, " Wins").c_str(), NK_TEXT_ALIGN_CENTERED, red);
				}
				else
				{
					nk_label_colored(ctx, "Player 1 and 2 are Draw", NK_TEXT_ALIGN_CENTERED, white);
				}
			}
		}
		else
		{
			nk_label_colored(ctx, "", NK_TEXT_ALIGN_CENTERED, white);
		}
		
		
		nk_label(ctx, TextCombiner("Score: ", enemyData->score, "").c_str(), NK_TEXT_ALIGN_RIGHT);

		struct nk_window *win;
		struct nk_rect bounds1;
		struct nk_rect bounds2;
		struct nk_rect bounds3;
		win = ctx->current;

		nk_layout_space_begin(ctx, NK_STATIC, 50, 2);
		nk_layout_space_push(ctx, nk_rect(0, 0, 100, 100));
		if (nk_widget(&bounds1, ctx))
		{
			if (playerData->playerType == PlayerType::PLAYER_1)
			{
				nk_draw_image(&win->buffer, bounds1, &oWinImage, nk_rgb(255, 255, 255));
			}
			else if (playerData->playerType == PlayerType::PLAYER_2)
			{
				nk_draw_image(&win->buffer, bounds1, &xWinImage, nk_rgb(255, 255, 255));
			}
		}

		nk_layout_space_push(ctx, nk_rect(m_width - 105, 0, 100, 100));
		if (nk_widget(&bounds2, ctx))
		{
			if (enemyData->playerType == PlayerType::PLAYER_1)
			{
				nk_draw_image(&win->buffer, bounds2, &oWinImage, nk_rgb(255, 255, 255));
			}
			else if (enemyData->playerType == PlayerType::PLAYER_2)
			{
				nk_draw_image(&win->buffer, bounds2, &xWinImage, nk_rgb(255, 255, 255));
			}
		}

		nk_layout_space_push(ctx, nk_rect(m_width/2 - 400, m_height - 200, 800, 800));
		if (nk_widget(&bounds3, ctx))
		{
			nk_label_colored(ctx, "Press Space to Show or Hide Console Window", NK_TEXT_ALIGN_CENTERED, white);
		}
		nk_layout_space_end(ctx);

	}

	static std::string TextCombiner(std::string text1, int score, std::string text2)
	{
		std::stringstream sstm;
		
		if (score < 0)
		{
			sstm << text1 << text2;
		}
		else
		{
			sstm << text1 << score << text2;
		}

		return sstm.str();
	}
};
