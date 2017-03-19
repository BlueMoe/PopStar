#include "GameScene.h"
#include "cocos2d.h"
#include "TitleScene.h"

using namespace cocos2d;

bool GameScene::init()
{
	if(!Scene::init()) return false;

	m_gameLayer = GameLayer::create();
	addChild(m_gameLayer);

	m_statusLayer = StatusLayer::create();
	addChild(m_statusLayer);

	m_gameLayer->setStatusLayer(m_statusLayer);

	auto listenerKeyBoard = EventListenerKeyboard::create();
	listenerKeyBoard->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)  //·µ»Ø
		{
			auto scene = SelectionScene::create();
			TransitionScene *transition = TransitionFade::create(1, scene);
			Director::getInstance()->replaceScene(transition);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);

	return true;
}

void GameScene::setLevelInformation(const LevelInformation & levelInfo)
{
	if (m_statusLayer != nullptr)
	{
		m_statusLayer->setLevelInformation(levelInfo);
	}
}
