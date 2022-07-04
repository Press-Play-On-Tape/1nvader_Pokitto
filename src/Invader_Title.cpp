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
        playTheme(Theme::Main);
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

    renderScenery(GameMode::Single, false);
    renderHighScore(this->cookie->gameMode, false);
    
    if (PC::buttons.pressed(BTN_B)) {

        this->cookie->gameRotation = this->cookie->gameRotation == GameRotation::Landscape ? GameRotation::Portrait : GameRotation::Landscape;
        gameState = GameState::Title_Init;
        this->cookie->saveRotation(this->cookie->gameRotation);

    }

    uint8_t frame = Constants::Mothership_Frames[(PC::frameCount % 36) / 6];

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:
           
            PD::drawBitmap(titleScreenVars.counter, 24, Images::Portrait::MOTHERSHIP_SIZE_PORTRAIT::Mothership_Title[frame]);

            switch (titleScreenVars.counter) {

                case 79:
                    renderPlayerSelection(true);
                    renderInvaderSign();
                    break;

                case 80 ... 87:
                    renderPlayerSelection(true);
                    renderInvaderSign();
                    titleScreenVars.counter++;
                    break;

                case 88 ... 95:
                    renderPlayerSelection(false);
                    renderInvaderSign();
                    titleScreenVars.counter++;
                    break;

                case 96 ... 110:
                    renderPlayerSelection(false);
                    titleScreenVars.counter++;
                    break;

                case 111:

                    this->cookie->saveCookie();
                    
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

            if (PC::buttons.pressed(BTN_A) && titleScreenVars.counter == 79) {

                titleScreenVars.counter = 80;

            }

            if (PC::buttons.pressed(BTN_UP)) { 

                this->cookie->sfx--;
                this->cookie->saveCookie();
                this->titleScreenVars.soundCounter = 64;

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    this->playTheme(Theme::Main);

                }

            }

            if (PC::buttons.pressed(BTN_DOWN)) { 

                this->cookie->sfx++;
                this->cookie->saveCookie();
                this->titleScreenVars.soundCounter = 64;

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    this->playTheme(Theme::Main);

                }

            }

            break;

        case GameRotation::Landscape:
           
            PD::drawBitmap(8, titleScreenVars.counter, Images::Landscape::MOTHERSHIP_SIZE_PORTRAIT::Mothership_Title[frame]);

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

            if (PC::buttons.pressed(BTN_LEFT)) { 

                this->cookie->sfx--;
                this->cookie->saveCookie();
                this->titleScreenVars.soundCounter = 64;

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    //this->playTheme();

                }

            }

            if (PC::buttons.pressed(BTN_RIGHT)) { 

                this->cookie->sfx++;
                this->cookie->saveCookie();
                this->titleScreenVars.soundCounter = 64;

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    //this->playTheme();

                }

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

            if (!renderPlayerSelection) return;

            PD::drawBitmap(54 - (static_cast<uint8_t>(this->cookie->gameMode) * 8), 17, Images::Portrait::DownArrow[frame]);
            PD::drawBitmap(54, 25, this->cookie->gameMode == GameMode::Single ? Images::Portrait::SurvivalMode : Images::Portrait::SurvivalMode_Grey);
            PD::drawBitmap(46, 25, this->cookie->gameMode == GameMode::Double ? Images::Portrait::VSMode : Images::Portrait::VSMode_Grey);
            PD::drawBitmap(38, 25, this->cookie->gameMode == GameMode::TugOfWar ? Images::Portrait::TugOfWarMode : Images::Portrait::TugOfWarMode_Grey);

            if (this->cookie->getLevel(0) == 0) PD::drawBitmap(46, 17, Images::Portrait::Lock);
            if (this->cookie->getLevel(1) == 0) PD::drawBitmap(38, 17, Images::Portrait::Lock);

            if (this->titleScreenVars.soundCounter == 0) {

                PD::drawBitmap(28, 32, Images::Portrait::Rotate);

            }
            else {

                switch (this->cookie->sfx) {

                    case SoundEffects::Both:
                        PD::drawBitmap(27, 36, Images::Portrait::Sound_Both_White);
                        break;

                    case SoundEffects::None:
                        PD::drawBitmap(27, 36, Images::Portrait::Sound_None_White);
                        break;

                    case SoundEffects::SFX:
                        PD::drawBitmap(27, 36, Images::Portrait::Sound_SFX_White);
                        break;

                    case SoundEffects::Music:
                        PD::drawBitmap(27, 36, Images::Portrait::Sound_Music_White);
                        break;

                    
                }
                
                this->titleScreenVars.soundCounter--;

            }

            break;

        case GameRotation::Landscape:

            if (!renderPlayerSelection) return;

            PD::drawBitmap(56, 12 + (static_cast<uint8_t>(this->cookie->gameMode) * 9), Images::Landscape::LeftArrow[frame]);
            PD::drawBitmap(64, 12, this->cookie->gameMode == GameMode::Single ? Images::Landscape::SurvivalMode : Images::Landscape::SurvivalMode_Grey);
            PD::drawBitmap(64, 21, this->cookie->gameMode == GameMode::Double ? Images::Landscape::VSMode : Images::Landscape::VSMode_Grey);
            PD::drawBitmap(64, 30, this->cookie->gameMode == GameMode::TugOfWar ? Images::Landscape::TugOfWarMode : Images::Landscape::TugOfWarMode_Grey);

            if (this->cookie->getLevel(0) == 0) PD::drawBitmap(71, 21, Images::Landscape::Lock);
            if (this->cookie->getLevel(1) == 0) PD::drawBitmap(71, 30, Images::Landscape::Lock);

            if (this->titleScreenVars.soundCounter == 0) {

                PD::drawBitmap(80, 53, Images::Landscape::Rotate);

            }
            else {

                switch (this->cookie->sfx) {

                    case SoundEffects::Both:
                        PD::drawBitmap(82, 53, Images::Landscape::Sound_Both_White);
                        break;

                    case SoundEffects::None:
                        PD::drawBitmap(82, 53, Images::Landscape::Sound_None_White);
                        break;

                    case SoundEffects::SFX:
                        PD::drawBitmap(82, 53, Images::Landscape::Sound_SFX_White);
                        break;

                    case SoundEffects::Music:
                        PD::drawBitmap(82, 53, Images::Landscape::Sound_Music_White);
                        break;

                    
                }
                
                this->titleScreenVars.soundCounter--;

            }


            break;
            
    }

}
