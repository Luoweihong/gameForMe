#include "Hero.h"
#include "Common.h"
#include "SceneMgr.h"
bool Hero::init()
{

	if (!Sprite::init())
	{
		return true;
	}
	
	
	/*for (int i = 1; i < 8; i++)
	{
	SpriteFrame * sprf = SpriteFrame::create(String::createWithFormat("walk%d.png", i)->getCString(), CCRectMake(0, 0, 84, 63));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(sprf, String::createWithFormat("walk%d.png", i)->getCString());
	}*/
	initWithFile("./Hero/dengmao (1).png");
	//创建动画
	_stay = Common::createAnimate("./Hero/dengmao", "dengmao", 4);
	_walk = Common::createAnimate("./Hero/dengmaowalk", "dengmaowalk", 8);
	 Common::createAnimate("./Hero/dengmaohit", "hit", 11,1);
	

	runAction(_stay);
	speed = 100;
	_speedUp = 0;
	_speedAcc = 10;
	_speedDown = _speedAcc;
	setAnchorPoint(Vec2(0,0));
	stateMachine = new StateMachine;
	
	state = STATE::STAY;
	stateMachine->init();
	scheduleUpdate();
	return true;
}

Hero * Hero::create()
{

	Hero * hero = new Hero;
	if (!hero->init())
	{
		return false;
	}
	return hero;
}

bool Hero::canMoveDown(float dt)
{
	//拿到MAP 对象 遍历所有的格子

	
	CCTMXTiledMap * map = getMap();
	if (map==NULL)
	{
		return false;
	}
	CCRect rcMario = boundingBox();
	//拿到层
	
	CCPoint pt[3];
	pt[0] = ccp(rcMario.getMidX(), rcMario.getMinY() - dt*_speedDown);
	pt[1] = ccp(rcMario.getMinX(), rcMario.getMinY() - dt*_speedDown);
	pt[2] = ccp(rcMario.getMaxX(), rcMario.getMinY() - dt*_speedDown);

	if (pt[0].y >= map->getContentSize().height)
		return true;
	for (int i = 0; i < 3;i++)
	{
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		static const char* layerName[2] = { "land","land2" };
		for (int j = 0; j < sizeof(layerName)/4; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
			if (layer==NULL)
			{
				continue;
			}
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				_speedDown = _speedAcc;
				CCPoint ptLB = Common::Tile2PointLB(map, ptTile + ccp(0, -1));
				this->setPositionY(ptLB.y-20);
				return false;
			}
		}
	}
	return true;
}

void Hero::moveDown(float dt)
{
	if (_speedUp<=0)
	{
		if (canMoveDown(dt))
		{
			Common::moveNode(this, ccp(0, -dt*_speedDown));
			_speedDown += _speedAcc;
		}
		else
		{

		}
	}
}


void Hero::run()
{
	Vector<CCAnimationFrame*> array;
	for (int i = 1; i <8 ; i++) {
		char str[50];
		sprintf(str, "walk%d.png", i);

		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		CCAnimationFrame* animationFrame = new CCAnimationFrame();

		animationFrame->setSpriteFrame(frame); //设置精灵帧
		animationFrame->setDelayUnits(i);    //设置间隔帧数

		array.pushBack(animationFrame);
	}

	//使用动画帧数组创建，单位帧间隔0.2秒

	//使用动画帧数组创建，单位帧间隔0.2秒
	CCAnimation* animation = CCAnimation::create(array, 1.0/60);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	CCAnimate* animate = CCAnimate::create(animation);
	runAction(animate);
}

void Hero::update(float dt)
{
	int dir = JoyStick::dir;
#ifdef WIN32
	short key;

	key = GetKeyState('D');
	if (key < 0) {
		dir = 4;
	

	}

	key = GetKeyState('A');
	if (key < 0) {
		dir = 3;
	
	}
#endif
	
	if (state == STATE::ATTACK)
	{
		return;
	}
	
	switch (dir)
	{
		//向右走
	case 3:
		CCLOG("%d", state);
		moveLeft(dt);
		break;
	case 4:
		
		moveRight(dt);
		break;
	case 1:
	{
			  CCTMXTiledMap * map = getMap();
			  Rect hero = boundingBox();

			  Vec2 ptToNext = Vec2(hero.getMidX(), hero.getMidY());
			  CCTMXLayer * layer = map->layerNamed("tp");
			  Vect ptTile = Common::Point2Tile2(map, ptToNext);
			  if (layer==NULL)
			  {
				  return;
			  }

			  int gid = layer->tileGIDAt(ptTile);
			  if (gid != 0)
			  {
				  CCLOG("传送11111");
				  unscheduleUpdate();
				  SceneMgr * sceneMgr = SceneMgr::getSceneMgr();
				  sceneMgr->changeScene("./map/map2.tmx");

			  }
	}
		break;
	case 0:
		if (state != STATE::STAY)
		{
			state = STAY;
			CCLOG("updataStatus(0);");
			stopAllActions();
			updataStatus(0);
		}
		break;

	default:
		


		break;
	}
	moveUp(dt);
	moveDown(dt);
}



void Hero::updataStatus(int state)
{
	switch (state)
	{
	case 3:
		CCLOG("dengmaowalk");
		runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("dengmaowalk"))));
		break;

	case 0:
		runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("dengmao"))));
	break;


	default:
		break;
	}


}

bool Hero::canMoveLeft(float dt)
{
	CCTMXTiledMap * map = getMap();
	Vec2 ptInWorld = map->convertToWorldSpace(this->getPosition());
	if (ptInWorld.x-this->getContentSize().width/2<0)
	{
		return false;
	}

	return true;
}

bool Hero::canMoveRight(float)
{
	CCTMXTiledMap * map = getMap();
	Vec2 ptInWorld = map->convertToWorldSpace(this->getPosition());
	if (ptInWorld>winSize)
	{
		return false;
	}


	return true;
}

void Hero::move(float dt)
{
	moveUp(dt);
}

void Hero::moveUp(float dt)
{
	if (_speedUp<=0)
	{
		return;
		
	}
	if (!canMoveUp(dt))
	{
		return;
	}
	Common::moveNode(this, ccp(0,_speedUp*dt)); 
	_speedUp = _speedUp - _speedAcc;
}

bool Hero::canMoveUp(float dt)
{
	CCTMXTiledMap  * map = getMap();
	Rect rcHero = getBoundingBox();

	
	Vec2 pt[3];


	pt[0] = ccp(rcHero.getMaxX(), rcHero.getMaxY() - dt*_speedDown);
	
	char * layername = { "land" };

	for (int i = 0; i < strlen(layername);i++)
	{
		CCTMXLayer *layer = map->layerNamed("land");
		//点转换成格子坐标
		for (int i = 0; i < 1;i++)
		{
			Vec2  ptTile = Common::Point2Tile2(map,pt[i]);
			int gid=layer->getTileGIDAt(ptTile);

			if (gid!=0)
			{
				CCPoint ptLB = Common::Tile2PointLB(map, ptTile);
				
				_speedUp = 0;
				return false;

			}
		}

	}

	return true;
}

void Hero::moveRight(float dt)
{
	if (state != STATE::WALK)
	{
		CCLOG("dengmaowalk");
		state = STATE::WALK;
		stopAllActions();
		updataStatus(3);
	}
	CCFlipX *action = CCFlipX::create(false);
	runAction(action);
	if (stateMachine->getState()==StateMachine::FACE::RIGHT)
	{
		setScaleX(1);
	}
	if (!canMoveRight(dt))
		return;

	Common::moveNode(this, ccp(dt*speed, 0));
	Vec2 ponitInWorld = getMap()->convertToWorldSpace(this->getPosition());
	Vec2 ptInMap = getMap()->convertToNodeSpace(this->getPosition());
	if (ponitInWorld.x>winSize.width/2)
	{
		if (ptInMap.x>getMap()->getContentSize().width)
		{
			return;
		}
		Common::moveNode(getMap(), Vec2(-dt*speed, 0));
	}

}

void Hero::moveLeft(float dt)
{

	if (state != STATE::WALK)
	{
		CCLOG("dengmaowalk");
		state = STATE::WALK;
		stopAllActions();
		updataStatus(3);
	}

	CCFlipX *action = CCFlipX::create(true);
	runAction(action);
	if (!canMoveLeft(dt))
	{
		return ;
	}
	Common::moveNode(this, Vec2(-dt*speed, 0));
	CCTMXTiledMap * map = getMap();

	Vec2 pointInWorld = map->convertToWorldSpace(this->getPosition());
	Vec2 ptInMap = map->convertToNodeSpace(this->getPosition());
	int x = this->getPositionX();
	if (pointInWorld.x<winSize.width/2)
	{
		
		if (ptInMap.x<winSize.width/2)
		{

			return;
		}
		else
		{

			Common::moveNode(getMap(), Vec2(dt*speed, 0));
		}
	}
}




void Hero::skillRelease(int skill_id)
{
	
	stopAllActions();
	switch (skill_id)
	{
	case 1:
	{
			  state = ATTACK;
			  CCCallFunc *callfun = CCCallFunc::create([&](){
				  CCLOG("state == NONE");
				  state = STATE::NONE;
				  CCLOG("state == NONE %d",state);
			  });
			  auto delay = DelayTime::create(0.2f);
			  _hit =Animate::create(AnimationCache::getInstance()->getAnimation("hit"));
			  CCSequence * sequence = CCSequence::create(_hit,delay,callfun , nullptr);
			  runAction(sequence);
	}
		break;
	default:
		break;
	}

	
}


