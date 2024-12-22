#include "../header/OptionsMenu.h"

OptionsMenu::OptionsMenu()
{
    muteMusic = false;
    display = false;

    setBackText();

    if (!backGroundTexture.loadFromFile(OPTIONS_BACKGROUND))
    {
        std::cerr << "Cannot load OPTIONS_BACKGROUND\n";
    }
    backGroundSprite.setTexture(backGroundTexture);

    if (!menuBuffer.loadFromFile(MENU_SOUND))
    {
        std::cerr << "Cannot load MENU_SOUND\n";
    }
    menuSound.setBuffer(menuBuffer);
    menuSound.setLoop(true);
    menuSound.play();

    setChangeOptionSound();

    // Set shadow properties
    if (!optionShadowTexture.loadFromFile(MENU_SHADOW))
    {
        std::cerr << "Cannot load MENU_SHADOW\n";
    }
    optionShadowSprite.setTexture(optionShadowTexture);
    optionShadowSprite.setColor(Color(255, 255, 255, 100));
    optionShadowSprite.setPosition(185, 140);
    optionShadowSprite.setScale(0.9, 1);

    // Set Music Ball Properties
    if (!musicBallTexture.loadFromFile(MUSIC_BALL))
    {
        std::cerr << "Cannot load MUSIC_BALL\n";
    }
    musicBallSprite.setTexture(musicBallTexture);
    musicBallSprite.setPosition(482, 410);

    // Set Control ball properties
    if (!controlBallTexture.loadFromFile(CONTROL_BALL))
    {
        std::cerr << "Can't load CONTROL_BALL\n";
    }
    controlBallSprite.setTexture(controlBallTexture);
    controlBallSprite.setPosition(966, 255);
}

void OptionsMenu::draw(sf::RenderWindow &window)
{
    if (display)
    {
        window.draw(backGroundSprite);
        window.draw(optionShadowSprite);
        window.draw(backText);
        window.draw(musicBallSprite);
        window.draw(controlBallSprite);
    }
}

void OptionsMenu::catchEvents(Event event, player &newPlayer)
{
    if (display)
    {
        switch (event.type)
        {
        case Event::KeyReleased:
            switch (event.key.code)
            {
            case Keyboard::Right:
                moveRight();
                changingOptionSound.play();
                break;

            case Keyboard::Left:
                moveLeft();
                changingOptionSound.play();
                break;

            case Keyboard::Up:
                changeSettings(true, newPlayer);
                changingOptionSound.play();
                break;

            case Keyboard::Down:
                changeSettings(false, newPlayer);
                changingOptionSound.play();
                break;

            case Keyboard::Escape:
                this->hide();
                changingOptionSound.play();
                break;

            default:
                break;
            }
        default:
            break;
        }
    }
}

void OptionsMenu::moveRight()
{
    // Cái này nữa căn chỉnh theo UI mới nha, tại mình không có làm có Difficulty
    // if box in Difficulty postion set to Music
    if (optionShadowSprite.getPosition().x == 1105)
    {
        optionShadowSprite.setPosition(185, 140);
        activeSlide = 0;
    }
    else
    {
        optionShadowSprite.move(460, 0);
        activeSlide++;
    }
}

void OptionsMenu::moveLeft()
{
    // Cái này nữa căn chỉnh theo UI mới nha, tại mình không có làm có Difficulty
    // if box in Music postion set to Difficulty
    if (optionShadowSprite.getPosition().x == 185)
    {
        optionShadowSprite.setPosition(1105, 140);
        activeSlide = 2;
    }
    else
    {
        optionShadowSprite.move(-460, 0);
        activeSlide--;
    }
}

void OptionsMenu::changeSettings(bool up, player &newPlayer)
{
    switch (activeSlide)
    {
    case 0:
        changeActiveMusicOption();
        break;
    case 1:
        changeActiveControlOption();
        break;
    case 2:
        // changeActiveDifficultyOption();
        break;
    }
}

void OptionsMenu::changeActiveMusicOption()
{
    muteMusic = !muteMusic;
    if (muteMusic)
    {
        musicBallSprite.setPosition(482, 468);
    }
    else
    {
        musicBallSprite.setPosition(482, 410);
    }
    updateMusicSettings();
}

void OptionsMenu::changeActiveControlOption()
{
    handControlled = !handControlled;
    if (handControlled)
    {
        controlBallSprite.setPosition(966, 450);
    }
    else
    {
        controlBallSprite.setPosition(966, 255);
    }
    updateControlSettings();
}

void OptionsMenu::updateControlSettings()
{
    if (handControlled)
    {
        // system("start cmd /k \"python  \"HandControler/HandControl.py\"\"");
        // handControlled = false;
    }
    else
    {
        // system("taskkill /f /im python.exe");
    }
}

void OptionsMenu::updateMusicSettings()
{
    if (muteMusic)
    {
        menuSound.pause();
        // levelSound.setVolume(0);
    }
    else
    {
        menuSound.play();
        // levelSound.setVolume(100);
    }
}