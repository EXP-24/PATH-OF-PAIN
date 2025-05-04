#ifndef _MAP__H
#define _MAP__H

#include <fstream>
#include "graphics.h"
#include <SDL_image.h>
#include "defs.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
struct Map {
    SDL_Texture* tile1;
    SDL_Texture* tile2;
    SDL_Texture* tile3;
    SDL_Texture* tile4;
    SDL_Texture* tile9;
    SDL_Texture* tile10;
    SDL_Texture* tile11;
    SDL_Texture* tile5;
    SDL_Texture* tile13;
    SDL_Texture* tile27;
    SDL_Texture* tile16;
    SDL_Texture* tile18;
    SDL_Texture* tile19;
    SDL_Texture* tile20;
    SDL_Texture* tile21;
    SDL_Texture* tile22;
    SDL_Texture* tile28;
    SDL_Texture* tile29;
    SDL_Texture* tile37;
    SDL_Texture* tile38;
    SDL_Texture* tile43;
    SDL_Texture* tile44;
    SDL_Texture* background1;
    SDL_Texture* background2;
    SDL_Texture* background3;
    SDL_Texture* background4;
    SDL_Texture* background5;
    TTF_Font* guide;
    SDL_Color color;
    SDL_Texture* guide1;
    SDL_Texture* guide2;
    SDL_Texture* guide3;
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    void init(Graphics& graphics){
        tile1 = graphics.loadTexture("include/maps/Tile_01.png");
        tile2 = graphics.loadTexture("include/maps/Tile_02.png");
        tile3 = graphics.loadTexture("include/maps/Tile_03.png");
        tile4 = graphics.loadTexture("include/maps/Tile_04.png");
        tile5 = graphics.loadTexture("include/maps/Tile_05.png");
        tile9 = graphics.loadTexture("include/maps/Tile_09.png");
        tile10 = graphics.loadTexture("include/maps/Tile_10.png");
        tile11 = graphics.loadTexture("include/maps/Tile_11.png");
        tile13 = graphics.loadTexture("include/maps/Tile_13.png");
        tile16 = graphics.loadTexture("include/maps/Tile_16.png");
        tile18 = graphics.loadTexture("include/maps/Tile_18.png");
        tile19 = graphics.loadTexture("include/maps/Tile_19.png");
        tile20 = graphics.loadTexture("include/maps/Tile_20.png");
        tile21 = graphics.loadTexture("include/maps/Tile_21.png");
        tile22 = graphics.loadTexture("include/maps/Tile_22.png");
        tile27 = graphics.loadTexture("include/maps/Tile_27.png");
        tile28 = graphics.loadTexture("include/maps/Tile_28.png");
        tile29 = graphics.loadTexture("include/maps/Tile_29.png");
        tile37 = graphics.loadTexture("include/maps/Tile_37.png");
        tile38 = graphics.loadTexture("include/maps/Tile_38.png");
        tile43 = graphics.loadTexture("include/maps/Tile_43.png");
        tile44 = graphics.loadTexture("include/maps/Tile_44.png");

        background1 = graphics.loadTexture("include/maps/1.png");
        background2 = graphics.loadTexture("include/maps/2.png");
        background3 = graphics.loadTexture("include/maps/3.png");
        background4 = graphics.loadTexture("include/maps/4.png");
        background5 = graphics.loadTexture("include/maps/5.png");

        guide = graphics.loadFont("include/PixelPurl.ttf",45);
        color = {240, 240, 240, 255};
        guide1 = graphics.renderText("Press A and D to walk", guide, color);
        guide2 = graphics.renderText("Press W to jump", guide, color);
        guide3 = graphics.renderText("Press ESC to pause game", guide, color);
    }

    void loadMap(const char* path, int arr[MAP_HEIGHT][MAP_WIDTH]){
        std::ifstream file(path);
        if (file.is_open()){
            for (int row=0; row < MAP_HEIGHT; row++){
                for (int col=0; col < MAP_WIDTH;col++){
                    file >> arr[row][col];
                }
            }
            file.close();
        }
        else {
            std::cerr << "ERROR!!!" << std::endl;
        }
    }

     void updateCamera(int playerX, int playerY) {

        camera.x = (playerX + PLAYER_WIDTH/2) - SCREEN_WIDTH / 2;
        camera.y = (playerY + PLAYER_HEIGHT/2) - SCREEN_HEIGHT / 2;

        if (camera.x < 0) camera.x = 0;
        if (camera.y < 0) camera.y = 0;
        if (camera.x > MAP_WIDTH * 32 - camera.w) camera.x = MAP_WIDTH * 32 - camera.w;
        if (camera.y > MAP_HEIGHT * 32 - camera.h) camera.y = MAP_HEIGHT * 32 - camera.h;
    }

    void render(Graphics& graphics, int arr[MAP_HEIGHT][MAP_WIDTH]) {
        graphics.renderTexture(background1, 0, 0);
        graphics.renderTexture(background2, 0, 0);
        graphics.renderTexture(background3, 0, 0);
        graphics.renderTexture(background4, 0, 0);
        graphics.renderTexture(background5, 0, 0);

        int type;
        for (int row = 0; row < MAP_HEIGHT; row++) {
            for (int col = 0; col < MAP_WIDTH; col++) {
                type = arr[row][col];
                int tileX = col * 32 - camera.x;
                int tileY = row * 32 - camera.y;
                if (tileX >= -32 && tileX < SCREEN_WIDTH && tileY >= -32 && tileY < SCREEN_HEIGHT) {
                    switch (type) {
                        case 1:
                            graphics.renderTexture(tile1, tileX, tileY);
                            break;
                        case 2:
                            graphics.renderTexture(tile2, tileX, tileY);
                            break;
                        case 3:
                            graphics.renderTexture(tile3, tileX, tileY);
                            break;
                        case 4:
                            graphics.renderTexture(tile4, tileX, tileY);
                            break;
                        case 5:
                            graphics.renderTexture(tile5, tileX, tileY);
                            break;
                        case 9:
                            graphics.renderTexture(tile9, tileX, tileY);
                            break;
                        case 10:
                            graphics.renderTexture(tile10, tileX, tileY);
                            break;
                        case 11:
                            graphics.renderTexture(tile11, tileX, tileY);
                            break;
                        case 13:
                            graphics.renderTexture(tile13, tileX, tileY);
                            break;
                        case 16:
                            graphics.renderTexture(tile16, tileX, tileY);
                            break;
                        case 18:
                            graphics.renderTexture(tile18, tileX, tileY);
                            break;
                        case 19:
                            graphics.renderTexture(tile19, tileX, tileY);
                            break;
                        case 20:
                            graphics.renderTexture(tile20, tileX, tileY);
                            break;
                        case 21:
                            graphics.renderTexture(tile21, tileX, tileY);
                            break;
                        case 22:
                            graphics.renderTexture(tile22, tileX, tileY);
                            break;
                        case 27:
                            graphics.renderTexture(tile27, tileX, tileY);
                            break;
                        case 28:
                            graphics.renderTexture(tile28, tileX, tileY);
                            break;
                        case 29:
                            graphics.renderTexture(tile29, tileX, tileY);
                            break;
                        case 37:
                            graphics.renderTexture(tile37, tileX, tileY);
                            break;
                        case 38:
                            graphics.renderTexture(tile38, tileX, tileY);
                            break;
                        case 43:
                            graphics.renderTexture(tile43, tileX, tileY);
                            break;
                        case 44:
                            graphics.renderTexture(tile44, tileX, tileY);
                            break;
                    }

                }
            }
        }
        graphics.renderTexture(guide1, 40 - camera.x, 610 - camera.y);
        graphics.renderTexture(guide2, 200 - camera.x, 900 - camera.y);
        graphics.renderTexture(guide3, 120 - camera.x, 950 - camera.y);
    }

    void close(){
        std::vector<SDL_Texture*> tiles = {tile1, tile2, tile3, tile4, tile5, tile9, tile10, tile11, tile13, tile16, tile18, tile19, tile20,
        tile21, tile22, tile27, tile28, tile29, tile37, tile38, tile43, tile44, guide1, guide2, guide3};
        for (SDL_Texture* texture : tiles){
            if (texture != nullptr){
                SDL_DestroyTexture(texture);
                texture = nullptr;
            }
        }
        if (guide != nullptr){
            TTF_CloseFont(guide);
            guide = nullptr;
        }
    }
};

#endif // _MAP__H

