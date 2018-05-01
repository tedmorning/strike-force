#ifndef BOSSSIX_H
#define BOSSSIX_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"

//BOSS 04��������
#define  BOSS06_STAGE01_HP	27500		//��һ�׶�Ѫ��
#define  BOSS06_STAGE02_HP	27500		//�ڶ��׶�Ѫ��
//#define  BOSS06_STAGE03_HP	15000		//�����׶�Ѫ��

#define  BOSSO6_SHOTFIRE_TIME		2.0f	//ɢ��ʱ����
#define  BOSSO6_SHOTFIRE_NUMBER		8		//ɢ������
////��һ�׶�
#define BOSS06_STAGE01_FIRENUM			4		//һ�η�������
//
////�ڶ��׶�
//#define BOSS04_STAGE02_SECTOR			90.0F	//ɢ��Ƕ�
//#define BOSS04_STAGE02_ROUNDS		6		//�ӵ�����
//
#define BOSS06_STAGE02_MISSLE		2.0f	//�������
////�����׶�
//#define BOSS04_STAGE03_SECTOR			90.0F	//ɢ��Ƕ�
//#define BOSS06_STAGE02_NUMBER			8		//�ӵ�����


class CBossSix :
	public CCNode
{
public:
	CBossSix(void);
	~CBossSix(void);
public:
	static CBossSix* createBoss(void);
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
	void lockTarget(void);
	void lockFire(void);
	//void stage3Fire(void);
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

	//boss06
	CCSprite *m_pCollideBody;	//��ײ��
	CCSprite *m_pMainBody;		//������
	CCSprite *m_pLeftBody;		//�����
	CCSprite *m_pRightBody;		//�һ���
	CCSprite *m_pLeftEngine;	//������
	CCSprite *m_pRightEngine;	//������
	CCSprite *m_pLeftGun;		//����
	CCSprite *m_pRightGun;		//����

	CCAction *m_pEngine;
	CCAction *m_pGun;

	float m_fShotGunTime;

	int m_nRounds;
	BULLET_DATA m_sStage2Data;

	float m_fEnemyTime;			//����С�ɻ�����ʱ��
};


#endif