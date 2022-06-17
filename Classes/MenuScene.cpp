#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace experimental;
USING_NS_CC;
Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	
	auto Title = Sprite::create("title.png");
	Title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 20));
	Title->setAnchorPoint(Vec2(0.5, 1));
	Title->setScale(0.5f);
	this->addChild(Title);

	auto ScoreRecordTitleLabel = Label::createWithTTF("최고기록","fonts/NANUMSQUAREROUNDEB.TTF",50);
	ScoreRecordTitleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 300));
	Score1st = UserDefault::getInstance()->getIntegerForKey("SCORE1ST");
	Score2nd = UserDefault::getInstance()->getIntegerForKey("SCORE2ND");
	Score3rd = UserDefault::getInstance()->getIntegerForKey("SCORE3RD");
	Score4th = UserDefault::getInstance()->getIntegerForKey("SCORE4TH");
	Score5th = UserDefault::getInstance()->getIntegerForKey("SCORE5TH");
	
	
	auto ScoreRecrod1stLabel = Label::createWithTTF("1st. 00:00", "fonts/NANUMSQUAREROUNDEB.TTF", 40);
	if (Score1st < 10)
	{
		ScoreRecrod1stLabel->setString(StringUtils::format("1st. 00:0%d", Score1st));
	}
	else if (Score1st < 60)
	{
		ScoreRecrod1stLabel->setString(StringUtils::format("1st. 00:%d", Score1st));
		
	}
	else if (Score1st < 600 && (Score1st % 60 < 10))
	{
		ScoreRecrod1stLabel->setString(StringUtils::format("1st. 0%d:0%d", Score1st / 60, Score1st % 60));
	}
	else if (Score1st < 600 && (Score1st % 60 > 10))
	{
		ScoreRecrod1stLabel->setString(StringUtils::format("1st. 0%d:%d", Score1st / 60, Score1st % 60));
	}
	else if (Score1st >= 600 && (Score1st % 60 < 10))
	{
		ScoreRecrod1stLabel->setString(StringUtils::format("1st. %d:0%d", Score1st / 60, Score1st % 60));
	}
	else if (Score1st >= 600 && (Score1st % 60 >= 10))
	{
		ScoreRecrod1stLabel->setString(StringUtils::format("1st. %d:%d", Score1st / 60, Score1st % 60));
	}

	auto ScoreRecrod2ndLabel = Label::createWithTTF("2nd. 00:00", "fonts/NANUMSQUAREROUNDEB.TTF", 40);
	if (Score2nd < 10)
	{
		ScoreRecrod2ndLabel->setString(StringUtils::format("2nd. 00:0%d", Score2nd));
	}
	else if (Score2nd < 60)
	{
		ScoreRecrod2ndLabel->setString(StringUtils::format("2nd. 00:%d", Score2nd));
	}
	else if (Score2nd < 600 && (Score2nd % 60 < 10))
	{
		ScoreRecrod2ndLabel->setString(StringUtils::format("2nd. 0%d:0%d", Score2nd / 60, Score2nd % 60));
	}
	else if (Score2nd < 600 && (Score2nd % 60 > 10))
	{
		ScoreRecrod2ndLabel->setString(StringUtils::format("2nd. 0%d:%d", Score2nd / 60, Score2nd % 60));
	}
	else if (Score2nd >= 600 && (Score2nd % 60 < 10))
	{
		ScoreRecrod2ndLabel->setString(StringUtils::format("2nd. %d:%d", Score2nd / 60, Score2nd % 60));
	}
	else if (Score2nd >= 600 && (Score2nd % 60 >= 10))
	{
		ScoreRecrod2ndLabel->setString(StringUtils::format("2nd. %d:0%d", Score2nd / 60, Score2nd % 60));
	}

	auto ScoreRecrod3rdLabel = Label::createWithTTF("3rd. 00:00", "fonts/NANUMSQUAREROUNDEB.TTF", 40);
	if (Score3rd < 10)
	{
		ScoreRecrod3rdLabel->setString(StringUtils::format("3rd. 00:0%d", Score3rd));
	}
	else if (Score3rd < 60)
	{
		ScoreRecrod3rdLabel->setString(StringUtils::format("3rd. 00:%d", Score3rd));
	}
	else if (Score3rd < 600 && (Score3rd % 60 < 10))
	{
		ScoreRecrod3rdLabel->setString(StringUtils::format("3rd. 0%d:0%d", Score3rd / 60, Score3rd % 60));
	}
	else if (Score3rd < 600 && (Score3rd % 60 > 10))
	{
		ScoreRecrod3rdLabel->setString(StringUtils::format("3rd. 0%d:%d", Score3rd / 60, Score3rd % 60));
	}
	else if (Score3rd >= 600 && (Score3rd % 60 < 10))
	{
		ScoreRecrod3rdLabel->setString(StringUtils::format("3rd. %d:0%d", Score3rd / 60, Score3rd % 60));
	}
	else if (Score3rd >= 600 && (Score3rd % 60 >= 10))
	{
		ScoreRecrod3rdLabel->setString(StringUtils::format("3rd. %d:%d", Score3rd / 60, Score3rd % 60));
	}

	auto ScoreRecrod4thLabel = Label::createWithTTF("4th. 00:00", "fonts/NANUMSQUAREROUNDEB.TTF", 40);
	if (Score4th < 10)
	{
		ScoreRecrod4thLabel->setString(StringUtils::format("4th. 00:0%d", Score4th));
	}
	else if (Score4th < 60)
	{
		ScoreRecrod4thLabel->setString(StringUtils::format("4th. 00:%d", Score4th));
	}
	else if (Score4th < 600 && (Score4th % 60 < 10))
	{
		ScoreRecrod4thLabel->setString(StringUtils::format("4th. 0%d:0%d", Score4th / 60, Score4th % 60));
	}
	else if (Score4th < 600 && (Score4th % 60 > 10))
	{
		ScoreRecrod4thLabel->setString(StringUtils::format("4th. 0%d:%d", Score4th / 60, Score4th % 60));
	}
	else if (Score4th >= 600 && (Score4th % 60 < 10))
	{
		ScoreRecrod4thLabel->setString(StringUtils::format("4th. %d:0%d", Score4th / 60, Score4th % 60));
	}
	else if (Score4th >= 600 && (Score4th % 60 >= 10))
	{
		ScoreRecrod4thLabel->setString(StringUtils::format("4th. %d:%d", Score4th / 60, Score4th % 60));
	}


	auto ScoreRecrod5thLabel = Label::createWithTTF("5th. 00:00", "fonts/NANUMSQUAREROUNDEB.TTF", 40);
	if (Score5th < 10)
	{
		ScoreRecrod5thLabel->setString(StringUtils::format("5th. 00:0%d", Score5th));
	}
	else if (Score5th < 60)
	{
		ScoreRecrod5thLabel->setString(StringUtils::format("5th. 00:%d", Score5th));
	}
	else if (Score5th < 600 && (Score5th % 60 < 10))
	{
		ScoreRecrod5thLabel->setString(StringUtils::format("5th. 0%d:0%d", Score5th / 60, Score5th % 60));
	}
	else if (Score5th < 600 && (Score5th % 60 > 10))
	{
		ScoreRecrod5thLabel->setString(StringUtils::format("5th. 0%d:%d", Score5th / 60, Score5th % 60));
	}
	else if (Score5th >= 600 && (Score5th % 60 < 10))
	{
		ScoreRecrod5thLabel->setString(StringUtils::format("5th. 0%d:0%d", Score5th / 60, Score5th % 60));
	}
	else if (Score5th >= 600 && (Score5th % 60 >= 10))
	{
		ScoreRecrod5thLabel->setString(StringUtils::format("5th. %d:%d", Score5th / 60, Score5th % 60));
	}




	ScoreRecrod1stLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 400));
	ScoreRecrod2ndLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 450));
	ScoreRecrod3rdLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 500));
	ScoreRecrod4thLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 550));
	ScoreRecrod5thLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 600));

	this->addChild(ScoreRecordTitleLabel);
	this->addChild(ScoreRecrod1stLabel);
	this->addChild(ScoreRecrod2ndLabel);
	this->addChild(ScoreRecrod3rdLabel);
	this->addChild(ScoreRecrod4thLabel);
	this->addChild(ScoreRecrod5thLabel);

	auto StartButton = MenuItemImage::create("start.png","start.png","start.png",CC_CALLBACK_1(MenuScene::changeScene, this));
	auto menu = Menu::create(StartButton, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize.width / 2, 200));
	menu->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(menu);
	return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
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

void MenuScene::changeScene(Ref *sender) 
{ 
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}