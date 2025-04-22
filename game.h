#ifndef _GAME__H
#define _Game__H

#include <SDL.h>
#include <SDL_image.h>
#include "map.h"
#include "defs.h"
#include "SDL_mixer.h"
#include "sprites.h"
#include "graphics.h"
#include <vector>


enum State { IDLE, RUN, JUMP, FALL};

struct Character {
    int velX = 0, velY = 0;
    SDL_Texture* Endpic;
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
        Endpic = graphics.loadTexture("include/texture/Thumb.png");
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
        //Neu game ket thuc
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
        if (map[tileRow][tileCol] == 18 || map[tileRow][tileCol] == 13 || map[tileRow][tileCol] == 22 || map[tileRow][tileCol] == 10 || map[tileRow][tileCol] == 19){
            x-=velX;
        }
        //Va chạm với mặt đất
        if (map[tileRow][tileCol] == 1 || map[tileRow][tileCol] == 2 || map[tileRow][tileCol] == 3 || map[tileRow][tileCol] == 4 || map[tileRow][tileCol] == 9){
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
        else if (velY > 0) {
            state = FALL;
        }
        //Rơi khỏi map quay về vị trí ban đầu
        if (y + PLAYER_HEIGHT >= MAP_HEIGHT*32){
            graphics.prepareScene();
            SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
            graphics.presentScene();
            SDL_Delay(1000);
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
        if (x >= ENDX && y >= ENDY) {
            graphics.renderTexture(Endpic,0,0);
            Mix_FreeChunk(jumpSound);
            End=true;
        }
    }
    void close(){
        if (idleTexture != nullptr){
            SDL_DestroyTexture(idleTexture);
            idleTexture = nullptr;
        }
        if (runTexture != nullptr){
            SDL_DestroyTexture(runTexture);
            runTexture = nullptr;
        }
        if (jumpTexture != nullptr){
            SDL_DestroyTexture(jumpTexture);
            jumpTexture = nullptr;
        }
        if (fallTexture != nullptr){
            SDL_DestroyTexture(fallTexture);
            fallTexture = nullptr;
        }
        if (Endpic != nullptr){
            SDL_DestroyTexture(Endpic);
            Endpic = nullptr;
        }
        if (runSound != nullptr) Mix_FreeChunk(runSound);
        if (jumpSound != nullptr) Mix_FreeChunk(jumpSound);
    }

};



#endif // _GAME__H
