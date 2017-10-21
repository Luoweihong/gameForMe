
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
};

#endif