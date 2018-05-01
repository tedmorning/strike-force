#ifndef BOSSTWO_H
#define BOSSTWO_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"

#define  BOSSTWO_STAGE01_HP	7500		//��һ�׶�Ѫ��
#define  BOSSTWO_STAGE02_HP	7500		//�ڶ��׶�Ѫ��
#define  BOSSTWO_STAGE03_HP	1000		//�����׶�Ѫ��


//��һ�׶�
#define STAGE01_SLOT			0.5f	//������
#define STAGE01_BULLETNUM		3		//һ�η�������
//Բ��ɢ��
#define STAGE01_COOL		5.0f	//��ȴ����
#define B2FIRE_SLOT		0.5f	//������
#define B2BULLET_NUM	30		//һ�η�������
#define B2FIRE_NUM		3		//һ���ڷ������
//�ڶ��׶�
#define STAGE02_NOMALCOOL	2.0f		//��ͨ������ȴ����
#define STAGE02_NOMALFIRENUM		8	//һ���ڷ������
#define STAGE02_NOMALSLOT		0.2f	//������
#define STAGE02_BSPEED		200.0f		//�ӵ��ٶ�
//����ɢ��
#define STAGE02_COOL		0.0f		//��ȴ����
#define STAGE02_SLOT		0.1f		//������
#define STAGE02_FIRENUM		30			//һ���ڷ������

class CBossTwo :
	public CCNode
{
public:
	CBossTwo(void);
	~CBossTwo(void);
public:
	static CBossTwo* createBoss(void);
	void underAttack(int nHurt);
	bool isCheck(void);
	void onEnter();
	void onExit();
	CCRect getCurBoundbox(void);
private:
	void createSprite(void);
	void bossUpdate(float fEscapeTime);
	//ֱ����BOSS 02
	void bossCallback(void);
	void flareWeapon(void);
	void destroyWeapon(void);
	void stage1Fire(void);
	void stage2Fire(void);
	void runEffect(void);
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

	//level02 data
	int m_nNomalFireNum;
	float m_fNomalFireRound;			//������ȴ��
	//STAGE 01
	int m_nFireNum;
	float m_fFireRound;			//������ȴ��
	float m_fShotFireSlot;		//�����ӵ����
	CCSprite *m_pPropeller;		//������
	//STAGE 01
	CCSprite *m_pLeftWeapon;	//������
	CCSprite *m_pLeftFlashSprite;
	CCSprite *m_pRightFlashSprite;
	CCSprite *m_pRightWeapon;	//������
	CCSprite *m_pLeftExplode;	//��ը
	CCSprite *m_pRightExplode;	//�ұ�ը

	float m_fEnemyTime;			//����С�ɻ�����ʱ��
};

#endif