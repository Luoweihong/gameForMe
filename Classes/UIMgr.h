#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC; 
class UIMgr
{
public :
	Node * getCsb(String name);
	
	static UIMgr * getUIMgr();
private:
	UIMgr(){

	}
	static UIMgr * _uiMgr;
};