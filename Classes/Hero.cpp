#include "Hero.h"
#include "Common.h"

bool Hero::init()
{
	if (!Sprite::init())
	{
		return true;
	}
	
	
	for (int i = 1; i < 8;i++)
	{
		SpriteFrame * sprf = SpriteFrame::create(String::createWithFormat("walk%d.png", i)->getCString(), CCRectMake(0, 0, 84, 63));
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(sprf, String::createWithFormat("walk%d.png", i)->getCString());
	}
	initWithFile("walk1.png");
	run();
	speed = 100;
	
	_speedUp = 0;
	_speedAcc = 10;
	_speedDown = _speedAcc;
	setAnchorPoint(Vec2(0.5,0));
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
		static const char* layerName[1] = { "land" };
		for (int j = 0; j < 1; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
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
	if (key < 0) moveRight(dt);

	key = GetKeyState('A');
	if (key < 0) moveLeft(dt);

#endif
	

	switch (dir)
	{
		//向右走
	case 3:
		moveLeft(dt);
		break;
	case 4:
		moveRight(dt);
		break;
	default:
		break;
	}
	moveUp(dt);
	moveDown(dt);
}

void Hero::updataStatus()
{

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
			Vec2  ptTile = Common::Point2Tile(map,pt[i]);
			int gid=layer->getTileGIDAt(ptTile);

			if (gid!=0)
			{
				CCPoint ptLB = Common::Tile2PointLB(map, ptTile);
				this->setPositionY(ptLB.y);
				_speedUp = 0;
				return false;

			}
		}

	}

	return true;
}

void Hero::moveRight(float dt)
{
	if (!canMoveRight(dt))
		return;

	Common::moveNode(this, ccp(dt*speed, 0));
	Vec2 ponitInWorld = getMap()->convertToWorldSpace(this->getPosition());
	Vec2 ptInMap = getMap()->convertToNodeSpace(this->getPosition());
	if (ponitInWorld.x>winSize.width/2)
	{
		CCLOG("%f", ptInMap.x);
		CCLOG("%f", ponitInWorld.x);
		CCLOG("contentsize%f", getMap()->getContentSize().width);
		if (ptInMap.x>getMap()->getContentSize().width)
		{
			return;
		}

		Common::moveNode(getMap(), Vec2(-dt*speed, 0));
		
		


	}

}

void Hero::moveLeft(float dt)
{
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

