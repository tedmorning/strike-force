#include "BossFive.h"

CBossFive::CBossFive(void)
{
	m_pCurAudio->stopBackgroundMusic(true);
}

CBossFive::~CBossFive(void)
{
}


CBossFive* CBossFive::createBoss(void)
{
	CBossFive *pBoss = new CBossFive();
	pBoss->createSprite();
	pBoss->setTag(BOSS_TYPE);
	//pBoss->m_eBossKind = eKind;
	return pBoss;
}

void CBossFive::createSprite(void)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	m_eCurState = BOS_READY_RUN;
	m_pCurAudio->playEffect(("sounds/Warning.ogg"));
	this->schedule(schedule_selector(CBossFive::bossUpdate));
}

bool CBossFive::isCheck(void)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02 || m_eCurStage == STAGE_ACTION03)
	{
		return true;
	}
	return false;
}

CCRect CBossFive::getCurBoundbox(void)
{
	CCRect mRect = CCRectMake(0,0,0,0);
	if (m_pCurAttack)
	{
		mRect = m_pCurAttack->boundingBox();
		mRect.origin.x = mRect.origin.x + getPositionX() - getContentSize().width * 0.5f;
		mRect.origin.y = mRect.origin.y + getPositionY() - getContentSize().height * 0.5f;
	}

	return mRect;
}

void CBossFive::onEnter(void)
{
	setAnchorPoint(ccp(0.5f,0.5f));
	setContentSize(CCSizeMake(400,283));
	m_pBaseSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss05_Base.png"));
	m_pBaseSprite->setAnchorPoint(ccp(0.5f,0.5f));
	addChild(m_pBaseSprite, ARMY_ZORDER);
	m_pBaseSprite->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	m_pBaseSprite->setVisible(false);

	m_pMainBody = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss05_Body01_01.png"));
	m_pMainBody->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.503f));
	addChild(m_pMainBody);


	m_pLeftWing = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss05_Body02_01.png"));
	m_pLeftWing->setPosition(ccp(getContentSize().width * 0.235f, getContentSize().height * 0.623f));
	addChild(m_pLeftWing);

	m_pRightWing = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss05_Body03_01.png"));
	m_pRightWing->setPosition(ccp(getContentSize().width * 0.765f,getContentSize().height * 0.623f));
	addChild(m_pRightWing);

	m_pTailFin = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss05_Body04_01.png"));
	m_pTailFin->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.095f));
	addChild(m_pTailFin);

	////������
	//m_pLaserGun = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss05_Gun02_01.png"));
	//m_pLaserGun->setPosition(ccp(m_pBaseSprite->getContentSize().width * 0.5f, m_pBaseSprite->getContentSize().height * 0.49f));
	//addChild(m_pLaserGun, ARMY_ZORDER);

	//����
	m_pMainGun = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss05_Gun01_01.png"));
	m_pMainGun->setPosition(ccp(m_pBaseSprite->getContentSize().width * 0.5f, m_pBaseSprite->getContentSize().height * 0.49f));
	m_pMainGun->setAnchorPoint(ccp(0.5f,0.7f));
	addChild(m_pMainGun, ARMY_ZORDER);
	//m_pLaserGun->runAction(CCRepeatForever::create((CCActionInterval*)CCRotateBy::create(0.5f,360.0f)));

	m_pExplode = CCSprite::create();
	m_pExplode->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	addChild(m_pExplode, ARMY_ZORDER);

	m_pCurAttack = NULL;
	m_fLaserTime = 0.0f;
	m_fTime = 0.0f;

	m_nBossHP = BOSS05_STAGE01_HP;
	if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
	{
		m_nBossHP = 8000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
	}
	m_fEnemyTime = 0.0f;


	//ִ�г�������
	setPosition(ccp(mScreenSize.width * 0.0f, - getContentSize().height));
	setScale(1.5f);
	//��ʱ
	CCDelayTime *pDelayTime = CCDelayTime::create(3.0f);
	//�ɳ�
	CCMoveTo *pMoveDown = CCMoveTo::create(3.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 1.2f - BANNER_HEIGHT));
	//��С
	CCScaleTo *pScaleTo = CCScaleTo::create(1.0f, 1.0f);
	//����
	CCMoveTo *pMoveBack =CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.8f - BANNER_HEIGHT));
	//�ϳɣ��Ŵ�+���ˣ�
	CCAction *pSpawn = CCSpawn::create(pScaleTo, pMoveBack,NULL);
	//չ�������ص�
	//CCCallFunc *pFlareWeapon = CCCallFunc::create(this, callfunc_selector(CBossThree::flareWeapon));
	//�ɵ�ָ��λ��
	CCMoveTo *pMoveLeft = CCMoveTo::create(0.5f,ccp(mScreenSize.width * 0.2f, mScreenSize.height * 0.8f - BANNER_HEIGHT));
	//�ص�
	CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossFive::bossCallback));

	//����
	//CCSequence *pSequence = CCSequence::create(pDelayTime,pMoveDown,pScaleTo,pMoveLeft,pCallback,NULL);
	runAction(CCSequence::create(pDelayTime,pMoveDown,pSpawn,/*pDelayTime,*/pMoveLeft,pCallback,NULL));


	//base color
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
	m_sBaseColor = pRGBAProtocol->getColor();
	m_fFlashTime = 0.0f;
	m_bBaseNormal = true;
	m_fTime = BOSS03_STAGE01_FIRETIME;
	m_eCurStage = STAGE_READY01;


	m_pCurAudio->playBackgroundMusic(("sounds/Boss01.ogg"));
	CCNode::onEnter();
}

void CBossFive::onExit()
{
	removeAllChildrenWithCleanup(true);
	CCNode::onExit();
}


void CBossFive::bossUpdate(float fEscapeTime)
{
	switch(m_eCurStage)
	{
	case STAGE_DEFAULT:
		break;
	case STAGE_ACTION01:
		{
			m_fTime += fEscapeTime;
			//if (m_fTime > BOSS05_STAGE01_FIRESLOT)
			//{
			//	m_fTime = 0.0f;
			//	BULLET_DATA mData;
			//	mData.mAttack = 5;
			//	mData.mMoveSpeed = 150.0f;
			//	mData.mDirection = ccpRotateByAngle(ccp(0, -1), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pMainGun->getRotation()));
			//	CCPoint mLeftPos = ccpRotateByAngle(ccp(-7, -130), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pMainGun->getRotation()));
			//	CCPoint mRightPos = ccpRotateByAngle(ccp(4, -130), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pMainGun->getRotation()));
			//	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
			//	pBullet->setPosition(ccp(getPositionX() + mLeftPos.x, getPositionY() + mLeftPos.y - m_pBaseSprite->getContentSize().height * 0.094f));
			//	getParent()->addChild(pBullet, ABULLET_ZORDER);
			//	pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
			//	pBullet->setPosition(ccp(getPositionX() + mRightPos.x, getPositionY() + mRightPos.y - m_pBaseSprite->getContentSize().height * 0.094f));
			//	getParent()->addChild(pBullet, ABULLET_ZORDER);
			//}

			//m_fLaserTime += fEscapeTime;
			//if (m_fLaserTime > BOSS05_STAGE01_LASERSLOT)
			//{
			//	m_fLaserTime = 0.0f;
			//	BULLET_DATA mData;
			//	mData.mKind = BK_THUNDERBALL;
			//	mData.mAttack = 5;
			//	mData.mMoveSpeed = 150.0f;
			//	mData.mDirection = ccp(0.0f, -1.0f);
			//	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_THUNDERBALL);
			//	pBullet->setPosition(ccp(getPositionX() - m_pBaseSprite->getContentSize().width * 0.5f + m_pLaserGun->getPositionX(), getPositionY() - m_pBaseSprite->getContentSize().height * 0.5f + m_pLaserGun->getPositionY()));
			//	getParent()->addChild(pBullet, PBULLET_ZORDER);
			//}

			m_fTime += fEscapeTime;
			if (m_fTime > BOSS05_STAGE01_FIRESLOT)
			{
				m_fTime = 0.0f;
				BULLET_DATA mData;
				mData.mAttack = 16;
				mData.mMoveSpeed = 150.0f;
				mData.mDirection = ccpNormalize(ccp(0.0f, -1.0f));
				CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_BLUE);
				pBullet->setPosition(ccp(getPositionX(), getPositionY() - getContentSize().height * 0.4f));
				getParent()->addChild(pBullet, ABULLET_ZORDER);
			}

		}
		break;
	case STAGE_ACTION02:
		{
			m_fTime += fEscapeTime;
			if (m_fTime > BOSS05_STAGE02_MISSLE)
			{
				m_fTime = 0.0f;

				BULLET_DATA mData;
				mData.mKind = BK_TARCKROCKET;
				mData.mAttack = 26;
				mData.mMoveSpeed = 250.0f;
				mData.mDirection = ccp(-1.0f, 0.0f);
				CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
				pBullet->setPosition(ccp(getPositionX() - getContentSize().width * 0.225f, getPositionY() + getContentSize().height * 0.165f));
				getParent()->addChild(pBullet, AIR_ZORDER);

				pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
				pBullet->setPosition(ccp(getPositionX() - getContentSize().width * 0.11f, getPositionY() + getContentSize().height * 0.165f));
				getParent()->addChild(pBullet, AIR_ZORDER);
			}

			//m_fTime += fEscapeTime;
			//if (m_fTime > BOSS05_STAGE01_FIRESLOT)
			//{
			//	m_fTime = 0.0f;
			//	BULLET_DATA mData;
			//	mData.mAttack = 5;
			//	mData.mMoveSpeed = 150.0f;
			//	mData.mDirection = ccpRotateByAngle(ccp(0, -1), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pLeftGun->getRotation()));
			//	CCPoint mLeftPos = ccpRotateByAngle(ccp(0, -32), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pLeftGun->getRotation()));
			//	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
			//	pBullet->setPosition(ccp(getPositionX() + m_pBaseSprite->getContentSize().width * 0.257f + mLeftPos.x, getPositionY() + mLeftPos.y - m_pBaseSprite->getContentSize().height * 0.208f));
			//	getParent()->addChild(pBullet, BBULLET_ZORDER);

			//	mData.mDirection = ccpRotateByAngle(ccp(0, -1), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pRightGun->getRotation()));
			//	CCPoint mRightPos = ccpRotateByAngle(ccp(0, -32), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pRightGun->getRotation()));
			//	pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
			//	pBullet->setPosition(ccp(getPositionX() - m_pBaseSprite->getContentSize().width * 0.257f + mRightPos.x, getPositionY() + mRightPos.y - m_pBaseSprite->getContentSize().height * 0.208f));
			//	getParent()->addChild(pBullet, BBULLET_ZORDER);
			//}

			//m_fLaserTime += fEscapeTime;
			//if (m_fLaserTime > BOSS05_STAGE01_LASERSLOT)
			//{
			//	m_fLaserTime = 0.0f;
			//	BULLET_DATA mData;
			//	mData.mKind = BK_TARCKROCKET;
			//	mData.mAttack = 5;
			//	mData.mMoveSpeed = 150.0f;
			//	mData.mDirection = ccp(0.0f, -1.0f);
			//	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
			//	pBullet->setPosition(ccp(getPositionX() - m_pBaseSprite->getContentSize().width * 0.4f, getPositionY() - m_pBaseSprite->getContentSize().height * 0.344f));
			//	getParent()->addChild(pBullet, PBULLET_ZORDER);

			//	pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
			//	pBullet->setPosition(ccp(getPositionX() + m_pBaseSprite->getContentSize().width * 0.4f, getPositionY() - m_pBaseSprite->getContentSize().height * 0.344f));
			//	getParent()->addChild(pBullet, PBULLET_ZORDER);
			//}
		}
		break;
	case STAGE_ACTION03:
		{
			m_fTime += fEscapeTime;
			if (m_fTime > BOSS05_STAGE02_MISSLE)
			{
				m_fTime = 0.0f;

				BULLET_DATA mData;
				mData.mKind = BK_TARCKROCKET;
				mData.mAttack = 26;
				mData.mMoveSpeed = 250.0f;
				mData.mDirection = ccp(1.0f, 0.0f);
				CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
				pBullet->setPosition(ccp(getPositionX() + getContentSize().width * 0.11f, getPositionY() + getContentSize().height * 0.165f));
				getParent()->addChild(pBullet, AIR_ZORDER);

				pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
				pBullet->setPosition(ccp(getPositionX() + getContentSize().width * 0.225f, getPositionY() + getContentSize().height * 0.165f));
				getParent()->addChild(pBullet, AIR_ZORDER);
			}
		}
		break;
	case STAGE_ACTION04:
		break;
	case STAGE_ACTION05:
		break;
	}

	if (!m_bBaseNormal && m_pCurAttack)
	{
		m_fFlashTime += fEscapeTime;
		if (m_fFlashTime > 0.1f)
		{
			m_fFlashTime = 0.0f;
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pCurAttack);
			pRGBAProtocol->setColor(m_sBaseColor);
			m_bBaseNormal = true;
		}
	}

	//���ͷɻ�
	m_fEnemyTime += fEscapeTime;
	if (m_fEnemyTime > LACKEY_TIME)
	{
		m_fEnemyTime = 0.0f;
		FLY_DATA mFdata;
		mFdata.mKind = (ENEMY_KINDS)((int)(CCRANDOM_0_1() * 4));
		mFdata.m_fTime = 4.0f;
		mFdata.mAttitude = FA_DEFAULT;
		mFdata.mAttitude = (FLYING_ATTITUDE)((int)(CCRANDOM_0_1() * FA_ENEMY_MAX));
		mFdata.mPosition = CGlobalData::getSingleton()->getPosByFlyAttitude(mFdata.mAttitude);
		CEnemySprite *pSprite = CEnemySprite::createEnemy(mFdata.mKind, mFdata);
		getParent()->addChild(pSprite, AIR_ZORDER);
		CGlobalData::getSingleton()->addAirScore(mFdata.mKind);
	}
}

void CBossFive::underAttack(int nHurt)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02 || m_eCurStage == STAGE_ACTION03)
	{
		if (m_bBaseNormal && m_pCurAttack)
		{
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pCurAttack);
			pRGBAProtocol->setColor(ccc3(255,0,0));
			m_bBaseNormal = false;

		}
	}

	switch(m_eCurStage)
	{
	case STAGE_ACTION01:
		{
			m_nBossHP -= nHurt;
			if (m_nBossHP <= 0)
			{
				m_eCurStage = STAGE_READY02;
				m_nBossHP = BOSS05_STAGE02_HP;
				if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
				{
					m_nBossHP = 8000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
				}
				//ֹͣ�ƶ�
				stopAction(m_pMoveAction);
				m_pMainGun->stopAllActions();
				m_pMainBody->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss05_Body01_02.png"));
				m_pTailFin->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss05_Body04_02.png"));

				runAction(CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.75f, mScreenSize.height * 0.65f - BANNER_HEIGHT * 0.5f)));
				runEffect();
				//
			}
		}
		break;
	case STAGE_ACTION02:
		{
			m_nBossHP -= nHurt;
			if (m_nBossHP <= 0)
			{
				m_eCurStage = STAGE_READY03;
				m_nBossHP = BOSS03_STAGE03_HP;
				if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
				{
					m_nBossHP = 9000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
				}
				m_pLeftWing->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss05_Body02_02.png"));
				stopAllActions();
				m_pMainGun->stopAllActions();
				runAction(CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.25f, mScreenSize.height * 0.65f - BANNER_HEIGHT * 0.5f)));
				runEffect();
			}
		}
		break;
	case STAGE_ACTION03:
		{
			m_nBossHP -= nHurt;
			if (m_nBossHP <= STAGEEND_HP)
			{
				m_pMainGun->stopAllActions();
				//m_eCurStage = STAGE_READY03;
				m_eCurStage = STAGE_EXPLODE;
				m_eCurState = BOS_EXPLODE;
				m_pRightWing->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss05_Body03_02.png"));
				//m_nBossHP = STAGE03_HP;
				stopAllActions();
				runEffect();
			}
		}
		break;
	}
}

void CBossFive::lockTarget(void)
{
	CCNode *m_pTarget = (CCNode*)(getParent()->getChildByTag(PALYER_TYPE));

	float o = m_pTarget->getPosition().x - (getPosition().x/* - getContentSize().width * 0.15f*/);
	float a = m_pTarget->getPosition().y - getPosition().y;
	float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );

	if( a < 0 ) 
	{
		if(  o < 0 )
			at = 180 + fabs(at);
		else
			at = 180 - fabs(at);    
	}

	m_pMainGun->runAction(CCRotateTo::create(0.5f,180.0f + at));

	o = m_pTarget->getPosition().x - (getPosition().x + getContentSize().width * 0.15f);
	a = m_pTarget->getPosition().y - getPosition().y;
	at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );

}

void CBossFive::lockFire(void)
{
	BULLET_DATA mData;
	mData.mAttack = 26;
	mData.mMoveSpeed = 150.0f;
	mData.mKind = BK_LASER;
	mData.mDirection = ccpRotateByAngle(ccp(0,-1.0f), ccp(0,0),  -CC_DEGREES_TO_RADIANS(m_pMainGun->getRotation()));
	CCPoint mLeftPos = ccpRotateByAngle(ccp(0, -56), ccp(0,0), -CC_DEGREES_TO_RADIANS(m_pMainGun->getRotation()));
	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, mData.mKind);
	pBullet->setPosition(ccp(getPositionX() + mLeftPos.x, getPositionY() + mLeftPos.y));
	pBullet->setRotation(m_pMainGun->getRotation());
	getParent()->addChild(pBullet, BBULLET_ZORDER);

}

void CBossFive::bossCallback(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY01:
		{
			//������ʼִ��
			//���ҷ�
			CCMoveTo *pMoveRight = CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.8f, mScreenSize.height * 0.8f - BANNER_HEIGHT * 0.5f));
			//�����
			CCMoveTo *pMoveLeft = CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.2f, mScreenSize.height * 0.8f - BANNER_HEIGHT * 0.5f));
			//����ص�
			//CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossThree::stage1Fire));
			//��ʱ
			//CCDelayTime *pDelayTime = CCDelayTime::create(0.1f);
			//m_pMoveAction = runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,pMoveRight,
			//	pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,
			//	pCallback,pDelayTime,pCallback,pDelayTime,pMoveLeft,NULL)));
			m_pMoveAction = runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(pMoveRight,pMoveLeft,NULL)));
			m_pCurAttack = m_pTailFin;
			m_eCurState = BOS_FIRE_RUN;
			m_eCurStage = STAGE_ACTION01;

			//�����ص�
			CCCallFunc *pLock = CCCallFunc::create(this, callfunc_selector(CBossFive::lockTarget));
			//�����ȴ�
			CCDelayTime *pLockTime = CCDelayTime::create(0.5f);
			//��������
			CCCallFunc *pLockFire = CCCallFunc::create(this, callfunc_selector(CBossFive::lockFire));
			m_pMainGun->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
				pLock,pLockTime,pLockFire,pLockTime,NULL)));
		}
		break;
	case STAGE_READY02:
		{
			//�����ص�
			CCCallFunc *pLock = CCCallFunc::create(this, callfunc_selector(CBossFive::lockTarget));
			//�����ȴ�
			CCDelayTime *pLockTime = CCDelayTime::create(0.5f);
			//��������
			CCCallFunc *pLockFire = CCCallFunc::create(this, callfunc_selector(CBossFive::lockFire));
			m_pMainGun->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
				pLock,pLockTime,pLockFire,pLockTime,NULL)));
			//��ʱ
			CCDelayTime *pDelayTime = CCDelayTime::create(0.1f);
			////����ص�
			//CCCallFunc *pDirection = CCCallFunc::create(this, callfunc_selector(CBossFive::stage2Direction));
			////����ص�
			//CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossFive::stage2Fire));
			//runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
			//	pDirection,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,NULL)));
			m_eCurStage = STAGE_ACTION02;
			m_pCurAttack = m_pLeftWing;
		}
		break;
	case STAGE_READY03:
		{
			//�����ص�
			CCCallFunc *pLock = CCCallFunc::create(this, callfunc_selector(CBossFive::lockTarget));
			//�����ȴ�
			CCDelayTime *pLockTime = CCDelayTime::create(0.5f);
			//��������
			CCCallFunc *pLockFire = CCCallFunc::create(this, callfunc_selector(CBossFive::lockFire));
			m_pMainGun->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
				pLock,pLockTime,pLockFire,pLockTime,NULL)));
			//��ʱ
			CCDelayTime *pDelayTime = CCDelayTime::create(0.1f);
			//����ص�
			//CCCallFunc *pDirection = CCCallFunc::create(this, callfunc_selector(CBossThree::stage2Direction));
			//����ص�
			//CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossFive::stage3Fire));
			//runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
			//	pCallback,pDelayTime,NULL)));
			m_eCurStage = STAGE_ACTION03;
			m_pCurAttack = m_pRightWing;
		}
		break;
	}
}

void CBossFive::runEffect(void)
{
	if (!m_bBaseNormal)
	{
		CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pCurAttack);
		pRGBAProtocol->setColor(m_sBaseColor);
	}

	CCAnimation *pAnimation = CCAnimation::create();
	char szName[128] = {0};
	for (int i=0; i<ANIMATE_MAX; i++)
	{
		sprintf(szName, "Explode03_%02d.png", i+1);
		if (m_pCurCache->spriteFrameByName(szName) == NULL)
		{
			break;
		}
		pAnimation->addSpriteFrame(m_pCurCache->spriteFrameByName(szName));
	}


	pAnimation->setDelayPerUnit(0.066f);
	pAnimation->setRestoreOriginalFrame(true);

	//CCPlace
	CCAnimate *pAnimate = CCAnimate::create(pAnimation);
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CBossFive::effectCallback));
	CCPoint mPos = getPosition();
	CCPoint mOffSet;
	mOffSet.x = m_pCurAttack->getPosition().x - m_pCurAttack->getContentSize().width * 0.5f;
	mOffSet.y = m_pCurAttack->getPosition().y - m_pCurAttack->getContentSize().height * 0.5f;
	CCActionInterval* pAction = (CCActionInterval*)(CCSequence::create(
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,CCMoveTo::create(0.1f,ccpAdd(mOffSet, ccp(CCRANDOM_0_1() * m_pCurAttack->getContentSize().width, CCRANDOM_0_1() * m_pCurAttack->getContentSize().height * 0.5f))),
		pAnimate,pCallback,NULL) );
	m_pExplode->runAction(pAction);

	if (m_eCurState == BOS_EXPLODE)
	{
		runAction(CCScaleTo::create(10.0f, 0.5f));
	}
}

void CBossFive::effectCallback(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY02:
		{
			m_pCurAttack = NULL;
			bossCallback();
		}
		break;
	case STAGE_READY03:
		{
			m_pCurAttack = NULL;
			bossCallback();
		}
		break;
	case STAGE_EXPLODE:
		{
			setVisible(false);
			//�ȴ�1��
			CCDelayTime *pDelayTime = CCDelayTime::create(1.0f);
			//ԭ�������� + ������������
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossFive::removeSelf));
			runAction(CCSequence::create(pDelayTime,pCallback,NULL));
		}
		break;
	}
}

void CBossFive::removeSelf(void)
{
	m_eCurState = BOS_HIDE;
	removeFromParentAndCleanup(true);
	if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
	{
		CGlobalData::getSingleton()->resetEndlessData();
	}
	else
	{
		CGlobalData::getSingleton()->setLevelClear(true);
	}
}