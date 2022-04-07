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
