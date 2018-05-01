#ifndef DRONE_H
#define DRONE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"

#define DRONE_HP	11000

class CDrone :
	public CCNode
{
public:
	CDrone(void);
	~CDrone(void);
public:
	static CDrone* createDrone(void);
	void underAttack(int nHurt);
	bool isCheck(void);
	bool isDead(void);
	void onEnter();
	void onExit();
	CCRect getCurBoundbox(void);
private:
	void createSprite(void);
	void droneUpdate(float fEscapeTime);
	void droneCallback(void);
	void lockTarget(void);
	void fireTarget(void);
	void runEffect(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	BOSS_STATE m_eCurState;
	STAGE_BOSS m_eCurStage;

	float m_fTime;				//��ʱ��
	int m_nBossHP;				//HP
	CCSprite *m_pBaseSprite;	//����
	CCAction *m_pMoveAction;	//�ƶ��¼�
	CCSprite *m_pExplode;		//��ը
	//SOUND
	SimpleAudioEngine *m_pCurAudio;
	//Base Flash Effect
	ccColor3B m_sBaseColor;
	float m_fFlashTime;
	bool m_bBaseNormal;

};

#endif