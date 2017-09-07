#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Card : public Sprite
{
public:
	static Card* createCardSprite(int number, int wight, int height, float CardSpriteX, float CardSpriteY);
	//static Card* createCardSprite(int number, int wight, int height, float CardSpriteX, float CardSpriteY, bool is_String);
	virtual bool init();
	//virtual bool init(bool is_String);
	CREATE_FUNC(Card);

	//获取数据
	int getNumber();
	//设置数据
	void setNumber(int num);
	void setType(bool);
	//转换数据
	void changeNumber();
private:
	//显示的数字
	int number;
	//显示类型是否为String
	bool is_String;
	//卡片尺寸
	int wight;

	//初始化
	void initCard(int number, int wight, int height, float CardSpriteX, float CardSpriteY);
	//显示数字的控件
	LabelTTF *labelCardNumber;
	//背景
	LayerColor *colorBackground;
};

