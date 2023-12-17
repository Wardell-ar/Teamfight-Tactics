#include "playerroleLayer.h"


Layer* playerroleLayer::createLayer() {
	return playerroleLayer::create();
}

bool playerroleLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto role = Sprite::create("playerrole.png");
	this->addChild(role, 0, ROLETAG);
	role->setPosition(955, 540);
	role->setScale(0.25);

	//»¹²îÑªÌõÏÔÊ¾

	return true;
}