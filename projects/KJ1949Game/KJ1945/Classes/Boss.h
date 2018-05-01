#ifndef BOSS_H
#define BOSS_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "EnemySprite.h"
//#include "GameLayer.h"
#include "Bullet.h"

class CBoss :
	public CCNode
{
public:
	CBoss(void);
	~CBoss(void);
public:
	static CBoss* createBoss(BOSS_KINDS eKind);
	void underAttack(int nHurt);
	bool isCheck(void);
	void onEnter();
	void onExit();
	CCRect getCurBoundbox(void);
public:
private:
	void createSprite(BOSS_KINDS eKind);
	void bossUpdate(float fEscapeTime);
	void readyUpdate(float fEscapeTime);
	void levelUpdate(float fEscapeTime);
	void stageUpdate(float fEscapeTime);
	void runEffect(void);
	void removeSelf(void);
	CCPoint lockTarget(void);

	//ͻ����BOSS 01
	void initCommandos(void);
	void commandosUpdate(float fEscapeTime);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	BOSS_KINDS m_eBossKind;
	BOSS_STATE m_eCurState;
	STAGE_BOSS m_eCurStage;

	float m_fTime;				//��ʱ��
	int m_nBossHP;				//HP
	CCSprite *m_pBaseSprite;	//����
	CCAction *m_pMoveAction;	//�ƶ��¼�
	CCSprite *m_pExplode;		//��ը

	//Base Flash Effect
	ccColor3B m_sBaseColor;
	float m_fFlashTime;
	bool m_bBaseNormal;

	//SOUND
	SimpleAudioEngine *m_pCurAudio;
	//level01 data
	int m_nPlaneNum;			//ͻ���ӷɻ�����
	float m_fDeltaTime;			//ʱ����
};

#endif