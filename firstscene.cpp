#include"firstsceneLayer.h"
#include"firstscene.h"

bool firstScene::init() {
    if (!Scene::init()) {  //�������ʼ������
        return false;
    }
    auto firstscenelayer = firstsceneLayer::createLayer();  //��ȡ��ʼ���泡���ĹҼ�
    addChild(firstscenelayer);   //��ӹҼ���Ⱦ,���layer
    return true;
}
