
#include "synth.h"


// Scene texture
LTexture gPromptTexture;

// Load music
Mix_Music* gMusic = NULL;
Mix_Music * dMusic = NULL;

// Sound effects to load
Mix_Chunk* gScratch = NULL;
Mix_Chunk* gHigh = NULL;
Mix_Chunk* gMedium = NULL;
Mix_Chunk* gLow = NULL;

bool loadMedia()
{
    // success flag
    bool success = true;

    // Load prompt texture
    if (!gPromptTexture.loadFromFile("../assets/prompt.png"))
    {
        printf("Failed to load prompt texture!\n");
        success = false;
    }

    // Load music
    gMusic = Mix_LoadMUS("../assets/beat.wav");
    if (gMusic == NULL)
    {
        printf("Failed to load music! SDL_mixer error: %s\n", Mix_GetError());
        success = false;
    }

    dMusic = Mix_LoadMUS("../assets/Demo_Beat_007.mp3");
    if (dMusic == NULL)
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

    gHigh = Mix_LoadWAV("../assets/high.wav");
    if (gScratch == NULL)
    {
        printf("Failed to load 'high' sound effect! SDL_mixer error: %s\n", Mix_GetError());
        success = false;
    }

    gMedium = Mix_LoadWAV("../assets/medium.wav");
    if (gScratch == NULL)
    {
        printf("Failed to load 'medium' sound effect! SDL_mixer error: %s\n", Mix_GetError());
        success = false;
    }

    gLow = Mix_LoadWAV("../assets/low.wav");
    if (gScratch == NULL)
    {
        printf("Failed to load 'low' sound effect! SDL_mixer error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}

void close()
{
    // Free loaded image
    gPromptTexture.free();

    // Free sound effects
    Mix_FreeChunk(gScratch);
    Mix_FreeChunk(gHigh);
    Mix_FreeChunk(gMedium);
    Mix_FreeChunk(gLow);
    gScratch = NULL;
    gHigh = NULL;
    gLow = NULL;

    // Free music
    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    closeWindow();

    // Quit SDL Subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}


int main( int argc, char* args[] )
{
    // Init function starts up SDL, creates window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // GAME LOOP ////////////////////////

            // Loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    // User quits
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                            case SDLK_1:
                                Mix_PlayChannel(-1, gHigh, 0);
                                break;
                            case SDLK_2:
                                Mix_PlayChannel(-1, gMedium, 0);
                                break;
                            case SDLK_3:
                                Mix_PlayChannel(-1, gLow, 0);
                                break;
                            case SDLK_4:
                                Mix_PlayChannel(-1, gScratch, 0);
                            case SDLK_9:
                                if (Mix_PlayingMusic() == 0)
                                {
                                    Mix_PlayMusic(gMusic, -1);
                                }
                                else
                                {
                                    if (Mix_PausedMusic() == 1)
                                    {
                                        Mix_ResumeMusic();
                                    }
                                    else
                                    {
                                        Mix_PauseMusic();
                                    }
                                }
                                break;
                            case SDLK_g:
                                if (Mix_PlayingMusic() == 0)
                                {
                                    Mix_PlayMusic(dMusic, -1);
                                }
                                else
                                {
                                    if (Mix_PausedMusic() == 1)
                                    {
                                        Mix_ResumeMusic();
                                    }
                                    else
                                    {
                                        Mix_PauseMusic();
                                    }
                                }
                                break;
                            case SDLK_0:
                                Mix_HaltMusic();
                                break;
                        }
                    }
                }
                clearScreen();

                gPromptTexture.render(0, 0);

                updateScreen();
            }
        }
    }

    close();


    return 0;
}
