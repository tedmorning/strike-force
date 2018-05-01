#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "MainUIScene.h"
#include "PlayerSprite.h"
#include "EnemySprite.h"
#include "ArmySprite.h"
#include "HelicopterSprite.h"
#include "Boss.h"
#include "BossTwo.h"
#include "BossThree.h"
#include "BossFour.h"
#include "BossFive.h"
#include "BossSix.h"
#include "BossSeven.h"
#include "Bullet.h"
#include "SuperBomb.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

enum GAME_STATE
{
	GS_DEFAULT,
	GS_INIT,
	GS_RUN,
	GS_BOSS,
	GS_AUTOFLY,
	GS_LANDING,
	GS_SCORE,
	GS_COUNTSCORE,
	GS_END,
};

struct CLOUD_DATA
{
	float mSpeed;
	CCSprite *mCloud;
	CCPoint mDirection;
	bool mIsMove;
};

class CGameLayer :
	public CCLayer
{
public:
	CGameLayer(void);
	~CGameLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(CGameLayer);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);

	//CPlayerSprite * getCurPlayer(void)
	//{
	//	if (m_pPlayer != NULL)
	//	{
	//		return m_pPlayer;
	//	}
	//}
	void keyBackClicked();

	void setLevelEnd(void);

	//��ǰ�ı�������
	void setHoldItem(ITEM_KINDS eKind);
private:
	void gameUpdate(float fEscapeTime);
	void moveMap(float fEscapeTime);

	void pauseCallback(CCObject* sender);
	void backMainCallback(CCObject* sender);
	void continueCallback(CCObject* sender);
	void fireBombCallback(CCObject* sender);
	void playerUpdate(void);

	void fireSuperBomb(void);
	void moveCloud(float fEscapeTime);

	void scoreCurLevel(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	ccLanguageType m_eLanguageType;
	char m_sPrefix[DATA_LENTH_MAX];

	CCSprite *m_pBannerbar;

	//CCPoint *m_pPlayerPos;
	CPlayerSprite *m_pPlayer;
	std::vector<CCSprite*> m_vMapSpriteVector;
	CCPoint m_tDirection;
	LEVEL_DATA m_sCurData;

	//CLOUD
	std::vector<CLOUD_DATA> m_vLowCloudVector;
	std::vector<CLOUD_DATA> m_vHightCloudVector;

	//UI
	CCSprite *m_pHoldSpirte;			//��������ͼʾ
	ITEM_KINDS m_eHoldItem;				//��������

	//CCSprite *m_pFailSprite;			//ʧ����ʾ
	CCSprite *m_pPauseBG;				//��ͣ����
	CCMenuItemSprite *m_pMenuItemPause;	//��ͣ
	CCMenuItemSprite *m_pMenuBackMain;	//�����˵�
	CCMenuItemSprite *m_pMenuContinue;	//������Ϸ
	CCMenuItemSprite *m_pMenuItemFail;	//ʧ�ܺ����
	CCProgressTimer *m_pMenuItemHP;		//Ѫ��
	CCLabelAtlas *m_pMenuFontScore;		//�÷�
	CCLabelAtlas *m_pMenuFontLife;		//������
	CCLabelAtlas *m_pMenuFontRocket;	//������

	CCMenuItemSprite *m_pSupperBomb;	//ը���׶�
	CCProgressTimer *m_pBombTime;		//ը��ʱ����

	CCSprite *m_pLevelScore;			//����ͳ�Ʊ���
	CCSprite *m_pScoreTitle;			//����ͳ�Ʊ���
	CCLabelAtlas *m_pScoreNum;			//����ͳ�Ʒ���
	CCLabelAtlas *m_pLevelXP;			//����ͳ�ƾ���ֵ
	CCMenuItemSprite *m_pMenuItemMain;	//�����ص����˵�
	CCLabelAtlas *m_pLevelPlane01;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane02;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane03;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane04;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane05;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane06;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane07;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane08;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane09;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane10;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane11;			//����ͳ�ƾ���ֵ
	CCLabelAtlas *m_pLevelPlane12;			//����ͳ�ƾ���ֵ

	CCLabelAtlas *m_pDesPercentage;			//ɱ�аٷֱ�
	CCLabelAtlas *m_pRewardXP;				//���ؽ�������ֵ
	CCLabelAtlas *m_pRewarPoint;			//���ؽ�����



	//������
	std::vector<CCSprite*> m_vDesStar;		//ɱ���Ǽ�


	GAME_STATE m_eCurState;

	float m_fLevelTime;					//Levelʱ���ܼ�

	//SOUND
	SimpleAudioEngine *m_pCurAudio;

	//����˫���¼�
	float m_fFirstTime;
	//temp
	float m_fTime;

	//int m_nLifeNum;

	CCSprite *m_pAirport;
	//�վ�
	std::vector<FLY_DATA> m_vCurPlaneData;
	std::vector<FLY_DATA>::iterator it;

	//½��
	std::vector<LAND_DATA> m_vCurLandData;
	std::vector<LAND_DATA>::iterator ite;


	//CCLabelAtlas *m_pTempX;				//���ؽ�������ֵ
	//CCLabelAtlas *m_pTempY;				//���ؽ�����
};


#endif