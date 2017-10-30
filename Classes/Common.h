
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
		// 0.1�Ǹ����������趨�������趨��Ĭ��ֵ������κ�ֵ������㲻�趨���������޷�����Animate����  
		// Cocos2d-x�Ŀӻ����ٰ�����λ�������  
		auto animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1);
		
		animation->setDelayPerUnit(2.8f / 14.0f);//�������÷��򲻻ᶯ̬����  
		animation->setRestoreOriginalFrame(true);//�Ƿ�ص���һ֡  
		animation->setLoops(-1);//�ظ����� ��-1:����ѭ����  
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation,"yudu");
		Animate *animate = Animate::create(animation);
		return animate;

	}


	static Animate * createAnimate(String  filename, String name,int count,int loops=-1)
	{
		Vector<SpriteFrame*> spriteFrameVec;
		auto spriteFrameCache = SpriteFrameCache::getInstance();
		
		char anim[100];

		sprintf(anim,"%s%s",filename.getCString(),".plist");
		spriteFrameCache->addSpriteFramesWithFile(anim);
		char path[256] = { 0 };
		for (int i = 1; i <= count; ++i)
		{
			sprintf(path, "%s (%d).png", name.getCString(),i);
			//log("path = %s", path);
			SpriteFrame *pSpriteFrame = spriteFrameCache->getSpriteFrameByName(path);
			spriteFrameVec.pushBack(pSpriteFrame);
		}
		// 0.1�Ǹ����������趨�������趨��Ĭ��ֵ������κ�ֵ������㲻�趨���������޷�����Animate����  
		// Cocos2d-x�Ŀӻ����ٰ�����λ�������  
		auto animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1);
		animation->setDelayPerUnit(0.15f);//�������÷��򲻻ᶯ̬����  
		animation->setRestoreOriginalFrame(true);//�Ƿ�ص���һ֡  
		animation->setLoops(loops);//�ظ����� ��-1:����ѭ����
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, name.getCString());

		Animate *animate = Animate::create(animation);
		return animate;
	}

	void HeapSort(Vector<Sprite> nodes, int size)
	{
		int i;
		BuildHeap(nodes,size);
	}

	void BuildHeap(Vector<Sprite> nodes, int size)
	{

	}



};

#endif