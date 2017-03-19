#include "TitleScene.h"
#include "ui\UIButton.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "SelectionScene.h"

using namespace cocos2d;
using namespace ui;

bool TitleScene::_isAudioLoaded = false;

TitleScene::TitleScene()
{

}
TitleScene::~TitleScene()
{
	
}

bool TitleScene::init()
{
	if(!Scene::init()) return false;

	if(!_isAudioLoaded)	loadAudio();

	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("popstar.plist", "popstar.png");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("bg_mainscene.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(background);

	Sprite* title = Sprite::create("lgo.png");
	title->setPosition(Point(visibleSize.width / 2, visibleSize.height * 3 / 4));
	addChild(title);

	Button* newgameButton = Button::create("begin.png");
	newgameButton -> setPosition(Point(visibleSize.width/2,visibleSize.height/4));
	addChild(newgameButton);

	auto newgameButtonListener = [=](Object* object,Widget::TouchEventType type)
	{
	if(type == Widget::TouchEventType::ENDED)
		{
			auto scene = SelectionScene::create();
			TransitionScene *transition = TransitionFade::create(1,scene);
			Director::getInstance()->replaceScene(transition);
		}
	};
	newgameButton->addTouchEventListener(newgameButtonListener);

	Button* soundbutton = Button::create("menu_sound_on.png");
	soundbutton->setPosition(Point(visibleSize.width - soundbutton->getContentSize().width, visibleSize.height - soundbutton->getContentSize().height));
	addChild(soundbutton);
	_isSoundOpen = UserDefault::getInstance()->getBoolForKey("Sound");

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/music.ogg", true);
	if (!_isSoundOpen)
	{
		soundbutton->loadTextureNormal("menu_sound_off.png");
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	auto soundButtonListener = [=](Object* object, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			_isSoundOpen = !_isSoundOpen;
			if (_isSoundOpen)
			{
				soundbutton->loadTextureNormal("menu_sound_on.png");
				CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			}
			else
			{
				soundbutton->loadTextureNormal("menu_sound_off.png");
				CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			}
			UserDefault::getInstance()->setBoolForKey("Sound", _isSoundOpen);
		}
	};
	soundbutton->addTouchEventListener(soundButtonListener);

	auto listenerKeyBoard = EventListenerKeyboard::create();
	listenerKeyBoard->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)  //·µ»Ø
		{
			Director::getInstance()->end();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);

	return true;

}
bool TitleScene::loadAudio()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/music.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/select.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/beep.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/pop.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_1.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_2.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_3.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/readygo.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/select.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/fireworks_01.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/fireworks_02.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/fireworks_03.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/NextGameRound.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/Props_Bomb.ogg");
	_isAudioLoaded = true;
	return true;
}

bool TitleScene::getIsSoundOpen()
{
	return _isSoundOpen;
}