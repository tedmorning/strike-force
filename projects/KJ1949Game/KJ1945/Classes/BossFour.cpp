#include "BossFour.h"

CBossFour::CBossFour(void)
{
	m_pCurAudio->stopBackgroundMusic(true);
}

CBossFour::~CBossFour(void)
{
}


CBossFour* CBossFour::createBoss(void)
{
	CBossFour *pBoss = new CBossFour();
	pBoss->createSprite();
	pBoss->setTag(BOSS_TYPE);
	//pBoss->m_eBossKind = eKind;
	return pBoss;
}

void CBossFour::createSprite(void)
{
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_pCurCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	m_eCurState = BOS_READY_RUN;
	m_pCurAudio->playEffect(("sounds/Warning.ogg"));
	this->schedule(schedule_selector(CBossFour::bossUpdate));
}

bool CBossFour::isCheck(void)
{
	if (m_eCurStage == STAGE_ACTION01 || m_eCurStage == STAGE_ACTION02)
	{
		return true;
	}
	return false;
}

CCRect CBossFour::getCurBoundbox(void)
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

void CBossFour::onEnter(void)
{
	setAnchorPoint(ccp(0.5f,0.5f));
	setContentSize(CCSizeMake(404,290));
	m_pBaseSprite = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss04_Base.png"));
	m_pBaseSprite->setAnchorPoint(ccp(0.5f,0.5f));
	addChild(m_pBaseSprite, BOSS_ZORDER);
	m_pBaseSprite->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	m_pBaseSprite->setVisible(false);

	m_pMainBody = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss04_Body01_01.png"));
	m_pMainBody->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.703f));
	addChild(m_pMainBody);


	m_pSecondBody = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss04_Body02_01.png"));
	m_pSecondBody->setPosition(ccp(getContentSize().width * 0.5f, getContentSize().height * 0.203f));
	addChild(m_pSecondBody);

	m_pLeftGun = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss04_Body03_01.png"));
	m_pLeftGun->setPosition(ccp(getContentSize().width * 0.094f,getContentSize().height * 0.6f));
	addChild(m_pLeftGun);

	m_pRightGun = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss04_Body03_01.png"));
	m_pRightGun->setPosition(ccp(getContentSize().width * 0.906f,getContentSize().height * 0.6f));
	addChild(m_pRightGun);

	m_pTailGun = CCSprite::createWithSpriteFrame(m_pCurCache->spriteFrameByName("Boss04_Body03_01.png"));
	m_pTailGun->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.062f));
	addChild(m_pTailGun);

	m_pExplode = CCSprite::create();
	m_pExplode->setPosition(ccp(getContentSize().width * 0.5f,getContentSize().height * 0.5f));
	addChild(m_pExplode, BOSS_ZORDER);

	m_pCurAttack = NULL;
	//m_pRightFlashSprite = NULL;
	//m_pLeftExplode = NULL;
	//m_pRightExplode = NULL;

	m_nBossHP = BOSS04_STAGE01_HP;

	if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
	{
		m_nBossHP = 10000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
	}

	m_fEnemyTime = 0.0f;


	//ִ�г�������
	setPosition(ccp(mScreenSize.width, - getContentSize().height));
	setScale(1.5f);
	//��ʱ
	CCDelayTime *pDelayTime = CCDelayTime::create(3.0f);
	//�ɳ�
	CCMoveTo *pMoveDown = CCMoveTo::create(3.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 1.2f - BANNER_HEIGHT));
	//��С
	CCScaleTo *pScaleTo = CCScaleTo::create(2.0f, 1.0f);
	//����
	CCMoveTo *pMoveBack =CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.8f - BANNER_HEIGHT));
	//�ϳɣ��Ŵ�+���ˣ�
	CCAction *pSpawn = CCSpawn::create(pScaleTo, pMoveBack,NULL);
	//չ�������ص�
	//CCCallFunc *pFlareWeapon = CCCallFunc::create(this, callfunc_selector(CBossThree::flareWeapon));
	//�ɵ�ָ��λ��
	CCMoveTo *pMoveLeft = CCMoveTo::create(0.5f,ccp(mScreenSize.width * 0.3f, mScreenSize.height * 0.8f - BANNER_HEIGHT));
	//�ص�
	CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossFour::bossCallback));

	//����
	//CCSequence *pSequence = CCSequence::create(pDelayTime,pMoveDown,pScaleTo,pMoveLeft,pCallback,NULL);
	runAction(CCSequence::create(pDelayTime,pMoveDown,pSpawn,/*pDelayTime,*/pMoveLeft,pCallback,NULL));


	//base color
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pBaseSprite);
	m_sBaseColor = pRGBAProtocol->getColor();
	m_fFlashTime = 0.0f;
	m_bBaseNormal = true;
	m_fTime = BOSS03_STAGE01_FIRETIME;
	m_fShotGunTime = 0.0f;
	m_eCurStage = STAGE_READY01;

	m_pCurAudio->playBackgroundMusic(("sounds/Boss01.ogg"));
	CCNode::onEnter();
}

void CBossFour::onExit()
{
	removeAllChildrenWithCleanup(true);
	CCNode::onExit();
}


void CBossFour::bossUpdate(float fEscapeTime)
{
	switch(m_eCurStage)
	{
	case STAGE_DEFAULT:
		break;
	case STAGE_ACTION01:
		{
			m_fTime += fEscapeTime;
			if (m_fTime > BOSS04_STAGE01_FIRETIME)
			{
				m_fTime = 0.0f;
				BULLET_DATA mData;
				mData.mAttack = 14;
				mData.mMoveSpeed = 150.0f;
				for (int i=0;i<BOSS04_STAGE01_FIRENUM;i++)
				{
					mData.mDirection = ccpNormalize(ccp(-1.0f + 2.0f / (BOSS04_STAGE01_FIRENUM - 1) * i, -1.0f));
					CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
					pBullet->setPosition(ccp(getPositionX() - m_pTailGun->getContentSize().width * 0.3f, getPositionY() - getContentSize().height * 0.5f));
					getParent()->addChild(pBullet, ABULLET_ZORDER);
					pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
					pBullet->setPosition(ccp(getPositionX() + m_pTailGun->getContentSize().width * 0.3f, getPositionY() - getContentSize().height * 0.5f));
					getParent()->addChild(pBullet, ABULLET_ZORDER);
				}
			}

			m_fShotGunTime += fEscapeTime;
			if (m_fShotGunTime > BOSSO4_SHOTFIRE_TIME)
			{
				m_fShotGunTime = 0.0f;
				BULLET_DATA mData;
				mData.mAttack = 14;
				mData.mMoveSpeed = 300.0f;
				for (int i=0;i<BOSSO4_SHOTFIRE_NUMBER;i++)
				{
					mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(360.0f / BOSSO4_SHOTFIRE_NUMBER * i));
					CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
					pBullet->setPosition(ccp(getPositionX(), getPositionY() - getContentSize().height * 0.034f));
					getParent()->addChild(pBullet, BBULLET_ZORDER);
				}
			}

		}
		break;
	case STAGE_ACTION02:
		{
			m_fTime += fEscapeTime;
			if (m_fTime > BOSS03_STAGE02_MISSLE)
			{
				m_fTime = 0.0f;

				BULLET_DATA mData;
				mData.mKind = BK_TARCKROCKET;
				mData.mAttack = 24;
				mData.mMoveSpeed = 250.0f;
				mData.mDirection = ccp(-1.0f, 0.0f);
				CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
				pBullet->setPosition(ccp(getPositionX(), getPositionY()));
				getParent()->addChild(pBullet, AIR_ZORDER);
			}

			m_fShotGunTime += fEscapeTime;
			if (m_fShotGunTime > BOSSO4_SHOTFIRE_TIME)
			{
				m_fShotGunTime = 0.0f;
				BULLET_DATA mData;
				mData.mAttack = 14;
				mData.mMoveSpeed = 300.0f;
				for (int i=0;i<BOSSO4_SHOTFIRE_NUMBER;i++)
				{
					mData.mDirection = ccpRotateByAngle(ccp(0, 1), ccp(0,0), -CC_DEGREES_TO_RADIANS(360.0f / BOSSO4_SHOTFIRE_NUMBER * i));
					CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_ARMY01);
					pBullet->setPosition(ccp(getPositionX(), getPositionY() - getContentSize().height * 0.034f));
					getParent()->addChild(pBullet, BBULLET_ZORDER);
				}
			}
		}
		break;
	case STAGE_ACTION03:
		{
			m_fTime += fEscapeTime;
			if (m_fTime > BOSS03_STAGE02_MISSLE)
			{
				m_fTime = 0.0f;

				BULLET_DATA mData;
				mData.mKind = BK_TARCKROCKET;
				mData.mAttack = 24;
				mData.mMoveSpeed = 250.0f;
				mData.mDirection = ccp(1.0f, 0.0f);
				CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, mData, BK_TARCKROCKET);
				pBullet->setPosition(ccp(getPositionX(), getPositionY()));
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

void CBossFour::underAttack(int nHurt)
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
				m_nBossHP = BOSS04_STAGE02_HP;

				if (CGlobalData::getSingleton()->getCurLevelData().mLevel == 8)
				{
					m_nBossHP = 15000 * (1.0f + 0.4f * CGlobalData::getSingleton()->getEndlessNum());
				}

				m_pSecondBody->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss04_Body02_02.png"));
				m_pTailGun->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss04_Body03_02.png"));
				//ֹͣ�ƶ�
				stopAction(m_pMoveAction);

				runAction(CCMoveTo::create(2.0f,ccp(mScreenSize.width * 0.5f, mScreenSize.height * 0.65f - BANNER_HEIGHT)));
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
				m_pMainBody->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss04_Body01_02.png"));
				m_pLeftGun->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss04_Body03_02.png"));
				m_pRightGun->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss04_Body03_02.png"));
				m_eCurStage = STAGE_EXPLODE;
				m_eCurState = BOS_EXPLODE;
				m_nBossHP = STAGEEND_HP;
				stopAllActions();
				runEffect();
			}
		}
		break;
	case STAGE_ACTION03:
		{
			m_nBossHP -= nHurt;
			if (m_nBossHP <= STAGEEND_HP)
			{
				//m_eCurStage = STAGE_READY03;
				m_eCurStage = STAGE_EXPLODE;
				m_eCurState = BOS_EXPLODE;
				//m_pRightWing->setDisplayFrame(m_pCurCache->spriteFrameByName("Boss03_Body03_02.png"));
				//m_nBossHP = STAGE03_HP;
				stopAllActions();
				runEffect();
			}
		}
		break;
	}


}


void CBossFour::bossCallback(void)
{
	switch(m_eCurStage)
	{
	case STAGE_READY01:
		{
			//������ʼִ��
			//���ҷ�
			CCMoveTo *pMoveRight = CCMoveTo::create(3.0f,ccp(mScreenSize.width * 0.7f, mScreenSize.height * 0.8f - BANNER_HEIGHT));
			//�����
			CCMoveTo *pMoveLeft = CCMoveTo::create(3.0f,ccp(mScreenSize.width * 0.3f, mScreenSize.height * 0.8f - BANNER_HEIGHT));

			m_pMoveAction = runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(pMoveRight,pMoveLeft,NULL)));
			m_pCurAttack = m_pSecondBody;
			m_eCurState = BOS_FIRE_RUN;
			m_eCurStage = STAGE_ACTION01;
		}
		break;
	case STAGE_READY02:
		{
			m_nRounds = 0;
			//��ʱ
			CCDelayTime *pDelayTime = CCDelayTime::create(0.2f);
			//����ص�
			CCCallFunc *pDirection = CCCallFunc::create(this, callfunc_selector(CBossFour::stage2Direction));
			//����ص�
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossFour::stage2Fire));
			runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
				pDirection,pCallback,pDelayTime,pCallback,pDelayTime,pCallback,NULL)));
			m_eCurStage = STAGE_ACTION02;
			m_pCurAttack = m_pMainBody;
		}
		break;
	case STAGE_READY03:
		{
			//m_nRounds = 0;
			//��ʱ
			CCDelayTime *pDelayTime = CCDelayTime::create(0.1f);
			//����ص�
			//CCCallFunc *pDirection = CCCallFunc::create(this, callfunc_selector(CBossThree::stage2Direction));
			//����ص�
			//CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossFour::stage3Fire));
			//runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(
			//	pCallback,pDelayTime,NULL)));
			//m_eCurStage = STAGE_ACTION03;
			//m_pCurAttack = m_pRightWing;
		}
		break;
	}
}


void CBossFour::stage2Direction(void)
{
	CCPoint mDirection = ccpNormalize(ccp(-1.0f,-1.0f));
	m_sStage2Data.mAttack = 14;
	m_sStage2Data.mMoveSpeed = 150.0f + CCRANDOM_0_1() * 100.0f;
	m_sStage2Data.mKind = BK_ARMY01;
	m_sStage2Data.mDirection = ccpRotateByAngle(mDirection, ccp(0,0), CC_DEGREES_TO_RADIANS(BOSS03_STAGE02_SECTOR * m_nRounds / (BOSS03_STAGE02_ROUNDS - 1)));
	m_nRounds ++;
	if (m_nRounds >= BOSS03_STAGE02_ROUNDS)
	{
		m_nRounds = 0;
	}
}

void CBossFour::stage2Fire(void)
{
	CBullet *pBullet = CBullet::createBullet(ENEMY_BULLET, m_sStage2Data, m_sStage2Data.mKind);
	pBullet->setPosition(ccp(getPositionX() - getContentSize().width * 0.5f + m_pLeftGun->getPositionX(), getPositionY() + m_pLeftGun->getPositionY() - m_pLeftGun->getContentSize().height * 0.5f - getContentSize().height * 0.5f));
	getParent()->addChild(pBullet, BBULLET_ZORDER);
}


void CBossFour::runEffect(void)
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
	CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(CBossFour::effectCallback));
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

void CBossFour::effectCallback(void)
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
			CCCallFunc *pCallback = CCCallFunc::create(this, callfunc_selector(CBossFour::removeSelf));
			runAction(CCSequence::create(pDelayTime,pCallback,NULL));
		}
		break;
	}
}

void CBossFour::removeSelf(void)
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