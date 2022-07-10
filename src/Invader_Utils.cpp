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



bool Game::collide(Rect rect1, Rect rect2) {

   return !(rect2.x                >= rect1.x + rect1.width  ||
            rect2.x + rect2.width  <= rect1.x                ||
            rect2.y                >= rect1.y + rect1.height ||
            rect2.y + rect2.height <= rect1.y);

}
