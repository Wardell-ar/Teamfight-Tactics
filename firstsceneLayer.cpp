#include"firstsceneLayer.h"

bool firstsceneLayer::init() {
	if (!Layer::init()) {   //�������ʼ������
		return false;
	}
	auto Background = Sprite::create("map1.png");
	Background->setPosition(960, 540);
	this->addChild(Background, 0);//��ӱ���ͼ
	return true;
}