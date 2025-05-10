#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint64 last_step;
} AppState;

#define WINDOW_WIDTH 1920 / 2
#define WINDOW_HEIGHT 1080 / 2
#define BACKGROUND_COLOR 69, 60, 103, SDL_ALPHA_OPAQUE
#define STEP_RATE_MS 125

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    if (!SDL_SetAppMetadata("platformer", "1.0", "com.tg.platformer")) {
        return SDL_APP_FAILURE;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState *as = (AppState *)SDL_calloc(1, sizeof(AppState));
    if (!as) {
        return SDL_APP_FAILURE;
    }
    *appstate = as;

    if (!SDL_CreateWindowAndRenderer("stuf", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                     &as->window, &as->renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    int resizable = 1; // allow resizing
    SDL_SetWindowResizable(as->window, resizable);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;

    case SDL_EVENT_KEY_UP:
        if (event->key.key == SDLK_ESCAPE)
            return SDL_APP_SUCCESS;
        break;

    default:
        // event handler
        break;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState *as = (AppState *)appstate;
    const Uint64 now = SDL_GetTicks();

    while ((now - as->last_step) >= STEP_RATE_MS) {
        // fixed update
        as->last_step += STEP_RATE_MS;
    }

    SDL_SetRenderDrawColor(as->renderer, BACKGROUND_COLOR);
    SDL_RenderClear(as->renderer);

    // render game stuff

    SDL_RenderPresent(as->renderer);
    SDL_Delay(16);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    if (appstate != NULL) {
        AppState *as = (AppState *)appstate;
        SDL_DestroyWindow(as->window);
        SDL_DestroyRenderer(as->renderer);
        SDL_free(as);
    }
}
