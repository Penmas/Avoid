#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

#define PLAYER	0

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
	//�÷��̾� ���� �������̽� ���
	auto Back = Sprite::create("joystick_Inter_back.png");
	Back->setAnchorPoint(Vec2(0.5, 0));
	Back->setPosition(Vec2(visibleSize.width / 2, 0));
	Back->setScaleY(0.7);
	Back->setZOrder(2);
	this->addChild(Back);



	//�÷��̾� ĳ����
	spr = Sprite::create("cid_icon4.png");
	spr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	spr->setTag(PLAYER);
	spr->setZOrder(1);
	this->addChild(spr);


	//�Ѿ�
	this->createBullet();
	//�Ѿ˻���
	this->schedule(schedule_selector(HelloWorld::myTick));




	//���̽�ƽ
	joystick = Joystick::create();
	joystick->setMainChar(spr);
	joystick->setSpeed(0.1f);
	joystick->setLimitScreen(true);
	joystick->setTouchShow(true);
	joystick->setZOrder(3);
	this->addChild(joystick);




	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::createBullet()
{ 
	auto player = (Sprite*)getChildByTag(PLAYER);
	srand(time(NULL));
	int pBulletX = rand() % ((int)visibleSize.width - 10);
	int pBulletY = rand() % ((int)visibleSize.height + 500);

	pBullet = Sprite::create("Bullet.png");
	pBullet->setPosition(Vec2(pBulletX, pBulletY));
	pBullet->setScale(0.5);
	this->addChild(pBullet);
	auto myActionForward = MoveBy::create(2, Vec2((player->getPosition().x - pBulletX) * 2, (player->getPosition().y - pBulletY) * 2));
	auto myAction = Sequence::create(Place::create(Vec2(pBulletX, pBulletY)), myActionForward, nullptr);
	auto rep = RepeatForever::create(myAction);
	pBullet->runAction(rep);
}

//�����췯�ݹ��Լ�
void HelloWorld::myTick(float f) 
{
	if (pBullet== nullptr) 
	{
		//log("pBulletis null!");
		this->createBullet();		//�Ѿ˾��������
		return;
	}
	
	if (pBullet->getBoundingBox().intersectsRect(spr->getBoundingBox())) 
	{
		//�浹�ϸ�
		// �浹�����������غ���(Ȯ���ϰ��浹�Ѱ�������)
		// �浹�ϸ��������÷����̺�����������
		log("GameOver");
		pBullet->removeFromParentAndCleanup(true);
		//�Ѿ�����
		pBullet= nullptr;		//�����ð�����̾�����������ü���������������Ƿιݵ��nullptr��ó���ؾ߻��λ����̵ɼ�����
		// this->removeChild(pBullet); // (Cleanup =true) default
	}
}