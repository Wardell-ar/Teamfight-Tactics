# Teamfight-Tactics
同济大学2022本科生大二期末项目-金铲铲之战（Teamfight-Tactics）

2020/12/19 许扬扬

/*设置和整体背景音乐效果实现*/

GameSettings.h       ----游戏设置头文件
GameSettings.cpp     ----游戏设置cpp文件
为Layer类 需贴图 位置放置为


添加的代码如下：

startLayer.h：
类中添加函数：
  void callbackof_set(Ref* pSender);  //设置

startLayer.cpp中：
添加函数：
  void startLayer::callbackof_set(Ref* pSender)   //创建房间
  {
	Director::getInstance()->pushScene(gamesettings);   //压栈
  }
  auto audio = SimpleAudioEngine::getInstance();
  audio->playBackgroundMusic("Bgm1.mp3", true);
  auto set1 = Sprite::create("SetButton2.png");
  auto set2 = Sprite::create("SetButton1.png");
  auto _set = MenuItemSprite::create(set1, set2,
	CC_CALLBACK_1(startLayer::callbackof_set, this));
  auto SET = Menu::create(_set, NULL);
  SET->setPosition(1795, 990);
  this->addChild(SET, 3);
删除内容：
删除退出按键（退出游戏的按钮已放入设置界面）

游戏界面Layer.h中：
类中添加函数：
  void callbackof_set(Ref* pSender);  //设置

游戏界面Layer.cpp中：
添加函数：
  void startLayer::callbackof_set(Ref* pSender)   //创建房间
  {
	auto gamesettings = GameSettings::createScene(); //设置
	Director::getInstance()->pushScene(gamesettings);   //压栈
  }


/*游戏界面上方时间倒计时进度条（只实现进度条呈现）*/

游戏界面Layer.cpp中：
init()添加代码：
	auto to1 = Sequence::createWithTwoActions(ProgressTo::create(6, 100), ProgressTo::create(0, 100));
	auto progress0 = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("progresstimer0.png"));
	auto progress1 = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("progresstimer1.png"));
	progress0->setType(cocos2d::ProgressTimer::Type::BAR);
	progress0->setMidpoint(cocos2d::Vec2(0, 0.5));// 设置起始点为左边中点
	progress0->setBarChangeRate(cocos2d::Vec2(1, 0)); // 设置只在水平方向改变
	progress0->setPercentage(100); // 设置初始百分比为 0%
	progress1->setType(cocos2d::ProgressTimer::Type::BAR);
	progress1->setMidpoint(cocos2d::Vec2(0, 0.5));// 设置起始点为左边中点
	progress1->setBarChangeRate(cocos2d::Vec2(1, 0)); // 设置只在水平方向改变
	progress1->setPercentage(0); // 设置初始百分比为 0%
	// 设置进度条位置
	progress0->setPosition(960, 1000);
	progress1->setPosition(960, 1000);
	progress1->runAction(Repeat::create(to1,1));
	// 添加进度条到场景
	this->addChild(progress0, 1);
	this->addChild(progress1, 2);


2023/12/23 许扬扬

实现了在vscode中用nodejs搭建一个简易的服务器，并在cocos2d中实现了连接。

后来使用C++在VS上搭建了一个服务器，nodejs版可当作备选。

下载websocketpp库（0.8.2） 下载boost（32）
搭建环境
在vs中实现服务器的搭建
IP地址为我的计算机IPv4地址 端口为9002
在http://www.websocket-test.com/网站测试成功
实现不同计算机连接到同一个ip地址


2023/12/24 许扬扬

在main()函数中实现服务器搭建

创建房间的场景切换

服务器的信息分配实现


2023/12/25 许扬扬

更新了服务器代码。
完成了客户端的初步搭建，还需完善传输的数据以及在游戏进程中应该调用的位置。

2023/12/26 许扬扬

完成了客户端的测试。将客户端放到了一个类里，类放到一个单独的Online.cpp和Online.h文件中。

2023/12/30
客户端、服务器的大更新。