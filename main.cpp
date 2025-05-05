#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "sprites.h"
#include "defs.h"
#include "game.h"
#include "map.h"
#include "menu.h"

using namespace std;
int main(int argc, char* args[]) {

    Graphics graphics;
    graphics.init();

    bool running = true;
    while(running){
        mainMenu menu;
        menu.init(graphics);

        Mix_Music *titleSong = graphics.loadMusic("include/m&s/Title Theme.mp3");
        graphics.play(titleSong);
        Mix_VolumeMusic(100);

        int mouseX, mouseY;
        SDL_Event e;
        bool inMenu = true;
        while (inMenu) {
            SDL_GetMouseState(&mouseX, &mouseY);
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT ){
                    running = false;
                    inMenu = false;
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (menu.playClicked(mouseX, mouseY)){
                        inMenu = false;
                    }
                    if (menu.quitClicked(mouseX, mouseY)){
                        running = false;
                        inMenu = false;
                    }
                }
            }
            graphics.prepareScene();
            menu.render(graphics, mouseX, mouseY);
            graphics.presentScene();
            SDL_Delay(30);
        }

        menu.close();
        if (titleSong != nullptr) Mix_FreeMusic(titleSong);

        if (!running) break;

        Map mapGame;
        mapGame.init(graphics);

        Character player;
        player.init(graphics);

        PauseMenu pMenu;
        pMenu.init(graphics);

        //Load map va nhac nen game
        int currentMap = 0;
        int maxMap = 1;
        int map[MAP_HEIGHT][MAP_WIDTH];
        mapGame.loadMap("include/map0.txt", map);

        Mix_Music *gMusic = graphics.loadMusic("include/m&s/City of Tears.mp3");
        graphics.play(gMusic);


        bool pause = false;
        bool quit = false;
        while (!quit) {
            SDL_GetMouseState(&mouseX, &mouseY);
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                    running = false;
                }

                else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                    pause = !pause;
                    if (!pause){
                        player.velX = 0;
                        player.velY = 0;
                    }
                }

                else if (e.type == SDL_MOUSEBUTTONDOWN){
                    if (pMenu.resumeClicked(mouseX, mouseY)){
                        pause = false;
                        player.velX = 0;
                        player.velY = 0;
                    }
                    else if (pMenu.backClicked(mouseX, mouseY)){
                        quit = true;
                        inMenu = true;

                    }
                }

                if (!pause){
                    player.handleEvent(graphics, e);
                }
            }

            if (!pause){
                player.move(graphics, map);

                if (player.x >= ENDX && player.y >= ENDY){
                    currentMap++;
                    if (currentMap <= maxMap){
                        char mapFile[64];
                        sprintf(mapFile, "include/map%d.txt", currentMap);
                        mapGame.loadMap(mapFile, map);
                        mapGame.clearGuides();
                        player.x = STARTX;
                        player.y = STARTY;
                    }
                }

                player.update();
                mapGame.updateCamera(player.x, player.y);
            }

            graphics.prepareScene();
            mapGame.render(graphics, map);
            player.render(graphics, mapGame.camera.x, mapGame.camera.y);
            if (pause){
                pMenu.render(graphics, mouseX, mouseY);
            }
            graphics.presentScene();
            SDL_Delay(30);
        }

        if (gMusic != nullptr) Mix_FreeMusic(gMusic);
        pMenu.close();
        player.close();
        mapGame.close();
    }

    graphics.quit();
    return 0;
}
