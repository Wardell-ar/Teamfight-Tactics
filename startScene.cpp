#include "startScene.h"
#include "C:\Users\86130\Desktop\Github\startLayer.h"
USING_NS_CC;

Scene* startScene::createScene() {
	return startScene::create();   //ֱ�ӵ���create����
}

bool startScene::init() {
	if (!Scene::init()) {  //�������ʼ������
		return false;
	}
	auto startlayer = startLayer::createLayer();  //��ȡ��ʼ���泡���ĹҼ�
	addChild(startlayer);   //��ӹҼ���Ⱦ
	return true;
}
