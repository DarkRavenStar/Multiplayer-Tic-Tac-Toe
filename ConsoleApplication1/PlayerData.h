#pragma once
#include "AllHeader.h"

enum PlayerType
{
	PLAYER_1,
	PLAYER_2,
	NO_PLAYER
};

enum MatchResult
{
	NONE,
	WIN,
	DRAW
};

struct PlayerData
{
	PlayerType playerType = PlayerType::NO_PLAYER;
	int score = 0;
};

struct GameData
{
	bool canPlay = false;
	bool doReset = false;
	MatchResult matchResult = MatchResult::NONE;
	PlayerType winner = PlayerType::NO_PLAYER;
	PlayerType curPlayer = PlayerType::PLAYER_1;
	unsigned int turnNum;
};


struct TransferData
{
	bool execute = false;
	unsigned char playerData;
};
