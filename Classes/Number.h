#ifndef __NUMBER_H__
#define __NUMBER_H__

#include "cocos2d.h"

class Number
{
public:
	static cocos2d::Node* createNumberNode(int num);
	static cocos2d::Node* createTimeNode(time_t time);
	static cocos2d::Node* createNumberNode(const std::string& num);
	static Number* getInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Number();
		}
		return m_instance;
	}
private:
	Number() {};
	~Number() 
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
		}
	};
private:
	static Number*	m_instance;
};

#endif // __NUMBER_H__
