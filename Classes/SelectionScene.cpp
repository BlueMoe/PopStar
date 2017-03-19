#include "SelectionScene.h"
#include "cocos2d.h"
#include "Number.h"
#include "ui\UIWidget.h"
#include "GameScene.h"
#include "TitleScene.h"

using namespace cocos2d;


std::vector<LevelInformation> SelectionScene::m_LevelInfomations = std::vector<LevelInformation>();

bool SelectionButton::init()
{
	if(!Node::init()) return false;

	m_starNum = 0;
	m_buttonNum = 1;

	m_planter = ui::Button::create("planter.png");
	m_planter->setAnchorPoint(Point(0, 0));
	m_planter->setPosition(Point(0, 0));
	addChild(m_planter);
	setContentSize(m_planter->getContentSize());

	Size size = getContentSize();
	m_leftStar = Sprite::create("left_star.png");
	m_leftStar->setPosition(Point(size.width * 25.5 / 133, size.height * 121 / 157));
	m_leftStar->setVisible(false);
	addChild(m_leftStar);
	m_vStar.push_back(m_leftStar);

	m_middleStar = Sprite::create("middle_star.png");
	m_middleStar->setPosition(Point(size.width * 66 / 133, size.height * 128 / 157));
	m_middleStar->setVisible(false);
	addChild(m_middleStar);
	m_vStar.push_back(m_middleStar);

	m_rightStar = Sprite::create("right_star.png");
	m_rightStar->setPosition(Point(size.width * 103.5 / 133, size.height * 117 / 157));
	m_rightStar->setVisible(false);
	addChild(m_rightStar);
	m_vStar.push_back(m_rightStar);

	m_buttonNumSprite = Number::createNumberNode(m_buttonNum);
	m_buttonNumSprite->setAnchorPoint(Point(0.5, 0.5));
	m_buttonNumSprite->setPosition(Point(size.width * 67.5 / 133, size.height * 49.5 / 157));
	addChild(m_buttonNumSprite);

	return true;
}

void SelectionButton::setButtonNum(int num)
{
	if (num > 7) num = 7;
	if (num < 1) num = 1;
	m_buttonNum = num;
	update(0);
}

void SelectionButton::setStarNum(int num)
{
	if (num < 0) num = 0;
	if (num > 3) num = 3;
	m_starNum = num;
	update(0);
}

void SelectionButton::update(float delta)
{
	auto iter = m_vStar.begin();
	for (int i = 0; i < m_starNum; i++)
	{
		(*iter++)->setVisible(true);
	}
	while (iter != m_vStar.end())
	{
		(*iter++)->setVisible(false);
	}
	
	removeChild(m_buttonNumSprite);
	Size size = getContentSize();
	m_buttonNumSprite = Number::createNumberNode(m_buttonNum);
	m_buttonNumSprite->setAnchorPoint(Point(0.5, 0.5));
	m_buttonNumSprite->setPosition(Point(size.width * 67.5 / 133, size.height * 49.5 / 157));
	m_buttonNumSprite->setScale(0.6);
	addChild(m_buttonNumSprite);
}

ui::Button * SelectionButton::getButton()
{
	return m_planter;
}

bool SelectionScene::init()
{
	if (!Scene::init()) return false;

	for (int i = 0; i < 7; i++)
	{
		m_LevelInfomations.push_back(LevelInformation());
		m_LevelInfomations[i].targetScore = LevelTargetScore[i];
	}
	

	int i = 1;
	std::string str;
	for (int i = 0; i < 7; i++)
	{
		str = "Level";
		str += Value(i+1).asString();
		m_LevelInfomations[i].firstStarScore = m_LevelInfomations[i].targetScore;
		m_LevelInfomations[i].SecondStarScore = m_LevelInfomations[i].targetScore*1.5;
		m_LevelInfomations[i].finalStarScore = m_LevelInfomations[i].targetScore*2;
		m_LevelInfomations[i].bestScore = UserDefault::getInstance()->getIntegerForKey(str.c_str());
		m_LevelInfomations[i].level = i + 1;
	}

	Sprite* background = Sprite::create("selection_background.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	addChild(background);

	for (int i = 0; i < 7; i++)
	{
		SelectionButton* node = SelectionButton::create();
		if (m_LevelInfomations[i].bestScore >= m_LevelInfomations[i].finalStarScore)
			node->setStarNum(3);
		else if (m_LevelInfomations[i].bestScore >= m_LevelInfomations[i].SecondStarScore)
			node->setStarNum(2);
		else if (m_LevelInfomations[i].bestScore >= m_LevelInfomations[i].firstStarScore)
			node->setStarNum(1);
		else
			node->setStarNum(0);

		node->setButtonNum(i + 1);
		node->setAnchorPoint(Point(0.5, 0.5));
		auto listener = [=](Object* object, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				auto scene = GameScene::create();
				scene->setLevelInformation(m_LevelInfomations[i]);
				TransitionScene *transition = TransitionFade::create(1, scene);
				Director::getInstance()->replaceScene(transition);
			}
		};
		node->getButton()->addTouchEventListener(listener);

		addChild(node);
		m_buttons.push_back(node);
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_buttons[0]->setPosition(Point(visibleSize.width * 170 / 640, visibleSize.height * 140 / 960));
	m_buttons[1]->setPosition(Point(visibleSize.width * 465 / 640, visibleSize.height * 270 / 960));
	m_buttons[2]->setPosition(Point(visibleSize.width * 135 / 640, visibleSize.height * 360 / 960));
	m_buttons[3]->setPosition(Point(visibleSize.width * 345 / 640, visibleSize.height * 435 / 960));
	m_buttons[4]->setPosition(Point(visibleSize.width * 220 / 640, visibleSize.height * 560 / 960));
	m_buttons[5]->setPosition(Point(visibleSize.width * 355 / 640, visibleSize.height * 785 / 960));
	m_buttons[6]->setPosition(Point(visibleSize.width * 66  / 640, visibleSize.height * 820 / 960));

	for (auto iter = m_buttons.begin() + 1; iter != m_buttons.end() - 1; iter++)
	{
		int i = iter - m_buttons.begin();
		if (m_LevelInfomations[i].bestScore < m_LevelInfomations[i].targetScore)
		{
			(*(iter+1))->getButton()->setEnabled(false);
		}
	}

	auto listenerKeyBoard = EventListenerKeyboard::create();
	listenerKeyBoard->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)  //·µ»Ø
		{
			auto scene = TitleScene::create();
			TransitionScene *transition = TransitionFade::create(1, scene);
			Director::getInstance()->replaceScene(transition);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);


	return true;
}

LevelInformation SelectionScene::getLevelInformationByIndex(int index)
{
	if (index < 0) index = 0;
	if (index > m_LevelInfomations.size() - 1) index = m_LevelInfomations.size() - 1;
	
	return m_LevelInfomations[index];
}
