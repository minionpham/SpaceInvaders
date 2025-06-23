#ifndef APPLICATION_USER_SRC_ENEMY_HPP_
#define APPLICATION_USER_SRC_ENEMY_HPP_
#include "Entity.hpp"
const uint8_t MAX_ENEMY = 20;

class Enemy: public Entity {
public:
	int MOVE_RATE = 800;
	int FIRE_RATE = 30000;
	Enemy();
	virtual ~Enemy();
	bool update(uint8_t dt);
	bool updateBullet(uint8_t dt);
};

#endif /* APPLICATION_USER_SRC_ENEMY_HPP_ */
