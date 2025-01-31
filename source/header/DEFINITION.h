#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include <memory>
#include <cstring>
#include <memory>

using namespace std;
using namespace sf;

enum CharacterTypeEnum
{
    MARIO,
    LUIGI
};

enum CharacterStateEnum
{
    SMALL,
    BIG,
    SUPER
};

enum ItemEnum
{
    COIN,
    MASHROOM,
    FLOWER,
    SPARKL,
    NONE
};

enum BlockEnum
{
    QUESTION,
    STONE,
    BRONZE,
    SMASH,
    ROCK
};

enum EnemyEnum
{
    BLACK,
    SMASHED,
    TURTLE,
    SHELL
};

struct player
{
    string username;
    string level1Score;
    string level2Score;
    string level3Score;
    string level;
    int lifes;
    float enemiesSpeed;
};

struct area
{
    float width;
    float height;
};

struct position
{
    float x;
    float y;
};

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define LEGACY_FONT "assets/fonts/legacy.ttf"

#define MAIN_MENU_FONT "assets/fonts/super_mario_256.ttf"

#define CAIRO_REGULAR "assets/fonts/Cairo-Regular.ttf"

#define MAIN_MENU_BACKGROUND "assets/textures/Menu/Menu.jpg"

#define LEVELS_LIST_BACKGROUND "assets/textures/Menu/levelsList.jpg"

#define PLAYER_NAME_BACKGROUND "assets/textures/Menu/Login.jpg"

#define MENU_SHADOW "assets/textures/MenuShadow.png"

#define HIGH_SCORE_BACKGROUND "assets/textures/Menu/1.jpg"

#define HOW_TO_PLAY_BACKGROUND "assets/textures/Menu/howToPlay.jpg"

#define OPTIONS_BACKGROUND "assets/textures/Menu/Options.jpg"

#define CREDITS_BACKGROUND "assets/textures/Menu/Credits.jpg"

#define FORMAT_BACKGROUND "assets/textures/Backgrounds/FormatScreen.jpg" // làm để winner screen

#define MUSIC_BALL "assets/textures/Menu/musicBall.png"

// #define DIFFICULTY_BALL "assets/textures/Menu/difficultyBall.png"

#define CONTROL_BALL "assets/textures/Menu/controlBall.png"

#define MENU_SOUND "assets/music/MenuMusic.ogg"

#define CHANGING_OPTION_SOUND "assets/sounds/fireball.wav"

/**********************************************************/

/***						Character						***/
#define MARIO_CHARACTER "assets/textures/Mario.png"

#define MARIO_SUPER_CHARACTER "assets/textures/MarioSuper.png"

#define LUIGI_CHARACTER "assets/textures/Luigi.png"

#define LUIGI_SUPER_CHARACTER "assets/textures/LuigiSuper.png"

#define JUMP_SOUND "assets/sounds/jump.wav"

#define DAMAGE_SOUND "assets/sounds/damage.wav"

#define DIE_SOUND "assets/sounds/mario_die.wav"

/**********************************************************/

/***					GameEngine						***/
#define PLAYERS_FILE "Files/Players.txt"

#define ACCOUNT_FILE "Files/users.txt"

#define GAME_HEADER_FONT "assets/fonts/legacy.ttf"

#define GAME_FONT "assets/fonts/legacy.ttf"

/**********************************************************/

/***						Items							***/
#define ITEMS "assets/textures/Items.png"

#define COIN_SOUND "assets/sounds/coin.wav"

#define POWERUP_SOUND "assets/sounds/powerup.wav"

#define POWERUP_APPEAR_SOUND "assets/sounds/powerup_appears.wav"

/**********************************************************/

/***						Blocks							***/
#define QUESTION_BLOCK "assets/textures/AnimTiles.png"

#define STONE_BLOCK "assets/textures/Tiles.png"

#define SMASH_STONE_BLOCK "assets/textures/Smash/Br"

#define FLOATING_FONT "assets/fonts/Floating_font.otf"

#define POPUP_SOUND "assets/sounds/pop_up.wav"

#define SMASH_SOUND "assets/sounds/smash.wav"

#define BRICK "assets/textures/brick.png"

/**********************************************************/

/***						Levels							***/
#define LEVEL_MUSIC "assets/music/Levels.wav"

#define LEVEL1_BACKGROUND "assets/textures/Backgrounds/Blue.jpg"

#define LEVEL2_BACKGROUND "assets/textures/Backgrounds/Red.jpg"

#define LEVEL1_GROUND "assets/textures/blueGround.png"

#define LEVEL2_GROUND "assets/textures/redGround.png"

/**********************************************************/

/***						Enemy							***/
#define ENEMY "assets/textures/Enemies.png"

#define KILL_SOUND "assets/sounds/kick.wav"

/**********************************************************/