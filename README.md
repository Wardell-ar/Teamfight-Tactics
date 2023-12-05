# Teamfight-Tactics
同济大学2022本科生大二期末项目-金铲铲之战（Teamfight-Tactics）
本文档运行方法：
1、将python、cocos、cmake都配置好后，用 cocos new 任意名字 -l cpp任意新建一个文档（假设命名为jcc）
2、jcc文件夹下，打开proj.win32目录下的sln文件，先运行程序，确保程序能正确运行
3、将fetch得到的文件里的Resource替换jcc文件夹里的Resource
4、在左侧资源管理器的class目录里，删掉所有cpp和h。然后点击class的添加现有项，在fetch得到的文件里选择AppDelegate.cpp\AppDelegate.h\startScene.h\startScene.cpp等四个文件
5、在左侧资源管理器的proj.win32目录下，选择添加现有项，在fetch得到的文件里选择helpLayer.cpp\helpLayer.h\helpScene.cpp\helpScene.h\startLayer.h\startLayer.cpp等六个文件
6、打开AppDelegate.cpp，将第二行改为自己fetch得到的文件里的startScene.h路径
7、打开startScene.cpp，将第二行改为自己fetch得到的文件里的startLayer.h路径
8、运行程序
注意：1—5步只有第一次需进行，后序修改时只需要在fetch后进行6——8步