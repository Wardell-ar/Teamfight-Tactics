#include "cocos2d.h"
USING_NS_CC;

//��ʼ���泡��
class startScene : public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(startScene);

    void get_position(Event* event);
};
