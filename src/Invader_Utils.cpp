#include "Invader.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::playTheme() {

    #ifdef SOUNDS

    constexpr char themes[1][19] = { "music/DarkB_01.raw" };

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
        case SoundEffects::Both:

            if (this->mainThemeFile.openRO(themes[0])) {
                auto& music = Audio::play<0>(this->mainThemeFile);
                music.setLoop(true);
            }

            break;

        case SoundEffects::SFX:
        case SoundEffects::None:

            this->muteTheme();

    }

    #endif

}

void Game::muteTheme() {

    #ifdef SOUNDS
    Audio::stop<0>();
    #endif

}


void Game::playSoundEffect(SoundEffect soundEffect) {

    #ifdef SOUNDS

    switch (this->cookie->sfx) {

        case SoundEffects::SFX:
        case SoundEffects::Both:
                
            switch (soundEffect) {
                
                case SoundEffect::Tone_00:
                    Audio::play<1>(Sounds::sfx_Tone_00);    
                    break;
                
                case SoundEffect::Tone_01:
                    Audio::play<1>(Sounds::sfx_Tone_01);    
                    break;
                
                case SoundEffect::Tone_02:
                    Audio::play<1>(Sounds::sfx_Tone_02);    
                    break;
                
                case SoundEffect::Tone_03:
                    Audio::play<1>(Sounds::sfx_Tone_03);    
                    break;
                            
                case SoundEffect::Tone_04:
                    Audio::play<1>(Sounds::sfx_Tone_04);    
                    break;               
                            
                case SoundEffect::Tone_05:
                    Audio::play<1>(Sounds::sfx_Tone_05);    
                    break;               
                            
                case SoundEffect::Tone_06:
                    Audio::play<1>(Sounds::sfx_Tone_06);    
                    break;               

                case SoundEffect::Tone_07:
                    Audio::play<1>(Sounds::sfx_Tone_07);    
                    break;               

                case SoundEffect::Tone_08:
                    Audio::play<1>(Sounds::sfx_Tone_08);    
                    break;               

                case SoundEffect::Tone_09:
                    Audio::play<1>(Sounds::sfx_Tone_09);    
                    break;               

            }

            break;

        default: break;
        
    }  

    #endif

}    


void Game::renderScores(bool flashPlayer1, bool flashPlayer2) {

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            switch (this->cookie->gameMode) {
                
                case GameMode::Single:

                    if (!flashPlayer1 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                        renderScore(28, Constants::ScreenWidth - 7, player1.getScore());
                    }

                    PD::drawBitmap(Constants::ScreenWidth - 7, 53, Images::Portrait::Normal::Numbers[mothership.getCounter() / 10]);
                    PD::drawBitmap(Constants::ScreenWidth - 7, 57, Images::Portrait::Normal::Numbers[mothership.getCounter() % 10]);

                    break;

                case GameMode::Double:

                    if (!flashPlayer1 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                        renderScore(3, Constants::ScreenWidth - 7, player1.getScore());
                    }

                    if (!flashPlayer2 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                        renderScore(70, Constants::ScreenWidth - 7, player2.getScore());
                    }

                    PD::drawBitmap(Constants::ScreenWidth - 7, 40, Images::Portrait::Normal::Numbers[mothership.getCounter() / 10]);
                    PD::drawBitmap(Constants::ScreenWidth - 7, 44, Images::Portrait::Normal::Numbers[mothership.getCounter() % 10]);

                    break;
                
                case GameMode::TugOfWar:

                    if (!flashPlayer1 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                        renderScore(3, Constants::ScreenWidth - 12, player1.getScore());
                    }

                    if (!flashPlayer2 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                        renderScore(70, Constants::ScreenWidth - 12, player2.getScore());
                    }

                    break;

            }

            break;

        case GameRotation::Landscape:
                
            if (this->cookie->gameMode == GameMode::Double) {

                if (!flashPlayer1 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                    renderScore(19, 0, player1.getScore());
                }

                if (!flashPlayer2 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                    renderScore(100, 0, player2.getScore());
                }

                PD::drawBitmap(51, 0, Images::Landscape::Numbers[mothership.getCounter() / 10]);
                PD::drawBitmap(55, 0, Images::Landscape::Numbers[mothership.getCounter() % 10]);

            }
            else {

                if (!flashPlayer1 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                    renderScore(24, 0, player1.getScore());
                }

                PD::drawBitmap(91, 0, Images::Landscape::Numbers[mothership.getCounter() / 10]);
                PD::drawBitmap(95, 0, Images::Landscape::Numbers[mothership.getCounter() % 10]);

            }

            break;

    }

}

void Game::renderScore(uint8_t location, uint8_t height, uint16_t score) {

    uint8_t digits[4] = {};
    extractDigits(digits, score);

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            for (uint8_t j = 4; j > 0; --j, location += 4) {

                PD::drawBitmap(height, location, Images::Portrait::Normal::Numbers[digits[j - 1]]);

            }

            break;

        case GameRotation::Landscape:

            for (uint8_t j = 0; j < 4; ++j, location -= 4) {

                PD::drawBitmap(location, height, Images::Landscape::Numbers[digits[j]]);

            }

            break;

    }

}


void Game::renderScoreTugOfWar(uint16_t score1, uint16_t score2) {

    uint8_t digits[4] = {};
    extractDigits(digits, score2);

    uint8_t location = 14;
    for (uint8_t j = 4; j > 0; --j, location -= 4) {

        PD::drawBitmap(95, location, Images::Portrait::Rotated::Numbers[digits[j - 1]]);

    }

    extractDigits(digits, score1);
    location = 71;
    for (uint8_t j = 4; j > 0; --j, location += 4) {

        PD::drawBitmap(10, location, Images::Portrait::Normal::Numbers[digits[j - 1]]);

    }

}

void Game::renderSceneryPortrait() {

    if (PC::frameCount % 2 == 0) {

        PD::drawPixel(36, 4, WHITE);
        PD::drawPixel(61, 25, WHITE);

    }
    else {

        PD::drawPixel(45, 52, WHITE);
        PD::drawPixel(106, 54, WHITE);
        PD::drawPixel(96, 24, WHITE);

    }

    for (int8_t y = -2; y < Constants::ScreenHeight; y+=16) {

        PD::drawBitmap(17, y, Images::Portrait::Mountain_TOP);

    }


    for (int8_t y = 0; y < Constants::ScreenHeight; y+=8) {
    
        PD::drawBitmap(0, y, Images::Portrait::Ground_BOT);

    }

}

void Game::renderScenery(GameMode gameMode, bool hideCentreline) {

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            switch (gameMode) {

                case GameMode::TugOfWar:

                    renderSceneryPortrait();

                    for (int8_t y = -2; y < Constants::ScreenHeight; y+=16) {

                        PD::drawBitmap(85, y, Images::Portrait::Mountain_BOT);

                    }

                    for (int8_t y = 0; y < Constants::ScreenHeight; y+=8) {

                        PD::drawBitmap(107, y, Images::Portrait::Ground_TOP);

                    }

                    if (!hideCentreline) {

                        for (uint8_t y = 1; y < Constants::ScreenHeight; y = y + 4) {

                            PD::drawFastVLine(Constants::ScreenWidth / 2, y, 2);

                        } 

                    }

                    break;

                default:

                    renderSceneryPortrait();
                    break;

            }

            break;

        case GameRotation::Landscape:
                
            if (PC::frameCount % 2 == 0) {

                PD::drawPixel(6, 4, WHITE);
                PD::drawPixel(61, 25, WHITE);
                PD::drawPixel(102, 38, WHITE);
                PD::drawPixel(126, 37, WHITE);

            }
            else {

                PD::drawPixel(10, 22, WHITE);
                PD::drawPixel(75, 3, WHITE);
                PD::drawPixel(124, 6, WHITE);

            }

            for (int16_t x = -2; x < Constants::ScreenWidth; x+=16) {

                PD::drawBitmap(x, 66, Images::Landscape::Mountain);

            }

            for (uint8_t x = 0; x < Constants::ScreenWidth; x+=8) {

                PD::drawBitmap(x, 85, Images::Landscape::Ground);

            }

            break;

    }

}


void Game::renderHighScore(GameMode gameMode, bool centre) {

    uint8_t digits[4] = {};

    uint16_t score = this->cookie->getScore(this->cookie->gameMode);
    extractDigits(digits, score);

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:
            {
                uint8_t y = 57;

                PD::drawBitmap(7, 17, Images::Portrait::HighScore);

                for (uint8_t j = 4; j > 0; --j, y += 4) {
                    PD::drawBitmap(7, y, Images::Portrait::Normal::Numbers[digits[j - 1]]);
                }

            }

            break;

        case GameRotation::Landscape:
            {
                uint8_t x = centre ? 70 : 51;

                PD::drawBitmap(centre ? 25 : 6, 53, Images::Landscape::HighScore);

                for (uint8_t j = 0; j < 4; ++j, x += 4) {
                    PD::drawBitmap(x, 53, Images::Landscape::Numbers[digits[3 - j]]);
                }

            }

            break;

    }

}

void Game::renderInvaderSign() {

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            PD::drawBitmap(68, 19, Images::Portrait::Invader);
            break;

        case GameRotation::Landscape:

            PD::drawBitmap(5, 31, Images::Landscape::Invader);
            break;
    
    }

}

bool Game::collide(Rect rect1, Rect rect2) {

   return !(rect2.x                >= rect1.x + rect1.width  ||
            rect2.x + rect2.width  <= rect1.x                ||
            rect2.y                >= rect1.y + rect1.height ||
            rect2.y + rect2.height <= rect1.y);

 }