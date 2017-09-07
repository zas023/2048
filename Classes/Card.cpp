#include "Card.h"

Card* Card::createCardSprite(int number, int wight, int height, float CardSpriteX, float CardSpriteY)
{
	//这里是创建一个自定义精灵类，格式很规范化

	Card *card = new Card();
	if (card && card->init())
	{
		card->autorelease();
		card->initCard(number,wight,height,CardSpriteX,CardSpriteY);
		return card;
	}
	CC_SAFE_DELETE(card);

	return NULL;
}
//这里也是规范化
bool Card::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	//创建词典类实例，将xml文件加载到词典中
	//chnStrings = Dictionary::createWithContentsOfFile("CHN_Strings.xml");

	is_String=false;

	return true;
}

//获取数据
int Card::getNumber()
{
	return number;
}

//设置数据
void Card::setNumber(int num)
{
	number = num;

	if(is_String){
		changeNumber();
	}
	else{
		//更新显示的数字
		if (num > 0)
		{
			labelCardNumber->setString(__String::createWithFormat("%i",number)->getCString());
		}
		else
		{
			labelCardNumber->setString("");
		}

		//设置数字大小
		if (num >= 0)
		{
			labelCardNumber->setFontSize(60);
		}
		if (num >= 16)
		{
			labelCardNumber->setFontSize(45);
		}
		if (num >= 128)
		{
			labelCardNumber->setFontSize(40);
		}
		if (num >= 1024)
		{
			labelCardNumber->setFontSize(20);
		}

	}

	//判断数字的大小来调整颜色  
	if(number == 0){  
		colorBackground->setColor(Color3B(200,190,180));  
	}  
	if (number == 2) {  
		colorBackground->setColor(Color3B(240,230,220));  
	}  
	if (number == 4) {  
		colorBackground->setColor(Color3B(240,220,200));  
	}  
	if (number == 8) {  
		colorBackground->setColor(Color3B(240,180,120));  
	}  
	if (number == 16) {  
		colorBackground->setColor(Color3B(240,140,90));  
	}  
	if (number == 32) {  
		colorBackground->setColor(Color3B(240,120,90));  
	}  
	if (number == 64) {  
		colorBackground->setColor(Color3B(240,90,60));  
	}  
	if (number == 128) {  
		colorBackground->setColor(Color3B(240,90,60));  
	}  
	if (number == 256) {  
		colorBackground->setColor(Color3B(240,200,70));  
	}  
	if (number == 512) {  
		colorBackground->setColor(Color3B(240,200,70));  
	}  
	if (number == 1024) {  
		colorBackground->setColor(Color3B(0,130,0));  
	}  
	if (number == 2048) {  
		colorBackground->setColor(Color3B(0,130,0));  
	}  
}

//设置数据类型
void Card::setType(bool is){
	is_String=is;
}

//转换数据
void Card::changeNumber(){

	labelCardNumber->setFontSize(wight/3);

	auto chnStrings = Dictionary::createWithContentsOfFile("CHN_Strings.xml");
	const char *title;

	//判断数字的大小来调整颜色  
	if(number == 0){  
		title = "";
	}  
	if (number == 2) {  
		title = ((String*)chnStrings->objectForKey("num2"))->getCString();
	}  
	if (number == 4) {  
		title = ((String*)chnStrings->objectForKey("num4"))->getCString();
	}  
	if (number == 8) {  
		title = ((String*)chnStrings->objectForKey("num8"))->getCString();
	}  
	if (number == 16) {  
		title = ((String*)chnStrings->objectForKey("num16"))->getCString();
	}  
	if (number == 32) {  
		title = ((String*)chnStrings->objectForKey("num32"))->getCString();
	}  
	if (number == 64) {  
		title = ((String*)chnStrings->objectForKey("num64"))->getCString();
	}  
	if (number == 128) {  
		title = ((String*)chnStrings->objectForKey("num128"))->getCString();
	}  
	if (number == 256) {  
		title = ((String*)chnStrings->objectForKey("num256"))->getCString();
	}  
	if (number == 512) {  
		title = ((String*)chnStrings->objectForKey("num512"))->getCString();
	}  
	if (number == 1024) {  
		title = ((String*)chnStrings->objectForKey("num1024"))->getCString();
	}  
	if (number == 2048) {  
		title = ((String*)chnStrings->objectForKey("num2048"))->getCString();
	}  
	if (number == 4096) {  
		title = ((String*)chnStrings->objectForKey("num4096"))->getCString();
	}  
	if (number > 4096) {  
		title = ((String*)chnStrings->objectForKey("num0"))->getCString();
	}  

	labelCardNumber->setString(title);
}

//初始化
void Card::initCard(int number, int wight, int height, float CardSpriteX, float CardSpriteY)
{
	//初始化数字
	this->number = number;
	this->wight=wight;
	//加入卡片背景颜色
	colorBackground = LayerColor::create(Color4B(200,190,180,255),wight-15,height-15);
	colorBackground->setPosition(Point(CardSpriteX,CardSpriteY));

	//判断如果大于0就显示，否则就不显示
	if (number > 0)
	{
		//加入字体
		labelCardNumber = LabelTTF::create(__String::createWithFormat("%i",number)->getCString(),"Consolas",100);
		labelCardNumber->setPosition(Point(colorBackground->getContentSize().width/2, colorBackground->getContentSize().height/2));
		labelCardNumber->setTag(8);
		colorBackground->addChild(labelCardNumber);
	}
	else
	{
		//加入字体
		labelCardNumber = LabelTTF::create("","Consolas",100);
		labelCardNumber->setPosition(Point(colorBackground->getContentSize().width/2, colorBackground->getContentSize().height/2));
		labelCardNumber->setTag(8);
		colorBackground->addChild(labelCardNumber);
	}

	this->addChild(colorBackground);
}