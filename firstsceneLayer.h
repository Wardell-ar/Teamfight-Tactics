#include "cocos2d.h"
USING_NS_CC;

class firstsceneLayer : public Layer
{
public:
	//��ʼ��
	static Layer* createLayer() {
		return firstsceneLayer::create();  //ֱ�ӵ���create����
	}
	virtual bool init();
	CREATE_FUNC(firstsceneLayer);

};