#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//¼àÌýÏµÍ³°´¼ü
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	bool onTouchBegan(cocos2d::Touch* touch, Event* event);

	void startStandModel();
	void startFiveModel();
	void startDegreeModel();

	LayerColor* spriteBtn1;
	LayerColor* spriteBtn2;
	LayerColor* spriteBtn3;
};

#endif // __HELLOWORLD_SCENE_H__
