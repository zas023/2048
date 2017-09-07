#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameScene5.h"
#include "GameSceneS.h"
#include "CommonData.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	//创建词典类实例，将xml文件加载到词典中
    auto chnStrings = Dictionary::createWithContentsOfFile("CHN_Strings.xml");

	//==========设置相应按键消息==========
	this->setKeypadEnabled(true);

	//==========设置相应按键消息==========
	this->setKeypadEnabled(true);

	//==========设置触摸事件监听==========
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//==========游戏背景==========
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main.plist");

	auto layerColorBG = LayerColor::create(Color4B(200,190,180,255));
	this->addChild(layerColorBG);

	spriteBtn1 = LayerColor::create(Color4B(218,165,32,255),VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/10);
	spriteBtn1->setPosition(VISIBLE_SIZE.width/4,VISIBLE_SIZE.height/2+spriteBtn1->getContentSize().height);
	spriteBtn1->setAnchorPoint(Point(0.5,0.5));
	this->addChild(spriteBtn1);

	auto scoreLabel = LabelTTF::create(StringUtils::format("4 X 4"),"Consolas",VISIBLE_SIZE.height/12);
	scoreLabel->setPosition(spriteBtn1->getPosition().x+spriteBtn1->getContentSize().width/2,
		spriteBtn1->getPosition().y+spriteBtn1->getContentSize().height/2);
	scoreLabel->setAnchorPoint(Point(0.5,0.5));
	addChild(scoreLabel);


	spriteBtn2 = LayerColor::create(Color4B(218,165,32,255),VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/10);
	spriteBtn2->setPosition(VISIBLE_SIZE.width/4,VISIBLE_SIZE.height/2-spriteBtn2->getContentSize().height);
	spriteBtn2->setAnchorPoint(Point(0.5,0.5));
	this->addChild(spriteBtn2);

	auto scoreLabe2 = LabelTTF::create(StringUtils::format("5 X 5"),"Consolas",VISIBLE_SIZE.height/12);
	scoreLabe2->setPosition(spriteBtn2->getPosition().x+spriteBtn2->getContentSize().width/2,
		spriteBtn2->getPosition().y+spriteBtn2->getContentSize().height/2);
	scoreLabe2->setAnchorPoint(Point(0.5,0.5));
	addChild(scoreLabe2);

	spriteBtn3 = LayerColor::create(Color4B(218,165,32,255),VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/10);
	spriteBtn3->setPosition(VISIBLE_SIZE.width/4,VISIBLE_SIZE.height/2-3*spriteBtn3->getContentSize().height);
	spriteBtn3->setAnchorPoint(Point(0.5,0.5));
	this->addChild(spriteBtn3);

	auto scoreLabe3 = LabelTTF::create(((String*)chnStrings->objectForKey("btn3"))->getCString(),"Consolas",VISIBLE_SIZE.height/14);
	scoreLabe3->setPosition(spriteBtn3->getPosition().x+spriteBtn3->getContentSize().width/2,
		spriteBtn3->getPosition().y+spriteBtn3->getContentSize().height/2);
	scoreLabe3->setAnchorPoint(Point(0.5,0.5));
	addChild(scoreLabe3);

	return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	//得到触摸时坐标
	auto touchPoint = touch->getLocation();

	if(spriteBtn1->getBoundingBox().containsPoint(touchPoint)){

		auto actiontwo =Sequence::create(  
			ScaleTo::create(0.5,2,11),  
			CallFunc::create(this,callfunc_selector(HelloWorld::startStandModel)), 
			NULL  
			); 
		spriteBtn2->runAction( actiontwo);
		return false;
	}

	if(spriteBtn2->getBoundingBox().containsPoint(touchPoint)){

		auto actiontwo =Sequence::create(  
			ScaleTo::create(0.5,2,12),  
			CallFunc::create(this,callfunc_selector(HelloWorld::startFiveModel)), 
			NULL  
			); 
		spriteBtn2->runAction( actiontwo);
		return false;
	}

	if(spriteBtn3->getBoundingBox().containsPoint(touchPoint)){

		auto actiontree =Sequence::create(  
			ScaleTo::create(0.5,2,15),  
			CallFunc::create(this,callfunc_selector(HelloWorld::startDegreeModel)), 
			NULL  
			); 
		spriteBtn3->runAction( actiontree);
		return false;
	}
	return true;
}

void HelloWorld::startStandModel(){
	Director::getInstance()->replaceScene(TransitionFlipX ::create(0.5,GameScene::createScene()));
}

void HelloWorld::startFiveModel(){
	Director::getInstance()->replaceScene(TransitionFlipX ::create(0.5,GameScene5::createScene()));
}

void HelloWorld::startDegreeModel(){
	Director::getInstance()->replaceScene(TransitionFlipX ::create(0.5,GameSceneS::createScene()));
}

//监听系统按键
void  HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event){  
	switch (keycode){  

	case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:  

	case cocos2d::EventKeyboard::KeyCode::KEY_BACK_SLASH: 

	case cocos2d::EventKeyboard::KeyCode::KEY_BACK_TAB: 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)  

		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");  

		return;  

#endif  
		Director::getInstance()->end(); 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

		exit(0);  

#endif  
		break;  

	default:  

		break;  

	}  
}  