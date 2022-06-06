#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "MenuScene.h"


USING_NS_CC;

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

	
	auto TimeLable = Label::createWithSystemFont(" 0 ", "", 40);
	
	thisGameTime = UserDefault::getInstance()->getIntegerForKey("THISSCORE");
	TimeLable->setString(StringUtils::format(" %d " ,thisGameTime));
	TimeLable->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(TimeLable);
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

