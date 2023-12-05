#include"firstsceneLayer.h"

bool firstsceneLayer::init() {
	if (!Layer::init()) {   //若父类初始化出错
		return false;
	}
	auto Background = Sprite::create("map1.png");
	Background->setPosition(960, 540);
	this->addChild(Background, 0);//添加背景图
	return true;
}