#include "cocos2d.h"

USING_NS_CC;

class FlyWord:public Node
{
public:
	static FlyWord* create(const char * word,int fontSize,Vec2 begin);


	bool init(const char * word, const int fontsize, Vec2 begin);
	void Flying();

	void Flyend();
protected:
private:

	int _fontSize;//�����С
	CCPoint _begin;//Ҫ��ӵ��Ĺ�������ĵ�
	CCLabelBMFont* m_plabel;//��������

};