#ifndef _GAME__H
#define _Game__H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "map.h"
#include "defs.h"
#include "SDL_mixer.h"
#include "sprites.h"
#include "graphics.h"

enum State { IDLE, RUN, JUMP, FALL};

struct Character {

    int velX = 0, velY = 0;
    SDL_Texture* endPic;
    SDL_Texture* endTitle;
    Sprite idleSprite;
    Sprite runSprite;
    Sprite jumpSprite;
    Sprite fallSprite;
    SDL_Texture *idleTexture;
    SDL_Texture *runTexture;
    SDL_Texture *jumpTexture;
    SDL_Texture *fallTexture;
    Mix_Chunk *runSound;
    Mix_Chunk *jumpSound;
    State state;
    int x = STARTX, y = STARTY;
    bool flip = false;
    bool End = false;
    bool check;

    void init(Graphics& graphics) {
        idleTexture = graphics.loadTexture(IDLE_SPRITE_FILE);
        idleSprite.init(idleTexture, IDLE_FRAMES, IDLE_CLIPS);

        runTexture = graphics.loadTexture(RUN_SPRITE_FILE);
        runSprite.init(runTexture, RUN_FRAMES, RUN_CLIPS);

        jumpTexture = graphics.loadTexture(JUMP_SPRITE_FILE);
        jumpSprite.init(jumpTexture, JUMP_FRAMES, JUMP_CLIPS);

        fallTexture = graphics.loadTexture(FALL_SPRITE_FILE);
        fallSprite.init(fallTexture, FALL_FRAMES, FALL_CLIPS);

        runSound = graphics.loadSound("include/m&s/run.mp3");
        jumpSound = graphics.loadSound("include/m&s/jump.wav");

        endTitle = graphics.loadTexture("include/texture/end title.png");
        endPic = graphics.loadTexture("include/texture/Dream no more.png");
    }

    void handleEvent(Graphics &graphics, SDL_Event& e) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
                case SDLK_a:
                    velX -= PLAYER_SPEED;
                    flip = true;
                    break;
                case SDLK_d:
                    velX += PLAYER_SPEED;
                    flip = false;
                    break;
                case SDLK_w:
                    if (state != JUMP && state != FALL) {
                        velY = -JUMP_STRENGTH;
                        graphics.play(jumpSound);
                        Mix_VolumeChunk(jumpSound, 100);
                        state = JUMP;
                    }
                    break;
            }
        }
        else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
                case SDLK_a:
                    velX += PLAYER_SPEED;
                    break;
                case SDLK_d:
                    velX -= PLAYER_SPEED;
                    break;
            }
        }
    }

    void move(Graphics& graphics, int map[MAP_HEIGHT][MAP_WIDTH]) {
        //Nếu game kết thúc
        if (End){
            velX=0;
            velY=0;
        }

        x += velX;
        y += velY;
        //Giới hạn
        if (x <= -64 || x + PLAYER_WIDTH/2 >= MAP_WIDTH * 32){
            x -= velX;
        }
        if (velY < 10) velY += GRAVITY;

        int bottomY = y + PLAYER_HEIGHT;
        int centralX = x + PLAYER_WIDTH/2;
        int tileCol = centralX/32;
        int tileRow = bottomY/32;

        //Va chạm với tường
        if (map[tileRow][tileCol] == 18 || map[tileRow][tileCol] == 13 || map[tileRow][tileCol] == 22 || map[tileRow][tileCol] == 10
            || map[tileRow][tileCol] == 19 || map[tileRow][tileCol] == 37 || map[tileRow][tileCol] == 38){
            x-=velX;
        }

        //Va chạm với mặt đất
        if (map[tileRow][tileCol] == 1 || map[tileRow][tileCol] == 2 || map[tileRow][tileCol] == 3 || map[tileRow][tileCol] == 4
            || map[tileRow][tileCol] == 9 || map[tileRow][tileCol] == 37 || map[tileRow][tileCol] == 38){
            y = (tileRow)*32 - PLAYER_HEIGHT;
            velY = 0;
            if (velX == 0) {
                state = IDLE;
            }
            else {
               state = RUN;
               if(!Mix_Playing(-1)){
                    graphics.play(runSound);
               }
            }
        }

        //Va chạm với trần
        int topX = x + PLAYER_WIDTH/2;
        int topY = y + PLAYER_HEIGHT/2;
        int tilecolTop = topX/32;
        int tilerowTop = topY/32;

        if (map[tilerowTop][tilecolTop] == 20 || map[tilerowTop][tilecolTop] == 22 || map[tilerowTop][tilecolTop] == 19){
            y = (tilerowTop)*32;
            velY = 0;
        }

        else if (velY > 0) {
            state = FALL;
        }

        //Rơi khỏi map quay về vị trí ban đầu
        if (y + PLAYER_HEIGHT >= MAP_HEIGHT*32){
            graphics.prepareScene();
            SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
            graphics.presentScene();
            SDL_Delay(500);
            x = STARTX;
            y = STARTY;
        }
    }

    void update() {
        switch (state) {
            case RUN:
                runSprite.tick();
                break;
            case IDLE:
                idleSprite.tick();
                break;
            case JUMP:
                jumpSprite.tick();
                break;
            case FALL:
                fallSprite.tick();
                break;
        }
    }

    void render(Graphics& graphics, int& camX, int& camY) {
        switch (state) {
            case RUN:
                graphics.render(x - camX, y - camY, runSprite, flip);
                break;
            case JUMP:
                graphics.render(x - camX, y - camY, jumpSprite, flip);
                break;
            case FALL:
                graphics.render(x - camX, y - camY, fallSprite, flip);
                break;
            case IDLE:
                graphics.render(x - camX, y - camY, idleSprite, flip);
                break;
        }
        //End Game
        if (x >= ENDX && y >= ENDY) {
            graphics.renderTexture(endPic,0,0);
            graphics.renderTexture(endTitle, 0, 0);
            Mix_FreeChunk(jumpSound);
            End=true;
        }
    }

    void close(){
        std::vector<SDL_Texture*> textures = {idleTexture, runTexture, fallTexture, jumpTexture, endPic, endTitle};
        for (SDL_Texture* texture : textures){
            if (texture != nullptr){
                SDL_DestroyTexture(texture);
                texture = nullptr;
            }
        }
        if (runSound != nullptr){
            Mix_FreeChunk(runSound);
            runSound = nullptr;
        }
        if (jumpSound != nullptr){
            Mix_FreeChunk(jumpSound);
            jumpSound = nullptr;
        }
    }

};

#endif // _GAME__H
