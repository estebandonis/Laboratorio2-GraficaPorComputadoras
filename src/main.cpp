#include <iostream>
#include <SDL2/SDL.h>

// Define the size of the framebuffer
const int FRAMEBUFFER_WIDTH = 90;
const int FRAMEBUFFER_HEIGHT = 90;
const int FRAMEBUFFER_SIZE = FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT;
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

// Define a Color struct to hold the RGB values of a pixel
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

// Declare the framebuffer as a global variable
Color framebuffer[FRAMEBUFFER_SIZE];

Color nextFramebuffer[FRAMEBUFFER_SIZE];

// Declare a global clearColor of type Color
Color clearColor = {0, 0, 0, 255}; // Initially set to black

// Declare a global currentColor of type Color
Color currentColor = {255, 255, 255, 255}; // Initially set to white

int x = 5;
int y = 5;

// Function to clear the framebuffer with the clearColor
void clear() {
    for (int i = 0; i < FRAMEBUFFER_SIZE; i++) {
        framebuffer[i] = clearColor;
    }
}

// Function to set a specific pixel in the framebuffer to the currentColor
void point(int x, int y) {
    if (x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT) {
        framebuffer[y * FRAMEBUFFER_WIDTH + x] = currentColor;
    }
}

void renderBuffer(SDL_Renderer* renderer) {
    // Create a texture
    SDL_Texture* texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        FRAMEBUFFER_WIDTH, 
        FRAMEBUFFER_HEIGHT
    );

    // Update the texture with the pixel data from the framebuffer
    SDL_UpdateTexture(
        texture, 
        NULL, 
        framebuffer, 
        FRAMEBUFFER_WIDTH * sizeof(Color)
    );

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}

void createSquare(int x, int y) {
    for (int i = x; i < x + 2; i++) {
        for (int j = y; j < y + 2; j++) {
            point(i, j);
        }
    }
}

void createLoaf(int x, int y) {
    point(x + 1, y);
    point(x + 2, y + 1);
    point(x, y + 2);
    point(x + 1, y + 2);
    point(x + 3, y + 2);
    point(x + 2, y + 3);
    point(x + 3, y + 3);
}

void createSliders(int x, int y) {
    point(x, y + 2);
    point(x + 1, y + 2);
    point(x + 2, y + 2);
    point(x + 3, y + 1);
    point(x + 3, y + 2);
    point(x + 3, y + 3);
}

void createBoat(int x, int y) {
    point(x + 1, y);
    point(x + 2, y + 1);
    point(x, y + 1);
    point(x + 1, y + 2);
    point(x + 2, y + 2);
}

void createBeacon(int x, int y) {
    point(x, y);
    point(x + 1, y);
    point(x, y + 1);
    point(x + 3, y + 4);
    point(x + 4, y + 4);
    point(x + 3, y + 5);
    point(x + 4, y + 5);
}

void createToad(int x, int y) {
    point(x + 1, y);
    point(x + 2, y);
    point(x + 3, y + 1);
    point(x, y + 1);
    point(x + 1, y + 1);
    point(x + 2, y + 1);
}

void setPattern(SDL_Renderer* renderer) {
    
    // Create a random number of squares and loafs
    int numSquares = rand() % 100 + 1;
    int numLoafs = rand() % 100 + 1;
    int numSliders = rand() % 100 + 1;
    int numBoats = rand() % 100 + 1;
    int numBeacons = rand() % 100 + 1;
    int numToads = rand() % 100 + 1;

    // Create random squares
    for (int i = 0; i < numSquares; i++) {
        // Generate random position and color
        int x = rand() % (FRAMEBUFFER_WIDTH - 2);
        int y = rand() % (FRAMEBUFFER_HEIGHT - 2);

        // Create square
        createSquare(x, y);
    }

    // Create random loafs
    for (int i = 0; i < numLoafs; i++) {
        // Generate random position and color
        int x = rand() % (FRAMEBUFFER_WIDTH - 4);
        int y = rand() % (FRAMEBUFFER_HEIGHT - 4);

        // Create loaf
        createLoaf(x, y);
    }

    // Create random sliders
    for (int i = 0; i < numSliders; i++) {
        // Generate random position and color
        int x = rand() % (FRAMEBUFFER_WIDTH - 4);
        int y = rand() % (FRAMEBUFFER_HEIGHT - 4);

        // Create sliders
        createSliders(x, y);
    }

    // Create random boats
    for (int i = 0; i < numBoats; i++) {
        // Generate random position and color
        int x = rand() % (FRAMEBUFFER_WIDTH - 4);
        int y = rand() % (FRAMEBUFFER_HEIGHT - 4);

        // Create loaf
        createBoat(x, y);
    }

    // Create random beacons
    for (int i = 0; i < numBeacons; i++) {
        // Generate random position and color
        int x = rand() % (FRAMEBUFFER_WIDTH - 4);
        int y = rand() % (FRAMEBUFFER_HEIGHT - 4);

        // Create beacons
        createBeacon(x, y);
    }

    // Create random toads
    for (int i = 0; i < numToads; i++) {
        // Generate random position and color
        int x = rand() % (FRAMEBUFFER_WIDTH - 4);
        int y = rand() % (FRAMEBUFFER_HEIGHT - 4);

        // Create toads
        createToad(x, y);
    }

    // Render the framebuffer to the screen
    renderBuffer(renderer);

    // Present the frame buffer to the screen
    SDL_RenderPresent(renderer);
}

// Function to update the game state based on Conway's rules
void updateGame() {
    for (int x = 0; x < FRAMEBUFFER_WIDTH; x++) {
        for (int y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
            int liveNeighbors = 0;

            // Count live neighbors
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue; // Skip the current cell
                    int nx = x + dx;
                    int ny = y + dy;

                    // Wrap around the edges
                    if (nx < 0) nx = FRAMEBUFFER_WIDTH - 1;
                    if (nx >= FRAMEBUFFER_WIDTH) nx = 0;
                    if (ny < 0) ny = FRAMEBUFFER_HEIGHT - 1;
                    if (ny >= FRAMEBUFFER_HEIGHT) ny = 0;

                    if (framebuffer[ny * FRAMEBUFFER_WIDTH + nx].b == 255) {
                        liveNeighbors++;
                    }
                }
            }

            // Apply Conway's rules
            if (framebuffer[y * FRAMEBUFFER_WIDTH + x].b == 255) {
                // Cell is alive
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    nextFramebuffer[y * FRAMEBUFFER_WIDTH + x].b = 0; // Cell dies
                } else {
                    nextFramebuffer[y * FRAMEBUFFER_WIDTH + x].b = 255; // Cell survives
                }
            } else {
                // Cell is dead
                if (liveNeighbors == 3) {
                    nextFramebuffer[y * FRAMEBUFFER_WIDTH + x].b = 255; // Cell becomes alive
                } else {
                    nextFramebuffer[y * FRAMEBUFFER_WIDTH + x].b = 0; // Cell remains dead
                }
            }
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Game of Life (Conway Algorithm)", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    clear();

    // Set the initial pattern
    setPattern(renderer);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        updateGame();

        // Copy the contents of nextFramebuffer to framebuffer
        memcpy(framebuffer, nextFramebuffer, sizeof(framebuffer));

        // Call our render function
        renderBuffer(renderer);

        // Present the frame buffer to the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}