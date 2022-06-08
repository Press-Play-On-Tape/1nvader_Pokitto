#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Constants.h"
#include "Enums.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		uint16_t highScore[3];
		GameMode gameMode;
		GameRotation gameRotation;
		uint8_t levelLock[3];
		SoundEffects sfx;

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			this->sfx = SoundEffects::Both;
			
			this->highScore[0] = 0;
			this->highScore[1] = 0;
			this->highScore[2] = 0;
			this->gameMode = GameMode::Single;
			this->gameRotation = GameRotation::Landscape;
			this->levelLock[0] = 1;	//SJH
			this->levelLock[1] = 1;	//SJH
			this->levelLock[2] = 1; //SJH

			this->saveCookie();

		}


		/* -----------------------------------------------------------------------------
		*   Get score. 
		*/
		uint16_t getScore(GameMode mode) {

			return this->highScore[static_cast<uint8_t>(mode)];

		}


		/* -----------------------------------------------------------------------------
		*   Save score ..
		*/
		void saveScore(GameMode mode, uint16_t score) {

			uint16_t oldScore = this->getScore(mode);
	
			if (oldScore < score) {

				this->highScore[static_cast<uint8_t>(mode)] = score;

			}

		}


		/* -----------------------------------------------------------------------------
		*   Get mode. 
		*/
		GameMode getMode() {

			return this->gameMode;

		}


		/* -----------------------------------------------------------------------------
		*   Save mode ..
		*/
		void saveMode(GameMode mode) {

			this->gameMode = mode;

		}


		/* -----------------------------------------------------------------------------
		*   Get rotation. 
		*/
		GameRotation getRotation() {

			return this->gameRotation;

		}


		/* -----------------------------------------------------------------------------
		*   Save rotation ..
		*/
		void saveRotation(GameRotation rotation) {

			this->gameRotation = rotation;
			
		}

		/* -----------------------------------------------------------------------------
		*   Get level. 
		*/
		uint8_t getLevel(uint8_t level) {

			return this->levelLock[level];

		}


		/* -----------------------------------------------------------------------------
		*   Save level ..
		*/
		void saveLevel(uint8_t level, uint8_t value) {

			this->levelLock[level] = value;

		}

};