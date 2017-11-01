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
	
	/*1. ����ҡ�˵ı���*/
	rocker_bg = Sprite::create("joystickBg.png");
	rocker_bg->setPosition(Vec2(150, 150));
	addChild(rocker_bg);
	rocker_bg->setScale(0.5);
	
	/*2. ����ҡ��*/
	rocker = Sprite::create("joystick.png");
	rocker->setPosition(Vec2(150, 150));
	addChild(rocker);
	rocker->setScale(0.5);
	addCtrl();


	return true;
}

/*��ǰ���󱻼��뵽����ڵ��ϻ���ø÷���*/
void JoyStick::onEnter()
{
	/*���ȵ��ø����onEnter����*/
	Layer::onEnter();

	/*�������㴥���ļ���, ������auto*/
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	/*����ʹ��lambda���ʽ��������������������̫��, �������ǻ���ʹ�ûص�����*/
	listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);

	/*ע�����*/
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
/*��ǰ����Ӹ������Ƴ�ʱ����ø÷���*/
void JoyStick::onExit()
{
	/*�ӷַ������Ƴ�ע��ļ���*/
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

	/*�����ø����onExit()����*/
	Layer::onExit();
}


bool JoyStick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*��������ʼ��ʱ�� ����������λ�ú��������ĵ�λ�õľ��� < Բ�İ뾶 ���ǲ���Move*/

	/*��ȡԲ�ĵ�Ͱ뾶*/
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
	/*�������ƶ���ʱ�� ����������λ�ú��������ĵ�λ�õľ��� < Բ�İ뾶 */

	/*��ȡԲ�ĵ�Ͱ뾶*/
	float radius = rocker_bg->getBoundingBox().size.width / 2;
	Vec2 center = rocker_bg->getPosition();

	/*��ȡ������λ��*/
	Vec2 touch_pos = touch->getLocation();
	float dis = touch_pos.distance(center);

	float angle = acos((touch_pos.x - center.x) / dis);

	if(dis <= radius) {
		rocker->setPosition(Vec2(touch_pos));
	}
 else {
	 /*������ϰ�Բ*/
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
	/*�ڽ�������ʱ����ҡ�˹�ΪԲ��λ��*/
	rocker->setPosition(rocker_bg->getPosition());
	dir = STAY;
}


void JoyStick::checkDirection(float angle)
{
	/*�ҷ���*/
	if (angle >= -M_PI / 8.0 && angle <= M_PI / 8.0) {
		dir = RIGHT;
	}
	/*�ұ��� -�˷�֮�� �� �˷�֮��*/
	if (angle >= -(M_PI / 8.0) && angle <= M_PI / 8.0) {
		dir = RIGHT;
	}
	/*���Ϸ��� �˷�֮�� �� �˷�֮����*/
	else if (angle >= M_PI / 8.0 && angle < 3 * M_PI / 8.0) {
		dir = R_UP;
	}
	/*�Ϸ��� �˷�֮���� �� �˷�֮����*/
	else if (angle >= 3 * M_PI / 8.0 && angle <= 5 * M_PI / 8.0) {
		dir = UP;
	}
	/*���Ϸ��� �˷�֮5�� �� �˷�֮����*/
	else if (angle > 5 * M_PI / 8.0 && angle < 7 * M_PI / 8.0) {
		dir = L_UP;
	}
	/*����*/
	else if ((angle >= 7 * M_PI / 8.0 && angle <= M_PI) || (angle <= -7 * M_PI / 8.0 && angle >= -M_PI)){
		dir = LEFT;
	}
	/*���·���*/
	else if (angle > -7 * M_PI / 8.0 && angle < -5 * M_PI / 8.0) {
		dir = L_DOWN;
	}
	/*�·���*/
	else if (angle >= -5 * M_PI / 8.0 && angle <= -3 * M_PI / 8.0) {
		dir = DOWN;
	}
	/*���·���*/
	else if (angle > -3 * M_PI / 8.0 && angle < -M_PI / 8.0) {
		dir = R_DOWN;
	}
}

void JoyStick::jump(CCObject *)
{
	CCLOG("���");
	MapUI * layer=(MapUI *)getParent();
	CCTMXTiledMap *tmx= (CCTMXTiledMap *)layer->getChildByTag(10);
	
	Hero * hero = (Hero *)tmx->getChildByName("hero");
	hero->setSpeedUp(300);
	


}

void JoyStick::addCtrl()
{
	CCMenuItemImage * jump = CCMenuItemImage::create("joystick.png", "joystick.png", this, menu_selector(JoyStick::jump));
	Menu * menu = Menu::create();
	menu->addChild(jump);
	menu->setPosition(800, 200);


	menu->alignItemsHorizontally();
	jump->setScale(0.5);
	


	CCMenuItemImage * hit = CCMenuItemImage::create("./skill/hit (1).png", "./skill/hit (1).png", this, menu_selector(JoyStick::skillRelease));
	hit->setPosition(jump->getPosition() - ccp(50, 50));
	hit->setTag(1);
	menu->addChild(hit);
	addChild(menu);
}

Hero * JoyStick::setHero()
{
	MapUI * map = (MapUI *)getParent();
	hero = map->getHero();
	return hero;
}

void JoyStick::skillRelease(CCObject * sender)
{
	//�жϵ�������ĸ�����
	CCMenuItemImage * skill = (CCMenuItemImage *)sender;
	int id =skill->getTag();

	setHero();

	if (hero->state != Hero::STATE::ATTACK)
	{
		hero->skillRelease(id);
	}
	

	CCLOG("%d", id);
}


