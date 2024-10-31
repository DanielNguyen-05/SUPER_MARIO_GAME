#pragma once
/***		Include SFML files			***/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/***		Include Helper Libraries		***/
#include<iostream>
#include <sstream>
#include<iomanip>
#include<fstream>
#include<map>
#include<string>

/***        Include  */
using namespace std;
using namespace sf;


/***			Special Variable			***/
typedef enum { SMALL, BIG, SUPER } marioState_t;

typedef enum { COIN, MASHROOM, FLOWER, SPARKL, NONE } item_t;

typedef enum { QUESTION, STONE, BRONZE, SMASH, ROCK } block_t;

typedef enum { BLACK, SMASHED, TURTLE, SHELL } enemy_t;

struct player {
    string name;
    string score; // to be easily when read from file
    string level;
    int lifes;
    float enemiesSpeed;
};

struct area {
    float width;
    float height;
};

struct position {
    float x;
    float y;
};


#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900


/***						Menu						***/
#define MAIN_MENU_FONT "assets/Fonts/Barkentina_font.ttf"

#define CAIRO_REGULAR "assets/Fonts/Cairo-Regular.ttf"

#define MAIN_MENU_BACKGROUND "assets/Textures/Menu/Menu.jpg"

#define LEVELS_LIST_BACKGROUND "assets/Textures/Menu/levelsList.jpg"

#define PLAYER_NAME_BACKGROUND "assets/Textures/Menu/playerName.jpg"

#define MENU_SHADOW "assets/Textures/MenuShadow.png"

#define HIGH_SCORE_BACKGROUND "assets/Textures/Menu/highScore.jpg"

#define HOW_TO_PLAY_BACKGROUND "assets/Textures/Menu/howToPlay.jpg"

#define OPTIONS_BACKGROUND "assets/Textures/Menu/Options.jpg"

#define CREDITS_BACKGROUND "assets/Textures/Menu/Credits.jpg"

#define MUSIC_BALL "assets/Textures/Menu/musicBall.png"

#define DIFFICULTY_BALL "assets/Textures/Menu/difficultyBall.png"

#define CONTROL_BALL "assets/Textures/Menu/controlBall.png"

#define MENU_SOUND "assets/Music/MenuMusic.ogg"

#define CHANGING_OPTION_SOUND "assets/Sounds/fireball.wav"

/**********************************************************/




/***						Mario						***/
#define MARIO_CHARACTER "assets/Textures/Mario.png"

#define MARIO_SUPER_CHARACTER "assets/Textures/MarioSuper.png"

#define JUMP_SOUND "assets/Sounds/jump.wav"

#define DAMAGE_SOUND "assets/Sounds/damage.wav"

#define DIE_SOUND "assets/Sounds/mario_die.wav"

/**********************************************************/




/***					GameEngine						***/
#define PLAYERS_FILE "Files/Players.txt"
#define GAME_HEADER_FONT "assets/Fonts/some_font.ttf"

/**********************************************************/




/***						Items							***/
#define ITEMS "assets/Textures/Items.png"

#define COIN_SOUND "assets/Sounds/coin.wav"

#define POWERUP_SOUND "assets/Sounds/powerup.wav"

#define POWERUP_APPEAR_SOUND "assets/Sounds/powerup_appears.wav"

/**********************************************************/




/***						Blocks							***/
#define QUESTION_BLOCK "assets/Textures/AnimTiles.png"

#define STONE_BLOCK "assets/Textures/Tiles.png"

#define SMASH_STONE_BLOCK "assets/Textures/Smash/Br"

#define FLOATING_FONT "assets/Fonts/Floating_font.otf"

#define POPUP_SOUND "assets/Sounds/pop_up.wav"

#define SMASH_SOUND "assets/Sounds/smash.wav"
/**********************************************************/




/***						Levels							***/
#define LEVEL_MUSIC "assets/Music/Levels.wav"

#define LEVEL1_BACKGROUND "assets/Textures/Backgrounds/Blue.jpg"

#define LEVEL2_BACKGROUND "assets/Textures/Backgrounds/Red.jpg"

#define LEVEL1_GROUND "assets/Textures/blueGround.png"

#define LEVEL2_GROUND "assets/Textures/redGround.png"

/**********************************************************/




/***						Enemy							***/
#define ENEMY "assets/Textures/Enemies.png"

#define KILL_SOUND "assets/Sounds/kick.wav"

/**********************************************************/