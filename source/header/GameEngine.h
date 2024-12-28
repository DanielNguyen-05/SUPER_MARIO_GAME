#pragma once
#include "DEFINITION.h"
#include "Characters.h"
#include "Mario.h"
#include "Luigi.h"

class GameEngine
{
    /*          Properties          */
private:
    Font headerFont;
    ostringstream scoreStr, timerStr, coinsStr, lifeStr;
    Clock timer, convertTimer, coinTimer;
    int currentTime, levelTime, counterTime, scoreInt, fontSize, coinsInt, remainTime, lifeInt;
    fstream playersFile;
    map<string, int> levelsMap;
    Texture coinTexture;
    Sprite coinSprite, charLifeSprite;
    SoundBuffer popUpBuffer, smashBuffer, coinBuffer, powerUpBuffer, powerUpAppearBuffer, killBuffer;
    IntRect coinRect;


public:
    bool lifeScreen, gameRunning;
    CharacterTypeEnum CHAR_TYPE;
    shared_ptr<Characters> character;
    Text timerText, scoreText, coinsText, levelText, lifeText;
    Font floatingTextFont;
    Texture stoneTexture, questionTexture, smashTextures[6], itemTexture, enemyTextrue;
    Sound popUpSound, smashSound, coinSound, powerUpSound, powerUpAppearSound, killSound;
    player currentPlayer;
    Texture bulletTexture;  // Khai báo bulletTexture


    /*         Constractar          */
    GameEngine();

    /*          Method         */

    // Update current score with Increased Score and display it
    void updateScore(int IncScore);

    // Start timer
    void startCountDown();

    // Update timer
    void updateTimer();

    // Check wheater Level time is finished or not
    bool isTimerFinished();

    // Convert remain time to score when player won
    void timeToScore();

    // draw GameEngine objects into screen
    void draw(RenderWindow& window);

    // Increase coins counter by one
    void updateCoins();

    // Add player name , his score and level to Players file
    void addPlayerInfo(int level);

    // Set level Name text
    void setLevelName(std::string levelName);

    // Start Converting time to Score
    void startTimeToScore();

    // make coin spin during time
    void coinAnimation();

    // update life times when mario dies
    void updateLifes();

    // Set header position to move with Camera
    void setHeaderPosition(position screenCenter);

    // Start Life Screen
    void startLifeScreen(RenderWindow& window);

    void setCharacterType(CharacterTypeEnum type);

    void reset();

    int getScore() {
        return scoreInt - ((levelTime - currentTime) * 100);
    }

    int getTime() {
        return levelTime - currentTime;
    }

    int getCoins() {
        return coinsInt;
    }
};
