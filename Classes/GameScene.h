#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
#include "StatusLayer.h"
#include "SelectionScene.h"

class GameLayer;
class StatusLayer;

class GameScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(GameScene);
	bool init();
	void setLevelInformation(const LevelInformation& levelInfo);
private:
	GameLayer*			m_gameLayer;
	StatusLayer*		m_statusLayer;
};

#endif	