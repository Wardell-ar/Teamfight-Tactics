#include "cocos2d.h"
USING_NS_CC;

class firstsceneLayer : public Layer
{
public:
	//初始化
	static Layer* createLayer() {
		return firstsceneLayer::create();  //直接调用create方法
	}
	virtual bool init();
	CREATE_FUNC(firstsceneLayer);

};