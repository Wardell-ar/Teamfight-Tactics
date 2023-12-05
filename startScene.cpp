#include "startScene.h"
#include "C:\Users\86130\Desktop\Github\startLayer.h"
USING_NS_CC;

Scene* startScene::createScene() {
	return startScene::create();   //直接调用create方法
}

bool startScene::init() {
	if (!Scene::init()) {  //若父类初始化有误
		return false;
	}
	auto startlayer = startLayer::createLayer();  //获取初始界面场景的挂件
	addChild(startlayer);   //添加挂件渲染
	return true;
}
