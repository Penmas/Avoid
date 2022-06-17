#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

class GameOverScene : public cocos2d::Scene
{
	Size visibleSize;
	Vec2 origin;
	int thisGameTime;
	int Score[5] = { 0, };
	int ScoreSpace;

public:
	int audio2;
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);

	void GameReStart(cocos2d::Ref* pSender);
	void MenuBack(cocos2d::Ref* pSender);


};

#endif // __HELLOWORLD_SCENE_H__
