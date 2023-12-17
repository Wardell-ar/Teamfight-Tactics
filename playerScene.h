#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"playerlistLayer.h"
#include"storeLayer.h"
#include"playerroleLayer.h"
#include"hero1.h"

USING_NS_CC;

/*
  put a chessboard photo(include preparation seat and chessboard)
  set a menu (option) to exit the game or stop the music

  func:
  the move of the player role
*/
class playerScene : public Scene
{
	
	

public:
	chessboardSeat seat1;   //����λ��
	preparationSeat seat2;   //��սϯλ��


	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(playerScene);
};

