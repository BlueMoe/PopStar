#include "Number.h"
#include "cocos2d.h"
#include <string>

using namespace cocos2d;

Number*	Number::m_instance = nullptr;

Node * Number::createNumberNode(int num)
{
	int pos;
	float cw, ch, w;
	std::string str;
	auto numberNode = Node::create();

	for (w = 0; num > 0 || numberNode->getChildrenCount() <= 0; num /= 10)
	{
		str = Value(num % 10).asString();
		str += ".png";
		auto child = Sprite::createWithSpriteFrameName(str);
		w += child->getContentSize().width;
		numberNode->addChild(child);
	}
	ch = numberNode->getChildren().at(0)->getContentSize().height;
	cw = w / numberNode->getChildrenCount();
	numberNode->setContentSize(Size(w, ch));

	pos = w;
	for (auto child : numberNode->getChildren())
	{
		child->setAnchorPoint(Point(1, 0));
		child->setPositionX(pos);
		pos -= cw;
	}
	return numberNode;
}

Node * Number::createTimeNode(time_t time)
{
	tm t = *localtime(&time);
	char ch[10];
		sprintf(ch, "%02d_%02d", t.tm_min, t.tm_sec);
	return createNumberNode(ch);
}

Node * Number::createNumberNode(const std::string & num)
{
	if (num.empty()) return nullptr;

	int pos;
	float cw, ch, w;
	std::string str;
	auto numberNode = Node::create();
	auto p = num.end() - 1;


	for (w = 0; p>num.begin(); p--)
	{
		str = *p;
		str += ".png";
		auto child = Sprite::createWithSpriteFrameName(str);
		w += child->getContentSize().width;
		numberNode->addChild(child);
	}
	ch = numberNode->getChildren().at(0)->getContentSize().height;
	cw = w / numberNode->getChildrenCount();
	numberNode->setContentSize(Size(w, ch));

	pos = w;
	for (auto child : numberNode->getChildren())
	{
		child->setAnchorPoint(Point(1, 0));
		child->setPositionX(pos);
		pos -= cw;
	}
	return numberNode;
}