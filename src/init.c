#include "init.h"

/*
 * Initializes the SDL context, renderer, and
 * window.
 */
void initSDL(void) {
  int rendererFlags;
  int windowFlags;

  rendererFlags = SDL_RENDERER_ACCELERATED;
  windowFlags   = 0;

  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initialization started.");

  // Initialize SDL and exit if we fail.
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL: %s.\n", SDL_GetError());
    exit(EXIT_ERROR);
  }

  // Initialize the SDL window.
  app.window = SDL_CreateWindow("Shooter Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

  if (!app.window) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not open window. %s.\n", SDL_GetError());
    exit(EXIT_ERROR);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  // Create renderer with the default graphics context.
  app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

  if (!app.renderer) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize renderer: %s.\n", SDL_GetError());
    exit(EXIT_ERROR);
  }

  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initialization Completed.");

  //  Initialize SDL to accept both JPG and PNGs.
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

  //  Remove cursor.
  SDL_ShowCursor(false);

  initAudioContext();
}

/*
 *
 */
void initAudioContext(void) {
  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) == -1) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL Mixer.\n");
    exit(EXIT_ERROR);
  }

  Mix_AllocateChannels(MAX_SND_CHANNELS);
}

/*
 * Cleans up the SDL context and game upon closing the application.
 */
void cleanup(void) {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Cleaning up.");
	SDL_DestroyRenderer(app.renderer);

	SDL_DestroyWindow(app.window);

	SDL_Quit();
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Program quit.");
}
