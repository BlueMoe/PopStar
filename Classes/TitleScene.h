#include "cocos2d.h"
#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

class TitleScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(TitleScene);
	TitleScene();
	~TitleScene();
	bool init();
	bool getIsSoundOpen();
protected:
private:
	static bool _isAudioLoaded;
private:
	bool loadAudio();
	bool _isSoundOpen;
};

#endif // !__TITLESCENE_H__





