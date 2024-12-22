#include "../header/Menu.h"

// Set Back Text Properties
void Menu::setBackText()
{
    // Tạo font và text
    if (!this->font.loadFromFile(CAIRO_REGULAR))
    {
        std::cerr << "Error loading font" << "\n";
    }

    this->backText.setFont(this->font);
    this->backText.setString("Press ESC to exit!");
    this->backText.setCharacterSize(30);
    this->backText.setFillColor(sf::Color::White); // Màu chữ trắng

    // Tạo khung nền cho text
    sf::RectangleShape textBackground;
    textBackground.setFillColor(sf::Color::Black);    // Nền đen
    textBackground.setOutlineColor(sf::Color::White); // Viền trắng
    textBackground.setOutlineThickness(2);

    // Tính toán kích thước khung dựa trên text
    sf::FloatRect textBounds = this->backText.getLocalBounds();
    textBackground.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20)); // Thêm padding 10px mỗi bên
    textBackground.setPosition(1350.0, 855.0);                                           // Vị trí của khung

    // Căn chỉnh text ở giữa khung
    this->backText.setPosition(
        textBackground.getPosition().x + (textBackground.getSize().x - textBounds.width) / 2 - textBounds.left,
        textBackground.getPosition().y + (textBackground.getSize().y - textBounds.height) / 2 - textBounds.top);
}

// Set Changing Option Sound Properties
void Menu::setChangeOptionSound()
{
    if (!this->changingOptionBuffer.loadFromFile(CHANGING_OPTION_SOUND))
    {
        std::cerr << "Error loading sound" << "\n";
    }
    // Create a sound source (changingOptionSound) and bind it to the buffer
    this->changingOptionSound.setBuffer(this->changingOptionBuffer);
    this->changingOptionSound.setVolume(100);
}

// Draw Menu Options
void Menu::draw(sf::RenderWindow &window)
{
    if (this->display == true)
    {
        window.draw(this->backGroundSprite);
        window.draw(this->backText);
    }
}

// Control Menu events
void Menu::catchEvents(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            this->hide();
            changingOptionSound.play();
        }
    }
}

// Make Menu display
void Menu::show()
{
    this->display = true;
}

// Close Menu
void Menu::hide()
{
    this->display = false;
}