#pragma once

#include "cocos2d.h"
#include "Card.h"

USING_NS_CC;

class GameSceneS : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	CREATE_FUNC(GameSceneS);

	//监听触摸事件回调函数
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	//监听系统按键
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
private:
	//计算自适应屏幕大小创建卡片
	void getCardSize(Size size);

	//创4X4建卡片
	void createCards();

	//记录触摸开始时的坐标
	Point beginPoint;
	//向左滑动
	void toLeft();
	//向右滑动
	void toRight();
	//向上滑动
	void toUp();
	//向下滑动
	void toDown();

	//储存卡片类
	Card* cardArray[4][4];
	//卡片大小
	int cardSize;
	//分数
	int m_Score;
	int m_highScore;
	//滑动后卡片是否移动
	bool is_Move;
	//刷新控件
	Sprite* spriteFresh;
	//分数控件
	LabelTTF *scoreLabel;
	//创建生成随机卡片
	void createCardNumber();
	//检测游戏是否结束
	void checkGameOver();
	//新游戏
	void startNewGame();
	//检测游戏是否结束
	void checkWin();

	//更新分数
	void updataScore();
};

