#pragma once

#include "Pokitto.h"
#include <LibAudio>
#include <LibSchedule>
#include "images/Images.h"
#include "utils/Constants.h"
#include "utils/Enums.h"
#include "utils/Structs.h"
#include "utils/GameCookie.h"
#include "entities/Entities.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;


class Game {

    private:

        TitleScreenVars titleScreenVars;
        SplashScreenVariables splashScreenVariables;
        GameOverScreenVars gameOverScreenVars;
        GamePlayVars gamePlayVars;
        Particle particles[Constants::ParticlesMax];

        GameCookie *cookie;
        GameStats gameStats;

        Player player1;
        Player player2;
        Mothership mothership;
        Bomb bomb;

        File mainThemeFile;

        GameState gameState = GameState::Splash_Init;


    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen_Init();
        void splashScreen();
        void game_Init();
        void game();
        void title_Init();
        void title();
        void renderPlayerSelection(bool renderPlayerSelection);
        void renderScores(bool flashPlayer1, bool flashPlayer2);
        void renderScore(uint8_t location, uint8_t height, uint16_t score);
        void renderScoreTugOfWar(uint16_t score1, uint16_t score2);

        void movePlayer(Player &player, Player &otherPlayer);
        void movePlayer1();
        void moveBullet(Player &player);
        void moveBomb();

        void tugOfWar_Init();
        void tugOfWar();

        void gameOver_Init();
        void gameOver();

        void launchParticles(GameRotation gameRotation);
        void launchParticles(GameRotation gameRotation, int16_t x, int16_t y);
        void updateAndRenderParticles(GameRotation gameRotation);

        void playTheme();
        void muteTheme();
        void playSoundEffect(SoundEffect soundEffect);

        void renderSceneryPortrait();
        void renderScenery(GameMode gameMode, bool hideCentreline);
        void renderHighScore(GameMode gameMode, bool centre);
        void renderInvaderSign();
        bool collide(Rect rect1, Rect rect2);
};

