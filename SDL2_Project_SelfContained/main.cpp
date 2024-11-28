#include <iostream>
#include <SDL2/SDL.h>
#include "glm/glm.hpp"
#include <vector>

struct Pothole {
    int x, y, width, height;
};

enum GameState {
    RUNNING,
    PAUSED
};

GameState gameState = RUNNING;



std::vector<Pothole> potholes;
Uint32 lastPotholeTime = 0;
bool startGeneratingPotholes = false;
const float potholeSpeed = 200.0f;


// Define window dimensions
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 800;

// Define SDL Window-related variables
SDL_Window* window = NULL;
SDL_Renderer* windowRenderer = NULL;
SDL_Event currentEvent;

bool quit = false;



float lineOffset = 0;         
const float lineSpeed = 200.0f; 
Uint32 lastFrameTime = 0;
Uint32 startTime = 0;
Uint32 duration = 90000;

int carHeight = 70;
int carWidth = 50;
int carX = WINDOW_WIDTH / 2 + 15 + ((WINDOW_WIDTH / 2) - 15 - 70) / 2 - carWidth / 2;
int carY = WINDOW_HEIGHT - 100 - carHeight;

bool initWindow() {
    bool success = true;

    // Try to initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initialization failed" << std::endl;
        success = false;
    }
    else {
        // Try to create the window
        window = SDL_CreateWindow(
            "Speed Race",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN);

        if (window == NULL) {
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        }
        else {
            // Create a renderer for the current window
            windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (windowRenderer == NULL) {
                std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
                success = false;
            }
            else {
                // Set background color
                SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
                SDL_RenderClear(windowRenderer);
            }
        }
    }

    return success;
}

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return !(a.x + a.w < b.x ||
        a.x > b.x + b.w ||
        a.y + a.h < b.y ||  
        a.y > b.y + b.h); 
}


void processEvents() {
    // Check for events in queue
    if (SDL_GetTicks() - startTime > 3000) {
        startGeneratingPotholes = true;
    }
    while (SDL_PollEvent(&currentEvent)) {
        // User requests quit
        if (currentEvent.type == SDL_QUIT) {
            quit = true;
        }
        int margine = WINDOW_WIDTH - 70 - carWidth;
        // Keyboard event
        if (currentEvent.type == SDL_KEYDOWN) {
            switch (currentEvent.key.keysym.sym) {
            case SDLK_UP:
                break;

            case SDLK_DOWN:
                break;

            case SDLK_r:
                gameState = RUNNING;
                potholes.clear();
                std::cout << "Game started!" << '\n';
                startTime = 0;
                duration += SDL_GetTicks();
                break;

            case SDLK_LEFT:
                if (gameState == RUNNING) {
                    if (carX <= 70) {
                        carX = 70;
                        break;
                    }
                    else {
                        carX -= 10;
                        if (carX <= 70) carX = 70;
                    }
                }
                break;

            case SDLK_RIGHT:
                if (gameState == RUNNING) {
                    if (carX >= margine) {
                        carX = margine;
                        break;
                    }
                    else {
                        carX += 10;
                        if (carX >= margine) carX = margine;
                    }
                }
                break;

            case SDLK_s:
                break;

            case SDLK_ESCAPE:
                quit = true;
                break;

            default:
                break;
            }
        }
    }
}
void drawDashedLine() {
    int dashHeight = 70;
    int dashSpacing = 50; 
    int lineWidth = 30;    
    int centerX = WINDOW_WIDTH / 2;


    SDL_SetRenderDrawColor(windowRenderer, 255, 255, 0, 255);

    for (int y = -dashHeight; y < WINDOW_HEIGHT; y += dashHeight + dashSpacing) {
        int adjustedY = y + static_cast<int>(lineOffset) % (dashHeight + dashSpacing);
        SDL_Rect dash = { centerX - lineWidth / 2, adjustedY, lineWidth, dashHeight };
        SDL_RenderFillRect(windowRenderer, &dash);
    }
}

void generatePothole() {
    int potholeWidth = carWidth / 2 + rand() % (carWidth * 3);
    int potholeHeight = carHeight / 2 + rand() % (carHeight);
    int potholeX = 70 + rand() % (WINDOW_WIDTH - 70 * 2 - potholeWidth);
    int potholeY = -potholeHeight;

    Pothole newPothole = { potholeX, potholeY, potholeWidth, potholeHeight };
    potholes.push_back(newPothole);
}

void updatePotholes(float deltaTime) {
    if (gameState == PAUSED) {
        return; 
    }

    SDL_Rect carRect = { carX, carY, carWidth, carHeight };

    for (auto& pothole : potholes) {
        pothole.y += potholeSpeed * deltaTime;

        SDL_Rect potholeRect = { pothole.x, pothole.y, pothole.width, pothole.height };

        if (checkCollision(carRect, potholeRect)) {
            std::cout << "Collision detected! Game finished. Press r to restart!" << std::endl;
            gameState = PAUSED;
            return;
        }
    }

    potholes.erase(
        std::remove_if(potholes.begin(), potholes.end(), [](const Pothole& p) {
            return p.y > WINDOW_HEIGHT;
            }),
        potholes.end()
    );
}




void drawPotholes() {
    SDL_SetRenderDrawColor(windowRenderer, 0, 0, 0, 255);
    for (const auto& pothole : potholes) {
        SDL_Rect rect = { pothole.x, pothole.y, pothole.width, pothole.height };
        SDL_RenderFillRect(windowRenderer, &rect);
    }
}


void drawCar() {
    if (gameState == RUNNING) {
        SDL_SetRenderDrawColor(windowRenderer, 0, 255, 0, 255);
        SDL_Rect car = { carX, carY, carWidth, carHeight };
        SDL_RenderFillRect(windowRenderer, &car);
    }
    else {
        SDL_SetRenderDrawColor(windowRenderer, 255, 0, 0, 255);
        SDL_Rect car = { carX, carY, carWidth, carHeight };
        SDL_RenderFillRect(windowRenderer, &car);
    }
}

void drawFrame() {
    SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(windowRenderer);

    SDL_SetRenderDrawColor(windowRenderer, 0, 0, 255, 255);
    SDL_Rect leftWall = { 50, 0, 20, WINDOW_HEIGHT };
    SDL_RenderFillRect(windowRenderer, &leftWall);

    SDL_Rect rightWall = { WINDOW_WIDTH-70, 0, 20, WINDOW_HEIGHT };
    SDL_RenderFillRect(windowRenderer, &rightWall);

    SDL_SetRenderDrawColor(windowRenderer, 128, 128, 128, 255);
    SDL_Rect street = { 70,0,WINDOW_WIDTH - 70 * 2,WINDOW_HEIGHT };
    SDL_RenderFillRect(windowRenderer, &street);
    
    drawDashedLine();
    drawCar();
    drawPotholes();
    SDL_RenderPresent(windowRenderer);
}

void cleanup() {
    // Destroy renderer
    if (windowRenderer) {
        SDL_DestroyRenderer(windowRenderer);
        windowRenderer = NULL;
    }

    // Destroy window
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    // Quit SDL
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    // Initialize window
    if (!initWindow()) {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }

    startTime = SDL_GetTicks();
    Uint32 lastFrameTime = startTime;
    // Game loop
    while (!quit) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentTime;

        processEvents();

        if (gameState == RUNNING) {
            lineOffset += lineSpeed * deltaTime;

            if (startGeneratingPotholes && SDL_GetTicks() - lastPotholeTime > 1000 + rand() % 4000) {
                generatePothole();
                lastPotholeTime = SDL_GetTicks();
            }

            updatePotholes(deltaTime);
        }
        if (lastFrameTime >= duration) {
            quit = true;
        }
        drawFrame();

        SDL_Delay(16);
    }


    cleanup();
    return 0;
}
