#include "GameScene5.h"
#include "HelloWorldScene.h"
#include "CommonData.h"
Scene* GameScene5::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene5::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene5::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	this->is_Move=true;

	//==========设置触摸事件监听==========
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene5::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene5::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//==========设置相应按键消息==========
	this->setKeypadEnabled(true);

	//==========游戏背景==========
	auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);

	//==========刷新精灵==========
	spriteFresh = Sprite::createWithSpriteFrameName("shuaxin.png");
	spriteFresh->setPosition(Point(VISIBLE_SIZE.width*4/5 ,VISIBLE_SIZE.height - 200));
	this->addChild(spriteFresh);

	//==========计算卡片大小==========
	getCardSize(VISIBLE_SIZE);

	//==========创建分数==========

	//最高分
	//从配置文件中读取历史最高得分，如果没有则返回默认值0
	m_highScore = UserDefault::getInstance()->getIntegerForKey("HIGHSCORE_5", 0);
	auto highScoreLabel = LabelTTF::create(StringUtils::format("High Score %i", m_highScore),"Consolas",cardSize/3);
	highScoreLabel->setPosition(Point(highScoreLabel->getContentSize().width/2+50,
		VISIBLE_SIZE.height-highScoreLabel->getContentSize().height/2-50));
	this->addChild(highScoreLabel);

	m_Score = 0;

	scoreLabel = LabelTTF::create(StringUtils::format("Current Score %i", m_Score),"Consolas",cardSize*2/5);
	scoreLabel->setPosition(Point(50 ,
		VISIBLE_SIZE.height-highScoreLabel->getContentSize().height-100));
	scoreLabel->setAnchorPoint(Point(0,0));
	addChild(scoreLabel);


	//==========创建卡片==========
	createCards();

	//==========初始生成两个值为2的卡片==========
	createCardNumber();
	createCardNumber();

	return true;
}

void GameScene5::getCardSize(Size size){

	//判断是否竖屏
	auto realWidth=size.width;

	if(size.width > size.height){
		realWidth=size.height;
	}

	//求出单元格的宽和高
	cardSize = realWidth / 5;
}
/**
*创建5X5卡片
*/
void GameScene5::createCards()
{
	//绘制出5X5的单元格
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//需要屏幕分辨率适配
			Card* card = Card::createCardSprite(0, cardSize, cardSize, cardSize*(i+1/5), cardSize*(j+2.0/10)+VISIBLE_SIZE.height/10);
			cardArray[i][j] = card;
			this->addChild(card);
		}
	}
}

bool GameScene5::onTouchBegan(Touch* touch, Event* event)
{
	//得到触摸时坐标
	beginPoint = touch->getLocation(); 

	if(spriteFresh->getBoundingBox().containsPoint(beginPoint)){

		//从新游戏
		auto actionOne =Sequence::create(  
			RotateTo::create(0.5, 720.0f),  
			CallFunc::create(this,callfunc_selector(GameScene5::startNewGame)),  
			NULL  
			); 
		spriteFresh->runAction( actionOne);
		return false;
	}
	return true;
}

void GameScene5::onTouchEnded(Touch* touch, Event* event)
{
	//得到触摸结束时坐标
	Point endTouch = touch->getLocation(); 
	//计算手指移动的距离
	float endX = beginPoint.x - endTouch.x;
	float endY = beginPoint.y - endTouch.y;
	if (abs(endX) > abs(endY))
	{
		//如果X轴移动的距离大于Y轴，则是左右移动
		if (endX + 5 > 0)
		{
			//向左移动
			toLeft();
			createCardNumber();
			updataScore();
		}
		else
		{
			//向右移动
			toRight();
			createCardNumber();
			updataScore();
		}
	}
	else //否则是上下移动
	{
		if (endY + 5 > 0)
		{
			//向下移动
			toDown();
			createCardNumber();
			updataScore();
		}
		else
		{
			//向上移动
			toUp();
			createCardNumber();
			updataScore();
		}
	}
	//每次移动后检测是否可以继续游戏
	checkGameOver();
}

//创建生成随机卡片
void GameScene5::createCardNumber()
{
	//若某方向滑动后不能移动卡片
	if(!is_Move){
		return ;
	}

	int i = CCRANDOM_0_1() * 5;        //生成0~4随机数
	int j = CCRANDOM_0_1() * 5;

	//判断是否已经存在
	if (cardArray[i][j]->getNumber() > 0)
	{
		createCardNumber();
	}
	else
	{
		//2和4的生成率为9:1
		cardArray[i][j]->setNumber(CCRANDOM_0_1()*10 > 1 ? 2 : 4);
	}
}

//检测游戏是否结束
void GameScene5::checkGameOver()
{
	bool isGameOver = true;
	//判断每一个的上下左右和自己是否相同
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{

			if(cardArray[x][y]->getNumber() == 2048){

			}

			if (cardArray[x][y]->getNumber() == 0 ||
				(x<3 && cardArray[x][y]->getNumber() == cardArray[x+1][y]->getNumber()) ||
				(x>0 && cardArray[x][y]->getNumber() == cardArray[x-1][y]->getNumber()) ||
				(y<3 && cardArray[x][y]->getNumber() == cardArray[x][y+1]->getNumber()) ||
				(y>0 && cardArray[x][y]->getNumber() == cardArray[x][y-1]->getNumber()) )
			{
				isGameOver = false;
			}
		}
	}
	if (isGameOver)
	{
		//从新游戏
		startNewGame();
	}
}

//新游戏
void GameScene5::startNewGame(){
	if (m_highScore<m_Score)
	{

		m_highScore = m_Score;

		UserDefault::getInstance()->setIntegerForKey("HIGHSCORE_5", m_highScore);
	}
	Director::getInstance()->replaceScene(TransitionFade ::create(1, GameScene5::createScene()));
}

//检测卡片最大值是否到达分数
void GameScene5::checkWin(){
}

//向左滑动
void GameScene5::toLeft()
{
	//判断有没有发生移动
	is_Move = false;
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			for (int x1 = x+1; x1<5; x1++)
			{
				if (cardArray[x1][y]->getNumber() > 0)
				{
					if (cardArray[x][y]->getNumber() <= 0)
					{
						cardArray[x][y]->setNumber(cardArray[x1][y]->getNumber());
						cardArray[x1][y]->setNumber(0);
						x--;
						is_Move = true;
					}
					else if(cardArray[x][y]->getNumber() == cardArray[x1][y]->getNumber())
					{
						cardArray[x][y]->setNumber(cardArray[x][y]->getNumber() * 2);
						cardArray[x1][y]->setNumber(0);

						//改变分数
						m_Score += cardArray[x][y]->getNumber();
						is_Move = true;
					}
					break;
				}
			}
		}
	}
}

//向右滑动
void GameScene5::toRight()
{
	//判断有没有发生移动
	is_Move = false;
	for (int y = 0; y < 5; y++)
	{
		for (int x = 4; x >= 0; x--)
		{
			for (int x1 = x-1; x1>=0; x1--)
			{
				if (cardArray[x1][y]->getNumber() > 0)
				{
					if (cardArray[x][y]->getNumber() <= 0)
					{
						cardArray[x][y]->setNumber(cardArray[x1][y]->getNumber());
						cardArray[x1][y]->setNumber(0);
						x++;
						is_Move = true;
					}
					else if(cardArray[x][y]->getNumber() == cardArray[x1][y]->getNumber())
					{
						cardArray[x][y]->setNumber(cardArray[x][y]->getNumber() * 2);
						cardArray[x1][y]->setNumber(0);
						//改变分数
						m_Score += cardArray[x][y]->getNumber();
						is_Move = true;
					}
					break;
				}
			}
		}
	}
}

//向上滑动
void GameScene5::toUp()
{
	//判断有没有发生移动
	is_Move = false;
	for (int x = 0; x < 5; x++)
	{
		for (int y = 4; y >= 0; y--)
		{
			for (int y1 = y-1; y1>=0; y1--)
			{
				if (cardArray[x][y1]->getNumber() > 0)
				{
					if (cardArray[x][y]->getNumber() <= 0)
					{
						cardArray[x][y]->setNumber(cardArray[x][y1]->getNumber());
						cardArray[x][y1]->setNumber(0);
						y++;
						is_Move = true;
					}
					else if(cardArray[x][y]->getNumber() == cardArray[x][y1]->getNumber())
					{
						cardArray[x][y]->setNumber(cardArray[x][y]->getNumber() * 2);
						cardArray[x][y1]->setNumber(0);
						//改变分数
						m_Score += cardArray[x][y]->getNumber();
						is_Move = true;
					}
					break;
				}
			}
		}
	}
}

//向下滑动
void GameScene5::toDown()
{
	//判断有没有发生移动
	is_Move = false;
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y <5; y++)
		{
			for (int y1 = y+1; y1<5; y1++)
			{
				if (cardArray[x][y1]->getNumber() > 0)
				{
					if (cardArray[x][y]->getNumber() <= 0)
					{
						cardArray[x][y]->setNumber(cardArray[x][y1]->getNumber());
						cardArray[x][y1]->setNumber(0);
						y--;
						is_Move = true;
					}
					else if(cardArray[x][y]->getNumber() == cardArray[x][y1]->getNumber())
					{
						cardArray[x][y]->setNumber(cardArray[x][y]->getNumber() * 2);
						cardArray[x][y1]->setNumber(0);
						//改变分数
						m_Score += cardArray[x][y]->getNumber();
						is_Move = true;
					}
					break;
				}
			}
		}
	}
}

//更新分数
void GameScene5::updataScore()
{
	scoreLabel->setString(__String::createWithFormat("Current Score %i",m_Score)->getCString());
}

//监听系统按键
void  GameScene5::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event){  

	switch (keycode){  

	case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:  

	case cocos2d::EventKeyboard::KeyCode::KEY_BACK_SLASH: 

	case cocos2d::EventKeyboard::KeyCode::KEY_BACK_TAB: 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)  

		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");  

		return;  

#endif  
		if (m_highScore<m_Score)
		{

			m_highScore = m_Score;

			UserDefault::getInstance()->setIntegerForKey("HIGHSCORE_5", m_highScore);
		}
		Director::getInstance()->replaceScene(TransitionMoveInL ::create(0.5, HelloWorld::createScene())); 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

		exit(0);  

#endif  
		break;  

	default:  

		break;  

	}  
}  