#include <iostream>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

int main()
{
        const std::string executablePath = "./source/lib/run.exe";

        if (std::filesystem::exists(executablePath))
        {
                std::cout << "Running the game..." << std::endl;
#ifdef _WIN32
                system(("start " + executablePath).c_str());
#elif __APPLE__
                system(("open " + executablePath).c_str());
#endif
        }
        else
        {
#ifdef _WIN32
                MessageBoxA(NULL, "Cannot find the game executable !", "Error", MB_OK | MB_ICONERROR);
#elif __APPLE__
                system("osascript -e 'display alert \"Error\" message \"Cannot find the game executable !\"'");
#endif
        }

        return 0;
}
