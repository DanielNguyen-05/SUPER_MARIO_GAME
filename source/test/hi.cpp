#include <iostream>
#include <fstream>
#include <string>

int main()
{
    system("cls");
    std::ifstream ignoreFile("../ignore.txt");
    if (!ignoreFile.is_open())
    {
        std::cerr << "Không thể mở file: " << std::endl;
        return 0;
    }

    std::string line;
    while (std::getline(ignoreFile, line))
    {
        std::cout << line << std::endl;
    }

    ignoreFile.close();

    return 0;
}
