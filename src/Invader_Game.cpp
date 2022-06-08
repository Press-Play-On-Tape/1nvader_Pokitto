#include "Invader.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::game_Init() {

    gameState = GameState::Game;

    mothership.reset(this->cookie->gameRotation, this->cookie->gameRotation == GameRotation::Landscape ? -Constants::MothershipRowHeight : Constants::MothershipRowHeight);
    gamePlayVars.bombCounter = random(256, 1024);

    player1.reset(0);
    player2.reset(1);

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            switch (this->cookie->gameMode) {

                case GameMode::Single:
                    player1.setPos(26);
                    player1.setMovement(Movement::Up);
                    break;

                default:
                    player1.setPlayerIdx(0);
                    player1.setPos(13);
                    player1.setMovement(Movement::Up);

                    player2.setPos(38);
                    player2.setMovement(Movement::Down);
                    break;

            }

            break;

        case GameRotation::Landscape:

            switch (this->cookie->gameMode) {

                case GameMode::Single:
                    player1.setPos(59);
                    player1.setMovement(Movement::Left);
                    break;

                default:
                    player1.setPlayerIdx(0);
                    player1.setPos(33);
                    player1.setMovement(Movement::Left);

                    player2.setPos(84);
                    player2.setMovement(Movement::Right);
                    break;

            }

            break;

    }            

}   

void Game::game() {

    // Randomly drop a bomb ?

   if (!gamePlayVars.waveCleared) {

        if (player1.getScore() + player2.getScore() > 20) {

            if ((this->cookie->gameRotation == GameRotation::Landscape && mothership.getHeight() < 30) || (this->cookie->gameRotation == GameRotation::Portrait && mothership.getHeight() > 56)) {

                gamePlayVars.bombCounter--;

                if (gamePlayVars.bombCounter == 0) {

                    #ifdef SOUNDS
                        sound.tones(Sounds::Enemy_Drops_Bomb);
                    #endif

                    bomb.setActive(true);
                    bomb.setPos(mothership.getPosDisplay() + 6);
                    bomb.setHeight(mothership.getHeight() + 6);

                    gamePlayVars.bombCounter = random(256, 1024);

                }

            }

        }

        // Handle movements ..

        if (!player1.getBeingPushed()) {

            if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.pressed(BTN_RIGHT) || PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN) ||
                ((PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) && this->cookie->gameMode == GameMode::Single)) {

                bool fired = player1.fire(this->cookie->gameRotation, this->cookie->gameMode, (this->cookie->gameMode == GameMode::Double ? &player2 : nullptr));

                #ifdef SOUNDS
                    if (fired) sound.tones(Sounds::Player_Fires_Bullet);
                #endif

            }

        }

        if (!player2.getBeingPushed()) {

            if ((PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) && this->cookie->gameMode == GameMode::Double) {

                bool fired = player2.fire(this->cookie->gameRotation, this->cookie->gameMode, (this->cookie->gameMode == GameMode::Double ? &player1 : nullptr));

                #ifdef SOUNDS
                    if (fired) sound.tones(Sounds::Player_Fires_Bullet);
                #endif

            }

        }


        if (this->cookie->gameMode == GameMode::Double) {

            movePlayer(player1, player2);
            movePlayer(player2, player1);
            mothership.move(this->cookie->gameRotation, this->cookie->gameMode, player1, player2);

        }
        else {

            movePlayer1();
            mothership.move(this->cookie->gameRotation, this->cookie->gameMode, player1);

        }

        if (player1.getBulletActive() && !gamePlayVars.waveCleared)      moveBullet(player1); 
        if (player2.getBulletActive() && !gamePlayVars.waveCleared)      moveBullet(player2);
        if (bomb.getActive()) moveBomb();

        player1.decExplodeCounter();
        player2.decExplodeCounter();


        // End of game?

        switch (this->cookie->gameRotation) {

            case GameRotation::Portrait:

                if (mothership.getHeight() < Constants::PlayerHeight) {

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

                break;
            
            case GameRotation::Landscape:

                if (mothership.getHeight() > Constants::ScreenHeight - Constants::PlayerHeight - Constants::MothershipHeight) {

                    switch (mothership.getMovement()) {

                        case Movement::Left:
                            if (mothership.getPosDisplay() < -Constants::MothershipHeight) {
                                gameState = GameState::GameOver_Init;
                            }
                            break;

                        case Movement::Right:
                            if (mothership.getPosDisplay() > Constants::ScreenWidth) {
                                gameState = GameState::GameOver_Init;
                            }
                            break;

                        default: break;

                    }

                }

                break;


        }    

    }    



    // Render screen ---------------------------------------------------------------------

    renderScores(false, false);
    renderScenery(this->cookie->gameMode, false);
    updateAndRenderParticles(this->cookie->gameRotation);

    uint8_t frame = (PC::frameCount % 36) / 6;

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            PD::drawBitmap(0, player1.getPos(), Images::Portrait::Normal::Player);

            if (player1.getExplosionCounter() > 0) {

                PD::drawBitmap(0, player1.getPos() - 4, Images::Portrait::Normal::Player_Explosion[(6 - player1.getExplosionCounter()) / 2]);

            }

            if (this->cookie->gameMode == GameMode::Double) {

                PD::drawBitmap(0, player2.getPos(), Images::Portrait::Normal::Player);

                if (player2.getExplosionCounter() > 0) {

                    PD::drawBitmap(0, player2.getPos() - 4, Images::Portrait::Normal::Player_Explosion[(6 - player2.getExplosionCounter()) / 2]);

                }

            }

            switch (mothership.getExplosionCounter()) {

                case 0:
                    PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Normal::Mothership[Constants::Mothership_Frames[frame]]);
                    break;

                case 1 ... Constants::MothershipExplosionMax / 2:
                    PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Explosion[1]);
                    break;

                case (Constants::MothershipExplosionMax / 2) + 1 ... Constants::MothershipExplosionMax:
                    PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Normal::Mothership[frame]);
                    PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Explosion[0]);
                    break;

            }

            if (player1.getBulletActive())  PD::drawBitmap(player1.getBulletX(), player1.getBulletY(), Images::Portrait::Laser);
            if (player2.getBulletActive())  PD::drawBitmap(player2.getBulletX(), player2.getBulletY(), Images::Portrait::Laser);
            
            if (bomb.getActive()) {

                if (bomb.getExplosionCounter() == 0) {

                    PD::drawBitmap(bomb.getHeight(), bomb.getPos(), Images::Portrait::Bomb);
                    
                }

                switch (bomb.getHeight()) {

                    case -2 ... -1:
                        PD::drawBitmap(0, bomb.getPos() - 4, Images::Portrait::Explosion[0]);
                        break;

                    case -4 ... -3:
                        PD::drawBitmap(0, bomb.getPos() - 4, Images::Portrait::Explosion[1]);
                        break;

                }        

                if (bomb.getExploding()) {

                    switch (bomb.getExplosionCounter()) {

                        case 1 ... 2:
                            PD::drawBitmap(bomb.getHeight(), bomb.getPos() - 4, Images::Portrait::Explosion[1]);
                            break;

                        case 3 ... 4:
                            PD::drawBitmap(bomb.getHeight(), bomb.getPos() - 4, Images::Portrait::Explosion[0]);
                            break;

                    }        

                }

            }    
            break;

        case GameRotation::Landscape:

            PD::drawBitmap(player1.getPos(), 80, Images::Landscape::Player);

            if (player1.getExplosionCounter() > 0) {

                PD::drawBitmap(player1.getPos() - 4, 76, Images::Landscape::Player_Explosion[(6 - player1.getExplosionCounter()) / 2]);

            }

            if (this->cookie->gameMode == GameMode::Double) {

                PD::drawBitmap(player2.getPos(), 80, Images::Landscape::Player); 

                if (player2.getExplosionCounter() > 0) {

                    PD::drawBitmap(player2.getPos() - 4, 76, Images::Landscape::Player_Explosion[(6 - player2.getExplosionCounter()) / 2]);

                }

            }

            switch (mothership.getExplosionCounter()) {

                case 0:
                    PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Mothership[Constants::Mothership_Frames[frame]]);
                    break;

                case 1 ... Constants::MothershipExplosionMax / 2:
                    PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Explosion[1]);
                    break;

                case (Constants::MothershipExplosionMax / 2) + 1 ... Constants::MothershipExplosionMax:
                    PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Mothership[Constants::Mothership_Frames[frame]]);
                    PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Explosion[0]);
                    break;

            }

            if (player1.getBulletActive())  PD::drawBitmap(player1.getBulletX(), player1.getBulletY(), Images::Landscape::Laser);
            if (player2.getBulletActive())  PD::drawBitmap(player2.getBulletX(), player2.getBulletY(), Images::Landscape::Laser);
            
            if (bomb.getActive()) {

                if (bomb.getExplosionCounter() == 0) {

                    PD::drawBitmap(bomb.getPos(), bomb.getHeight(), Images::Landscape::Bomb);

                }

                switch (bomb.getHeight()) {

                    case Constants::ScreenHeight - 4 ... Constants::ScreenHeight - 2:
                        PD::drawBitmap(bomb.getPos() - 4, 58, Images::Landscape::Explosion[0]);
                        break;

                    case Constants::ScreenHeight - 1 ... Constants::ScreenHeight:
                        PD::drawBitmap(bomb.getPos() - 4, 58, Images::Landscape::Explosion[1]);
                        break;

                }        

                if (bomb.getExploding()) {

                    switch (bomb.getExplosionCounter()) {

                        case 1 ... 2:
                            PD::drawBitmap(bomb.getPos() - 4, bomb.getHeight(), Images::Landscape::Explosion[1]);
                            break;

                        case 3 ... 4:
                            PD::drawBitmap(bomb.getPos() - 4, bomb.getHeight(), Images::Landscape::Explosion[0]);
                            break;

                    }        

                }

            }        

            break;

    }

    if (gamePlayVars.waveCleared) {


        // Clear an bullets from the screen ..

        if (player1.getBulletActive()) player1.setBulletActive(false);
        if (player2.getBulletActive()) player2.setBulletActive(false);

        if (gamePlayVars.waveCounter == 8) {
            #ifdef SOUNDS
                sound.tones(Sounds::Wave_Cleared);
            #endif
        }

        if (gamePlayVars.waveCounter >= 55 && PC::frameCount % 64 == 0) { launchParticles(this->cookie->gameRotation); }

        if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.pressed(BTN_RIGHT) || PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN) || PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {

            gamePlayVars.waveCounter = 0;
            gamePlayVars.waveCleared = false;

        }

        if (this->cookie->gameMode == GameMode::Double) {

            movePlayer(player1, player2);
            movePlayer(player2, player1);


            if (mothership.getExplosionCounter() > 0) mothership.move(this->cookie->gameRotation, this->cookie->gameMode, player1, player2);

        }
        else {

            movePlayer1();
            if (mothership.getExplosionCounter() > 0) mothership.move(this->cookie->gameRotation, this->cookie->gameMode, player1);

        }

        uint8_t idx = gamePlayVars.waveCounter / 8;

        updateAndRenderParticles(this->cookie->gameRotation);

        switch (this->cookie->gameRotation) {

            case GameRotation::Portrait:
                PD::setColor(0);
                PD::drawRect(51, 44 - (idx * 4), 9, 4 + (idx * 8));
                PD::drawBitmap(51, 44 - (idx * 4), Images::Portrait::WaveCleared[idx]);
                break;

            case GameRotation::Landscape:
                PD::setColor(0);
                PD::drawRect(53 - (idx * 4), 36, 4 + (idx * 8), 9);
                PD::drawBitmap(53 - (idx * 4), 36, Images::Landscape::WaveCleared[idx]);
                break;

        }         

        if (gamePlayVars.waveCounter < 55) gamePlayVars.waveCounter++;

    }

}


void Game::movePlayer(Player &player, Player &otherPlayer) {

    if ((PC::frameCount % 2) == player.getPlayerIdx()) {

        switch (player.getMovement()) {

            case Movement::Up:

                if (player.getPos() > Constants::Portrait::PlayerMinPos) {

                    player.decPos();
                    
                    if (this->cookie->gameMode == GameMode::TugOfWar) return;

                    if (abs(player.getPos() - otherPlayer.getPos()) < Constants::PlayerWidthNoMask ) {
                        
                        if (otherPlayer.getPos() > Constants::Portrait::PlayerMinPos && otherPlayer.getMovement() == Movement::Down) {
                            otherPlayer.changeMovement(this->cookie->gameRotation);
                        }
                        else {
                            player.incPos();
                            player.changeMovement(this->cookie->gameRotation);
                        }

                    }

                }
                else {
                    player.changeMovement(this->cookie->gameRotation);
                }

                break;

            case Movement::Down:

                if (player.getPos() < Constants::Portrait::PlayerMaxPos) {

                    player.incPos();
                    
                    if (this->cookie->gameMode == GameMode::TugOfWar) return;

                    if (abs(player.getPos() - otherPlayer.getPos()) < Constants::PlayerWidthNoMask) {

                        if (otherPlayer.getPos() < Constants::Portrait::PlayerMaxPos && otherPlayer.getMovement() == Movement::Up) {
                            otherPlayer.changeMovement(this->cookie->gameRotation);
                        }
                        else {
                            player.decPos();
                            player.changeMovement(this->cookie->gameRotation);
                        }

                    }

                }
                else {
                    player.changeMovement(this->cookie->gameRotation);
                }

                break;

            case Movement::Left:

                if (player.getPos() > Constants::Landscape::PlayerMinPos) {

                    player.decPos();

                    if (abs(player.getPos() - otherPlayer.getPos()) < Constants::PlayerWidthNoMask ) {
                        
                        if (otherPlayer.getPos() > Constants::Landscape::PlayerMinPos && otherPlayer.getMovement() == Movement::Right) {
                            otherPlayer.changeMovement(this->cookie->gameRotation);
                        }
                        else {
                            player.incPos();
                            player.changeMovement(this->cookie->gameRotation);
                        }

                    }

                }
                else {
                    player.changeMovement(this->cookie->gameRotation);
                }

                break;

            case Movement::Right:

                if (player.getPos() < Constants::Landscape::PlayerMaxPos) {

                    player.incPos();

                    if (abs(player.getPos() - otherPlayer.getPos()) < Constants::PlayerWidthNoMask) {

                        if (otherPlayer.getPos() < Constants::Landscape::PlayerMaxPos && otherPlayer.getMovement() == Movement::Left) {
                            otherPlayer.changeMovement(this->cookie->gameRotation);
                        }
                        else {
                            player.decPos();
                            player.changeMovement(this->cookie->gameRotation);
                        }

                    }

                }
                else {
                    player.changeMovement(this->cookie->gameRotation);
                }

                break;


        }

    }

}


void Game::movePlayer1() {

    if (PC::frameCount % 2 == 0) {

        switch (player1.getMovement()) {

            case Movement::Up:
                player1.decPos();
                if (player1.getPos() == Constants::Portrait::PlayerMinPos) {
                    player1.changeMovement(this->cookie->gameRotation);
                }
                break;

            case Movement::Left:
                player1.decPos();
                if (player1.getPos() == Constants::Landscape::PlayerMinPos) {
                    player1.changeMovement(this->cookie->gameRotation);
                }
                break;

            case Movement::Down:
                player1.incPos();
                if (player1.getPos() == Constants::Portrait::PlayerMaxPos) {
                    player1.changeMovement(this->cookie->gameRotation);
                }
                break;

            case Movement::Right:
                player1.incPos();
                if (player1.getPos() == Constants::Landscape::PlayerMaxPos) {
                    player1.changeMovement(this->cookie->gameRotation);
                }
                break;

        }

    }

}

void Game::moveBullet(Player &player) {

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            switch (this->cookie->gameMode) {
            
                case GameMode::Single ... GameMode::Double:
                    player.incBulletX();
                    break;
            
                case GameMode::TugOfWar:

                    switch (player.getPlayerIdx()) {

                        case 0:
                            player.incBulletX();
                            break;

                        case 1:
                            player.decBulletX();
                            break;

                    }
                    break;

            }

            break;

        case GameRotation::Landscape:
            if (PC::frameCount % 2 == 0) {
                player.decBulletY();
            }
            break;

    }

    if (mothership.getExplosionCounter() != 0) return;
    if (!player.getBulletActive()) return;


    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:
            {
                Rect bulletRect = { player.getBulletX() + 1, player.getBulletY() +1, Constants::BulletHeight - 2, Constants::BulletWidth - 2 };
                Rect mothershipRect = { mothership.getHeight() + 1, mothership.getPosDisplay() + 1, Constants::MothershipWidth - 2, Constants::MothershipHeight - 2 };

                if (this->collide(bulletRect, mothershipRect)) {

                    #ifdef SOUNDS
                        sound.tones(Sounds::Enemy_Explosion);
                    #endif


                    launchParticles(this->cookie->gameRotation, mothership.getPosDisplay() + (Constants::MothershipHeight / 2), mothership.getHeight() + (Constants::MothershipWidth / 2));


                    if (this->cookie->gameMode == GameMode::TugOfWar) {
                        mothership.explode(player.getPlayerIdx() == 0 ? -Constants::TugOfWarRowAdjustment : Constants::TugOfWarRowAdjustment);
                        gamePlayVars.waveCleared = false;
                        mothership.decCounter();
                    }
                    else {
                        mothership.explode(Constants::MothershipRowHeight);
                        gamePlayVars.waveCleared = mothership.decCounter();
                    }

                    player.incScore();
                    player.setBulletActive(false);

                }

                if (bomb.getActive()) {

                    Rect bombRect = { bomb.getHeight() + 1, bomb.getPos() + 1, Constants::BombHeight - 2, Constants::BombWidth - 2 };

                    if (this->collide(bulletRect, bombRect)) {

                        #ifdef SOUNDS
                            sound.tones(Sounds::Bomb_Explosion);
                        #endif

                        bomb.explode();
                        player.setBulletActive(false);

                    }
                    
                }

            }

            break;

        case GameRotation::Landscape:
            {        
                Rect bulletRect = { player.getBulletX() + 1, player.getBulletY() + 1, Constants::BulletWidth - 2, Constants::BulletHeight - 2 };
                Rect mothershipRect = { mothership.getPosDisplay() + 1, mothership.getHeight() + 1, Constants::MothershipWidth - 2, Constants::MothershipHeight - 2 };

                if (this->collide(bulletRect, mothershipRect)) {

                    #ifdef SOUNDS
                        sound.tones(Sounds::Enemy_Explosion);
                    #endif

                    launchParticles(this->cookie->gameRotation, mothership.getPosDisplay() + (Constants::MothershipHeight / 2), mothership.getHeight() + (Constants::MothershipWidth / 2));

                    mothership.explode(-Constants::MothershipRowHeight);                    
                    gamePlayVars.waveCleared = mothership.decCounter();

                    player.incScore();
                    player.setBulletActive(false);

                }

                if (bomb.getActive()) {

                    Rect bombRect = { bomb.getHeight() + 1, bomb.getPos() + 1, Constants::BombWidth - 2, Constants::BombHeight - 2 };

                    if (this->collide(bulletRect, bombRect)) {

                        #ifdef SOUNDS
                            sound.tones(Sounds::Bomb_Explosion);
                        #endif

                        bomb.explode();
                        player.setBulletActive(false);

                    }
                    
                }

            }

            break;

    }

}

void Game::moveBomb() {

    bomb.decHeight(this->cookie->gameRotation);

    if (!bomb.getActive() || bomb.getExplosionCounter() > 0) return;

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:
            {
                Rect bombRect = { bomb.getHeight() + 1, bomb.getPos() + 1, Constants::BombHeight - 2, Constants::BombWidth - 2 };
                Rect player1Rect = { 0, player1.getPos() + 1, Constants::PlayerHeight - 2, Constants::PlayerWidth - 2 };

                if (this->collide(bombRect, player1Rect)) {

                    bool explode = player1.explode();

                    #ifdef SOUNDS
                        if (explode) {
                            sound.tones(Sounds::Player_Hit_By_Bomb);
                        }
                    #endif
                }

                if (this->cookie->gameMode != GameMode::Single) {

                    Rect player2Rect = { 0, player2.getPos() + 1, Constants::PlayerHeight - 2, Constants::PlayerWidth - 2 };

                    if (this->collide(bombRect, player2Rect)) {

                        bool explode = player2.explode();

                        #ifdef SOUNDS
                            if (explode) {
                                sound.tones(Sounds::Player_Hit_By_Bomb);
                            }
                        #endif

                    }

                }

            }

            break;

        case GameRotation::Landscape:
            {        
                Rect bombRect = { bomb.getPos() + 1, bomb.getHeight() + 1, Constants::BombWidth - 2, Constants::BombHeight - 2 };
                Rect player1Rect = { player1.getPos() + 1, Constants::ScreenHeight - Constants::PlayerHeight + 1, Constants::PlayerWidth - 2, Constants::PlayerHeight - 1 };

                if (this->collide(bombRect, player1Rect)) {

                    bool explode = player1.explode();

                    #ifdef SOUNDS
                        if (explode) {
                            sound.tones(Sounds::Player_Hit_By_Bomb);
                        }
                    #endif

                }

                if (this->cookie->gameMode != GameMode::Single) {

                    Rect player2Rect = { player2.getPos() + 1, Constants::ScreenHeight - Constants::PlayerHeight + 1, Constants::PlayerWidth - 2, Constants::PlayerHeight - 1 };

                    if (this->collide(bombRect, player2Rect)) {

                        bool explode = player2.explode();

                        #ifdef SOUNDS
                            if (explode) {
                                sound.tones(Sounds::Player_Hit_By_Bomb);
                            }
                        #endif

                    }

                }

            }

            break;

    }

}
