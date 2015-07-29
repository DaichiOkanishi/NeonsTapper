//
//  RyResultLayer.cpp
//  NeonsTapper
//
//  Created by okanishi on 2015/07/29.
//
//

#include "RyResultLayer.h"
#include "RyTitleScene.h"
#include "SimpleAudioEngine.h"

RyResultLayer* RyResultLayer::create()
{
    RyResultLayer *ret = new (std::nothrow) RyResultLayer();
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

bool RyResultLayer::init()
{
    if ( Layer::init() == false )
    {
        return false;
    }
    
    // タッチ判定
    if (auto listener = EventListenerTouchOneByOne::create())
    {
        listener->setSwallowTouches(true);
        listener->onTouchBegan		= CC_CALLBACK_2(RyResultLayer::onTouchBegan, this);
        listener->onTouchMoved		= CC_CALLBACK_2(RyResultLayer::onTouchMoved, this);
        listener->onTouchEnded		= CC_CALLBACK_2(RyResultLayer::onTouchEnded, this);
        listener->onTouchCancelled	= CC_CALLBACK_2(RyResultLayer::onTouchCancelled, this);
        
        auto dispatcher = this->getEventDispatcher();
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
    
    return true;
}

void RyResultLayer::onEnter()
{
    if (auto pTitleLabel = LabelTTF::create("Neons Tapper", "fonts/lovelolinelight.ttf", 60))
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        pTitleLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.9f));
        pTitleLabel->setColor(Color3B::GREEN);
        this->addChild(pTitleLabel);
    }
    Layer::onEnter();
}

void RyResultLayer::onExit()
{
    Layer::onExit();
}

bool RyResultLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    return true;
}

void RyResultLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
}

void RyResultLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (Scene* pScene = RyTitleScene::createScene())
    {
        TransitionFade* pTrans = TransitionFade::create(1.0f, pScene, Color3B::BLACK);
        Director::getInstance()->replaceScene(pTrans);
        
        if (auto dispatcher = Director::getInstance()->getEventDispatcher())
        {
            dispatcher->removeAllEventListeners();
        }
    }
}

void RyResultLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
}