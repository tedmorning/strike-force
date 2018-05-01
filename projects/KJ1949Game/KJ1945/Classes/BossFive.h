#ifndef BOSSFIVE_H
#define BOSSFIVE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"


//BOSS 05��������
#define  BOSS05_STAGE01_HP	15000		//��һ�׶�Ѫ��
#define  BOSS05_STAGE02_HP	15000		//�ڶ��׶�Ѫ��
#define  BOSS05_STAGE03_HP	15000		//�����׶�Ѫ��
//��һ�׶�
#define  BOSS05_STAGE01_LASERSLOT	3.0f	//�������ڿ�����

#define  BOSS05_STAGE01_FIRESLOT	1.0f	//���ڿ�����

#define BOSS05_STAGE02_MISSLE		2.0f	//�������

class CBossFive :
	public CCNode
{
public:
	CBossFive(void);
	~CBossFive(void);
public:
	static CBossFive* createBoss(void);
	void underAttack(int nHurt);
	bool isCheck(void);
	void onEnter();
	void onExit();
	CCRect getCurBoundbox(void);
private:
	void createSprite(void);
	void bossUpdate(float fEscapeTime);
	void bossCallback(void);
	void stage1Fire(void);
	//void stage3Fire(void);
	void lockTarget(void);
	void lockFire(void);
	void runEffect(void);
	void effectCallback(void);
	void removeSelf(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;

	//BOSS_KINDS m_eBossKind;
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

	//��ǰ�ɹ�����λ
	CCSprite *m_pCurAttack;

	//level05 data
	CCSprite *m_pMainBody;			//������
	CCSprite *m_pLeftWing;			//�����
	CCSprite *m_pRightWing;			//�һ���
	CCSprite *m_pTailFin;			//β��

	CCSprite *m_pMainGun;		//����

	float m_fLaserTime;			//�����ڿ���ʱ��

	float m_fEnemyTime;			//����С�ɻ�����ʱ��

};

#endif