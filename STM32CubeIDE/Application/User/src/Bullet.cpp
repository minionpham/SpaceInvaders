#include "Bullet.hpp"

Bullet::Bullet() {
	this->width = 16;
	this->height = 34;
	this->displayStatus = IS_HIDDEN;
	this->velocityX = 0;
	this->velocityY = 0;
	this->moveRate = MOVE_RATE;
}

Bullet::~Bullet() {

}

bool Bullet::update(uint8_t dt) {
	if(this->coordinateX < -this->width || this->coordinateX > 240 ||
			this->coordinateY < -this->height || this->coordinateY > 320) {
		this->displayStatus = SHOULD_HIDE;
		this->moveRate = MOVE_RATE;
		return false;
	}
	this->moveRate -= dt;
	if(this->moveRate > 0) return false;
	this->coordinateX += this->velocityX;
	this->coordinateY += this->velocityY;
	this->moveRate = MOVE_RATE;
	return true;
}

