#ifndef _SPRITES__H
#define _SPRITES__H

const char* RUN_SPRITE_FILE = "include/texture/run.png";
const int RUN_CLIPS[][4]={
    {0,0,128,128},
    {128,0,128,128},
    {256,0,128,128},
};
const int RUN_FRAMES = sizeof(RUN_CLIPS)/sizeof(int)/4;

const char* FALL_SPRITE_FILE = "include/texture/fall.png";
const int FALL_CLIPS[][4]={
    {256,0,128,128},
};
const int FALL_FRAMES = sizeof(FALL_CLIPS)/sizeof(int)/4;


const char* IDLE_SPRITE_FILE = "include/texture/idle.png";
const int IDLE_CLIPS[][4]={
    {0,0,128,128},
};
const int IDLE_FRAMES = sizeof(IDLE_CLIPS)/sizeof(int)/4;

const char* JUMP_SPRITE_FILE = "include/texture/jump.png";
const int JUMP_CLIPS[][4]={
    {0,0,128,128},
    {128,0,128,128},
    {256,0,128,128},

    {0,128,128,128},
    {128,128,128,128},
    {256,128,128,128},

    {0,256,128,128},
    {128,256,128,128},
    {256,256,128,128},
};
const int JUMP_FRAMES = sizeof(JUMP_CLIPS)/sizeof(int)/4;

const char* FIGHT_SPRITE_FILE = "include/texture/f-melee.png";
const int FIGHT_CLIPS[][4]= {
    {0,0,128,128},
    {128,0,128,128},
};
const int FIGHT_FRAMES = sizeof(FIGHT_CLIPS)/sizeof(int)/4;
#endif
