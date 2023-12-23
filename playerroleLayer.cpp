#include "playerroleLayer.h"

playerroleLayer* smallhero;

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


	healthBar = ProgressTimer::create(Sprite::create("bloodbarred.png"));
	healthBar->setType(ProgressTimer::Type::BAR);
	healthBar->setMidpoint(Vec2(0, 0.5));
	healthBar->setBarChangeRate(Vec2(1, 0));
	healthBar->setScaleX(0.7);
	// �� healthBar ��ӵ� mySprite ��
	role->addChild(healthBar);
	healthBar->setPosition(Vec2(healthBar->getPositionX() + 250, healthBar->getPositionY() + 400));

	// ����Ѫ����ʼ����
	healthBar->setPercentage(roleHP);


	return true;
}

void playerroleLayer::updateblood() {
	healthBar->setPercentage(roleHP);
}

int playerroleLayer::roleHPreturn() {
	return roleHP;
}

