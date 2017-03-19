#ifndef __STATUSLAYER_H__
#define __STATUSLAYER_H__

#include "cocos2d.h"
#include "SelectionScene.h"

class LevelClearBox : public cocos2d::Node
{
public:
	CREATE_FUNC(LevelClearBox);
	std::function<void()>	toNextLevelFunction;
	std::function<void()>	toSelectionSceneFunction;
	std::function<void()>	reStartFunction;
	void					setTarget(int target);
	void					setScore(int score);
	void					setTargetClearNum(int num);
	bool					init();

private:
	cocos2d::ui::Button*	m_buttonToSelectionScene;
	cocos2d::ui::Button*	m_buttonToNextLevel;
	cocos2d::ui::Button*	m_buttonToReStart;
	cocos2d::Sprite*		m_backGround;
	cocos2d::Sprite*		m_starSprite[3];
	cocos2d::Sprite*		m_title;
	cocos2d::Sprite*		m_targetTitle;
	Node*					m_rewardSprite;
	Node*					m_scoreSprite;

};

class LevelFailedBox : public cocos2d::Node
{
public:
	CREATE_FUNC(LevelFailedBox);
	std::function<void()>	toSelectionSceneFunction;
	std::function<void()>	reStartFunction;
	void					setTarget(int target);
	void					setScore(int score);
	bool					init();

private:
	cocos2d::ui::Button*	m_buttonToSelectionScene;
	cocos2d::ui::Button*	m_buttonToReStart;
	cocos2d::Sprite*		m_backGround;
	cocos2d::Sprite*		m_title;
	cocos2d::Sprite*		m_targetTitle;
	Node*					m_targetSprite;
	Node*					m_scoreSprite;

};

class StatusLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(StatusLayer);
	void	update(float delta);
	int		getScore();
	void    setScore(int score);
	void	setLevelInformation(const LevelInformation & levelInfo);
	void	gameEnd(int num);
	bool	init();
private:
	cocos2d::ProgressTimer* m_bar;
	cocos2d::Sprite*		m_starSprite[3];
	cocos2d::Size			m_visibleSize;
	LevelInformation		m_levelInfo;
	time_t					m_startTime;
	Node*					m_scoreSprite;
	Node*					m_playTimeSprite;
	int						m_score;



};

#endif