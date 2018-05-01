#ifndef MAINUILAYER_H
#define MAINUILAYER_H

#include "cocos2d.h"

#include "GlobalData.h"
#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "ShopLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

using namespace cocos2d;
using namespace CocosDenshion;
using namespace extension;

enum UI_STATE
{
	US_MAIN,
	US_HIGHSCORES,
	US_OPTIONS,
	US_HELP,
	US_EXIT,
};

#define MUSIC_VOLUME		100
#define FX_VOLUME			200
#define DIFFICULTY_VOLUME	300

class CMainUILayer :
	public CCLayer
{
public:
	CMainUILayer(void);
	~CMainUILayer(void);

public:
	virtual bool init();
	CREATE_FUNC(CMainUILayer);
	void keyBackClicked();
public:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;


	//temp
	CCMenuItemSprite* m_pLeftArrow;
	CCMenuItemSprite* m_pRightArrow;
	CCLabelTTF* pLabel;
private:
	void setMainMenuItem(void);
	void toLeftCallback(CCObject* sender);
	void toRightCallback(CCObject* sender);
	void toMainCallback(CCObject* sender);
	void toPopExitDialog(void);
	void toEnterCallback(CCObject* sender);
	void toCancelCallback(CCObject* sender);
	void toTouchBackCall(CCObject* sender);
	void toMusicOnAndOff(CCObject* sender);
	void toFXOnAndOff(CCObject* sender);

	void toTouchOnAndOff(CCObject* sender);
	void toGravityOnAndOff(CCObject* sender);
	void toRunOnAndOff(CCObject* sender);
	void toDoubleOnAndOff(CCObject* sender);

	void toSliderCallback(CCObject *sender, CCControlEvent controlEvent);

	void toShopCallback(CCObject* sender);

	void addAnimationToUI(CCMenuItemSprite* pMenuItem, const char* pszName);

	void toMoreGame(CCObject* sender);
	void toRateGame(CCObject* sender);
	void layerUpdate(float fEscapeTime);
private:
	ccLanguageType m_eLanguageType;
	char m_sPrefix[DATA_LENTH_MAX];
	UI_STATE m_eCurState;
	std::vector<CCMenuItemSprite*> m_vMenuItemVector;

	CCSprite *m_pBannerbar;

	CCMenuItemImage *m_pMenuImageBG;
	CCMenuItemSprite *m_pMenuYes;
	CCMenuItemSprite *m_pMenuNo;

	CCMenuItemSprite *m_pMenuMute;
	CCMenuItemSprite *m_pMenuMoreGame;

	CCMenuItemSprite *m_pMenuGameShop;

	CCMenu *m_pOptionMenu;
	CCMenuItemSprite *m_pTouchBack;
	CCControlSlider *m_pMusicVolume;
	CCControlSlider *m_pFXVolume;
	CCControlSlider *m_pDifficultyVolume;

	//���Ʊ���
	CCSprite *m_pOptionBG;
	//����
	CCMenuItemToggle *m_pMusicMute;
	//��Ч
	CCMenuItemToggle *m_pFXMute;
	//��������
	CCMenuItemToggle *m_pTouchControl;
	//��������
	CCMenuItemToggle *m_pGravityControl;
	//��������
	CCMenuItemToggle *m_pRunControl;
	//˫������
	CCMenuItemToggle *m_pDoubleControl;


	CCSprite *m_pHighScore;
	CCSprite *m_pHelp;

	CCLabelAtlas *m_pLevelTotal;		//�����ܷ���
	CCLabelAtlas *m_pLevel01;			//���ط���
	CCLabelAtlas *m_pLevel02;			//���ط���
	CCLabelAtlas *m_pLevel03;			//���ط���
	CCLabelAtlas *m_pLevel04;			//���ط���
	CCLabelAtlas *m_pLevel05;			//���ط���
	CCLabelAtlas *m_pLevel06;			//���ط���
	CCLabelAtlas *m_pLevel07;			//���ط���
	CCLabelAtlas *m_pLevel08;			//���ط���
	//SOUND
	SimpleAudioEngine *m_pCurAudio;

	CCSprite *pMenuBG;
	CCSprite *pTile;
	ccColor3B m_sBaseColor;
};


#endif