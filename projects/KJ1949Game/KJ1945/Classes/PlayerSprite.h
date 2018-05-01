#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include "cocos2d.h"

using namespace cocos2d;

#include "GlobalData.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"
#include "ItemSprite.h"

using namespace CocosDenshion;

#define PFRAME_TIME	0.1f

enum PLAYER_STATE
{
	PS_DEFAULT,
	PS_AUTOMOVE,
	PS_MOVE,
	PS_AUTOFLY,
	PS_LANDING,
	PS_EXPLODE,
	PS_HIDE,
};

class CPlayerSprite :
	public CCNode
{
public:
	CPlayerSprite(void);
	~CPlayerSprite(void);

public:
	static CPlayerSprite* createPlayer(PLAYER_KINDS eKind);
	void setTargetPoint(const CCPoint& pos);
	//CC_PROPERTY_PASS_BY_REF(CCPoint, m_tTargetPosition, TargetPosition)
	void underAttack(int nHurt);
	void addHealthPoint(int nValue);

	void setGravityOffset(CCPoint Offset){m_sGravityOffset = Offset;}
	//void addFire(void);
	//void addIronCurtain(void);

	//
	void addItemKind(ITEM_KINDS eKind);
	//ʹ�ñ����ĵ���
	void usingHoldItem(void);
	void addItem(ITEM_KINDS eKind);
	bool isDead(void);
	bool isShieldTaken(void);
	float getHPPercentage(void);
	PLAYER_STATE getCurState(void){return m_eCurState;} 
	void setAutoFly(void);
	void runLand(const CCPoint& pos);
public:
private:
	void createSprite(PLAYER_KINDS eKind);
	void playerUpdate(float fEscapeTime);
	void setFlyingAttitude(float fOffset);				//���÷�����̬
	void displayFrameByIndex(unsigned int nIndex);
	void fireBullet(float fEscapeTime);

	void itemUpdate(float fEscapeTime);
	void itemLogic(ITEM_KINDS eKind, float fEscapeTime);
	void removeItemIndex(ITEM_KINDS eKind);
	void removeItemByKind(ITEM_KINDS eKind);
	bool isExistItem(ITEM_KINDS eKind);
	void removeAllItem(void);

	void removeSelf(void);
	void runEffect(void);
	void activatePlayer(void);
	void returnNormalTexture(void);

	//FIRE BALL
	void addFireBall(void);
	//POWER
	void addPower(void);
	//IRON CURTAIN
	void addIronCurtain(void);
	//TRACK ROCKET
	void addTarckRocket(void);
	//SHIELD TAKEN
	void addShieldTaken(void);
	void removeIronCurtain(void);
	//WING MAN
	void addWingMan(void);
	void removeWingMan(void);

	void lostPower(void);
private:
	CCSize mScreenSize;
	CCSpriteFrameCache *m_pCurCache;
	PLAYER_DATA m_sCurData;
	PLAYER_DATA m_sInitData;
	std::vector<CCSprite*> m_vPlayerSpriteVector;
	CCPoint m_tTargetPosition;
	float m_fTime;
	int m_nCurFrame;
	CCSprite *m_pEffectSprite;
	PLAYER_STATE m_eCurState;

	int m_nFireLevel;
	float m_fFireHoldTime;			//��������ʱ��

	//FIRE BALL
	float m_fFireBallTime;			//�������ʱ��
	float m_fFireBallSlot;			//���򿪻�ʱ�����ۼ�
	//IRON CURTAIN
	float m_fIronCurtainTime;		//��Ļ����ʱ��
	ccColor3B m_sOriginalColor;			//ԭʼ��ɫ
	//TRACK ROCKET
	float m_fTarckRocketSlot;		//����ʱ�����ۼ�
	//SHIELD TAKEN
	float m_fShieldTakenTime;		//����ܳ���ʱ��
	CCSprite *m_pShieldTaken;
	//SUPER GUN
	float m_fSuperGunTime;			//����ǹ����ʱ��
	float m_fSuperGunSlot;			//����ǹ����ʱ�����ۼ�
	float m_fSuperGunPos;				//����λ��
	//SIDE BULLET
	float m_fSideBulletTime;		//ɢ������ʱ��
	float m_fSideBulletSlot;		//ɢ������ʱ�����ۼ�
	//WING MAN
	float m_fWingManTime;			//�Ż�����ʱ��
	float m_fWingManSlot;			//�Ż�����ʱ�����ۼ�
	CCSprite *m_pLeftWingMan;
	CCSprite *m_pRightWingMan;		

	CCSprite *m_pShadow;			//Ӱ��
	bool m_bIsNormal;

	CCSprite *m_pFireFlashSprite;
	CCAction *m_pFireFlash;
	//CPlayerWeapon *m_pPlayerWeapon;

	std::vector<ITEM_KINDS> m_vItemVector;

	//SOUND
	SimpleAudioEngine *m_pCurAudio;

	//Gravity Offset
	CCPoint m_sGravityOffset;

	//��ǰ���ʱ��
	float m_fPlayerTime;

	//������ITEM
	ITEM_KINDS m_eHoldItem;
	//temp
	float m_fBtime;
	float m_fBRoundTime;
	int m_nBNumber;

	ccColor3B color;
	float m_fFlashTime;
};

#endif