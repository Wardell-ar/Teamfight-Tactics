#include "playerroleLayer.h"


playerroleLayer* playerroleLayer::createLayer(int c) {
	playerroleLayer* role = new playerroleLayer;
	if (role) {  //��������ɹ�
		role->autorelease();
		role->camp = c;
		if(c)  //�ҷ�ССӢ��
		{
			auto sprite = Sprite::create("playerrole.png");
			role->addChild(sprite, 0, ROLETAG);
			sprite->setPosition(471 + 70, 362 + 50);
			sprite->setScale(0.25);
			role->cur_position = Vec2(471 + 70, 362 + 50);

			auto bloodbar1 = Sprite::create("bloodbar1.png");
			auto bloodbar0 = Sprite::create("bloodbar0.png");

			role->healthBar = ProgressTimer::create(bloodbar1);
			role->healthBar->setType(ProgressTimer::Type::BAR);
			role->healthBar->setMidpoint(Vec2(0, 0.5));
			role->healthBar->setBarChangeRate(Vec2(1, 0));
			// �� healthBar ��ӵ� mySprite ��
			sprite->addChild(role->healthBar, 1);
			sprite->addChild(bloodbar0, 0);
			role->healthBar->setPosition(200, 400);
			bloodbar0->setPosition(200, 400);
			// ����Ѫ����ʼ����
			role->healthBar->setPercentage(100);  //��Ѫ
		}
		else {  //�з�ССӢ��
			auto sprite = Sprite::create("playerrole.png");
			role->addChild(sprite, 0, ROLETAG);
			sprite->setPosition(1214 + 70, 800 + 50);
			sprite->setScale(0.25);
			role->cur_position = Vec2(1214 + 70, 800 + 50);

			auto bloodbar1 = Sprite::create("bloodbar11.png");
			auto bloodbar0 = Sprite::create("bloodbar0.png");
			bloodbar1->setColor(Color3B::RED);
			role->healthBar = ProgressTimer::create(bloodbar1);
			role->healthBar->setType(ProgressTimer::Type::BAR);
			role->healthBar->setMidpoint(Vec2(0, 0.5));
			role->healthBar->setBarChangeRate(Vec2(1, 0));
			// �� healthBar ��ӵ� mySprite ��
			sprite->addChild(role->healthBar, 1);
			sprite->addChild(bloodbar0, 0);
			role->healthBar->setPosition(200, 400);
			bloodbar0->setPosition(200, 400);
			// ����Ѫ����ʼ����
			role->healthBar->setPercentage(100);  //��Ѫ
		}




		return role;
	}

	CC_SAFE_DELETE(role);
	return nullptr;
}