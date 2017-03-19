#include "StatusLayer.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui\UIButton.h"
#include "ui\UIWidget.h"
#include "Number.h"
#include <time.h>
#include "GameScene.h"

using namespace cocos2d;
const int CURRENT_SCORE_SPRITE_TAG = 6666;
const int PLAY_TIME_SPRITE_TAG = 6667;

bool LevelClearBox::init()
{
	if (!Node::init())	return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	setContentSize(visibleSize);

	m_backGround = Sprite::create("end_box.png");
	m_backGround->setPosition(Point(visibleSize.width * 318.5 / 640, visibleSize.height*464.5 / 960));
	addChild(m_backGround);

	m_starSprite[0] = Sprite::create("game_end_left_star_gray.png");
	m_starSprite[0]->setPosition(Point(visibleSize.width * 168.5 / 640, visibleSize.height*770.5 / 960));
	addChild(m_starSprite[0]);

	m_starSprite[1] = Sprite::create("game_end_middle_star_gray.png");
	m_starSprite[1]->setPosition(Point(visibleSize.width * 314 / 640, visibleSize.height*794.5 / 960));
	addChild(m_starSprite[1]);

	m_starSprite[2] = Sprite::create("game_end_right_star_gray.png");
	m_starSprite[2]->setPosition(Point(visibleSize.width * 466 / 640, visibleSize.height * 770 / 960));
	addChild(m_starSprite[2]);

	m_title = Sprite::create("level_clear_title.png");
	m_title->setPosition(Point(visibleSize.width * 319.7 / 640, visibleSize.height * 663.5 / 960));
	addChild(m_title);

	m_targetTitle = Sprite::create("target.png");
	m_targetTitle->setPosition(Point(visibleSize.width * 316.9 / 640, visibleSize.height * 429 / 960));
	addChild(m_targetTitle);

	m_buttonToSelectionScene = ui::Button::create("to_selection_scene.png");
	m_buttonToSelectionScene->setPosition(Point(visibleSize.width * 149 / 640, visibleSize.height * 159 / 960));
	addChild(m_buttonToSelectionScene);
	auto buttonToSelectionSceneListener = [=](Object* object, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			toSelectionSceneFunction();
		}
	};
	m_buttonToSelectionScene->addTouchEventListener(buttonToSelectionSceneListener);

	m_buttonToReStart = ui::Button::create("to_restart.png");
	m_buttonToReStart->setPosition(Point(visibleSize.width * 320 / 640, visibleSize.height * 159 / 960));
	addChild(m_buttonToReStart);
	auto buttonToReStartListener = [=](Object* object, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			reStartFunction();
		}
	};
	m_buttonToReStart->addTouchEventListener(buttonToReStartListener);

	m_buttonToNextLevel = ui::Button::create("to_next_level.png");
	m_buttonToNextLevel->setPosition(Point(visibleSize.width * 489.7 / 640, visibleSize.height * 159 / 960));
	addChild(m_buttonToNextLevel);
	auto buttonToNextLevelListener = [=](Object* object, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			toNextLevelFunction();
		}
	};
	m_buttonToNextLevel->addTouchEventListener(buttonToNextLevelListener);

	return true;
}

void LevelClearBox::setTarget(int target)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_rewardSprite = Number::createNumberNode(target);
	m_rewardSprite->setAnchorPoint(Point(0.5, 0.5));
	m_rewardSprite->setPosition(Point(visibleSize.width * 316.9 / 640, visibleSize.height * 316 / 960));
	addChild(m_rewardSprite);
}

void LevelClearBox::setScore(int score)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_scoreSprite = Number::createNumberNode(score);
	m_scoreSprite->setAnchorPoint(Point(0, 0.5));
	m_scoreSprite->setPosition(Point(visibleSize.width * 300 / 640, visibleSize.height * 535.5 / 960));
	addChild(m_scoreSprite);
}

void LevelClearBox::setTargetClearNum(int num)
{
	if (num >= 1)
	{
		m_starSprite[0]->initWithFile("game_end_left_star.png");
	}
	if (num >= 2)
	{
		m_starSprite[1]->initWithFile("game_end_middle_star.png");
	}
	if (num >= 3)
	{
		m_starSprite[2]->initWithFile("game_end_right_star.png");
	}
}

void LevelFailedBox::setTarget(int target)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_targetSprite = Number::createNumberNode(target);
	m_targetSprite->setAnchorPoint(Point(0.5, 0.5));
	m_targetSprite->setPosition(Point(visibleSize.width * 316.9 / 640, visibleSize.height * 316 / 960));
	addChild(m_targetSprite);
}

void LevelFailedBox::setScore(int score)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_scoreSprite = Number::createNumberNode(score);
	m_scoreSprite->setAnchorPoint(Point(0, 0.5));
	m_scoreSprite->setPosition(Point(visibleSize.width * 300 / 640, visibleSize.height * 535.5 / 960));
	addChild(m_scoreSprite);
}

bool LevelFailedBox::init()
{
	if (!Node::init()) return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	setContentSize(visibleSize);

	m_backGround = Sprite::create("end_box.png");
	m_backGround->setPosition(Point(visibleSize.width * 318.5 / 640, visibleSize.height*464.5 / 960));
	addChild(m_backGround);

	m_title = Sprite::create("level_failed_title.png");
	m_title->setPosition(Point(visibleSize.width * 380.5 / 640, visibleSize.height * 754 / 960));
	addChild(m_title);

	m_targetTitle = Sprite::create("target.png");
	m_targetTitle->setPosition(Point(visibleSize.width * 316.9 / 640, visibleSize.height * 429 / 960));
	addChild(m_targetTitle);

	m_buttonToSelectionScene = ui::Button::create("to_selection_scene.png");
	m_buttonToSelectionScene->setPosition(Point(visibleSize.width * 235 / 640, visibleSize.height * 159 / 960));
	addChild(m_buttonToSelectionScene);
	auto buttonToSelectionSceneListener = [=](Object* object, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			toSelectionSceneFunction();
		}
	};

	m_buttonToReStart = ui::Button::create("to_restart.png");
	m_buttonToReStart->setPosition(Point(visibleSize.width * 404 / 640, visibleSize.height * 159 / 960));
	addChild(m_buttonToReStart);
	auto buttonToRestartListener = [=](Object* object, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			reStartFunction();
		}
	};
	m_buttonToReStart->addTouchEventListener(buttonToRestartListener);

	return true;
}



bool StatusLayer::init()
{
	if (!Layer::init())	return false;

	m_score = 0;
	m_visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* statusBackground = Sprite::create("statusBackground.png");
	statusBackground->setAnchorPoint(Point(0, 1));
	statusBackground->setPosition(0, m_visibleSize.height);
	addChild(statusBackground);

	Sprite* bar = Sprite::create("bar.png");
	m_bar = ProgressTimer::create(bar);
	m_bar->setPercentage(0);
	m_bar->setAnchorPoint(Point(0.5, 0.5));
	m_bar->setPosition(Point(m_visibleSize.width*430.5 / 640, m_visibleSize.height * 866.5 / 960));
	m_bar->setType(ProgressTimer::Type::BAR);
	m_bar->setBarChangeRate(Vec2(1, 0));
	m_bar->setMidpoint(Vec2(0, 0));
	addChild(m_bar);

	Sprite* targetScoreTitle = Sprite::createWithSpriteFrameName("word_06.png");
	targetScoreTitle->setPosition(Point(m_visibleSize.width * 222 / 640, m_visibleSize.height * 918 / 960));
	addChild(targetScoreTitle);

	m_starSprite[0] = Sprite::create("target_star_grey.png");
	m_starSprite[0]->setPosition(Point(m_visibleSize.width*343.5 / 640, m_visibleSize.height * 867 / 960));
	addChild(m_starSprite[0]);

	m_starSprite[1] = Sprite::create("target_star_grey.png");
	m_starSprite[1]->setPosition(Point(m_visibleSize.width*483.5 / 640, m_visibleSize.height * 867 / 960));
	addChild(m_starSprite[1]);

	m_starSprite[2] = Sprite::create("target_star_grey.png");
	m_starSprite[2]->setPosition(Point(m_visibleSize.width*622.5 / 640, m_visibleSize.height * 867 / 960));
	addChild(m_starSprite[2]);

	m_startTime = time(0);
	scheduleUpdate();
	return true;
}

void StatusLayer::update(float delta)
{
	if (getChildByTag(PLAY_TIME_SPRITE_TAG))
	{
		removeChildByTag(PLAY_TIME_SPRITE_TAG);
	}
	m_playTimeSprite = Number::getInstance()->createTimeNode(time(0) - m_startTime);
	m_playTimeSprite->setAnchorPoint(Point(0.5, 0.5));
	m_playTimeSprite->setPosition(Point(m_visibleSize.width*0.14f, m_visibleSize.height*0.96f));
	m_playTimeSprite->setTag(PLAY_TIME_SPRITE_TAG);
	addChild(m_playTimeSprite);

	if (getChildByTag(CURRENT_SCORE_SPRITE_TAG))
	{
		removeChildByTag(CURRENT_SCORE_SPRITE_TAG);
	}
	m_scoreSprite = Number::getInstance()->createNumberNode(m_score);
	m_scoreSprite->setAnchorPoint(Point(0, 0.5));
	m_scoreSprite->setPosition(Point(m_visibleSize.width*0.175f, m_visibleSize.height*0.91f));
	m_scoreSprite->setScale(0.65);
	m_scoreSprite->setTag(CURRENT_SCORE_SPRITE_TAG);
	addChild(m_scoreSprite, 1000);

	if (m_score >= m_levelInfo.finalStarScore)
	{
		m_starSprite[0]->initWithFile("target_star.png");
		m_starSprite[1]->initWithFile("target_star.png");
		m_starSprite[2]->initWithFile("target_star.png");
		m_bar->setPercentage(100);
	}
	else if (m_score >= m_levelInfo.SecondStarScore)
	{
		m_starSprite[0]->initWithFile("target_star.png");
		m_starSprite[1]->initWithFile("target_star.png");
		m_bar->setPercentage(66 + static_cast<float>((m_score - m_levelInfo.SecondStarScore)*1.0 * 33 / (m_levelInfo.finalStarScore - m_levelInfo.SecondStarScore)));
	}
	else if (m_score >= m_levelInfo.firstStarScore)
	{
		m_starSprite[0]->initWithFile("target_star.png");
		m_bar->setPercentage(33 + static_cast<float>((m_score - m_levelInfo.firstStarScore)*1.0 * 33 / (m_levelInfo.SecondStarScore - m_levelInfo.firstStarScore)));
	}
	else
	{
		m_bar->setPercentage(static_cast<float>(m_score*1.0 / m_levelInfo.firstStarScore * 33));
	}

}

int StatusLayer::getScore()
{
	return m_score;
}

void StatusLayer::setScore(int score)
{
	m_score = score;
}

void StatusLayer::setLevelInformation(const LevelInformation & levelInfo)
{
	m_levelInfo = levelInfo;
	Node* targetScore = Number::getInstance()->createNumberNode(m_levelInfo.targetScore);
	targetScore->setAnchorPoint(Point(0, 0.5));
	targetScore->setPosition(Point(m_visibleSize.width * 325 / 640, m_visibleSize.height * 918 / 960));
	addChild(targetScore);
}

void StatusLayer::gameEnd(int num)
{
	int reward = 0;
	if (num < 10)
		reward = 2000 - num*num * 20;
	m_score += reward;
	if (m_score > m_levelInfo.bestScore)
	{
		std::string str = "Level";
		str += Value(m_levelInfo.level).asString();
		UserDefault::getInstance()->setIntegerForKey(str.c_str(), m_score);
	}

	FadeIn* fadein = FadeIn::create(1);
	Sprite* gameEndBackground = Sprite::create("game_end_background.png");
	gameEndBackground->setAnchorPoint(Point(0, 0));
	gameEndBackground->setPosition(Point(0, 0));
	gameEndBackground->setCascadeOpacityEnabled(true);
	gameEndBackground->setOpacity(0);
	gameEndBackground->runAction(fadein);
	addChild(gameEndBackground);

	if (m_score < m_levelInfo.firstStarScore) //游戏失败
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/Props_Bomb.ogg");
		LevelFailedBox* m_gameFailedBox = LevelFailedBox::create();
		m_gameFailedBox->setAnchorPoint(Point(0.5, 0.5));
		m_gameFailedBox->setPosition(Point(m_visibleSize.width / 2, m_visibleSize.height / 2));
		m_gameFailedBox->setCascadeOpacityEnabled(true);
		m_gameFailedBox->setOpacity(0);
		m_gameFailedBox->setTarget(m_levelInfo.firstStarScore);
		m_gameFailedBox->setScore(m_score);
		m_gameFailedBox->runAction(fadein->clone());
		addChild(m_gameFailedBox);
		m_gameFailedBox->toSelectionSceneFunction = [=]()
		{
			auto scene = SelectionScene::create();
			TransitionScene *transition = TransitionFade::create(1, scene);
			Director::getInstance()->replaceScene(transition);
		};

		m_gameFailedBox->reStartFunction = [=]()
		{
			auto scene = GameScene::create();
			scene->setLevelInformation(m_levelInfo);
			TransitionScene *transition = TransitionFade::create(1, scene);
			Director::getInstance()->replaceScene(transition);
		};
	}
	else //达到目标分数,过关
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_3.ogg");
		int targetNum = 0;
		if (std::max(m_score, m_levelInfo.bestScore) >= m_levelInfo.firstStarScore)
			targetNum = 1;
		if (std::max(m_score, m_levelInfo.bestScore) >= m_levelInfo.SecondStarScore)
			targetNum = 2;
		if (std::max(m_score, m_levelInfo.bestScore) >= m_levelInfo.finalStarScore)
			targetNum = 3;

		LevelClearBox* m_gameClearBox = LevelClearBox::create();
		m_gameClearBox->setAnchorPoint(Point(0.5, 0.5));
		m_gameClearBox->setPosition(Point(m_visibleSize.width / 2, m_visibleSize.height / 2));
		m_gameClearBox->setCascadeOpacityEnabled(true);
		m_gameClearBox->setOpacity(0);
		m_gameClearBox->setTarget(m_levelInfo.firstStarScore);
		m_gameClearBox->setScore(m_score);
		m_gameClearBox->setTargetClearNum(targetNum);
		m_gameClearBox->runAction(fadein->clone());
		addChild(m_gameClearBox);

		m_gameClearBox->toSelectionSceneFunction = [=]()
		{
			auto scene = SelectionScene::create();
			TransitionScene *transition = TransitionFade::create(1, scene);
			Director::getInstance()->replaceScene(transition);
		};

		m_gameClearBox->reStartFunction = [=]()
		{
			auto scene = GameScene::create();
			scene->setLevelInformation(m_levelInfo);
			TransitionScene *transition = TransitionFade::create(1, scene);
			Director::getInstance()->replaceScene(transition);
		};

		m_gameClearBox->toNextLevelFunction = [=]()
		{
			auto scene = GameScene::create();
			auto nextLevelInfo = SelectionScene::getLevelInformationByIndex(m_levelInfo.level + 1);
			scene->setLevelInformation(nextLevelInfo);
			TransitionScene *transition = TransitionFade::create(1, scene);
			Director::getInstance()->replaceScene(transition);
		};
	}

	unscheduleUpdate();
	update(0);

}