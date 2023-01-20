#include <SDL.h>
#include <stdio.h>
#include <string>




// creates a window
bool init();
//loads media
bool loadMedia();
//shut down protocol
void close();

SDL_Window* gwindow = NULL; // main window
SDL_Surface* gScreenSurface = NULL; // base layer of the window
SDL_Surface* gHelloWorld = NULL; // our image

//Screen size constants
const int SCREENWIDTH = 640;
const int SCREENHEIGHT = 480;





int main(int argc, char* args[]) {

	bool quit = false;

	if (!init()) {
		printf("Failed to initialize \n");
	}
	else {

		//loading media

		if (!loadMedia()) {
			printf("Failed to load media \n");
			
		}
		else {
			//applying image
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

			//swap to back buffer
			SDL_UpdateWindowSurface(gwindow);

			//trick to keep window open
			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}
	close(); //closin aka free resources

	return 0;
}

bool init() {

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_ERROR: s%\n", SDL_GetError());
		success = false;
	}
	else {
		gwindow = SDL_CreateWindow("SDLTEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);

		if (gwindow == NULL) {
			printf("Window couldn't be initialized ERRORl s%\n:", SDL_GetError());
			success = false;
		}
		else gScreenSurface = SDL_GetWindowSurface(gwindow);	
	}

	if (success)
		printf("init() initialized successfully s%\n");

	SDL_Delay(3000);
	return success;
}

bool loadMedia() {

	bool success = true;

	gHelloWorld = SDL_LoadBMP("C:\\Users\\David\\source\\Projects\\SDLTest\\SDLOne\\x64\\Debug\\maxresdefault.bmp");

	if (gHelloWorld == nullptr) {
		printf("Unable to load image %s! SDL Error: %s\n", "img/maxresdefault.bmp", SDL_GetError());
		success = false;
	}

	if (!success)
		printf("Error in loadMedia()");

	return success;
}

void close() {

	//DEALLOCATING IMAGE - AKA
	//Functions below probably contain the delete keyword somewhere.
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//DESTROYING WINDOW
	SDL_DestroyWindow(gwindow);
	gwindow = NULL;

	SDL_Quit();
}

