#ifndef JoyStick_hpp  
#define JoyStick_hpp  

#include "cocos2d.h"  
#include "mapUI.h"
USING_NS_CC;
class Hero;
/*����ҡ�˷����ö��*/
enum direction
{
	STAY = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	R_UP, //����  
	R_DOWN,
	L_UP,
	L_DOWN

};
class JoyStick : public Layer
{
public:
	
	static  direction  dir;
	virtual bool init() override;
	void checkDirection(float angle);
	void addCtrl();

	CREATE_FUNC(JoyStick);
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	Hero* hero;
	Hero * setHero();
	void jump(CCObject *);
	void skillRelease(CCObject *);
private:

	EventListenerTouchOneByOne* listener;  /*����Ϊ��Ա�����������Ƴ�����*/
	Sprite* rocker;  /*�����ȡ*/
	Sprite* rocker_bg;  /*�����ȡ*/
};

#endif  