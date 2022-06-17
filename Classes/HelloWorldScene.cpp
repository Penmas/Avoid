#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "audio/include/AudioEngine.h"


USING_NS_CC;
using namespace experimental;
#define PLAYER		0
#define SHIELD		2
#define COOL		3
#define COOLING		4
#define SKILL		5
#define PARTICLE	10


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
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	srand(time(NULL));
	peas.clear();

	//�÷��̾� ���� �������̽� ���
	auto Back = Sprite::create("joystick_Inter_back.png");
	Back->setAnchorPoint(Vec2(0.5, 0));
	Back->setPosition(Vec2(visibleSize.width / 2, 0));
	Back->setScaleY(0.7);
	Back->setZOrder(2);
	this->addChild(Back);

	//�ð������
	this->schedule(schedule_selector(HelloWorld::callEveryFrame), 1.0f);


	//�÷��̾� ĳ����
	spr = Sprite::create("cid_icon4.png");
	spr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	spr->setTag(PLAYER);
	spr->setScale(0.8f);
	spr->setZOrder(1);
	this->addChild(spr);

	//���ӿ��� ����Ʈ
	auto particle = ParticleExplosion::create();
	if (isGameOver)
	{
		this->addChild(particle);
	}

	//�Ѿ�
	this->createBullet();
	//�Ѿ˻���
	this->schedule(schedule_selector(HelloWorld::myTick));




	//���̽�ƽ
	joystick = Joystick::create();
	joystick->setMainChar(spr);
	joystick->setSpeed(0.18f);
	joystick->setLimitScreen(true);
	joystick->setTouchShow(true);
	joystick->setZOrder(3);
	this->addChild(joystick);

	//Ÿ�̸�
	time_label = Label::createWithTTF(" 00:00 ", "fonts/NANUMSQUAREROUNDEB.TTF", 40);
	time_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 30)); //ȭ���߾ӻ��
	time_label->setColor(Color3B::RED);

	this->addChild(time_label);
	mytime = 0;

	//��ų
	auto SkillButton = MenuItemImage::create("Skill.png", "Skill.png", "Skill.png", CC_CALLBACK_1(HelloWorld::SkillCallBack, this));
	SkillButton->setAnchorPoint(Vec2(0.5, 0.5));
	SkillButton->setScale(2);
	auto Skill = Menu::create(SkillButton, NULL);
	Skill->alignItemsVertically();
	Skill->setPosition(Vec2(visibleSize.width - 180, 130));
	Skill->setZOrder(3);
	Skill->setTag(SKILL);
	this->addChild(Skill);


	//auto listener = EventListenerTouchOneByOne::create(); //�̺�Ʈ�����ʻ���
	//listener->setSwallowTouches(true);
	//listener->onTouchBegan= CC_CALLBACK_2(HelloWorld::onTouchBegan, this);//�ʿ����ݹ��Լ����
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	audio1 = AudioEngine::play2d("sound/InPlay.mp3", true, 0.2f); 

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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto player = (Sprite*)getChildByTag(PLAYER);


	int BulletPos = (rand() % 4) + 1;
	int pBulletX, pBulletY;

	//�Ѿ� ������ ��ġ ����
	if (BulletPos == 1)	//����
	{
		//srand(time(NULL));
		pBulletX = -10;
		pBulletY = (rand() % 650) + 300;
		//pBulletY = (rand() % ((int)visibleSize.height - 290)) + 300;
		log("����");
	}
	else if (BulletPos == 2)//�ϴ�
	{
		//srand(time(NULL));
		//pBulletX = (rand() % ((int)visibleSize.width + 10)) -10;
		pBulletX = (rand() % 520) - 10;
		pBulletY = 250;
		log("�ϴ�");
	}
	else if (BulletPos == 3)//����
	{
		//srand(time(NULL));
		pBulletX = visibleSize.width + 10;
		//pBulletY = (rand() % ((int)visibleSize.height - 290)) + 300;
		pBulletY = (rand() % 650) + 300;
		log("����");
	}
	else if (BulletPos == 4)//���
	{
		//srand(time(NULL));
		//pBulletX = (rand() % ((int)visibleSize.width + 10)) - 10;
		pBulletX = (rand() % 520) - 10;
		pBulletY = visibleSize.height + 10;
		log("���");
	}



	pBullet = Sprite::create("Bullet.png");
	pBullet->setPosition(Vec2(pBulletX, pBulletY));
	pBullet->setScale(0.2);
	this->addChild(pBullet);
	//auto myActionForward = MoveBy::create(2000, Vec2((player->getPosition().x - pBulletX)*1000, (player->getPosition().y - pBulletY)*1000));


	//�Ѿ� Ÿ�� ��ġ ����	
	float vecX = (player->getPosition().x - pBulletX);
	float vecY = (player->getPosition().y - pBulletY);
	float time = sqrt((vecX * vecX) + (vecY * vecY));



	auto myActionForward = MoveBy::create(time * 3.0f
		, Vec2((player->getPosition().x - pBulletX) * 1000, (player->getPosition().y - pBulletY) * 1000));
	auto myAction = Sequence::create(Place::create(Vec2(pBulletX, pBulletY)), myActionForward, nullptr);
	auto rep = RepeatForever::create(myAction);
	pBullet->runAction(rep);

	peas.pushBack(pBullet);
}

//�����췯�ݹ��Լ�
void HelloWorld::myTick(float f)
{

	auto player = (Sprite*)getChildByTag(PLAYER);
	if (OutBullet < BulletNum)
	{
		//log("pBulletis null!");
		this->createBullet();		//�Ѿ˾��������
		OutBullet++;
		//return;

	}


	//�Ѿ� �ٿ���ڽ� �ν� & �Ѿ� ���� ����� ����
	Rect location = player->getBoundingBox();

	for (int i = 0; i < peas.size(); i++)
	{
		auto spr = (Sprite*)peas.at(i);
		Rect rect = spr->getBoundingBox();
		float BulletPosX = spr->getPosition().x;
		float BulletPosY = spr->getPosition().y;

		if (rect.intersectsRect(location))
		{
			this->removeChild(spr);
			peas.eraseObject(spr);
			OutBullet--;
			if (!isSkillTrue)
			{
				log("���� ����");
				GameOverAudio1 = AudioEngine::play2d("sound/GameOver.mp3", false, 0.1f);
				AudioEngine::stop(audio1);
				isGameOver = true;
				changeGameOverScene();
			}
			
		}

		if (BulletPosX >= 800 || BulletPosX <= -150 || BulletPosY >= 1000 || BulletPosY <= 200)
		{
			this->removeChild(spr);
			peas.eraseObject(spr);
			//spr->removeFromParentAndCleanup(true);
			OutBullet--;
			log("�Ѿ� ���� ���");
		}



	}


}


void HelloWorld::callEveryFrame(float f)
{
	mytime++;
	if (isGameOver)
	{
		GameOverWaitingTime++;
	}
	//log("�ð� : %d", nNum);
	if (mytime < 10)
	{
		time_label->setString(StringUtils::format("00:0%d", mytime));
	}
	else if (mytime < 60)
	{
		time_label->setString(StringUtils::format("00:%d", mytime));
	}
	else if (mytime < 600 && (mytime % 60 < 10))
	{
		time_label->setString(StringUtils::format("0%d:0%d", mytime / 60, mytime % 60));
	}
	else if (mytime < 600 && (mytime % 60 > 10))
	{
		time_label->setString(StringUtils::format("0%d:%d", mytime / 60, mytime % 60));
	}
	else if (mytime >= 600 && (mytime % 60 > 10))
	{
		time_label->setString(StringUtils::format("0%d:%d", mytime / 60, mytime % 60));
	}
	else if (mytime >= 600 && (mytime % 60 < 10))
	{
		time_label->setString(StringUtils::format("0%d:%d", mytime / 60, mytime % 60));
	}

	if ((mytime % 3) == 0)
	{
		BulletNum++;
	}

	if (isSkillCoolTime)
	{
		SkillCool++;
		SkillDuration++;

		if (SkillCool >= 3) // ���ӽð�
		{
			isSkillTrue = false;
			log("��ų ����");
			spr->removeChildByTag(SHIELD);
		}

		if (SkillCool >= 10)
		{
			SkillCool = 0;
			isSkillCoolTime = false;

			this->removeChildByTag(COOL);
            this->removeChildByTag(COOLING);
            auto SkillButton = MenuItemImage::create("Skill.png", "Skill_Dark.png", "Skill.png", CC_CALLBACK_1(HelloWorld::SkillCallBack, this));
            SkillButton->setAnchorPoint(Vec2(0.5, 0.5));
            SkillButton->setScale(2);
            auto Skill = Menu::create(SkillButton, NULL);
            Skill->alignItemsVertically();
            Skill->setPosition(Vec2(visibleSize.width - 180, 130));
            Skill->setZOrder(3);
            Skill->setTag(SKILL);
            this->addChild(Skill);
			log("��ų �� �ʱ�ȭ");
		}
	}
}

void HelloWorld::GameOverCheck()
{

}


void HelloWorld::SkillCallBack(Ref* pSender)
{
	if (!isSkillCoolTime)
	{
		isSkillTrue = true;
		isSkillCoolTime = true;
		auto shiledEffect = Sprite::create("shield.png");
		shiledEffect->setAnchorPoint(Vec2(0.5f, 0.5f));
		shiledEffect->setPosition(21.5, 15);
		shiledEffect->setTag(SHIELD);
		shiledEffect->setScale(1.0f);
		shiledEffect->setZOrder(2);
		spr->addChild(shiledEffect);

		this->removeChildByTag(SKILL);

		auto skillCoolBack = Sprite::create("Skill_Dark.png");
		skillCoolBack->setAnchorPoint(Vec2(0.5f, 0.5f));
		skillCoolBack->setPosition(visibleSize.width - 180, 130);
		skillCoolBack->setTag(COOL);
		skillCoolBack->setScale(2.0f);
		skillCoolBack->setZOrder(4);
		this->addChild(skillCoolBack);

		auto skillCool = Sprite::create("Skill.png");
		skillCool->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto skillCoolTime = ProgressTimer::create(skillCool);
		skillCoolTime->setType(ProgressTimer::Type::RADIAL);
		skillCoolTime->setMidpoint(Vec2(0.5f, 0.5f));
		skillCoolTime->setScale(2.0f);
		skillCoolTime->setPosition(visibleSize.width - 180, 130);
		skillCoolTime->setTag(COOLING);
		skillCoolTime->setZOrder(5);
		this->addChild(skillCoolTime);
		auto to = ProgressTo::create(9.8f, 100);
		skillCoolTime->runAction(to);
	}

	log("��ų ���");
}

void HelloWorld::changeGameOverScene()
{
	ThisScore = mytime;
	UserDefault::getInstance()->setIntegerForKey("THISSCORE", ThisScore);
	UserDefault::getInstance()->flush();
	Director::getInstance()->replaceScene(GameOverScene::createScene());
	
	log("���ӿ��� ������ �̵�");
}