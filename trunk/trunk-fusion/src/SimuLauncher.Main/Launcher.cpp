/*This source code copyrighted by Lazy Foo' Productions (2004-2014)
 and may not be redistributed without written permission.*/

//Using SDL, standard IO, strings, and string streams
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>
#include <string>

#include "SDL/SDL_svg.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 665;

//Total windows
const int TOTAL_WINDOWS = 3;

class LWindow
{
public:
	//Intializes internals
	LWindow();

	//Creates window
	bool init(int i);

	//Handles window events
	void handleEvent(SDL_Event& e);

	//Focuses on window
	void focus();

	//Shows windows contents
	void render(int i);

	//Deallocates internals
	void free();

	//Window dimensions
	int getWidth();
	int getHeight();

	//Window focii
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();
	bool isClosed();

private:
	//Window data
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Surface* mImage;
	SDL_Texture* mTexture;
	SDL_Rect dstrect;

	int mWindowID;

	//Window dimensions
	int mWidth;
	int mHeight;

	//Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
	bool mShown;
	bool mClosed;
};

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Our custom windows
LWindow gWindows[TOTAL_WINDOWS];

LWindow::LWindow()
{
	//Initialize non-existant window
	mWindow = NULL;
	mRenderer = NULL;
	mImage = NULL;
	mTexture = NULL;
	dstrect =
	{	0,0,0,0};

	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mShown = false;
	mClosed = false;
	mWindowID = -1;

	mWidth = 0;
	mHeight = 0;
}

bool LWindow::init(int i)
{
	switch (i)
	{
	case 0:

		//Create window
		mWindow = SDL_CreateWindow("Main Window", 200, 0, SCREEN_WIDTH,
				SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (mWindow != NULL)
		{
			mMouseFocus = true;
			mKeyboardFocus = true;
			mWidth = SCREEN_WIDTH;
			mHeight = SCREEN_HEIGHT;

			//Create renderer for window
			mRenderer = SDL_CreateRenderer(mWindow, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n",
						SDL_GetError());
				SDL_DestroyWindow(mWindow);
				mWindow = NULL;
			}
			else
			{

				 //Initialize renderer color
				 mImage =
				 IMG_Load(
				 "/home/pmx/workspaceTest/SimuLauncher/Debug/resources/E2015_Sketchup-2-hires-interieur-3000x2000.png");
				 mTexture = SDL_CreateTextureFromSurface(mRenderer, mImage);

				 dstrect =
				 {	0, 0, 1000, 666};

				 render(i);



				/*
					//test SVG
					double Scalex, Scaley;

					SDL_svg_context *TestImage =
							SVG_Load(
									"/home/pmx/workspaceTest/SimuLauncher/Debug/resources/tux.svg");

					SVG_SetOffset(TestImage, SVG_Width(TestImage) / 2,
							SVG_Height(TestImage) / 2);

					Scalex = mImage->w / SVG_Width(TestImage);
					Scaley = mImage->h / SVG_Height(TestImage);
					//SVG_SetScale(TestImage, Scalex, Scaley);

					SVG_RenderToSurface(TestImage, mImage->w / 2 ,
							mImage->h / 2, mImage);

					SVG_RenderToSurface(TestImage, mImage->w / 2 ,
											mImage->h / 2, mImage);
	*/
					//Clear screen
								//SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
								//SDL_RenderClear(mRenderer);
					//fin test SVG



				//Grab window identifier
				mWindowID = SDL_GetWindowID(mWindow);

				//Flag as opened
				mShown = true;
			}
		}
		else
		{
			printf("Window could not be created! SDL Error: %s\n",
					SDL_GetError());
		}
		printf("Main Window n°%d => ID=%d\n", i, mWindowID);
		break;

	case 1:

		//Create window
		mWindow = SDL_CreateWindow("Windows 1", 0, 0, 200, 200,
				SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (mWindow != NULL)
		{
			mMouseFocus = true;
			mKeyboardFocus = true;
			mWidth = SCREEN_WIDTH;
			mHeight = SCREEN_HEIGHT;

			//Create renderer for window
			mRenderer = SDL_CreateRenderer(mWindow, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n",
						SDL_GetError());
				SDL_DestroyWindow(mWindow);
				mWindow = NULL;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(mRenderer);
				SDL_RenderPresent(mRenderer);

				//Grab window identifier
				mWindowID = SDL_GetWindowID(mWindow);

				//Flag as opened
				mShown = true;
			}
		}
		else
		{
			printf("Window could not be created! SDL Error: %s\n",
					SDL_GetError());
		}
		printf("Window n°%d => ID=%d\n", i, mWindowID);
		break;

	case 2:

		//Create window
		mWindow = SDL_CreateWindow("Windows 2", 0, 250, 200, 200,
				SDL_WINDOW_SHOWN);
		if (mWindow != NULL)
		{
			mMouseFocus = true;
			mKeyboardFocus = true;
			mWidth = SCREEN_WIDTH;
			mHeight = SCREEN_HEIGHT;

			//Create renderer for window
			mRenderer = SDL_CreateRenderer(mWindow, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n",
						SDL_GetError());
				SDL_DestroyWindow(mWindow);
				mWindow = NULL;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(mRenderer);
				SDL_RenderPresent(mRenderer);

				//Grab window identifier
				mWindowID = SDL_GetWindowID(mWindow);

				//Flag as opened
				mShown = true;
			}
		}
		else
		{
			printf("Window could not be created! SDL Error: %s\n",
					SDL_GetError());
		}
		printf("Window n°%d => ID=%d\n", i, mWindowID);
		break;

	default:

		//Create window
		mWindow = SDL_CreateWindow("SDL Tutorial default",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow != NULL)
		{
			mMouseFocus = true;
			mKeyboardFocus = true;
			mWidth = SCREEN_WIDTH;
			mHeight = SCREEN_HEIGHT;

			//Create renderer for window
			mRenderer = SDL_CreateRenderer(mWindow, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n",
						SDL_GetError());
				SDL_DestroyWindow(mWindow);
				mWindow = NULL;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(mRenderer);
				SDL_RenderPresent(mRenderer);

				//Grab window identifier
				mWindowID = SDL_GetWindowID(mWindow);

				//Flag as opened
				mShown = true;
			}
		}
		else
		{
			printf("Window could not be created! SDL Error: %s\n",
					SDL_GetError());
		}
	}
	printf("SDL Tutorial n°%d => ID=%d\n", i, mWindowID);
	return mWindow != NULL && mRenderer != NULL;
}

void LWindow::handleEvent(SDL_Event& e)
{
	//If an event was detected for this window
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID)
	{
		//Caption update flag
		bool updateCaption = false;

		switch (e.window.event)
		{
		//Window appeared
		case SDL_WINDOWEVENT_SHOWN:
			mShown = true;
			break;

			//Window disappeared
		case SDL_WINDOWEVENT_HIDDEN:
			mShown = false;
			break;

			//Get new dimensions and repaint
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			SDL_RenderPresent(mRenderer);
			break;

			//Repaint on expose
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(mRenderer);
			break;

			//Mouse enter
		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			updateCaption = true;
			break;

			//Mouse exit
		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			updateCaption = true;
			break;

			//Keyboard focus gained
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			updateCaption = true;
			break;

			//Keyboard focus lost
		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			updateCaption = true;
			break;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;

			//Hide and quit on close
		case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow(mWindow);
			mClosed = true;
			break;
		}

		//Update window caption with new data
		/*
		 if (updateCaption)
		 {
		 std::stringstream caption;
		 caption << "SDL Tutorial - ID: " << mWindowID << " MouseFocus:"
		 << ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:"
		 << ((mKeyboardFocus) ? "On" : "Off");
		 SDL_SetWindowTitle(mWindow, caption.str().c_str());
		 }*/
	}
}

void LWindow::focus()
{
	//Restore window if needed
	if (!mShown)
	{
		SDL_ShowWindow(mWindow);
	}

	//Move window forward
	SDL_RaiseWindow(mWindow);
}

void LWindow::render(int i)
{
	if (!mMinimized)
	{
		switch (i)
		{
		case 0:
			SDL_RenderCopy(mRenderer, mTexture, NULL, &dstrect);
			break;

		case 1:
			break;

		case 2:
			break;

		default:

			//Clear screen
			SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(mRenderer);

		}

		//Update screen
		SDL_RenderPresent(mRenderer);
	}
}

void LWindow::free()
{
	//SDL_DestroyTexture(texture);
	//    SDL_FreeSurface(image);
	SDL_DestroyRenderer(mRenderer);

	if (mWindow != NULL)
	{
		SDL_DestroyWindow(mWindow);
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int LWindow::getWidth()
{
	return mWidth;
}

int LWindow::getHeight()
{
	return mHeight;
}

bool LWindow::hasMouseFocus()
{
	return mMouseFocus;
}

bool LWindow::hasKeyboardFocus()
{
	return mKeyboardFocus;
}

bool LWindow::isMinimized()
{
	return mMinimized;
}

bool LWindow::isShown()
{
	return mShown;
}

bool LWindow::isClosed()
{
	return mClosed;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//init image png
		IMG_Init(IMG_INIT_PNG);

		//Create window
		if (!gWindows[0].init(0))
		{
			printf("Window 0 could not be created!\n");
			success = false;
		}
	}

	return success;
}

void close()
{
	//Destroy windows
	for (int i = 0; i < TOTAL_WINDOWS; ++i)
	{
		gWindows[i].free();
	}

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Initialize the rest of the windows
		for (int i = 1; i < TOTAL_WINDOWS; ++i)
		{
			gWindows[i].init(i);
		}

		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				//Handle window events
				for (int i = 0; i < TOTAL_WINDOWS; ++i)
				{
					gWindows[i].handleEvent(e);
				}

				//Pull up window
				if (e.type == SDL_KEYDOWN)
				{
					cout << "key pressed: " << e.key.keysym.sym << endl;
					switch (e.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						quit = true;

					case SDLK_KP_1:
						gWindows[0].focus();
						break;

					case SDLK_KP_2:
						gWindows[1].focus();
						break;

					case SDLK_KP_3:
						gWindows[2].focus();
						break;
					}
				}
			}

			//Update all windows

			for (int i = 0; i < TOTAL_WINDOWS; ++i)
			{
				gWindows[i].render(i);
			}

			//checked if one window is closed, so close all windows and quit
			for (int i = 0; i < TOTAL_WINDOWS; ++i)
			{
				if (gWindows[i].isClosed())
				{
					quit = true;
					break;
				}
			}

			//checked if all windows are minimized, if yes, close and quit
			bool allWindowsClosed = true;
			for (int i = 0; i < TOTAL_WINDOWS; ++i)
			{
				if (gWindows[i].isShown())
				{
					allWindowsClosed = false;
					break;
				}
			}

			if (allWindowsClosed)
			{
				quit = true;
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
