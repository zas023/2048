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

	//���������¼��ص�����
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	//����ϵͳ����
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
private:
	//��������Ӧ��Ļ��С������Ƭ
	void getCardSize(Size size);

	//��4X4����Ƭ
	void createCards();

	//��¼������ʼʱ������
	Point beginPoint;
	//���󻬶�
	void toLeft();
	//���һ���
	void toRight();
	//���ϻ���
	void toUp();
	//���»���
	void toDown();

	//���濨Ƭ��
	Card* cardArray[4][4];
	//��Ƭ��С
	int cardSize;
	//����
	int m_Score;
	int m_highScore;
	//������Ƭ�Ƿ��ƶ�
	bool is_Move;
	//ˢ�¿ؼ�
	Sprite* spriteFresh;
	//�����ؼ�
	LabelTTF *scoreLabel;
	//�������������Ƭ
	void createCardNumber();
	//�����Ϸ�Ƿ����
	void checkGameOver();
	//����Ϸ
	void startNewGame();
	//�����Ϸ�Ƿ����
	void checkWin();

	//���·���
	void updataScore();
};

