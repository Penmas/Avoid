#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
using namespace cocos2d;
#include "Joystick.h"
USING_NS_CC;

class MenuScene : public cocos2d::Scene
{
	Size visibleSize;
	Vec2 origin;
	
public:

	int Score1st;
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void changeScene(Ref *sender);
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);


};

#endif // __HELLOWORLD_SCENE_H__
