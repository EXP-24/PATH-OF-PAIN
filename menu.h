#ifndef _MENU__H
#define _MENU__H

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "graphics.h"

struct mainMenu{
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* menuPic;
    SDL_Texture* title;
    SDL_Texture* playText;
    SDL_Texture* quitText;
    SDL_Rect playbutton;
    SDL_Rect quitbutton;
    ScrollingBackground background;

    void init(Graphics& graphics){

        title = graphics.loadTexture("include/texture/w-title.png");
        menuPic = graphics.loadTexture("include/texture/menu.png");
        background.setTexture(menuPic);
        font = graphics.loadFont("include/PixelPurl.ttf",50);
        color = {240, 240, 240, 255};
        playText = graphics.renderText("PLAY", font, color);
        quitText = graphics.renderText("QUIT", font, color);

        SDL_QueryTexture(playText, NULL, NULL, &playbutton.w, &playbutton.h);
        playbutton.x = 560;
        playbutton.y = 500;

        SDL_QueryTexture(quitText, NULL, NULL, &quitbutton.w, &quitbutton.h);
        quitbutton.x = 560;
        quitbutton.y = 550;
    }

    bool playClicked(int mouseX, int mouseY){
        if (mouseX >= playbutton.x && mouseX <= playbutton.x + playbutton.w && mouseY >= playbutton.y && mouseY <= playbutton.y + playbutton.h){
            return true;
        }
        return false;
    }

    bool quitClicked(int mouseX, int mouseY){
        if (mouseX >= quitbutton.x && mouseX <= quitbutton.x + quitbutton.w && mouseY >= quitbutton.y && mouseY <= quitbutton.y + quitbutton.h){
            return true;
        }
        return false;
    }

    void render(Graphics& graphics){
        background.scroll(1);
        graphics.renderBackground(background);
        graphics.renderTexture(title, 0, 0);
        graphics.renderTexture(playText, playbutton.x, playbutton.y);
        graphics.renderTexture(quitText, quitbutton.x, quitbutton.y);
    }

    void close(){
        if (menuPic != nullptr){
            SDL_DestroyTexture(menuPic);
            menuPic = nullptr;
        }
        if (title != nullptr){
            SDL_DestroyTexture(title);
            title = nullptr;
        }
        if (playText != nullptr){
            SDL_DestroyTexture(playText);
            playText = nullptr;
        }
        if (quitText != nullptr){
            SDL_DestroyTexture(quitText);
            quitText = nullptr;
        }
        if (font != nullptr){
            TTF_CloseFont(font);
            font = nullptr;
        }
    }
};

struct PauseMenu {
    TTF_Font* font;
    SDL_Texture* pausePic;
    SDL_Color colorPause;
    SDL_Rect pauseBackground;
    SDL_Texture* resumeText;
    SDL_Texture* backText;
    SDL_Rect resumeButton;
    SDL_Rect backButton;
    void init(Graphics& graphics){
        font = graphics.loadFont("include/PixelPurl.ttf",50);
        pausePic = graphics.loadTexture("include/texture/pause menu.png");
        pauseBackground = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        colorPause = {255, 255, 255, 255};
        resumeText = graphics.renderText("RESUME", font, colorPause);
        backText = graphics.renderText("QUIT TO MENU", font, colorPause);

        SDL_QueryTexture(resumeText, NULL, NULL, &resumeButton.w, &resumeButton.h);
        resumeButton.x = 540;
        resumeButton.y = 350;

        SDL_QueryTexture(backText, NULL, NULL, &backButton.w, &backButton.h);
        backButton.x = 484;
        backButton.y = 420;

    }
    bool resumeClicked(int mouseX, int mouseY){
        return (mouseX >= resumeButton.x && mouseX <= resumeButton.x + resumeButton.w
                && mouseY >= resumeButton.y && mouseY <= resumeButton.y + resumeButton.h);
    }

    bool backClicked(int mouseX, int mouseY){
        return (mouseX >= backButton.x && mouseX <= backButton.x + backButton.w
                && mouseY >= backButton.y && mouseY <= backButton.y + backButton.h);
    }
    void render(Graphics& graphics){
        SDL_SetRenderDrawBlendMode(graphics.renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 128);
        SDL_RenderFillRect(graphics.renderer, &pauseBackground);
        graphics.renderTexture(pausePic, 0, 0);
        graphics.renderTexture(resumeText, resumeButton.x, resumeButton.y);
        graphics.renderTexture(backText, backButton.x, backButton.y);

    }
    void close(){
        if (resumeText != nullptr){
            SDL_DestroyTexture(resumeText);
            resumeText = nullptr;
        }
        if (backText != nullptr){
            SDL_DestroyTexture(backText);
            backText = nullptr;
        }
        if (pausePic != nullptr){
            SDL_DestroyTexture(pausePic);
            pausePic = nullptr;
        }
        TTF_CloseFont(font);
    }
};
#endif // _MENU__H
