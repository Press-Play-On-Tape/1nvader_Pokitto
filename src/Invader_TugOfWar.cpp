#include "Invader.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"
#include "utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::tugOfWar_Init() {

    gameState = GameState::TugOfWar;

    mothership.reset(this->cookie->gameRotation, 0);
    mothership.setHeight((Constants::ScreenWidth / 2) - 4);

    player1.reset(0);
    player2.reset(1);

    player1.setPos(45);
    player1.setMovement(Movement::Up);

    player2.setPos(25);
    player2.setMovement(Movement::Down);

}   

void Game::tugOfWar() {


    // Handle movements ..

    if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.pressed(BTN_RIGHT) || PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN)) {

        bool fired = player1.fire(this->cookie->gameRotation, this->cookie->gameMode, nullptr);

        #ifdef SOUNDS
            if (fired) playSoundEffect(SoundEffect::Laser);
        #endif

    }

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {

         bool fired = player2.fire(this->cookie->gameRotation, this->cookie->gameMode, nullptr);

        #ifdef SOUNDS
            if (fired) playSoundEffect(SoundEffect::Laser);
        #endif

    }
    
    movePlayer(player1, player2);
    movePlayer(player2, player1);
    mothership.moveTugOfWar(player1, player2);

    if (player1.getBulletActive())      moveBullet(player1); 
    if (player2.getBulletActive())      moveBullet(player2);



    // End of game?

    if ((mothership.getHeight() <= Constants::PlayerHeight) ||
        (mothership.getHeight() >= 96 - Constants::PlayerHeight)) {

        switch (mothership.getMovement()) {

            case Movement::Up:
                if (mothership.getPosDisplay() < -Constants::MothershipHeight) {
                    gameState = GameState::GameOver_Init;
                }
                break;

            case Movement::Down:
                if (mothership.getPosDisplay() > Constants::ScreenHeight) {
                    gameState = GameState::GameOver_Init;
                }
                break;

            default: break;

        }

    }
       

    renderScenery(this->cookie->gameMode, false);
    renderScoreTugOfWar(player1.getScore(), player2.getScore());
    updateAndRenderParticles(GameRotation::Landscape);

    PD::drawBitmap(0, player1.getPos(), Images::Portrait::Normal::Player);

    if (player1.getExplosionCounter() > 0) {

        PD::drawBitmap(0, player1.getPos() - 4, Images::Portrait::Normal::Player_Explosion[(6 - player1.getExplosionCounter()) / 2]);

    }

    PD::drawBitmap(102, player2.getPos(), Images::Portrait::Rotated::Player);

    if (player2.getExplosionCounter() > 0) {

        PD::drawBitmap(102, player2.getPos() - 4, Images::Portrait::Rotated::Player_Explosion[(6 - player2.getExplosionCounter()) / 2]);

    }

    uint8_t frame = (PC::frameCount % 36) / 6;

    if (mothership.getHeight() < Constants::ScreenHeight) {

        switch (mothership.getExplosionCounter()) {

            case 0:
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Normal::Mothership[Constants::Mothership_Frames[frame]]);
                break;

            case 1 ... Constants::MothershipExplosionMax / 2:
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Explosion[1]);
                break;

            case (Constants::MothershipExplosionMax / 2) + 1 ... Constants::MothershipExplosionMax - 1:
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Normal::Mothership[Constants::Mothership_Frames[frame]]);
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Explosion[0]);
                break;

            case Constants::MothershipExplosionMax:
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Normal::Mothership[Constants::Mothership_Frames[frame]]);
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Explosion[0]);
                launchParticles(GameRotation::Landscape, mothership.getHeight() + (Constants::MothershipWidth / 2), mothership.getPosDisplay() + (Constants::MothershipHeight / 2));
                break;

        }

    }
    else {

        switch (mothership.getExplosionCounter()) {

            case 0:
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Rotated::Mothership[Constants::Mothership_Frames[frame]]);
                break;

            case 1 ... Constants::MothershipExplosionMax / 2:
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Explosion[1]);
                break;

            case (Constants::MothershipExplosionMax / 2) + 1 ... Constants::MothershipExplosionMax - 1:
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Rotated::Mothership[Constants::Mothership_Frames[frame]]);
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Explosion[0]);
                break;

            case Constants::MothershipExplosionMax:
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Rotated::Mothership[Constants::Mothership_Frames[frame]]);
                PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Explosion[0]);
                launchParticles(GameRotation::Landscape, mothership.getHeight() + (Constants::MothershipWidth / 2), mothership.getPosDisplay() + (Constants::MothershipHeight / 2));
                break;

        }

    }

    if (player1.getBulletActive())  PD::drawBitmap(player1.getBulletX(), player1.getBulletY(), Images::Portrait::Laser);
    if (player2.getBulletActive())  PD::drawBitmap(player2.getBulletX(), player2.getBulletY(), Images::Portrait::Laser);

}
