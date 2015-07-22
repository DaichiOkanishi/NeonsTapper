//
//  RyGameCountDownLayer.cpp
//  NeonsTapper
//
//  Created by okanishi on 2015/07/22.
//
//

#include "RyGameCountDownLayer.h"

USING_NS_CC;

RyGameCountDownLayer* RyGameCountDownLayer::create()
{
    RyGameCountDownLayer *ret = new (std::nothrow) RyGameCountDownLayer();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

RyGameCountDownLayer::RyGameCountDownLayer()
: m_elapsedTime(0.0f)
, m_countDownLabel(nullptr)
, m_status(WAIT)
{
}

RyGameCountDownLayer::~RyGameCountDownLayer()
{
    
}

bool RyGameCountDownLayer::init()
{
    if ( Layer::init() == false )
    {
        return false;
    }
    
    return true;
}

void RyGameCountDownLayer::onEnter()
{
    m_countDownLabel = Label::create();
    m_countDownLabel->setSystemFontName("fonts/lovelolinelight.ttf");
    m_countDownLabel->setSystemFontSize(100);
    m_countDownLabel->setColor(Color3B::WHITE);
    m_countDownLabel->setString("");
    
    Size size = Director::getInstance()->getVisibleSize();
    m_countDownLabel->setPosition(Vec2(size.width/2, size.height/2));
    
    this->addChild(m_countDownLabel);
    
    Layer::onEnter();
}

void RyGameCountDownLayer::onExit()
{
    Layer::onExit();
}

void RyGameCountDownLayer::update(float delta)
{
    switch (m_status)
    {
        case WAIT:
        {
            break;
        }
            
        case THREE:
        {
            m_countDownLabel->setString("3");
            CountDownEffect(TWO);
            break;
        }
            
        case TWO:
        {
            m_countDownLabel->setString("2");
            CountDownEffect(ONE);
            break;
        }
            
        case ONE:
        {
            m_countDownLabel->setString("1");
            CountDownEffect(ZERO);
            break;
        }
            
        case ZERO:
        {
            m_countDownLabel->setString("GO");
            CountDownEffect(END);
            break;
        }
        default:
            break;
    }
}

void RyGameCountDownLayer::CountDownEffect(STATUS state)
{
    m_countDownLabel->setOpacity(255);
    m_countDownLabel->setScale(2.0f);
    
    auto callfunc0 = CallFunc::create( [&, state] () {
        m_status = state;
    });
    
    auto pSeq = CCSequence::create(
                                   CCSpawn::create(CCScaleTo::create(1.0f, 0.0f), CCFadeOut::create(1.0f), nullptr),
                                   callfunc0,
                                   nullptr
                                   );
    
    m_countDownLabel->stopAllActions();
    m_countDownLabel->runAction(pSeq);
    
    m_status = WAIT;
}