#include "GameLayer.h"
#include "StarSprite.h"
#include <utility>
#include "TitleScene.h"
#include "StatusLayer.h"
#include "SimpleAudioEngine.h"

#define STARROW 10
#define STARCOL 10
#define X_OFFSET 10
#define Y_OFFSET 150

using namespace cocos2d;

bool GameLayer::init()
{
	if(!Layer::init())	return false;

	starSize = StarSprite::starSize;
	starHeartSize = StarSprite::starHeartSize;
	m_isStalemate = false;

	m_bg_game = Sprite::create("bg_game.png");
	m_bg_game->setAnchorPoint(Point(0, 0));
	m_bg_game->setPosition(0, 0);
	addChild(m_bg_game);

	m_bg_stars = Sprite::create("bg_stars.png");
	m_bg_stars->setAnchorPoint(Point(0, 0));
	m_bg_stars->setPosition(0, Y_OFFSET);
	addChild(m_bg_stars);

	m_stars.resize(10);
	for(int i = 0; i < STARCOL; i++)
	{
		for(int j = 0; j < STARROW; j++)
		{
			m_stars[i].push_back(StarSprite::create());
			m_stars[i][j]->setPosition(Point(starSize.width/2 + starSize.width*i+X_OFFSET,starSize.height/2+starSize.height*j+Y_OFFSET));
			addChild(m_stars[i][j]);
		}
	}

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		return true;
	};
	touchListener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		Point pos = convertToNodeSpace(touch->getLocation());
		int x = (pos.x - X_OFFSET) / starSize.width;
		int y = (pos.y - Y_OFFSET) / starSize.height;
		if (x >= m_stars.size())		return;	
		if (y >= m_stars[x].size())		return;	//û�е��з�����Ϊ��Ч���
		if (!m_stars[x][y]->isHighLight())		//����ķ��鲻�Ǹ�����ʾ
		{
			clearMark();						//�������������ʾ�ķ���
			markStars(x, y);					//��x,y����Ϊ��������ʾ��֮������ͬɫ����
		}
		else									//�������ķ����Ǹ�����ʾ
		{										
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/select.ogg");//������Ч
			popAllMarkedStars();															//�������и�����ʾ�ķ���
			if (StalemateCheck())															//ͬʱ�������
			{
				m_leaveStarNum = 0;
				float t = 0;
				for (auto p : m_stars)
				{
					m_leaveStarNum += p.size();
					for (auto q : p)
					{
						ParticleSystem* ps = ParticleExplosion::createWithTotalParticles(20);
						ps->setTexture(Director::getInstance()->getTextureCache()->addImage("target_star.png"));
						ps->setLife(0.1);
						ps->setPosition(q->getPosition());
						addChild(ps);
						removeChild(q);
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/clear.ogg");
					}
				}
				scheduleOnce(schedule_selector(GameLayer::gameEnd), 1);
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/readygo.ogg");

	return true;

}

//�������,��ÿһ������,�Ա���������ұߵ�������ɫ,������ֱͬ�ӷ���false,��������m_stars�󷵻�true,��Ϸ����
bool GameLayer::StalemateCheck()
{
	StarColor color;
	int x, y;
	for (x = 0; x < m_stars.size(); x++)
	{
		for (y = 0; y < m_stars[x].size(); y++)
		{
			color = m_stars[x][y]->getStarColor();
			if (y < m_stars[x].size() - 1)//�Ϸ��߽�����
			{
				if (m_stars[x][y + 1]->getStarColor() == color)//��
				{
					m_isStalemate = false;
					return m_isStalemate;
				}
			}
			if (x < m_stars.size() - 1)//�ҷ�x��߽�����
			{
				if (y < m_stars[x + 1].size())//�ҷ�y��߽�����
				{
					if (m_stars[x + 1][y]->getStarColor() == color)
					{
						m_isStalemate = false;
						return m_isStalemate;
					}
				}
			}
		}
	}
	m_isStalemate = true;
	return m_isStalemate;
}

void GameLayer::popOneStar(int x, int y)
{
	ParticleSystem* ps = ParticleExplosion::createWithTotalParticles(30);
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("target_star.png"));
	ps->setLife(0.1);
	ps->setPosition(m_stars[x][y]->getPosition());
	addChild(ps);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/pop.ogg");
	removeChild(m_stars[x][y]);
	auto yiter = m_stars[x].erase(m_stars[x].begin() + y);
	MoveBy* movedown = MoveBy::create(0.2, Vec2(0, -starSize.height));
	while (yiter != m_stars[x].end())
	{
		(*yiter)->runAction(movedown->clone());
		yiter++;
	}
	if (m_stars[x].empty())
	{
		MoveBy* moveleft = MoveBy::create(0.1, Vec2(-starSize.width, 0));
		auto xiter = m_stars.erase(m_stars.begin() + x);
		while (xiter != m_stars.end())
		{
			for (auto p : *(xiter))
			{
				p->runAction(moveleft->clone());
			}
			xiter++;
		}
	}
}

void GameLayer::popAllMarkedStars()
{
	//ʹ��vector��erase()����Ԫ�ص�ɾ��,Ϊ����ɾ��ǰ���Ԫ�غ�,
	//vector�Զ��������Ԫ���ƶ���ǰ��,���Ӧ��Ԫ�ص�Ԫ����ǰ�ƶ�,
	//�ȶ�Ҫɾ���������������,�Ӻ���ǰɾ��.
	//�������:x�ή��,���x���,��y�ή��
	sort(m_willPopLocation.begin(), m_willPopLocation.end(), IntPairGreaterEqual());
	for (auto p : m_willPopLocation)
	{
		popOneStar(p.first, p.second);
	}
	m_statusLayer->setScore(m_statusLayer->getScore() + 5 * m_willPopLocation.size()*m_willPopLocation.size());
	m_willPopLocation.clear();
}

void GameLayer::clearMark()
{
	for (auto p : m_willPopLocation)
	{
		m_stars[p.first][p.second]->setHighLight(false);
	}
	m_willPopLocation.clear();
}

void GameLayer::markStars(int x, int y)
{
	int _x;
	int _y;
	std::queue<std::pair<int, int> > q;
	std::pair<int, int> pos;
	StarColor color;

	q.push(std::make_pair(x, y));
	color = m_stars[x][y]->getStarColor();
	m_stars[x][y]->setHighLight(true);
	m_willPopLocation.push_back(std::make_pair(x, y));

	while (!q.empty())
	{
		pos = q.front();
		_x = pos.first;
		_y = pos.second;
		q.pop();

		if (_x > 0&& _y < m_stars[_x - 1].size())//��
		{
			if (m_stars[_x - 1][_y]->getStarColor() == color&&!m_stars[_x - 1][_y]->isHighLight())
			{
				m_stars[_x - 1][_y]->setHighLight(true);
				q.push(std::make_pair(_x - 1, _y));
				m_willPopLocation.push_back(std::make_pair(_x - 1, _y));
			}
		}
		if (_x < m_stars.size() - 1 && _y < m_stars[_x + 1].size())//��
		{
			if (m_stars[_x + 1][_y]->getStarColor() == color&&!m_stars[_x + 1][_y]->isHighLight())
			{
				m_stars[_x + 1][_y]->setHighLight(true);
				q.push(std::make_pair(_x + 1, _y));
				m_willPopLocation.push_back(std::make_pair(_x + 1, _y));
			}
		}if (_y < m_stars[_x].size() - 1)//��
		{
			if (m_stars[_x][_y + 1]->getStarColor() == color&&!m_stars[_x][_y + 1]->isHighLight())
			{
				m_stars[_x][_y + 1]->setHighLight(true);
				q.push(std::make_pair(_x, _y + 1));
				m_willPopLocation.push_back(std::make_pair(_x, _y + 1));
			}
		}if (_y > 0)//��
		{
			if (m_stars[_x][_y - 1]->getStarColor() == color&&!m_stars[_x][_y - 1]->isHighLight())
			{
				m_stars[_x][_y - 1]->setHighLight(true);
				q.push(std::make_pair(_x, _y - 1));
				m_willPopLocation.push_back(std::make_pair(_x, _y - 1));
			}
		}
	}

	if (m_willPopLocation.size() <= 1)
	{
		m_willPopLocation.clear();
		m_stars[x][y]->setHighLight(false);
		return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/select.ogg");
}

void GameLayer::setStatusLayer(StatusLayer* layer)
{
	m_statusLayer = layer;
}

void GameLayer::gameEnd(float dt)
{
	m_statusLayer->gameEnd(m_leaveStarNum);
}
