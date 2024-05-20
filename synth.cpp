
#include "synth.h"

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

LTexture::LTexture()
{
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    // Deallocate
    free();  // Easy peasy
}

bool LTexture::loadFromFile(std::string path)
{
    // Gets rid of preexisting texture
    free();

    // Final texture to render
    SDL_Texture* newTexture = NULL;

    // Loads image
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Color key
        SDL_SetColorKey(
                loadedSurface,
                SDL_TRUE,
                SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF)
        );

        // Texture
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // Get dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;

    return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
    if (mTexture != NULL)
    {
        // SDL_render.h
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    // Set blending function
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {
        x,
        y,
        mWidth,
        mHeight
    };

    // setting clip dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Renders to the screen
    SDL_RenderCopyEx(
        gRenderer,
        mTexture,
        clip,
        &renderQuad,
        angle,
        center,
        flip
    );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
    {
        printf("Could not initialize SDL! SDL error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        gWindow = SDL_CreateWindow(
            "SOFT SYNTH",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) &imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image error: %s\n", IMG_GetError());
                    success = false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    // success flag
    bool success = true;

    // Load prompt texture

    // Load music
    gMusic = Mix_LoadMUS("../assets/beat.wav");
    if (gMusic == NULL)
    {
        printf("Failed to load music! SDL_mixer error: %s\n", Mix_GetError());
        success = false;
    }

    // Load sound effects
    gScratch = Mix_LoadWAV("../assets/scratch.wav");
    if (gScratch == NULL)
    {
        printf("Failed to load 'scratch' sound effect! SDL_mixer error: %s\n", Mix_GetError());
        success = false;
    }

    gScratch = Mix_LoadWAV("../assets/high.wav");
    if (gScratch == NULL)
    {
        printf("Failed to load 'high' sound effect! SDL_mixer error: %s\n", Mix_GetError());
        success = false;
    }

    gScratch = Mix_LoadWAV("../assets/medium.wav");
    if (gScratch == NULL)
    {
        printf("Failed to load 'medium' sound effect! SDL_mixer error: %s\n", Mix_GetError());
        success = false;
    }

    gScratch = Mix_LoadWAV("../assets/low.wav");
    if (gScratch == NULL)
    {
        printf("Failed to load 'low' sound effect! SDL_mixer error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}
