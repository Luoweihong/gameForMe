#ifndef JoyStick_hpp  
#define JoyStick_hpp  

#include "cocos2d.h"  
#include "mapUI.h"
class Hero;
/*定义摇杆方向的枚举*/
enum direction
{
	STAY = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	R_UP, //右上  
	R_DOWN,
	L_UP,
	L_DOWN

};
class JoyStick : public cocos2d::Layer
{
public:
	
	static  direction  dir;
	virtual bool init() override;
	void JoyStick::checkDirection(float angle);
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

	cocos2d::EventListenerTouchOneByOne* listener;  /*定义为成员变量，方便移除监听*/
	cocos2d::Sprite* rocker;  /*方便获取*/
	cocos2d::Sprite* rocker_bg;  /*方便获取*/
};

#endif  