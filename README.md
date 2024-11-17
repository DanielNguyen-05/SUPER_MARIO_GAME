# SUPER MARIO BROS
![](https://raw.githubusercontent.com/DanielNguyen-05/SUPER_MARIO_GAME/refs/heads/main/assets/icon.ico?token=GHSAT0AAAAAAC2EDGJ5AKIPLMNBAUR73PEUZZZQMSA)

![](https://img.shields.io/github/release/pandao/editor.md.svg)

----
## Project Details
[CS202-FinalProject_SuperMario](https://docs.google.com/document/d/1N59hDBAQYoavpiW9zewu9_QKwtMipv-ZIDnmylP1gEg/edit?tab=t.0#heading=h.pdkhz280o558 "CS202-FinalProject_SuperMario")

##Contributors
Nguyen Hai Dang - 23127165
Ngo An Binh - 23127330
Dao Hoang Duc Manh - 23127417

<h2 style="display: flex; align-items: center;">
  <span>Tutorial</span>
  <img src="https://raw.githubusercontent.com/DanielNguyen-05/SUPER_MARIO_GAME/refs/heads/main/assets/vscode.svg?token=GHSAT0AAAAAAC2EDGJ4Y6BBSZNYMN27CUQEZZZRKDA" style="width: 35px; margin-left: 15px;">
</h2>

<img src="https://raw.githubusercontent.com/DanielNguyen-05/SUPER_MARIO_GAME/refs/heads/main/assets/windows.svg?token=GHSAT0AAAAAAC2EDGJ4KI6M5GUF5CXVK6VKZZZRJRA" style="width: 35px; margin-right: 10px;" align="mid"> **WINDOWS**

**Note** : If you want to play the game only, see *step 5*.
1. Install a [C++ compiler](https://code.visualstudio.com/docs/cpp/config-mingw "C++ compiler"). ( using [MSYS2](https://www.msys2.org/ "MSYS2") )
2. Install [Make](https://packages.msys2.org/packages/make "Make"). ( to run *makefile* )
3. Install SFML based on your compiler : [clang64](https://packages.msys2.org/packages/mingw-w64-clang-x86_64-sfml "clang64"), [ucrt64](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-sfml "ucrt64") or [mingw64](https://packages.msys2.org/packages/mingw-w64-x86_64-sfml "mingw64")
4. Open a terminal in the directory that contains the *makefile*, then run `make` to build the program.
5. Run `launcher.exe`
6. To clean game files (and rebuild the program), run `make clean` in the terminal.

**The terminal may display the following**
1. `make: Nothing to be done for 'all'` — This means the program has already been built.

