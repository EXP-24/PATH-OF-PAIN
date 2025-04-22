#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "graphics.h"
#include "sprites.h"
#include "defs.h"
#include "game.h"
#include "map.h"

using namespace std;
int main(int argc, char* args[]) {

    Graphics graphics;
    graphics.init();
    Mix_Music *gMusic = graphics.loadMusic("include/m&s/White Palace.mp3");
    graphics.play(gMusic);
    Mix_VolumeMusic(50);

    Map mapGame;
    mapGame.init(graphics);

    Character player;
    player.init(graphics);

    int map[MAP_HEIGHT][MAP_WIDTH];
    mapGame.loadMap("include/map.txt", map);
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else{
                player.handleEvent(graphics, e);
            }
        }
        player.move(graphics, map);
        player.update();
        mapGame.updateCamera(player.x, player.y);

        graphics.prepareScene();
        mapGame.render(graphics, map);
        player.render(graphics, mapGame.camera.x, mapGame.camera.y);

        graphics.presentScene();
        SDL_Delay(30);
    }
    if (gMusic != nullptr) Mix_FreeMusic(gMusic);

    player.close();
    mapGame.close();
    graphics.quit();
    return 0;
}
