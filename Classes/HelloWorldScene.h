#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
using namespace cocos2d;
#include "Joystick.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
	Size visibleSize;
	Vec2 origin;
	Sprite* spr;
	Joystick* joystick;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


};

#endif // __HELLOWORLD_SCENE_H__