#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;


enum ENEMY_KINDS
{
	EK_DEFAULT,			//Ĭ��
	EK_PLANE02,			//
	EK_PLANE03,			//
	EK_PLANE04,			//
	EK_HELI01,
	EK_HELI02,
	EK_AIRMINE,			//���е��׷ɻ�
	EK_ARMOR,			//�ؼ׻�
	EK_MINE,			//���е���
};

enum ARMY_KINDS
{
	AK_DEFAULT,				//Ĭ��
	AK_MISSILEARMY,			//����̹��
	AK_GREENGUN01,			//������01
	AK_GREENGUN02,			//������02
	AK_BATTERY01,			//�ڱ�01
	AK_BATTERY02,			//�ڱ�02
	AK_BUNKER01,			//�ر�01
	AK_BUNKER02,			//�ر�02
	AK_ARMY_MAX,			//���ֵ
};

enum FLYING_ATTITUDE	//������̬
{
	FA_DEFAULT,			//ֱ�����϶���
	FA_LEFTTORIGHT,		//������
	FA_RIGHTTOLEFT,		//���ҵ���
	FA_LEANLR,			//б������-���£�
	FA_LEANRL,			//б������-���£�
	FA_LROUNDTB,		//���ƣ����ϰ벿�ֳ����ư���������°벿�֣�
	FA_RROUNDTB,		//�һ��ƣ����ϰ벿�ֳ����ư���������°벿�֣�
	FA_LROUNDBT,		//���ƣ����°벿�ֳ����ư���������ϰ벿�֣�
	FA_RROUNDBT,		//�һ��ƣ����°벿�ֳ����ư���������ϰ벿�֣�
	FA_TROUNDLR,		//���������������ư�����ηɳ������ң�
	FA_TROUNDRL,		//���������������ư�����ηɳ����ҵ���
	FA_LQROUNDTB,		//����1/4�����ϰ벿�ֳ�����1/4���εײ���ʧ��
	FA_RQROUNDTB,		//�һ���1/4�����ϰ벿�ֳ�����1/4���εײ���ʧ��
	FA_TQROUNDLR,		//������1/4�����ϰ벿�ֳ�����1/4�����ұ���ʧ��
	FA_TQROUNDRL,		//������1/4�����ϰ벿�ֳ�����1/4���������ʧ)
	FA_ENEMY_MAX,		//�л����ֵ
	FA_M_A_M,			//ֱ��������(���϶����ƶ�,��ͣ,��������ƶ��ɳ�)
	FA_AIRMINE,			//���е��׻�
	FA_MINE,			//���е���(���Ƿɻ�)
	FA_ARMOR,			//�ؼ׻�
};

enum PLAYER_KINDS
{
	PK_DEFAULT,			//����
	PK_HURRICANE,			//쫷�hurricane
	PK_WOLFANG,		//����Wolfang
	PK_EAGLEEYE,		//ӥ��eagle eye
	PK_KINGKONG,		//���King Kong
	PK_TITAN,		//̩̹Titan
};

//�������
enum PLAYER_WEAPON
{
	PW_DEFAULT,
};

enum ENEMY_WEAPON
{
	EW_DEFAULT,
	EW_NONE,		//������
	EW_SCATTER,		//ɢ��
	EW_AIRMINE,		//���е���
	EW_HOLDFIRE,	//��������
};

enum BULLET_KINDS
{
	BK_DEFAULT,
	BK_DEFAULT01,
	BK_ARMY01,
	BK_ENEMY01,
	BK_FIREBALL,
	BK_TARCKROCKET,
	BK_SUPERGUN,	//�����ǹ
	BK_LASER,		//������
	BK_THUNDERBALL,	//����
	BK_BLUE,		//��ɫ�ӵ�
	BK_SINBALL,		//���������ӵ�
	BK_USINBALL,	//�����������ӵ�
	BK_CRESCEN,		//��������ƫ��
	BK_UCRESCEN,	//��������ƫ��
};

enum ITEM_KINDS
{
	IK_DEFAULT,
	IK_HP,
	IK_FIREPOWER,
	IK_FIREBALL,
	IK_IRONCURTAIN,
	IK_SHIELDTAKEN,
	IK_TRACKROCKET,
	IK_SUPERGUN,
	IK_LIFE,
	IK_WINGMAN,
	IK_SIDEBULLET,

	IK_MAX,
};

enum BOSS_KINDS
{
	BOK_DEFAULT,
	BOK_LEVEL01,
	BOK_LEVEL02,
	BOK_LEVEL03,
	BOK_LEVEL04,
	BOK_LEVEL05,
	BOK_LEVEL06,
	BOK_LEVEL07,
	BOK_LEVEL08,
};

enum BOSS_STATE
{
	BOS_DEFAULT,
	BOS_READY,
	BOS_READY_RUN,
	BOS_STAGE,
	BOS_STAGE_RUN,
	BOS_FIRE,
	BOS_FIRE_RUN,
	BOS_EXPLODE,
	BOS_EXPLODE_RUN,
	BOS_HIDE,
};

enum STAGE_BOSS
{
	STAGE_DEFAULT,
	STAGE_READY01,
	STAGE_ACTION01,
	STAGE_READY02,
	STAGE_ACTION02,
	STAGE_READY03,
	STAGE_ACTION03,
	STAGE_READY04,
	STAGE_ACTION04,
	STAGE_READY05,
	STAGE_ACTION05,
	STAGE_EXPLODE,
};

#define  STAGEEND_HP	0		//����

struct BULLET_DATA
{
	BULLET_KINDS mKind;
	float mMoveSpeed;		//�����ٶ�
	CCPoint mDirection;		//���з���
	int mAttack;			//�˺�ֵ
	//���
	float m_fAmplitude;
};

struct ENEMY_DATA	//��������
{
	ENEMY_KINDS mKind;			//����
	int mIndex;					//�������
	FLYING_ATTITUDE mAttitude;	//���з�ʽ
	int mScoreValue;			//��ֵ(�򱬺��õķ���)
	float mMoveSpeed;			//�ٶ�
	//int mDirection;				//����
	int mHealthPoint;			//HP
	//CCPoint mPoint;				//λ��
	int mAttack;				//������
};

struct ARMY_DATA
{
	ARMY_KINDS mKind;
	int mIndex;
	int mScoreValue;
	float mMoveSpeed;
	CCPoint mDirection;		//��������
	int mHealthPoint;
	int mAttack;
};

struct FLY_DATA
{
	FLYING_ATTITUDE mAttitude;
	CCPoint mPosition;			//��ʼλ��
	//temp
	float m_fTime;				//����ʱ��
	ENEMY_KINDS mKind;			//�ɻ���ʽ
};

struct LAND_DATA
{
	CCPoint mPosition;			//��ʼλ��
	//temp
	float m_fTime;				//����ʱ��
	ARMY_KINDS mKind;			//½����ʽ
};

struct PLAYER_DATA
{
	PLAYER_KINDS mKind;			//����
	PLAYER_WEAPON mWeapon;		//��������
	int mLevel;
	int mFreePropertyPoints;	//�������Ե�
	int mSpeed;					//�ٶ�
	int mArmor;					//װ��
	int mAttack;				//�������ӳ�
	int mBonusAttack;			//���߼ӳ�
	int mHealthPoint;			//HP
	int mIndex;					//�������
};

struct WEAPON_DATA
{
	PLAYER_WEAPON mKind;
	float mAttackSpeed;
};

struct LEVEL_DATA
{
	int mLevel;
	std::string	mMission;
	float mMapSpeed;
	float mBossTime;			//BOSS���ֵ�ʱ��
};

//����
enum ASSESS_KINDS
{
	ASK_DEFAULT,
	ASK_PERFECT,
	ASK_ADD50,
	ASK_ADD100,
	ASK_FIRE,
	ASK_HP,
	ASK_LIFE,
	ASK_FIREBALL,
	ASK_IRONCURTAIN,
	ASK_SHIELDTAKEN,
	ASK_TRACKROCKET,
	ASK_SUPERGUN,
	ASK_WINGMAN,
	ASK_SIDEBULLET,
};
struct	ASSESS_DATA
{
	ASSESS_KINDS mKind;
	CCPoint mPos;
};

#define DATA_LENTH_MAX	128	//�����ַ�������

#define INIT_LIFE	3		//��ʼ������
#define PLAYER_MAX	6		//��ҿ�ѡ�ɻ���
#define LEVEL_MAX	8		//��ҿ�ѡ�ؿ���
#define ANIMATE_MAX 32		//��󶯻�֡��
#define OFFSET_MAX	10.0f	//����ƶ�������
#define FLYING_MAX	0.0f	//������̬ƫ�����
#define ITEM_LIFE	10.0f	//���ߴ�������
#define FIRE_MAX	2		//������󼶱�(��������)
#define FIRE_HOLD	10.0f	//��������ʱ��
#define IRON_HOLD	10.0f	//��Ļ����ʱ��
#define FIREBALL_SLOT	0.4f	//��������
#define SUPERGUN_SLOT	0.05f	//����ǹ������
#define SIDEBULLET_SLOT	0.2f	//ɢ��������
#define WINGMAN_HOLD	13.0f	//�Ż�����ʱ��
#define WINGMAN_SLOT	0.2f	//�Ż�������
#define TARCKROCKET_SLOT	1.0f	//����������
#define TOUCH_OFFSET 75.0f	//����λ��ƫ��
#define BANNER_HEIGHT	75.0f	//������߶�
#define DROPITEM_SLOT	5.0f	//��Ʒ����ʱ����
#define NUCLEAR_HURT	1000	//�˵����˺�ֵ
#define ROCKET_NUM		10		//����������
#define SHIELD_DES		64.0f	//�����ж�����
#define LACKEY_TIME		3.0f	//���ͷɻ�����ʱ�� 

#define DOUBLE_TIME		0.5f	//˫���¼��ж�ʱ����

#define SLOT_TIME	0.5f	//�ɻ����ּ��
#define LAND_TIME	1.0f	//�ɻ���½ʱ��
#define ROUND_TIME	1.0f	//�ɻ������֮����

#define ENEMY_TYPE		10000
#define ARMY_TYPE		11000
#define BOSS_TYPE		12000
#define HELI_TYPE		13000
#define DRONE_TYPE		14000
#define PALYER_TYPE		20000
#define ENEMY_BULLET	30000
#define PALYER_BULLET	40000

#define MAP_ZORDER		1		//���汳��Z-order
#define ARMY_ZORDER		11		//���沿��Z-order
#define BOMB_ZORDER		20		//�Ե�ը��Z-order
#define LCLOUD_ZORDER	21		//�Ͳ���Z-order
#define ABULLET_ZORDER	30		//���в����ӵ�Z-order
#define AIR_ZORDER		31		//���в���Z-order
#define BOSS_ZORDER	34			//BOSS Z-order
#define BBULLET_ZORDER	35		//BOSS�ӵ� Z-order
#define PBULLET_ZORDER	40		//����ӵ�Z-order
#define FLASH_ZORDER	41		//��ҿ�������Z-order
#define PLAYER_ZORDER	42		//���Z-order
#define HCLOUD_ZORDER	51		//�߲���Z-order
#define ASSESS_ZORDER	58		//����Z-order
#define GAMEUI_ZORDER	61		//��ϷUI��Z-order

#define BANNER_ZORDER	80		//����Z-order

#define MAIN_UI			1000
#define SELECT_UI		2000
#define SHOP_UI			3000
#define MISSION_UI		4000

#define VERSION			2		//�汾���ƣ�1Ϊ��ȫ��2Ϊȥ��溣��棩

class CGlobalData
{
public:
	CGlobalData(void);
	~CGlobalData(void);
public:
	static CGlobalData* getSingleton(void);

	void setSelectedPlayerID(unsigned int nIndexID);
	void setLevelID(unsigned int nLevelID);
	LEVEL_DATA getCurLevelData(void){return m_sCurLevelData;}

	void saveFighterConfigure(void);

	std::string getNameByKind();
	ENEMY_DATA getDataByKind(ENEMY_KINDS eKind);
	ARMY_DATA getDataByKind(ARMY_KINDS eKind);
	PLAYER_DATA getDataByKind(PLAYER_KINDS eKind);
	//temp end
	void initProData(void);
	void loadProData(void);

	void addScore(int nScore);
	int getCurScore(void){return m_nCurScore;}
	int getCurPoint(void){return m_nPlayerPoint;}
	PLAYER_KINDS getSelectKind(void) {return m_eSelectPlayer;}
	std::vector<FLY_DATA> getLevelPlaneData(int nLevel);
	std::vector<LAND_DATA> getLevelLandData(int nLevel);

	void resetLevelScore(void);
	void addAirScore(ENEMY_KINDS eKind);
	void addArmyScore(ARMY_KINDS eKind);
	void addDesAirScore(ENEMY_KINDS eKind);
	void addDesArmyScore(ARMY_KINDS eKind);
	int getAirScoreByIndex(ENEMY_KINDS eKind);
	int getArmyScoreByIndex(ARMY_KINDS eKind);
	int getDesAirScoreByIndex(ENEMY_KINDS eKind);
	int getDesArmyScoreByIndex(ARMY_KINDS eKind);

	int getDesPercentage(void);

	void upDateGameTime(float fEscapeTime){m_fGameTime += fEscapeTime;}
	void recordDropTime(void){m_fItemDropTime = m_fGameTime;}
	bool isDropItem(void)
	{
		if (abs(m_fItemDropTime - m_fGameTime) > DROPITEM_SLOT)
		{
			return true;
		}
		return false;
	}

	void addBombPercentage(void)
	{
		m_fBombPercentage += 0.5f;
		if (m_fBombPercentage > 100.0f)
		{
			m_fBombPercentage = 100.0f;
		}
	}

	void resetBombPercentage(void){m_fBombPercentage = 0.0f;}
	float getBombPercentage(void){return m_fBombPercentage;}

	void addRocket(int nNumber)
	{
		m_nRocketNumber += nNumber;
		if (m_nRocketNumber > 99)
		{
			m_nRocketNumber = 99;
		}
	}
	void reduceRocket(int nNumber)
	{
		m_nRocketNumber -= nNumber;
		if (m_nRocketNumber < 0)
		{
			m_nRocketNumber = 0;
		}
	}
	int getRocket(void){return m_nRocketNumber;}

	void reduceLife(void)
	{
		m_nLifeNumber --;
		if (m_nLifeNumber < 0)
		{
			m_nLifeNumber = 0;
		}
	}

	void addLife(int nNumber)
	{
		m_nLifeNumber += nNumber;
		if (m_nLifeNumber > 9)
		{
			m_nLifeNumber = 9;
		}
	}
	
	int getLife(void){return m_nLifeNumber;}

	void resetPlayerData(void);

	void setIsWingman(bool bIsExist){m_bWingmanExist = bIsExist;}
	bool isExistWingman(void){return m_bWingmanExist;}

	void setLevelClear(bool bIsClear){m_bLevelClear = true;}
	bool isLevelClear(void){return m_bLevelClear;}

	//ѡ��
	void setOption(void);
	void setMusicONOFF(bool bOnOff){m_bOpenMusic = bOnOff;}
	bool isOpenMusic(void){return m_bOpenMusic;}

	void setFXONOFF(bool bOnOff){m_bOpenFX = bOnOff;}
	bool isOpenFX(void){return m_bOpenFX;}

	void setMusicVolume(float fVolume){m_fMusicVolume = fVolume;}
	float getMusicVolume(void){return m_fMusicVolume;}

	void setFXVolume(float fVolume){m_fFXVolume = fVolume;}
	float getFXVolume(void){return m_fFXVolume;}

	void setDifficultyVolume(float fVolume){m_fDifficultyVolume = fVolume;}
	float getDifficultyVolume(void){return m_fDifficultyVolume;}

	bool isTouchControl(void){return m_bTouchControl;}
	void setTouchControl(bool bTouch){m_bTouchControl = bTouch;}

	bool isGravityControl(void){return m_bGravityControl;}
	void setGravityControl(bool bGravity){m_bGravityControl = bGravity;}

	bool isRunControl(void){return m_bRunControl;}
	void setRunControl(bool bRun){m_bRunControl = bRun;}

	bool isDoubleControl(void){return m_bDoubleControl;}
	void setDoubleControl(bool bDouble){m_bDoubleControl = bDouble;}

	void setPlayerPoint(int nPoint){m_nPlayerPoint = nPoint;}
	int getPlayerPoint(void){return m_nPlayerPoint;}

	void setPlayerSpeed(int nSpeed){m_nPlayerSpeed = nSpeed;}
	int getPlayerSpeed(void){return m_nPlayerSpeed;}

	void setPlayerArmor(int nArmor){m_nPlayerArmor = nArmor;}
	int getPlayerArmor(void){return m_nPlayerArmor;}

	void setPlayerAttack(int nAttack){m_nPlayerAttack = nAttack;}
	int getPlayerAttack(void){return m_nPlayerAttack;}

	void setPlayerBouns(int nBouns){m_nPlayerBouns = nBouns;}
	int getPlayerBouns(void){return m_nPlayerBouns;}

	//��¼��ǰ�ؿ�����
	void setRewardByLevel(int nLevel);

	int getTotalScore(void){return m_nScoreTotal;}

	int getScoreByLevel(int nLevel);

	//��ǰ�ؿ���������
	void countCurLevelReward(int nLevel);
	int getCurRewardScore(void){return m_nCurRewardScore;}
	int getCurRewardPoint(void){return m_nCurRewardPoint;}

	//ת�����������;���
	bool convertRewardScore(void);
	//����ת������
	void convertAllRewardScore(void);

	//��ǰ�ı�������
	void setHoldItem(ITEM_KINDS eKind){m_eHoldItem = eKind;}
	ITEM_KINDS getHoldItem(void){return m_eHoldItem;}

	CCPoint getPosByFlyAttitude(FLYING_ATTITUDE eKind);		//���ݷ�����̬��ó�ʼλ��

	//��ս��
	void addEndlessNum(void){m_nEndlessNum ++;}
	int getEndlessNum(void){return m_nEndlessNum;}
	void resetEndlessData(void);
	bool isRefreshEndlessData(void){return m_bRefreshData;}
	void resetRefreshData(bool bResfresh){m_bRefreshData = bResfresh;}
	void setEndlessBossID(int nBossID){m_nEndlessBossID = nBossID;}
	int getEndlessBossID(void){return m_nEndlessBossID;}
	//�ɻ���
	int getUnlockPlane(void){return m_nPlaneUnlock;}

	//�ؿ���
	int getUnlockLevel(void){return m_nLevelUnlock;}
	int getCurUnlockLevel(void){return m_sPlaneLevelVector[m_eSelectPlayer];}
private:
	
private:
	CCUserDefault *m_pSaveData;

	std::vector<PLAYER_DATA> m_vPlayerDataVector;
	std::vector<LEVEL_DATA> m_vLevelDataVector;
	std::vector<ENEMY_DATA> m_vEnemyDataVector;
	std::vector<ARMY_DATA> m_vArmyDataVector;
	std::vector<FLY_DATA> m_vFlyDataVector;
	PLAYER_DATA m_sCurPalyerData;
	LEVEL_DATA m_sCurLevelData;


	PLAYER_KINDS m_eSelectPlayer;
	int m_nRocketNumber;

	int m_nLifeNumber;

	//��ǰ�����ļ���
	ITEM_KINDS m_eHoldItem;

	//temp

	//��ǰ����
	int m_nCurScore;
	//��ǰ����
	//int m_nCurLevelPoint;
	std::vector<FLY_DATA> m_vLevelPlaneData;
	std::vector<LAND_DATA> m_vLevelLandData;

	std::vector<int> m_vDesAirScore;
	std::vector<int> m_vAirScore;

	std::vector<int> m_vDesArmyScore;
	std::vector<int> m_vArmyScore;

	float m_fGameTime;
	float m_fItemDropTime;
	//float m_fBombTime;			//�˵�ʱ��
	float m_fBombPercentage;	//�˵�����
	bool m_bWingmanExist;		//�Ƿ��Ѿ����Ż�

	bool m_bLevelClear;			//���ؿ��Ƿ����

	bool m_bOpenMusic;
	bool m_bOpenFX;
	float m_fMusicVolume;
	float m_fFXVolume;
	float m_fDifficultyVolume;

	bool m_bTouchControl;
	bool m_bGravityControl;
	bool m_bRunControl;
	bool m_bDoubleControl;
	//������Ե�
	int m_nPlayerPoint;

	int m_nPlayerSpeed;
	int m_nPlayerArmor;
	int m_nPlayerAttack;
	int m_nPlayerBouns;

	//ÿ���Ѿ���������
	int m_nLevel01Point;
	int m_nLevel02Point;
	int m_nLevel03Point;
	int m_nLevel04Point;
	int m_nLevel05Point;
	int m_nLevel06Point;
	int m_nLevel07Point;

	//��ǰ��������
	int m_nCurRewardPoint;
	//��ǰ��������
	int m_nCurRewardScore;

	//�ܷ�
	int m_nScoreTotal;
	//ÿ��ͳ�Ʒ���
	int m_nScore01;
	int m_nScore02;
	int m_nScore03;
	int m_nScore04;
	int m_nScore05;
	int m_nScore06;
	int m_nScore07;

	//��ս������
	int m_nScore08;
	//��ս�����BOSS��ID
	int m_nEndlessBossID;
	//��ս���ظ�����
	int m_nEndlessNum;
	//�Ƿ���Ҫˢ������
	bool m_bRefreshData;

	//�ؿ���
	int m_nLevelUnlock;
	//�ɻ���
	int m_nPlaneUnlock;

	//�����ɻ��Ĺؿ���������
	std::vector<int> m_sPlaneLevelVector;
	int m_nPlane01Level;
	int m_nPlane02Level;
	int m_nPlane03Level;
	int m_nPlane04Level;
	int m_nPlane05Level;
	int m_nPlane06Level;

};


#endif