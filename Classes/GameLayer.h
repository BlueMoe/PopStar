#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "StarSprite.h"
#include <functional>
#include "StatusLayer.h"

struct IntPairGreaterEqual : public std::binary_function<std::pair<int, int>, std::pair<int, int>,bool>
{
	bool operator ()(std::pair<int, int> lp, std::pair<int, int> rp)
	{
		if (lp.first == rp.first)
			return lp.second >= rp.second;
		else
			return lp.first > rp.first;
	}
};

class GameLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameLayer);
	bool init();
	bool StalemateCheck();
	void popOneStar(int x,int y);
	void popAllMarkedStars();
	void markStars(int x,int y);
	void clearMark();
	void setStatusLayer(StatusLayer* layer);
	void gameEnd(float dt);
private:
	std::vector<std::vector<StarSprite*>>	m_stars;
	std::vector<std::pair<int, int> >		m_willPopLocation;
	cocos2d::Size							starSize;
	cocos2d::Size							starHeartSize;
	cocos2d::Sprite*						m_bg_game;
	cocos2d::Sprite*						m_bg_stars;
	StatusLayer*							m_statusLayer;
	bool									m_isStalemate;
	int										m_leaveStarNum;
};

#endif // !__GAMELAYER_H__
