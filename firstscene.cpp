#include"firstsceneLayer.h"
#include"firstscene.h"

bool firstScene::init() {
    if (!Scene::init()) {  //若父类初始化有误
        return false;
    }
    auto firstscenelayer = firstsceneLayer::createLayer();  //获取初始界面场景的挂件
    addChild(firstscenelayer);   //添加挂件渲染,添加layer
    auto shoplayer = ShopLayer::createShopLayer();  //获取初始界面场景的挂件
    addChild(shoplayer);   //添加挂件渲染,添加layer
    return true;
}
