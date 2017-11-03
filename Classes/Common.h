
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
		// 0.1那个参数必须设定，可以设定除默认值意外的任何值，如果你不设定，根本就无法播放Animate动作  
		// Cocos2d-x的坑还不少啊，各位需谨慎啊  
		auto animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1);
		animation->setDelayPerUnit(0.15f);//必须设置否则不会动态播放  
		animation->setRestoreOriginalFrame(true);//是否回到第一帧  
		animation->setLoops(loops);//重复次数 （-1:无限循环）
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, name.getCString());

		Animate *animate = Animate::create(animation);
		return animate;
	}

	static void HeapSort(Vector<Sprite *> nodes, int size)
	{
		int i;
		BuildHeap(nodes, size);

		for (i = size-1; i > 0; i--)
		{
			//cout<<a[1]<<" ";
			Sprite * first = nodes.at(0);
			Sprite * parent = nodes.at(i);

			nodes.replace(i, first);
			nodes.replace(1, parent);       //交换堆顶和最后一个元素，即每次将剩余元素中的最大者放到最后面 
			//BuildHeap(a,i-1);        //将余下元素重新建立为大顶堆 
			HeapAdjust(nodes, 1, i - 1);      //重新调整堆顶节点成为大顶堆
		}



	}

	static void BuildHeap(Vector<Sprite *> nodes, int size)
	{
		
		for (int i = size/2-1; i >0; i--)
		{
			HeapAdjust(nodes, i, size);
		}


	}
	static void HeapAdjust(Vector<Sprite *>nodes, int i, int size)
	{
		ssize_t lchild = 2 * i;
		ssize_t rchild = 2 * i + 1;
		ssize_t max = i;

		if (i<=size/2-1)
		{
			if (lchild <= size&&nodes.at(lchild)->getPositionX()>nodes.at(max)->getPositionX())
			{
				max = lchild;
			}
			if (rchild <= size&&nodes.at(rchild)->getPositionX()>nodes.at(max)->getPositionX())
			{
				max = rchild;
			}
		}
		if (max != i)
		{
			Sprite * child=nodes.at(max);
			Sprite * parent = nodes.at(i);

			nodes.replace(i, child);
			nodes.replace(max, parent);

			HeapAdjust(nodes, max, size);    //避免调整之后以max为父节点的子树不是堆 
		}
	}

	static String* numToString(int num)
	{
		char number[100] = { 0 };
		
		int temp = 0; 
		int i = 0;
		while (num / 10)
		{
			temp = num % 10;
			num = num / 10;
			number[i] = temp + '0';
			i++;
		}
		temp = num % 10;
		number[i] = temp + '0';

		int head = 0;
		int tail = strlen(number)-1;

		while(tail>head)
		{
			char temp = number[head];
			number[head]=number[tail];
			number[tail] = temp;
			head++;
			tail--;
		}




		return String::create(number);
	}

	
};

#endif
