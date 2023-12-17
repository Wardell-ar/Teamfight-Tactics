#include "hero1.h"

Layer* hero1::createLayer() {
	return hero1::create();
}


bool hero1::init() {
	if (!Layer::init()) {
		return 0;
	}

	auto hero = Sprite::create("playerrole.png");
	this->addChild(hero, 0, HEROTAG);
	hero->setScale(0.25);

	return 1;
}