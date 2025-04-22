#ifndef MAP_H
#define MAP_H
#include <fstream>
#include "graphics.h"
#include <SDL_image.h>
#include "defs.h"
#include <vector>
#include <SDL.h>
#include <string>
struct Map {
    SDL_Texture* tile1;
    SDL_Texture* tile2;
    SDL_Texture* tile3;
    SDL_Texture* tile4;
    SDL_Texture* tile9;
    SDL_Texture* tile10;
    SDL_Texture* tile11;
    SDL_Texture* tile12;
    SDL_Texture* tile13;
    SDL_Texture* tile15;
    SDL_Texture* tile16;
    SDL_Texture* tile18;
    SDL_Texture* tile19;
    SDL_Texture* tile20;
    SDL_Texture* tile21;
    SDL_Texture* tile22;
    SDL_Texture* tile55;
    SDL_Texture* tile56;
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    void init(Graphics& graphics){
        tile1 = graphics.loadTexture("include/maps/Tile_01.png");
        tile2 = graphics.loadTexture("include/maps/Tile_02.png");
        tile3 = graphics.loadTexture("include/maps/Tile_03.png");
        tile4 = graphics.loadTexture("include/maps/Tile_04.png");
        tile9 = graphics.loadTexture("include/maps/Tile_09.png");
        tile10 = graphics.loadTexture("include/maps/Tile_10.png");
        tile11 = graphics.loadTexture("include/maps/Tile_11.png");
        tile12 = graphics.loadTexture("include/maps/Tile_12.png");
        tile13 = graphics.loadTexture("include/maps/Tile_13.png");
        tile15 = graphics.loadTexture("include/maps/Tile_15.png");
        tile16 = graphics.loadTexture("include/maps/Tile_16.png");
        tile18 = graphics.loadTexture("include/maps/Tile_18.png");
        tile19 = graphics.loadTexture("include/maps/Tile_19.png");
        tile20 = graphics.loadTexture("include/maps/Tile_20.png");
        tile21 = graphics.loadTexture("include/maps/Tile_21.png");
        tile22 = graphics.loadTexture("include/maps/Tile_22.png");
        tile55 = graphics.loadTexture("include/maps/Tile_55.png");
        tile56 = graphics.loadTexture("include/maps/Tile_56.png");

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
                        case 9:
                            graphics.renderTexture(tile9, tileX, tileY);
                            break;
                        case 10:
                            graphics.renderTexture(tile10, tileX, tileY);
                            break;
                        case 11:
                            graphics.renderTexture(tile11, tileX, tileY);
                            break;
                        case 12:
                            graphics.renderTexture(tile12, tileX, tileY);
                            break;
                        case 13:
                            graphics.renderTexture(tile13, tileX, tileY);
                            break;
                        case 15:
                            graphics.renderTexture(tile15, tileX, tileY);
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
                        case 55:
                            graphics.renderTexture(tile55, tileX, tileY);
                            break;
                        case 56:
                            graphics.renderTexture(tile56, tileX, tileY);
                            break;
                    }

                }
            }
        }
    }
    void close(){
        std::vector<SDL_Texture*> tiles = {tile1, tile2, tile3, tile4, tile9, tile10, tile11, tile12, tile13, tile15, tile16, tile18, tile19, tile20,
        tile21, tile22, tile55, tile56};
        for (SDL_Texture* texture : tiles){
            if (texture != nullptr){
                SDL_DestroyTexture(texture);
                texture = nullptr;
            }
        }
    }
};




#endif // MAP_H

