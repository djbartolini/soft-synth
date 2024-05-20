
#include "synth.h"


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


                }
            }
        }
    }


    return 0;
}
