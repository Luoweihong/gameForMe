#include "JoyStick.h"  
#include "Common.h"
#include "Hero.h"
USING_NS_CC;

direction JoyStick::dir = direction::STAY;

bool JoyStick::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	/*1. 创建摇杆的背景*/
	 rocker_bg = Sprite::create("joystickBg.png");
	rocker_bg->setPosition(Vec2(150, 150));
	addChild(rocker_bg);
	rocker_bg->setScale(0.5);
	
	/*2. 创建摇杆*/
	 rocker = Sprite::create("joystick.png");
	rocker->setPosition(Vec2(150, 150));
	addChild(rocker);
	rocker->setScale(0.5);


	
	
	
	

	CCMenuItemImage * jump = CCMenuItemImage::create("joystick.png", "joystick.png", this, menu_selector(JoyStick::jump));
	Menu * menu = Menu::create();
	menu->addChild(jump);
	menu->setPosition(800, 200);


	menu->alignItemsVertically();
	jump->setScale(0.5);
	addChild(menu);
	return true;
}

/*当前对象被加入到父类节点上会调用该方法*/
void JoyStick::onEnter()
{
	/*首先调用父类的onEnter方法*/
	Layer::onEnter();

	/*开启单点触摸的监听, 可以用auto*/
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	/*可以使用lambda表达式来创建，但那样看起来太乱, 这里我们还是使用回调函数*/
	listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);

	/*注册监听*/
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
/*当前对象从父类上移除时会调用该方法*/
void JoyStick::onExit()
{
	/*从分发中心移除注册的监听*/
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

	/*最后调用父类的onExit()方法*/
	Layer::onExit();
}


bool JoyStick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*当触摸开始的时候， 如果触摸点的位置和我们中心点位置的距离 < 圆的半径 我们才能Move*/

	/*获取圆心点和半径*/
	float radius = rocker_bg->getContentSize().width / 2;
	Vec2 center = rocker_bg->getPosition();

	if (touch->getLocation().distance(center) > radius) {
		return false;
	}
	else {
		rocker->setPosition(Vec2(touch->getLocation()));
		return true;
	}
}

void JoyStick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*当触摸移动的时候， 如果触摸点的位置和我们中心点位置的距离 < 圆的半径 */

	/*获取圆心点和半径*/
	float radius = rocker_bg->getBoundingBox().size.width / 2;
	Vec2 center = rocker_bg->getPosition();

	/*获取触摸点位置*/
	Vec2 touch_pos = touch->getLocation();
	float dis = touch_pos.distance(center);

	float angle = acos((touch_pos.x - center.x) / dis);

	if(dis <= radius) {
		rocker->setPosition(Vec2(touch_pos));
	}
 else {
	 /*如果在上半圆*/
	 if (touch_pos.y > center.y) {
		 rocker->setPosition(Vec2(center.x + radius*cos(angle), center.y + radius*sin(angle)));
		 checkDirection(angle);
	 }
	 else {
		 checkDirection(-angle);
		 rocker->setPosition(Vec2(center.x + radius*cos(angle), center.y - radius*sin(angle)));
	 }
 }
}

void JoyStick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*在结束触摸时，将摇杆归为圆点位置*/
	rocker->setPosition(rocker_bg->getPosition());
	dir = STAY;
}


void JoyStick::checkDirection(float angle)
{
	/*右方向*/
	if (angle >= -M_PI / 8.0 && angle <= M_PI / 8.0) {
		dir = RIGHT;
	}
	/*右边走 -八分之派 到 八分之派*/
	if (angle >= -(M_PI / 8.0) && angle <= M_PI / 8.0) {
		dir = RIGHT;
	}
	/*右上方向 八分之派 到 八分之三派*/
	else if (angle >= M_PI / 8.0 && angle < 3 * M_PI / 8.0) {
		dir = R_UP;
	}
	/*上方向 八分之三派 到 八分之五派*/
	else if (angle >= 3 * M_PI / 8.0 && angle <= 5 * M_PI / 8.0) {
		dir = UP;
	}
	/*左上方向 八分之5派 到 八分之七派*/
	else if (angle > 5 * M_PI / 8.0 && angle < 7 * M_PI / 8.0) {
		dir = L_UP;
	}
	/*左方向*/
	else if ((angle >= 7 * M_PI / 8.0 && angle <= M_PI) || (angle <= -7 * M_PI / 8.0 && angle >= -M_PI)){
		dir = LEFT;
	}
	/*左下方向*/
	else if (angle > -7 * M_PI / 8.0 && angle < -5 * M_PI / 8.0) {
		dir = L_DOWN;
	}
	/*下方向*/
	else if (angle >= -5 * M_PI / 8.0 && angle <= -3 * M_PI / 8.0) {
		dir = DOWN;
	}
	/*右下方向*/
	else if (angle > -3 * M_PI / 8.0 && angle < -M_PI / 8.0) {
		dir = R_DOWN;
	}
}

void JoyStick::jump(CCObject *)
{
	CCLOG("点击");
	MapUI * layer=(MapUI *)getParent();
	CCTMXTiledMap *tmx= (CCTMXTiledMap *)layer->getChildByTag(10);
	
	Hero * hero = (Hero *)tmx->getChildByName("hero");
	hero->setSpeedUp(300);
	hero->updataStatus();


}
