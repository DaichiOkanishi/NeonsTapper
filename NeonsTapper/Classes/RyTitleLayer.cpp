//
//  RyTitleLayer.cpp
//  NeonsTapper
//
//  Created by okanishi on 2015/07/19.
//
//

#include "RyTitleLayer.h"
#include "RyGameScene.h"
#include "SimpleAudioEngine.h"

RyTitleLayer* RyTitleLayer::create()
{
    RyTitleLayer *ret = new (std::nothrow) RyTitleLayer();
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

bool RyTitleLayer::init()
{
    if ( Layer::init() == false )
    {
        return false;
    }
    
    // タッチ判定
    if (auto listener = EventListenerTouchOneByOne::create())
    {
        listener->setSwallowTouches(true);
        listener->onTouchBegan		= CC_CALLBACK_2(RyTitleLayer::onTouchBegan, this);
        listener->onTouchMoved		= CC_CALLBACK_2(RyTitleLayer::onTouchMoved, this);
        listener->onTouchEnded		= CC_CALLBACK_2(RyTitleLayer::onTouchEnded, this);
        listener->onTouchCancelled	= CC_CALLBACK_2(RyTitleLayer::onTouchCancelled, this);
        
        auto dispatcher = this->getEventDispatcher();
        dispatcher->addEventListenerWithFixedPriority(listener, 1);
    }
    
    return true;
}

void RyTitleLayer::onEnter()
{
    if (auto pTitleLabel = LabelTTF::create("Neons Tapper", "fonts/lovelolinelight.ttf", 60))
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        pTitleLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.9f));
        pTitleLabel->setColor(Color3B::GREEN);
        this->addChild(pTitleLabel);
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm/title.mp3");
    
    Layer::onEnter();
}

void RyTitleLayer::onExit()
{
    Layer::onExit();
}

bool RyTitleLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    return true;
}

void RyTitleLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
}

void RyTitleLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (Scene* pScene = RyGameScene::createScene())
    {
        TransitionFade* pTrans = TransitionFade::create(1.0f, pScene, Color3B::BLACK);
        Director::getInstance()->replaceScene(pTrans);
        
        if (auto dispatcher = Director::getInstance()->getEventDispatcher())
        {
            dispatcher->removeAllEventListeners();
        }
    }
}

void RyTitleLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
}