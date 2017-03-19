#include "StarSprite.h"
#include <time.h>
#include "2d\CCSpriteFrameCache.h"
#include <stdlib.h>
#include <iostream>
#include "CCPlatformMacros.h"

using namespace cocos2d;

Size StarSprite::starSize = Size(62, 62);
Size StarSprite::starHeartSize = Size(62, 62);

StarSprite::StarSprite()
{

}

StarSprite::~StarSprite()
{

}

bool StarSprite::init()
{
	m_isHighLight = false;
	static std::string colorstr;
	srand((unsigned)time(0) + rand()); //ͬһ���� srand(time(0));rand()����� ��������ͬ�ģ����Խ�������Ϊsrand(time(0) + rand())���Ա�������ͼ�궼һ����
	int x = rand()%5;
	m_starcolor =  static_cast<StarColor>(x);
	colorstr = getPNGNameByColor(m_starcolor);

	if(!initWithSpriteFrameName(colorstr)) return false;
	m_HighLightSprite = Sprite::createWithSpriteFrameName("highlight.png");
	m_HighLightSprite->setPosition(starSize.width / 2, starSize.height / 2);
	m_HighLightSprite->setVisible(false);
	addChild(m_HighLightSprite);

	return true;
}

void StarSprite::setStarColor(StarColor color)
{
	m_starcolor = color;
}

void StarSprite::setHighLight(bool flag)
{
	m_isHighLight = flag;
	m_HighLightSprite->setVisible(flag);
}

StarColor StarSprite::getStarColor()
{
	return m_starcolor;
}

bool StarSprite::isHighLight()
{
	return m_isHighLight;
}

std::string StarSprite::getPNGNameByColor(StarColor color)
{
	std::string colorstr;
	switch (color)
	{
	case StarColor::BLUE:colorstr = "blue";
		break;
	case StarColor::GREEN:colorstr = "green";
		break;
	case StarColor::PURPLE:colorstr = "purple";
		break;
	case StarColor::RED:colorstr = "red";
		break;
	case StarColor::ORANGE:colorstr = "orange";
		break;
	default:
		break;
	}
	colorstr += ".png";
	return colorstr;
}