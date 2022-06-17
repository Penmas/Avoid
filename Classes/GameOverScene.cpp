#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "MenuScene.h"
#include "audio/include/AudioEngine.h"


USING_NS_CC;
using namespace experimental;
#define PLAYER	0

Scene* GameOverScene::createScene()
{
    return GameOverScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	auto title = Sprite::create("over.png");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 30));
	title->setScale(1.5);
	title->setAnchorPoint(Vec2(0.5, 1));
	this->addChild(title);

	auto StartButton = MenuItemImage::create("retry.png", "retry.png", "retry.png", CC_CALLBACK_1(GameOverScene::GameReStart, this));
	StartButton->setScale(1.5);
	auto MenuBackButton = MenuItemImage::create("menu.png", "menu.png", "menu.png", CC_CALLBACK_1(GameOverScene::MenuBack, this));
	MenuBackButton->setScale(1.5);
	auto menu = Menu::create(StartButton,MenuBackButton, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize.width / 2, 200));
	this->addChild(menu);

	
	auto TimeLable = Label::createWithTTF(" 0 ", "fonts/NANUMSQUAREROUNDEB.TTF", 50);
	
	thisGameTime = UserDefault::getInstance()->getIntegerForKey("THISSCORE");

	if (thisGameTime < 10)
	{
		TimeLable->setString(StringUtils::format("00:0%d", thisGameTime));
	}
	else if (thisGameTime < 60)
	{
		TimeLable->setString(StringUtils::format("00:%d", thisGameTime));
	}
	else if (thisGameTime < 600 && (thisGameTime % 60 < 10) )
	{
		TimeLable->setString(StringUtils::format("0%d:0%d", thisGameTime / 60, thisGameTime%60));
	}
	else if (thisGameTime < 600 && (thisGameTime % 60 > 10))
	{
		TimeLable->setString(StringUtils::format("0%d:%d", thisGameTime / 60, thisGameTime%60));
	}
	else if (thisGameTime >= 600 && (thisGameTime % 60 > 10))
	{
		TimeLable->setString(StringUtils::format("%d:%d", thisGameTime / 60, thisGameTime % 60));
	}
	else if (thisGameTime >= 600 && (thisGameTime % 60 < 10))
	{
		TimeLable->setString(StringUtils::format("0%d:0%d", thisGameTime / 60, thisGameTime % 60));
	}
	//TimeLable->setString(StringUtils::format("%d " ,thisGameTime));
	TimeLable->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)+30));
	this->addChild(TimeLable);

	Score[0] = UserDefault::getInstance()->getIntegerForKey("SCORE1ST");
	Score[1] = UserDefault::getInstance()->getIntegerForKey("SCORE2ND");
	Score[2] = UserDefault::getInstance()->getIntegerForKey("SCORE3RD");
	Score[3] = UserDefault::getInstance()->getIntegerForKey("SCORE4TH");
	Score[4] = UserDefault::getInstance()->getIntegerForKey("SCORE5TH");

	auto HighScoreTitle = Label::createWithTTF(" 최고기록 갱신 ", "fonts/NANUMSQUAREROUNDEB.TTF", 50);
	auto ScoreTitle = Label::createWithTTF(" 현재 기록 ", "fonts/NANUMSQUAREROUNDEB.TTF", 50);
	HighScoreTitle->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2) + 80));
	ScoreTitle->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2) + 80));
	if (thisGameTime > Score[0])
	{
		this->addChild(HighScoreTitle);
	}
	else
	{
		this->addChild(ScoreTitle);
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Score[j] < thisGameTime)
			{
				ScoreSpace = Score[j];
				Score[j] = thisGameTime;
				thisGameTime = ScoreSpace;
			}
		}
	}
	UserDefault::getInstance()->setIntegerForKey("SCORE1ST", Score[0]);
	UserDefault::getInstance()->setIntegerForKey("SCORE2ND", Score[1]);
	UserDefault::getInstance()->setIntegerForKey("SCORE3RD", Score[2]);
	UserDefault::getInstance()->setIntegerForKey("SCORE4TH", Score[3]);
	UserDefault::getInstance()->setIntegerForKey("SCORE5TH", Score[4]);
	UserDefault::getInstance()->flush();


	return true;
}


void GameOverScene::menuCloseCallback(Ref* pSender)
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

void GameOverScene::GameReStart(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void GameOverScene::MenuBack(Ref* pSender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

