#pragma once

#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "Player.h"

struct Mothership {

    private:

        int16_t pos = 0;
        int8_t rowAdjustment = 0;
        uint8_t height = 0;
        uint8_t explosionCounter = 0;
        uint8_t counter = Constants::MothershipCounterMax;
        uint8_t wave = 0;
        Movement movement = Movement::Up;

        EnemyType type = EnemyType::Single;
        EnemyType frame = EnemyType::Single;

        Movement exclaimMovement = Movement::Up;
        uint8_t exclaimCounter = 0;
        int16_t exclaimX = 0;
        int16_t exclaimY = 0;

        bool canTurn = false;
        bool active = false;


    public:

        int16_t getPos()                                    { return this->pos; }
        uint8_t getHeight()                                 { return this->height; }
        uint8_t getCounter()                                { return this->counter; }
        uint8_t getExplosionCounter()                       { return this->explosionCounter; }
        uint8_t getExclamationCounter()                     { return this->exclaimCounter; }
        int16_t getExclamationX()                           { return this->exclaimX; }
        int16_t getExclamationY()                           { return this->exclaimY; }

        bool getCanTurn()                                   { return this->canTurn && (this->explosionCounter == 0); }
        bool isActive()                                     { return this->active; }

        Movement getMovement()                              { return this->movement; }
        Movement getExclaimMovement()                       { return this->exclaimMovement; }
        EnemyType getEnemyType()                            { return this->type; }
        EnemyType getEnemyFrame()                           { return this->frame; }  // which image to show

        void setPos(int16_t val)                            { this->pos = val; }
        void setHeight(uint8_t val)                         { this->height = val; }
        void setCounter(uint8_t val)                        { this->counter = val; }
        void setRowAdjustment(int8_t val)                   { this->rowAdjustment = val; }
        void setCanTurn(bool val)                           { this->canTurn = val; }

        void setMovement(Movement val)                      { this->movement = val; }
        void setExclaimMovement(Movement val)               { this->exclaimMovement = val; }

        void setEnemyType(EnemyType val)                    { this->type = val; }
        void setEnemyFrame(EnemyType val)                   { this->type = val; }
        void setActive(bool val)                            { this->active = val; }

    private:
    
        uint16_t getSpeed(GameRotation gameRotation, GameMode gameMode) {

            uint16_t base = 240 + (gameMode == GameMode::TugOfWar ? 30 : 0);

            switch (gameRotation) {

                case GameRotation::Portrait:
                    return base + (wave * Constants::WaveIncrease) - (counter * 3 / 2);

                case GameRotation::Landscape:

                    return base + (wave * Constants::WaveIncrease) - (counter * 3 / 2);

                default: return 0;

            }
            
        }

        void move(GameRotation gameRotation, GameMode gameMode, Mothership *otherShip) {

            if (this->explosionCounter > 0) {

                this->explosionCounter--;

                if (this->explosionCounter == 0) {

                    this->die(gameRotation, otherShip);

                }

            }

            switch (this->getMovement()) {

                case Movement::Up:

                    this->decPos(gameRotation, gameMode);

                    if (this->getPos() <= Constants::Portrait::MothershipMinPos) {

                        this->setMovement(Movement::Down);
                        this->canTurn = true;

                        if (this->getHeight() > 0) {
                            this->decHeight();
                        }

                    }

                    break;

                case Movement::Down:

                    this->incPos(gameRotation, gameMode);

                    if (this->getPos() >= Constants::Portrait::MothershipMaxPos) {

                        this->setMovement(Movement::Up);
                        this->canTurn = true;

                        if (this->getHeight() > 0) {
                            this->decHeight();
                        }

                    }

                    break;

                case Movement::Left:

                    this->decPos(gameRotation, gameMode);

                    if (this->getPos() <= Constants::Landscape::MothershipMinPos) {

                        this->setMovement(Movement::Right);
                        this->canTurn = true;

                        if (this->getHeight() < Constants::ScreenHeight) {
                            this->decHeight();
                        }

                    }

                    break;

                case Movement::Right:

                    this->incPos(gameRotation, gameMode);

                    if (this->getPos() >= Constants::Landscape::MothershipMaxPos) {

                        this->setMovement(Movement::Left);
                        this->canTurn = true;

                        if (this->getHeight() < Constants::ScreenHeight) {
                            this->decHeight();
                        }

                    }

                    break;

            }

        }

        void die(GameRotation gameRotation, Mothership *otherShip) {

            if (this->type == EnemyType::Double && this->frame == EnemyType::Single) {

                this->frame = EnemyType::Double;
                return;

            }


            // Calculate Random_RemoveEnemy:

            switch (gameRotation) {

                case GameRotation::Portrait:        

                    if (this->rowAdjustment == Constants::MothershipRowHeight) {

                        if (otherShip != nullptr && otherShip->isActive() && random(0, Constants::Random_RemoveEnemy) == 0) {

                            this->setActive(false);

                        }
                        else {

                            this->canTurn = true;
                            this->type = static_cast<EnemyType>(random(0,2));
                            this->frame = EnemyType::Single;

                            if (random(0, 2) == 0) {
                                this->pos = Constants::Portrait::MothershipMinPos;
                                this->movement = Movement::Down;
                            }
                            else {
                                this->pos = Constants::Portrait::MothershipMaxPos;
                                this->movement = Movement::Up;
                            }

                            switch (this->height) {

                                case Constants::Portrait::MothershipStartHeight:
                                    break;

                                case Constants::Portrait::MothershipStartHeight - Constants::MothershipRowHeight:
                                    this->height = Constants::Portrait::MothershipStartHeight;
                                    break;

                                case Constants::Portrait::MothershipStartHeight - Constants::MothershipRowHeight - Constants::MothershipRowHeight:
                                    this->height = Constants::Portrait::MothershipStartHeight;
                                    break;

                                default:
                                    this->height = this->height + Constants::MothershipRowHeight + Constants::MothershipRowHeight;
                                    break;

                            }

                        }

                    }
                    else {

                        if (random(0, 2) == 0) {
                            this->pos = Constants::Portrait::MothershipMinPos;
                            this->movement = Movement::Down;
                        }
                        else {
                            this->pos = Constants::Portrait::MothershipMaxPos;
                            this->movement = Movement::Up;
                        }

                        this->height = this->height - this->rowAdjustment;
                        
                    }

                    break;

                case GameRotation::Landscape:        

                    if (otherShip != nullptr && otherShip->isActive() && random(0, Constants::Random_RemoveEnemy) == 0) {

                        this->setActive(false);

                    }
                    else {

                        this->canTurn = true;
                        this->type = static_cast<EnemyType>(random(0,2));
                        this->frame = EnemyType::Single;

                        if (random(0, 2) == 0) {
                            this->pos = Constants::Landscape::MothershipMinPos;
                            this->movement = Movement::Right;
                        }
                        else {
                            this->pos = Constants::Landscape::MothershipMaxPos;
                            this->movement = Movement::Left;
                        }

                        switch (this->height) {

                            case Constants::Landscape::MothershipStartHeight:
                                break;

                            case Constants::Landscape::MothershipStartHeight + Constants::MothershipRowHeight:
                                this->height = Constants::Landscape::MothershipStartHeight;
                                break;

                            case Constants::Landscape::MothershipStartHeight + Constants::MothershipRowHeight + Constants::MothershipRowHeight:
                                this->height = Constants::Landscape::MothershipStartHeight;
                                break;

                            default:
                                this->height = this->height - Constants::MothershipRowHeight - Constants::MothershipRowHeight;
                                break;

                        }

                    }

                    break;                    

            }

        }

    public:

        void move(GameRotation gameRotation, GameMode gameMode, Player &player1) {

            move(gameRotation, gameMode, player1, nullptr);

        }

        void move(GameRotation gameRotation, GameMode gameMode, Player &player1, Mothership *othership) {

            this->move(gameRotation, gameMode, othership);

            switch (this->getMovement()) {

                case Movement::Down:

                    if (this->height < Constants::PlayerHeight && this->getPosDisplay() + Constants::MothershipHeight >= player1.getPos()) {

                        player1.setPos(this->getPosDisplay() + Constants::MothershipHeight);
                        player1.setBeingPushed(true);

                    }

                    break;

                case Movement::Up:

                    if (this->height < Constants::PlayerHeight && this->getPosDisplay() - Constants::PlayerHeight < player1.getPos()) {

                        player1.setPos(this->getPosDisplay() - Constants::PlayerHeight);
                        player1.setBeingPushed(true);

                    }

                    break;

                case Movement::Right:

                    if (this->height > Constants::ScreenHeight - Constants::PlayerHeight - Constants::MothershipHeight && this->getPosDisplay() + Constants::MothershipHeight >= player1.getPos()) {

                        player1.setPos(this->getPosDisplay() + Constants::MothershipHeight);
                        player1.setBeingPushed(true);

                    }

                    break;

                case Movement::Left:

                    if (this->height > Constants::ScreenHeight - Constants::PlayerHeight - Constants::MothershipHeight && this->getPosDisplay() - Constants::PlayerHeight < player1.getPos()) {

                        player1.setPos(this->getPosDisplay() - Constants::PlayerHeight);
                        player1.setBeingPushed(true);

                    }

                    break;

            }
        
        }


        void move(GameRotation gameRotation, GameMode gameMode, Player &player1, Player &player2) {

            move(gameRotation, gameMode, player1, player2, nullptr);

        }

        void move(GameRotation gameRotation, GameMode gameMode, Player &player1, Player &player2, Mothership *othership) {

            this->move(gameRotation, gameMode, othership);

            switch (this->getMovement()) {

                case Movement::Up:

                    if (this->height < Constants::PlayerHeight && this->getPosDisplay() - Constants::PlayerHeight <= player2.getPos()) {

                        player2.setPos(this->getPosDisplay() - Constants::PlayerHeight);
                        player2.setBeingPushed(true);

                        if (player2.getPos() - Constants::PlayerHeight <= player1.getPos()) {

                            player1.setPos(player2.getPos() - Constants::PlayerHeight);

                        }

                    }

                    break;

                case Movement::Down:

                    if (this->height < Constants::PlayerHeight && this->getPosDisplay() + Constants::MothershipHeight >= player1.getPos()) {

                        player1.setPos(this->getPosDisplay() + Constants::MothershipHeight);
                        player1.setBeingPushed(true);

                        if (player1.getPos() + Constants::PlayerHeight >= player2.getPos()) {

                            player2.setPos(player1.getPos() + Constants::PlayerHeight);

                        }

                    }

                    break;

                case Movement::Left:

                    if (this->height > Constants::ScreenHeight - Constants::PlayerHeight - Constants::MothershipHeight && this->getPosDisplay() - Constants::PlayerHeight <= player2.getPos()) {

                        player2.setPos(this->getPosDisplay() - Constants::PlayerHeight);
                        player2.setBeingPushed(true);

                        if (player2.getPos() - Constants::PlayerHeight <= player1.getPos()) {

                            player1.setPos(player2.getPos() - Constants::PlayerHeight);

                        }

                    }

                    break;

                case Movement::Right:

                    if (this->height > Constants::ScreenHeight - Constants::PlayerHeight - Constants::MothershipHeight && this->getPosDisplay() + Constants::MothershipHeight >= player1.getPos()) {

                        player1.setPos(this->getPosDisplay() + Constants::MothershipHeight);
                        player1.setBeingPushed(true);

                        if (player1.getPos() + Constants::PlayerHeight >= player2.getPos()) {

                            player2.setPos(player1.getPos() + Constants::PlayerHeight);

                        }

                    }

                    break;

            }

        }


        void moveTugOfWar(Player &player1, Player &player2) {

            this->move(GameRotation::Portrait, GameMode::TugOfWar, nullptr);

            switch (this->getMovement()) {

                case Movement::Up:

                    if (this->height < Constants::PlayerHeight && this->getPosDisplay() - Constants::PlayerWidth <= player1.getPos()) {
                        player1.setPos(this->getPosDisplay() - Constants::PlayerWidth);
                        player1.setBeingPushed(true);
                    }

                    if (this->height + Constants::MothershipHeight > Constants::ScreenWidth - Constants::PlayerHeight && this->getPosDisplay() - Constants::PlayerWidth <= player2.getPos()) {
                        player2.setPos(this->getPosDisplay() - Constants::PlayerWidth);
                        player2.setBeingPushed(true);
                    }

                    break;

                case Movement::Down:

                    if (this->height < Constants::PlayerHeight && this->getPosDisplay() + Constants::PlayerWidth >= player1.getPos()) {
                        player1.setPos(this->getPosDisplay() + Constants::PlayerWidth);
                        player1.setBeingPushed(true);
                    }

                    if (this->height + Constants::MothershipHeight > Constants::ScreenWidth - Constants::PlayerHeight && this->getPosDisplay() + Constants::PlayerWidth >= player2.getPos()) {
                        player2.setPos(this->getPosDisplay() + Constants::PlayerWidth);
                        player2.setBeingPushed(true);
                    }

                    break;

                default: break;

            }
        }


        void explode(int8_t rowAdjustment) {

            this->explosionCounter = Constants::MothershipExplosionMax;
            this->rowAdjustment = rowAdjustment;

        }


        int16_t getPosDisplay() { 

            return this->pos / 100; 

        }


        bool decCounter() {

            this->counter--;

            if (this->counter == 0) {
                this->counter = 80;
                this->wave++;
                return true;
            }
            
            return false;
            
        }


        void decExclamationCounter() {

            if (this->exclaimCounter > 0) this->exclaimCounter--;

        }

        
        void decHeight() {

            this->height = this->height - this->rowAdjustment;
            
        }


        void decPos(GameRotation gameRotation, GameMode gameMode) {

            this->pos = this->pos - this->getSpeed(gameRotation, gameMode);
            
        }


        void incPos(GameRotation gameRotation, GameMode gameMode) {

            this->pos = this->pos + this->getSpeed(gameRotation, gameMode);
            
        }


        void swapMovement() {

             switch (this->getMovement()) {

                case Movement::Up:

                    this->setMovement(Movement::Down);
                    break;

                case Movement::Down:

                    this->setMovement(Movement::Up);
                    break;

                case Movement::Left:

                    this->setMovement(Movement::Right);
                    break;

                case Movement::Right:

                    this->setMovement(Movement::Left);
                    break;

            }

            this->canTurn = false;

            this->exclaimCounter = 12;
            this->exclaimX = this->getPosDisplay() + ((this->movement == Movement::Left || this->movement == Movement::Up) ? 18 : -6);
            this->exclaimY = this->height;
            this->exclaimMovement = this->getMovement();

        }


        void reset(GameRotation gameRotation, int8_t rowAdjustment, EnemyType enemyType, bool active) {

            this->counter = Constants::MothershipCounterMax;
            this->rowAdjustment = rowAdjustment;
            this->wave = 0;
            this->canTurn = true;
            this->type = enemyType;
            this->active = active;

            switch (gameRotation) {

                case GameRotation::Portrait:     
                    this->movement = Movement::Down;   
                    this->pos = Constants::Portrait::MothershipMinPos;
                    this->height = Constants::Portrait::MothershipStartHeight;
                    break;
                    
                case GameRotation::Landscape:        
                    this->movement = Movement::Right;   
                    this->pos = Constants::Landscape::MothershipMinPos;
                    this->height = Constants::Landscape::MothershipStartHeight;
                    break;

            }

        }

};
