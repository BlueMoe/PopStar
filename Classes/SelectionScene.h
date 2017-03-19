#ifndef __SELECTIONSCENE_H__
#define __SELECTIONSCENE_H__

#include "cocos2d.h"
#include "ui\UIButton.h"

struct LevelInformation
{
	int firstStarScore;
	int SecondStarScore;
	int finalStarScore;
	int targetScore;
	int bestScore;
	int level;
};

class SelectionButton : public cocos2d::Node
{
public:
	CREATE_FUNC(SelectionButton);
	bool					init();
	void					setButtonNum(int num);
	void					setStarNum(int num);
	void					update(float delta);
	cocos2d::ui::Button*	getButton();
private:
	cocos2d::Sprite*				m_leftStar;
	cocos2d::Sprite*				m_middleStar;
	cocos2d::Sprite*				m_rightStar;
	cocos2d::ui::Button*			m_planter;
	cocos2d::Node*					m_buttonNumSprite;
	int								m_starNum;
	int								m_buttonNum;
	std::vector<cocos2d::Sprite*>	m_vStar;

};											

class SelectionScene : public cocos2d::Scene
{
public:										
		CREATE_FUNC(SelectionScene);			
	bool init();
	static LevelInformation getLevelInformationByIndex(int index);
private:
	static std::vector<LevelInformation>	m_LevelInfomations;
	std::vector<SelectionButton*>			m_buttons;
	const int LevelTargetScore[7] = { 1000 ,1500 ,2000, 3000 ,4000, 5000 ,6000 };
};

#endif
