//
// Created by Daniel Bartolini on 5/20/24.
//

#ifndef SOFT_SYNTH_SYNTH_H
#define SOFT_SYNTH_SYNTH_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LTexture
{
public:
    // Constructor
    LTexture();

    // Destructor
    ~LTexture();

    // Load image at specified path
    bool loadFromFile(std::string path);

    #if defined (SDL_TTF_MAJOR_VERSION)
        // Apparently we load a font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
    #endif

    // Deallocate texture
    void free();

    // Set color modulations
    void setColor( Uint8 red, Uint8 green, Uint8 blue);

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulations
    void setAlpha(Uint8 alpha);

    // Render texture at given point x,y
    void render(
            int x,
            int y,
            SDL_Rect* clip = NULL,
            double angle = 0.0,
            SDL_Point* center = NULL,
            SDL_RendererFlip  flip = SDL_FLIP_NONE
    );

    // getter for image dimensions
    int getWidth();
    int getHeight();

private:
    // The actual hardware texture
    SDL_Texture* mTexture;

    // Image dimesions
    int mWidth;
    int mHeight;
};

// Start up SDL
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Window
SDL_Window* gWindow = NULL;

// Window renderer
SDL_Renderer* gRenderer = NULL;

// Scene texture
LTexture gPromptTexture;

// Load music
Mix_Music* gMusic = NULL;

// Sound effects to load
Mix_Chunk* gScratch = NULL;
Mix_Chunk* gHigh = NULL;
Mix_Chunk* gMedium = NULL;
Mix_Chunk* gLow = NULL;


#endif //SOFT_SYNTH_SYNTH_H
