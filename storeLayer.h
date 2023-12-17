#include"cocos2d.h"
USING_NS_CC;

/*
  there are totally 6 menuitem in this layer
  the first one is used to upgrade
  the second one is used to refresh the store
  the left 4 is the photo of the roles(the key items of the store)

  we use a position array to save the position of the 4 roles' position
  it will be convinent for us to refresh the store and reset the roles' photo
*/

class storeLayer : public Layer
{

public:
	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(storeLayer);
};

