#include <stdio.h>
#include <SDL2/SDL.h>

#include "src/App/AppImpl.h"
#include "src/Chip8/CC8_Api.h"

#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH  32
#define PROGRAM_PATH  "/home/dev/repos/chip-8-binaries/1-chip8-logo.ch8"

CC8_Machine * context;

void OnStep(unsigned int* pixels)
{
    // int i = 0,j = 0;
    // for (i = 0; i < SCREEN_HEIGHT; i++) 
    // {

    //     for (j = 0; j < SCREEN_WIDTH; j++)
    //     {

    //         char value = context->VRAM[i*SCREEN_HEIGHT+j] > 0 ? 'X' :' ';
    //         printf("%c",value);
    //     }
    //     printf("\n");
    //     // printf("line draw at %i %i", i,j);
    // }
    // printf("\n");
        for(int i = 0; i < SCREEN_HEIGHT; ++i) {
        for(int j = 0; j < SCREEN_WIDTH; ++j) {
            if(context->VRAM[i * SCREEN_WIDTH + j] > 0) { 
                // printf("X");
                pixels[i+j*SCREEN_HEIGHT] = 0xFFFFFFFF;
            } else {
                // printf(" ");
                pixels[i+j*SCREEN_HEIGHT] = 0x00000000;
            }
        }
        // printf("\n");
    }
    // Iterate over the rows and columns of the 2D array
}

void OnInputAction(const char code)
{
    printf("Key pressed %c\n", code);
    //BOILER PLATE CODE
    // switch (code) 
    // {
    //     case SDLK_q:
    //         // Handle key A
    //         break;
    //     case SDLK_w:
    //         // Handle key B
    //         break;
    //     case SDLK_e:
    //         // Handle key C
    //         break;
    //     case SDLK_a:
    //         // Handle key P
    //         break;
    //     case SDLK_s:
    //         // Handle key Q
    //         break;
    //     case SDLK_d:
    //         // Handle key R
    //         break;
    // }
}

int main(int argc, char** argv)
{
    App * chip8App = &TinySDLApp;
    CC8_Core * emulator = &Chip8Emulator;
    context = calloc(1, sizeof(CC8_Machine)); //Initialize machine state

    chip8App->Init(SCREEN_HEIGHT, SCREEN_WIDTH);

    emulator->SetEmulationContext(context);
    emulator->LoadProgram(PROGRAM_PATH);

    while(chip8App->Step(OnStep, OnInputAction))
    {
        emulator->TickEmulation();
        SDL_Delay(200);
    }

    // emulator->QuitProgram();
    // chip8App->Exit(); 
}