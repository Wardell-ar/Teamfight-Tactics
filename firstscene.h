#include "cocos2d.h"
USING_NS_CC;

//初始界面场景
class firstScene : public Scene
{
public:
    static Scene* createfirstScene() {
        return firstScene::create();
    }
    virtual bool init();
    CREATE_FUNC(firstScene);
};