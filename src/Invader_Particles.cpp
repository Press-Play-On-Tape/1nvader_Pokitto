#include "Invader.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"
#include "utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::launchParticles(GameRotation gameRotation) {

    switch (gameRotation) {

        case GameRotation::Portrait:
            launchParticles(gameRotation, Constants::ScreenHeight / 2, Constants::ScreenWidth / 2);
            break;

        case GameRotation::Landscape:
            launchParticles(gameRotation, Constants::ScreenWidth / 2, Constants::ScreenHeight / 2);
            break;

    }

}

void Game::launchParticles(GameRotation gameRotation, int16_t x, int16_t y) {

    for (int i = 0; i < Constants::ParticlesMax; i++) {

        particles[i].setX(x);
        particles[i].setY(y);
        particles[i].setVelX(random(-4, 5));
        particles[i].setVelY(random(-1, 6));
        particles[i].setCounter(random(10, 46));
        particles[i].setSize(random(1, 3));
        particles[i].setRotation(gameRotation);
    
    }

}

void Game::updateAndRenderParticles(GameRotation gameRotation) {

    for ( int i = 0; i < Constants::ParticlesMax; i++) {

        particles[i].update();

        if ( particles[i].render() ) { // the dot should be rendered

            int pSize = particles[i].getSize();

            switch (gameRotation) {

                case GameRotation::Portrait:

                    if (pSize == 1) {

                        PD::setColor(7);
                        PD::drawPixel(particles[i].getY(), particles[i].getX());

                    } 
                    else {

                        PD::setColor(7);
                        PD::drawRect(particles[i].getY(), particles[i].getX(), pSize, pSize);

                    }

                    break;

                case GameRotation::Landscape:

                    if (pSize == 1) {

                        PD::setColor(7);
                        PD::drawPixel( particles[i].getX(), particles[i].getY());

                    } 
                    else {

                        PD::setColor(7);
                        PD::drawRect( particles[i].getX(), particles[i].getY(), pSize, pSize);

                    }

                    break;
                    
            }

        }

    }

}
