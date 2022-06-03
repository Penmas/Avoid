#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto Title = Sprite::create("title.png");
	Title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 20));
	Title->setAnchorPoint(Vec2(0.5, 1));
	Title->setScale(0.5f);
	this->addChild(Title);

	auto ScoreRecordTitleLabel = Label::create("최고기록","",50);
	ScoreRecordTitleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 300));
	Score1st = 100;
	auto ScoreRecrod1stLabel = Label::create("1st. ---   00:00", "", 40);
	auto ScoreRecrod2ndLabel = Label::create("2nd. ---   00:00", "", 40);
	auto ScoreRecrod3rdLabel = Label::create("3rd. ---   00:00", "", 40);
	auto ScoreRecrod4thLabel = Label::create("4th. ---   00:00", "", 40);
	auto ScoreRecrod5thLabel = Label::create("5th. ---   00:00", "", 40);
	ScoreRecrod1stLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 2));
	this->addChild(ScoreRecordTitleLabel);
	this->addChild(ScoreRecrod1stLabel);
	auto StartButton = MenuItemImage::create("start.png","start.png","start.png",CC_CALLBACK_1(MenuScene::changeScene, this));
	auto menu = Menu::create(StartButton, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize.width / 2, 200));
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