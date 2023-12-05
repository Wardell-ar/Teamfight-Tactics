# Teamfight-Tactics
同济大学2022本科生大二期末项目-金铲铲之战（Teamfight-Tactics）
本文档运行方法：
1、将python、cocos、cmake都配置好后，用 cocos new 任意名字 -l cpp任意新建一个文档（假设命名为jcc）
2、jcc文件夹下，打开proj.win32目录下的sln文件，先运行程序，确保程序能正确运行
3、将fetch得到的文件里的Resource替换jcc文件夹里的Resource
4、在左侧资源管理器的class目录里，删掉所有cpp和h。然后点击class的添加现有项，在fetch得到的文件里选择AppDelegate.cpp\AppDelegate.h\startScene.h\startScene.cpp等四个文件
5.在左侧资源管理器的proj.win32目录下，选择添加现有项，在fetch得到的文件里选择helpLayer.cpp\helpLayer.h\helpScene.cpp\helpScene.h\startLayer.h\startLayer.cpp等六个文件
6.运行程序