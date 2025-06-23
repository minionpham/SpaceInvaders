#include "Entity.hpp"

Entity::Entity() {
	// TODO Auto-generated constructor stub
	this->displayStatus = IS_HIDDEN;
	this->width = 32;
	this->height = 32;
}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

bool Entity::update() {
	// TODO Auto-generated destructor stub
	return false;
}

void Entity::updateDisplayStatus(uint8_t status) {
	this->displayStatus = status;
}
void Entity::updateCoordinate(uint16_t x, uint16_t y) {
	this->coordinateX = x;
	this->coordinateY = y;
}

void Entity::updateVelocity(uint16_t x, uint16_t y) {
	this->velocityX = x;
	this->velocityY = y;
}

bool Entity::isCollide(Entity &a, Entity &b) {
    // Kiểm tra va chạm theo chiều ngang (giữ nguyên)
    bool collideX = (a.coordinateX + a.width > b.coordinateX) && (b.coordinateX + b.width > a.coordinateX);

    // Tính toán trung tâm theo chiều dọc của mỗi đối tượng
    int centerY_a = a.coordinateY + a.height / 2;
    int centerY_b = b.coordinateY + b.height / 2;

    // Kiểm tra va chạm theo chiều dọc trong phạm vi 10 pixel từ trung tâm mỗi đối tượng
    bool collideY = (centerY_a - 5 < centerY_b + 5) && (centerY_a + 5 > centerY_b - 5);

    // Trả về kết quả kiểm tra va chạm tổng thể
    return collideX && collideY;
}




