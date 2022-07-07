#include "Invader.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::playTheme(Theme theme) {

    #ifdef SOUNDS

    constexpr char themes[3][19] = { "music/1nvad_00.raw", "music/1nvad_01.raw", "music/1nvad_02.raw" };

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
        case SoundEffects::Both:

            switch (theme) {

                case Theme::Game_Over:

                    if (this->mainThemeFile.openRO(themes[static_cast<uint8_t>(theme)])) {
                        auto& music = Audio::play<0>(this->mainThemeFile);
                        music.setLoop(false);
                    }

                    break;

                case Theme::Hover:
                case Theme::Main:

                    if (this->mainThemeFile.openRO(themes[static_cast<uint8_t>(theme)])) {
                        auto& music = Audio::play<0>(this->mainThemeFile);
                        music.setLoop(true);
                    }

                    break;
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

    constexpr char themes[1][19] = { "music/1nvad_00.raw" };

    switch (this->cookie->sfx) {

        case SoundEffects::SFX:
        case SoundEffects::Both:
                
            switch (soundEffect) {
                
                case SoundEffect::Laser:
                    Audio::play<1>(Sounds::sfx_Laser);    
                    break;
                
                case SoundEffect::Mini_Explosion:
                    Audio::play<1>(Sounds::sfx_Mini_Explosion);    
                    break;
                                
                case SoundEffect::Level_Cleared:
                    Audio::play<1>(Sounds::sfx_Level_Cleared);    
                    break;
                
                case SoundEffect::Bomb_HitGround:
                    Audio::play<1>(Sounds::sfx_Bomb_HitGround);    
                    break;
                
                case SoundEffect::Drop_Bomb:
                    Audio::play<1>(Sounds::sfx_Drop_Bomb);    
                    break;
                
                case SoundEffect::Player_Hit:
                    Audio::play<1>(Sounds::sfx_Player_Hit);    
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

    #ifdef NEW_GRAPHICS

        PD::drawBitmap(0, 0, Images::Portrait::Mountain_BOT_New);

    #else

        PD::setColor(4);
        PD::fillRect(0, 0, 17, 88);

        for (int8_t y = -2; y < Constants::ScreenHeight; y+=16) {

            PD::drawBitmap(17, y, Images::Portrait::Mountain_Bot);

        }

        for (int8_t y = 0; y < Constants::ScreenHeight; y+=8) {
        
            PD::drawBitmap(0, y, Images::Portrait::Ground_Bot);

        }

    #endif

}

void Game::renderScenery(GameMode gameMode, bool hideCentreline) {

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            switch (gameMode) {

                case GameMode::TugOfWar:

                    renderSceneryPortrait();

                    #ifdef NEW_GRAPHICS

                        PD::drawBitmap(72, 0, Images::Portrait::Mountain_TOP_New);

                    #else

                        PD::setColor(4);
                        PD::fillRect(85 + 8, 0, 110 - 85 - 8, 88);

                        for (int8_t y = -2; y < Constants::ScreenHeight; y+=16) {

                            PD::drawBitmap(85, y, Images::Portrait::Mountain_TOP);

                        }

                        for (int8_t y = 0; y < Constants::ScreenHeight; y+=8) {

                            PD::drawBitmap(107, y, Images::Portrait::Ground_TOP);

                        }

                    #endif

                    if (!hideCentreline) {

                        PD::setColor(5);
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

            #ifdef NEW_GRAPHICS
                
                PD::drawBitmap(0, 50, Images::Landscape::Mountain_New);

            #else

                for (int16_t x = -2; x < Constants::ScreenWidth; x+=16) {

                    PD::drawBitmap(x, 66, Images::Landscape::Mountain);

                }


                for (uint8_t x = 0; x < Constants::ScreenWidth; x+=8) {

                    PD::drawBitmap(x, 85, Images::Landscape::Ground);

                }

            #endif

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

            PD::drawBitmap(4, 37, Images::Landscape::Invader);
            break;
    
    }

}

bool Game::collide(Rect rect1, Rect rect2) {

   return !(rect2.x                >= rect1.x + rect1.width  ||
            rect2.x + rect2.width  <= rect1.x                ||
            rect2.y                >= rect1.y + rect1.height ||
            rect2.y + rect2.height <= rect1.y);

 }

void Game::renderStars(GameMode gameMode, GameRotation gameRotation) {

    uint8_t stars_X_Landscape[] = { 2,  7, 14, 20, 24, 35, 42, 48, 60, 64, 70, 78, 85, 88, 90, 98, 102, 108 };
    uint8_t stars_Y_Landscape[] = { 8, 12, 38, 23, 14, 32, 26,  8, 23, 18, 40, 22, 16, 37, 23,  8,   20, 40 };

    uint8_t stars_X_Potrait[] = { 2,  7, 14, 20, 24, 35, 42, 48, 60, 64, 70, 78, 85, 88, 16, 44, 58, 78 };
    uint8_t stars_Y_Potrait[] = { 8, 12, 38, 23, 14, 32, 26,  8, 23, 18, 40, 22, 16, 37, 50, 56, 60, 58 };

    switch (gameMode) {

        case GameMode::Single:
        case GameMode::Double:

            switch (gameRotation) {

                case GameRotation::Landscape:

                    for (uint8_t i = 0; i < 18; i++) {

                        PD::setColor(5 + random(0, 2));
                        PD::drawPixel(stars_X_Landscape[i], stars_Y_Landscape[i]);

                    }

                    break;

                case GameRotation::Portrait:

                    for (uint8_t i = 0; i < 18; i++) {

                        PD::setColor(5 + random(0, 2));
                        PD::drawPixel(110 - stars_Y_Potrait[i], stars_X_Potrait[i]);

                    }

                    break;

            }

        default:
            break;

    }


}
