#ifndef BOSSTHREE_H
#define BOSSTHREE_H
#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"


//BOSS 03��������
#define  BOSS03_STAGE01_HP	8000		//��һ�׶�Ѫ��
#define  BOSS03_STAGE02_HP	8000		//�ڶ��׶�Ѫ��
#define  BOSS03_STAGE03_HP	9000		//�����׶�Ѫ��
//��һ�׶�
#define BOSS03_STAGE01_FIRETIME		1.0f	//������
#define BOSS03_STAGE01_FIRENUM		8		//һ�η�������
//�ڶ��׶�
#define BOSS03_STAGE02_SECTOR			90.0F	//ɢ��Ƕ�
#define BOSS03_STAGE02_ROUNDS		6		//�ӵ�����

#define BOSS03_STAGE02_MISSLE		2.0f	//�������
//�����׶�
#define BOSS03_STAGE03_SECTOR			90.0F	//ɢ��Ƕ�
#define BOSS03_STAGE03_NUMBER			8		//�ӵ�����

class CBossThree :
	public CCNode
{
public:
	CBossThree(void);
	~CBossThree(void);
public:
	static CBossThree* createBoss(void);
	void underAttack(int nHurt);
	bool isCheck(void);
	void onEnter();
	void onExit();
	CCRect getCurBoundbox(void);
private:
	void createSprite(void);
	void bossUpdate(float fEscapeTime);
	//BOSS 03
	void bossCallback(void);
	void flareWeapon(void);
	void destroyWeapon(void);
	void stage1Fire(void);
	void stage2Direction(void);
	void stage2Fire(void);
	void stage3Fire(void);
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
	//level03 data
	//int m_nBoss03Stage2Num;		//�ӵ�����
	CCSprite *m_pMainBody;			//������
	CCSprite *m_pLeftWing;			//�����
	CCSprite *m_pRightWing;			//�һ���
	CCSprite *m_pTailFin;			//β��

	//stage2
	int m_nRounds;
	BULLET_DATA m_sStage2Data;

	float m_fEnemyTime;			//����С�ɻ�����ʱ��
};

#endif