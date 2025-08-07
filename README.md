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
- 2025.08.07.
  	* Note to self: Preparing and installing SDL needs the following steps:
  		** Install Mingw86_64 (any version, the posix one seems common
  	  	** Install CMake and Git
  	  	** Git Pull SDL from their Github to an external_lib folder where you will use it from.
  	  	** create a build folder in the newly pulled SDL folder (SDL/build)
  	  	** cd into it and prepare the configuration:
  	  	** cmake .. -G "MinGW Makefiles"
  	  	** once it is done relatively without any failures and major problems
		** (Need Administrator terminal for the next step - still in SDL/build folder)
  	  	** mingw32-make install -j8
  	  	** Do the same for SDL_image, SDL_Ttf and so on whatever extension you would like to use in your code.
  	  	** after git pull of extension make sure you pull all the submodules as well
  	  	** git submodule update --init --recursive
  	  	** let's cd into the targeted external lib to be built: such as SDL_Image/external/zlib
  	  	** mkdir build, cd build and go again with the cmake .. -G "MinGW Makefiles", then make install -j8
  	  	** Do this with libpng as well and repeat the same steps.
  	  	** After this you can go and to the same build for SDL_Image itself, so you set up a simple libPNG usage for SDL_Image
  	  	
  	  
