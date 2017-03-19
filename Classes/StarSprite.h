#ifndef __STARSPRITE_H__
#define __STARSPRITE_H__

#include "cocos2d.h"

enum class StarColor 
{
	BLUE,
	GREEN,
	PURPLE,
	RED,
	ORANGE
};

class StarSprite : public cocos2d::Sprite
{
public:
	StarSprite();
	~StarSprite();
	CREATE_FUNC(StarSprite);
	bool		init();
	void		setStarColor(StarColor color);
	void		setHighLight(bool flag);
	StarColor	getStarColor();
	bool		isHighLight();
public:
	static cocos2d::Size starSize;
	static cocos2d::Size starHeartSize;
private:
	std::string getPNGNameByColor(StarColor color);
	StarColor	m_starcolor;
	bool		m_isHighLight;
	Sprite*		m_HighLightSprite;
};

#endif