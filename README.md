# Testris_vs
Test Tetris project written in C++ using SDL2

ChangeLog:
- 2022.04.06.
	* Added VStudio Solution
	* Added GameEngine
	* Added RenderEngine
	* Added Game logic of GameBoard and Block 
** Important Note: ** makefile based build is not supported yet, Solution includes SDL2 and SDL_TTF libraries, these should be included into project in VStudio before building!

- 2022.04.07.
	* Added Ghost to falling blocks
	* Fixed Runtime Exception in case of dropping lines had to reach the bottom of the grid (over indexing exception)
	* Removed a lot of commented out (leftover code)
	* Removed debug console outputs
- 2025.07.04.
  	* Removed VStudio related project files and changed to VSCode based project
  	* Introducing CMake based build system
  	* Added SDL2 library based on release: SDL 2.32.8 [https://github.com/libsdl-org/SDL/releases/tag/release-2.32.8]
  	* Added SDL2_ttf library (but struggling with linking) based on release: SDL2_ttf 2.24.0 [https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.24.0]
  	* Removed original static DLLs and font (Debug folder) as they will be handled by CMake from sources and dynamic copied next to executable after build.
