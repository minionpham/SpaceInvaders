#ifndef APPLICATION_USER_SRC_GAME_HPP_
#define APPLICATION_USER_SRC_GAME_HPP_
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

class Game {
public:
	uint16_t score = 0;
	uint8_t diff = 0;
	Ship ship;
	Game();
	virtual ~Game();
	void update();
	void updateScore(short score);
	void updateDiff(short diff);
};

#endif /* APPLICATION_USER_SRC_GAME_HPP_ */
