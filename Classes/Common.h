
#ifndef __COMMON_H__
#define __COMMON_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
USING_NS_CC;


#define winSize CCDirector::sharedDirector()->getWinSize()

struct Common
{

	enum DIRECTION { LEFT, RIGHT, UP, DOWN, NONE };
	static CCScene* scene(CCLayer* layer)
	{
		CCScene* s = CCScene::create();
		s->addChild(layer);
		return s;
	}

	static void moveNode(CCNode* node, CCPoint pt)
	{
		node->setPosition(node->getPosition() + pt);
	}

	static char* format(int v, const char* prefix = "", const char* suffix = "")
	{
		static char buf[2048];
		sprintf(buf, "%s%d%s", prefix, v, suffix);
		return buf;
	}
	static CCAnimation* CreateAnimation(const char* filename, int start, int end, int width, float delay)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(filename);
	

		Vector<SpriteFrame*> arr;
		for (int i = start; i <= end; ++i)
		{
			CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(i*width, 0, width, texture->getContentSize().height));
			arr.pushBack(frame);
		}

		return CCAnimation::createWithSpriteFrames(arr, delay);
	}


	static CCPoint Point2Tile(CCTMXTiledMap* map, CCPoint ptInMap)
	{
		int dx = map->getTileSize().width;
		int dy = map->getTileSize().height;

		int x = ptInMap.x / dx;
		int y = ptInMap.y / dy;
		y = map->getMapSize().height - 1 - y;

		return ccp(x, y);
	}

	static Vec2 Point2Tile2(CCTMXTiledMap * map, Vec2 ptInMap)
	{
	int 	x = ptInMap.x / map->getContentSize().width * map->getMapSize().width;
	int 	y = map->getMapSize().height - ptInMap.y / map->getContentSize().height*map->getMapSize().height;
		return Vec2(x, y);
	}

	static CCPoint Tile2PointLB(CCTMXTiledMap* map, CCPoint ptTile)
	{
		ptTile.y = map->getMapSize().height - 1 - ptTile.y;

		return ccp(ptTile.x * map->getTileSize().width,
			ptTile.y * map->getTileSize().height);
	}


	static CCSpriteFrame* getSpriteFrame(const char* filename, int pos, int width)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(filename);
		CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(pos*width, 0, width, texture->getContentSize().height));
		return frame;
	}

	static Animate * createAnimate(String  filename,int count)
	{
		Vector<SpriteFrame*> spriteFrameVec;
		auto spriteFrameCache = SpriteFrameCache::getInstance();
		spriteFrameCache->addSpriteFramesWithFile(filename.getCString());


		char path[256] = { 0 };
		for (int i = 1; i <= count; ++i)
		{
			sprintf(path, "yudu%d.png", i);
		//	log("path = %s", path);
			SpriteFrame *pSpriteFrame = spriteFrameCache->getSpriteFrameByName(path);
			spriteFrameVec.pushBack(pSpriteFrame);
		}
		// 0.1那个参数必须设定，可以设定除默认值意外的任何值，如果你不设定，根本就无法播放Animate动作  
		// Cocos2d-x的坑还不少啊，各位需谨慎啊  
		auto animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1);
		animation->setDelayPerUnit(2.8f / 14.0f);//必须设置否则不会动态播放  
		animation->setRestoreOriginalFrame(true);//是否回到第一帧  
		animation->setLoops(-1);//重复次数 （-1:无限循环）  
		Animate *animate = Animate::create(animation);
		return animate;

	}


	static Animate * createAnimate(String  filename, String name,int count)
	{
		Vector<SpriteFrame*> spriteFrameVec;
		auto spriteFrameCache = SpriteFrameCache::getInstance();
		spriteFrameCache->addSpriteFramesWithFile(filename.getCString());


		char path[256] = { 0 };
		for (int i = 1; i <= count; ++i)
		{
			sprintf(path, "%s (%d).png", name.getCString(),i);
			//log("path = %s", path);
			SpriteFrame *pSpriteFrame = spriteFrameCache->getSpriteFrameByName(path);
			spriteFrameVec.pushBack(pSpriteFrame);
		}
		// 0.1那个参数必须设定，可以设定除默认值意外的任何值，如果你不设定，根本就无法播放Animate动作  
		// Cocos2d-x的坑还不少啊，各位需谨慎啊  
		auto animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1);
		animation->setDelayPerUnit(2.8f / 14.0f);//必须设置否则不会动态播放  
		animation->setRestoreOriginalFrame(true);//是否回到第一帧  
		animation->setLoops(-1);//重复次数 （-1:无限循环）  
		Animate *animate = Animate::create(animation);
		return animate;

	}
};

#endif