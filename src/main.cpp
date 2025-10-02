#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <cmath>

#include "Game.h"
#include "input.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* pieces_texture = nullptr;

void cleanup() {
    if (pieces_texture != nullptr) {
        SDL_DestroyTexture(pieces_texture);
    }

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

int main() {
    const int INITIAL_WINDOW_WIDTH = 1280;
    const int INITIAL_WINDOW_HEIGHT = 720;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "[ERROR] SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Chess", INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cerr << "[ERROR] SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        cleanup();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        std::cerr << "[ERROR] SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        cleanup();
        return 1;
    }

    pieces_texture = IMG_LoadTexture(renderer, "assets/chess-pieces.png");
    if (pieces_texture == nullptr) {
        std::cerr << "[ERROR] IMG_LoadTexture failed: " << SDL_GetError() << std::endl;
        cleanup();
        return 1;
    }

    Game game(8, 8, pieces_texture);

    float left_mouse_button_down_x = -1;
    float left_mouse_button_down_y = -1;
    float right_mouse_button_down_x = -1;
    float right_mouse_button_down_y = -1;
    MouseClickEvent mouse_click_event;
    const int MOUSE_CLICK_POSITION_TOLERANCE = 10;

    bool is_running = true;
    while (is_running) {
        MouseClickEvent* current_mouse_click_event = nullptr;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
                    is_running = false;
                }
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    left_mouse_button_down_x = event.button.x;
                    left_mouse_button_down_y = event.button.y;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    right_mouse_button_down_x = event.button.x;
                    right_mouse_button_down_y = event.button.y;
                }
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                if (event.button.button == SDL_BUTTON_LEFT && abs(event.button.x - left_mouse_button_down_x) < MOUSE_CLICK_POSITION_TOLERANCE && abs(event.button.y - left_mouse_button_down_y) < MOUSE_CLICK_POSITION_TOLERANCE) {
                    mouse_click_event = { event.button.x, event.button.y, SDL_BUTTON_LEFT };
                    current_mouse_click_event = &mouse_click_event;
                } else if (event.button.button == SDL_BUTTON_RIGHT && abs(event.button.x - right_mouse_button_down_x) < MOUSE_CLICK_POSITION_TOLERANCE && abs(event.button.y - right_mouse_button_down_y) < MOUSE_CLICK_POSITION_TOLERANCE) {
                    mouse_click_event = { event.button.x, event.button.y, SDL_BUTTON_RIGHT };
                    current_mouse_click_event = &mouse_click_event;
                }
            }
        }

        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);
        game.process_input(window_width, window_height, current_mouse_click_event);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        game.render(renderer);

        SDL_RenderPresent(renderer);
    }

    cleanup();

    return 0;
}
