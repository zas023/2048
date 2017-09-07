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

	//��ȡ����
	int getNumber();
	//��������
	void setNumber(int num);
	void setType(bool);
	//ת������
	void changeNumber();
private:
	//��ʾ������
	int number;
	//��ʾ�����Ƿ�ΪString
	bool is_String;
	//��Ƭ�ߴ�
	int wight;

	//��ʼ��
	void initCard(int number, int wight, int height, float CardSpriteX, float CardSpriteY);
	//��ʾ���ֵĿؼ�
	LabelTTF *labelCardNumber;
	//����
	LayerColor *colorBackground;
};

