#include "helpScene.h"
#include"helpLayer.h"
USING_NS_CC;

Scene* helpScene::createScene() {
	return helpScene::create();
}

bool helpScene::init() {
	if (!Scene::init()) {  //若父类初始化出错
		return false;
	}

	//将挂件挂到场景上
	auto layer = helpLayer::createLayer();  
	this->addChild(layer);
	return true;
}