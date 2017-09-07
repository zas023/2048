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

	//==========���ô����¼�����==========
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene5::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene5::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//==========������Ӧ������Ϣ==========
	this->setKeypadEnabled(true);

	//==========��Ϸ����==========
	auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);

	//==========ˢ�¾���==========
	spriteFresh = Sprite::createWithSpriteFrameName("shuaxin.png");
	spriteFresh->setPosition(Point(VISIBLE_SIZE.width*4/5 ,VISIBLE_SIZE.height - 200));
	this->addChild(spriteFresh);

	//==========���㿨Ƭ��С==========
	getCardSize(VISIBLE_SIZE);

	//==========��������==========

	//��߷�
	//�������ļ��ж�ȡ��ʷ��ߵ÷֣����û���򷵻�Ĭ��ֵ0
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


	//==========������Ƭ==========
	createCards();

	//==========��ʼ��������ֵΪ2�Ŀ�Ƭ==========
	createCardNumber();
	createCardNumber();

	return true;
}

void GameScene5::getCardSize(Size size){

	//�ж��Ƿ�����
	auto realWidth=size.width;

	if(size.width > size.height){
		realWidth=size.height;
	}

	//�����Ԫ��Ŀ�͸�
	cardSize = realWidth / 5;
}
/**
*����5X5��Ƭ
*/
void GameScene5::createCards()
{
	//���Ƴ�5X5�ĵ�Ԫ��
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//��Ҫ��Ļ�ֱ�������
			Card* card = Card::createCardSprite(0, cardSize, cardSize, cardSize*(i+1/5), cardSize*(j+2.0/10)+VISIBLE_SIZE.height/10);
			cardArray[i][j] = card;
			this->addChild(card);
		}
	}
}

bool GameScene5::onTouchBegan(Touch* touch, Event* event)
{
	//�õ�����ʱ����
	beginPoint = touch->getLocation(); 

	if(spriteFresh->getBoundingBox().containsPoint(beginPoint)){

		//������Ϸ
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
	//�õ���������ʱ����
	Point endTouch = touch->getLocation(); 
	//������ָ�ƶ��ľ���
	float endX = beginPoint.x - endTouch.x;
	float endY = beginPoint.y - endTouch.y;
	if (abs(endX) > abs(endY))
	{
		//���X���ƶ��ľ������Y�ᣬ���������ƶ�
		if (endX + 5 > 0)
		{
			//�����ƶ�
			toLeft();
			createCardNumber();
			updataScore();
		}
		else
		{
			//�����ƶ�
			toRight();
			createCardNumber();
			updataScore();
		}
	}
	else //�����������ƶ�
	{
		if (endY + 5 > 0)
		{
			//�����ƶ�
			toDown();
			createCardNumber();
			updataScore();
		}
		else
		{
			//�����ƶ�
			toUp();
			createCardNumber();
			updataScore();
		}
	}
	//ÿ���ƶ������Ƿ���Լ�����Ϸ
	checkGameOver();
}

//�������������Ƭ
void GameScene5::createCardNumber()
{
	//��ĳ���򻬶������ƶ���Ƭ
	if(!is_Move){
		return ;
	}

	int i = CCRANDOM_0_1() * 5;        //����0~4�����
	int j = CCRANDOM_0_1() * 5;

	//�ж��Ƿ��Ѿ�����
	if (cardArray[i][j]->getNumber() > 0)
	{
		createCardNumber();
	}
	else
	{
		//2��4��������Ϊ9:1
		cardArray[i][j]->setNumber(CCRANDOM_0_1()*10 > 1 ? 2 : 4);
	}
}

//�����Ϸ�Ƿ����
void GameScene5::checkGameOver()
{
	bool isGameOver = true;
	//�ж�ÿһ�����������Һ��Լ��Ƿ���ͬ
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
		//������Ϸ
		startNewGame();
	}
}

//����Ϸ
void GameScene5::startNewGame(){
	if (m_highScore<m_Score)
	{

		m_highScore = m_Score;

		UserDefault::getInstance()->setIntegerForKey("HIGHSCORE_5", m_highScore);
	}
	Director::getInstance()->replaceScene(TransitionFade ::create(1, GameScene5::createScene()));
}

//��⿨Ƭ���ֵ�Ƿ񵽴����
void GameScene5::checkWin(){
}

//���󻬶�
void GameScene5::toLeft()
{
	//�ж���û�з����ƶ�
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

						//�ı����
						m_Score += cardArray[x][y]->getNumber();
						is_Move = true;
					}
					break;
				}
			}
		}
	}
}

//���һ���
void GameScene5::toRight()
{
	//�ж���û�з����ƶ�
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
						//�ı����
						m_Score += cardArray[x][y]->getNumber();
						is_Move = true;
					}
					break;
				}
			}
		}
	}
}

//���ϻ���
void GameScene5::toUp()
{
	//�ж���û�з����ƶ�
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
						//�ı����
						m_Score += cardArray[x][y]->getNumber();
						is_Move = true;
					}
					break;
				}
			}
		}
	}
}

//���»���
void GameScene5::toDown()
{
	//�ж���û�з����ƶ�
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
						//�ı����
						m_Score += cardArray[x][y]->getNumber();
						is_Move = true;
					}
					break;
				}
			}
		}
	}
}

//���·���
void GameScene5::updataScore()
{
	scoreLabel->setString(__String::createWithFormat("Current Score %i",m_Score)->getCString());
}

//����ϵͳ����
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