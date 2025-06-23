#include "Game.hpp"

Game::Game() {

}

Game::~Game() {
}

void Game::updateScore(short score) {
	this->score += score;
}

void Game::updateDiff(short diff) {
	this->diff = diff;
}

void Game::update() {
}

