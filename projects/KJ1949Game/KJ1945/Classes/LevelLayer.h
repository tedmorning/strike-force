#ifndef LEVELLAYER_H
#define LEVELLAYER_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "SelectScene.h"
#include "MissionScene.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

class CLevelLayer :
	public CCLayer
{
public:
	CLevelLayer(void);
	~CLevelLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(CLevelLayer);
	void keyBackClicked();
private:
	void addLevelUI(const char* pszName, CCMenu* pAttachMenu);
	void selectLevelCallback(CCObject* sender);
	void toPlayerCallback(CCObject* sender);
	void setLock(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	ccLanguageType m_eLanguageType;
	char m_sPrefix[DATA_LENTH_MAX];

	CCSprite *m_pBannerbar;

	CCMenuItemSprite *m_pMenuItemBack;
	CCMenuItemSprite *m_pMenuItemShop;
	std::vector<CCMenuItemSprite*> m_vLevelMenuVector;
	//SOUND
	SimpleAudioEngine *m_pCurAudio;

	std::vector<CCSprite*> m_vLockSpriteVector;
};

#endif