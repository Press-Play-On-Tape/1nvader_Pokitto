#include "Invader.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title_Init() {

    gameState = GameState::Title;
    titleScreenVars.reset(this->cookie->gameRotation);

    #ifdef SOUNDS
        sound.tones(Sounds::Theme);
    #endif

    titleScreenVars.levels = 0;

    for (uint8_t i = 0; i < 3; i++) {
        if (this->cookie->getLevel(i) == 1) titleScreenVars.levels++;
    }

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title() {

    renderScenery(GameMode::Single);
    renderHighScore(this->cookie->gameMode, false);
    
    if (PC::buttons.pressed(BTN_B)) {

        this->cookie->gameRotation = this->cookie->gameRotation == GameRotation::Landscape ? GameRotation::Portrait : GameRotation::Landscape;
        gameState = GameState::Title_Init;
        this->cookie->saveRotation(this->cookie->gameRotation);

    }

    uint8_t frame = Constants::Mothership_Frames[(PC::frameCount % 36) / 6];

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:
           
            PD::drawBitmap(titleScreenVars.counter, 12, Images::Portrait::MOTHERSHIP_SIZE_PORTRAIT::Mothership_Title[frame]);

            switch (titleScreenVars.counter) {

                case 89:
                    renderPlayerSelection(true);
                    renderInvaderSign();
                    break;

                case 90 ... 97:
                    renderPlayerSelection(true);
                    renderInvaderSign();
                    titleScreenVars.counter++;
                    break;

                case 98 ... 105:
                    renderPlayerSelection(false);
                    renderInvaderSign();
                    titleScreenVars.counter++;
                    break;

                case 106 ... 128:
                    renderPlayerSelection(false);
                    titleScreenVars.counter++;
                    break;

                case 129:

                    switch (this->cookie->gameMode) {

                        case GameMode::Single ... GameMode::Double:
                            gameState = GameState::Game_Init;
                            break;

                        case GameMode::TugOfWar:
                            gameState = GameState::TugOfWar_Init;
                            break;

                    }

                    break;
                    
            }

            if (PC::buttons.pressed(BTN_RIGHT) && this->cookie->gameMode != GameMode::Single) { 

                this->cookie->gameMode--;
            
            }

            if (PC::buttons.pressed(BTN_LEFT) && static_cast<uint8_t>(this->cookie->gameMode) < titleScreenVars.levels) { 

                this->cookie->gameMode++;

            }

            if (PC::buttons.pressed(BTN_A) && titleScreenVars.counter == 89) { 

                titleScreenVars.counter = 90;

            }

            break;

        case GameRotation::Landscape:
           
            PD::drawBitmap(14, titleScreenVars.counter, Images::Landscape::MOTHERSHIP_SIZE_PORTRAIT::Mothership_Title[frame]);

            switch (titleScreenVars.counter) {

                case 0:
                    renderPlayerSelection(true);
                    renderInvaderSign();
                    break;

                case -8 ... -1:
                    renderPlayerSelection(true);
                    renderInvaderSign();
                    titleScreenVars.counter--;
                    break;

                case -18 ... -9:
                    renderPlayerSelection(false);
                    renderInvaderSign();
                    titleScreenVars.counter--;
                    break;

                case -38 ... -19:
                    renderPlayerSelection(false);
                    titleScreenVars.counter--;
                    break;

                case -39:

                    switch (this->cookie->gameMode) {

                        case GameMode::Single ... GameMode::Double:
                            gameState = GameState::Game_Init;
                            break;

                        case GameMode::TugOfWar:

                            if (this->cookie->gameRotation == GameRotation::Landscape) {
                                this->cookie->gameRotation = this->cookie->gameRotation == GameRotation::Landscape ? GameRotation::Portrait : GameRotation::Landscape;
                                gameState = GameState::Title_Init;
                                this->cookie->saveRotation(this->cookie->gameRotation);
                            }
                            
                            gameState = GameState::TugOfWar_Init;
                            break;

                    }

                    break;
                    
            }

            if (PC::buttons.pressed(BTN_UP) && this->cookie->gameMode != GameMode::Single) { 

                this->cookie->gameMode--;

            }

            if (PC::buttons.pressed(BTN_DOWN) && static_cast<uint8_t>(this->cookie->gameMode) < titleScreenVars.levels) { 

                this->cookie->gameMode++;

            }

            if (PC::buttons.pressed(BTN_A) && titleScreenVars.counter == 0) { 

                titleScreenVars.counter = -1;

            }

            break;

    }

}

void Game::renderPlayerSelection(bool renderPlayerSelection) {

    uint8_t frame = Constants::Arrow_Frames[(PC::frameCount % 48) / 12];

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            PD::drawBitmap(31, 20, Images::Portrait::Rotate);

            if (!renderPlayerSelection) return;

            PD::drawBitmap(62 - (static_cast<uint8_t>(this->cookie->gameMode) * 8), 5, Images::Portrait::DownArrow[frame]);
            PD::drawBitmap(62, 13, Images::Portrait::SurvivalMode);
            PD::drawBitmap(54, 13, Images::Portrait::VSMode);
            PD::drawBitmap(46, 13, Images::Portrait::TugOfWarMode);

            if (this->cookie->getLevel(0) == 0) PD::drawBitmap(54, 5, Images::Portrait::Lock);
            if (this->cookie->getLevel(1) == 0) PD::drawBitmap(46, 5, Images::Portrait::Lock);

            break;

        case GameRotation::Landscape:

            PD::drawBitmap(85, 53, Images::Landscape::Rotate);

            if (!renderPlayerSelection) return;

            PD::drawBitmap(71, 12 + (static_cast<uint8_t>(this->cookie->gameMode) * 9), Images::Landscape::LeftArrow[frame]);
            PD::drawBitmap(79, 12, Images::Landscape::SurvivalMode);
            PD::drawBitmap(79, 21, Images::Landscape::VSMode);
            PD::drawBitmap(79, 30, Images::Landscape::TugOfWarMode);

            if (this->cookie->getLevel(0) == 0) PD::drawBitmap(71, 21, Images::Landscape::Lock);
            if (this->cookie->getLevel(1) == 0) PD::drawBitmap(71, 30, Images::Landscape::Lock);

            break;
            
    }

}
