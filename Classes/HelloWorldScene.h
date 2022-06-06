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

	int nNum;


	int BulletNum;
	int OutBullet;
	int pBulletPosX;
	int pBulletPosY;

	bool isGameOver;
	bool isSkillTrue;
	bool isSkillCollTime;
	int SkillCool;
	int SkillDuration;
	//float PlayerPosX;
	//float PlayerPosY;
public:


	static cocos2d::Scene* createScene();
	int mytime;
	int highscore;
	int ThisScore;
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	void myTick(float delta);
	void callEveryFrame(float f);

	cocos2d::Sprite* pEnemy;
	cocos2d::Sprite* pBullet;
	cocos2d::Label* time_label;
	void createBullet();
	void GameOverCheck();

	void SkillCallBack(cocos2d::Ref* pSender);
	Vector<Sprite*>peas;

	void changeGameOverScene();


};

#endif // __HELLOWORLD_SCENE_H__
