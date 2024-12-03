#include "../header/CreditsMenu.h"

CreditsMenu::CreditsMenu() {
    display = false;

    setBackText();
    setChangeOptionSound();

    // Load background
    if (!backGroundTexture.loadFromFile(CREDITS_BACKGROUND)) { std::cout << "Can't load CREDITS_BACKGROUND\n"; }
    backGroundSprite.setTexture(backGroundTexture);
}