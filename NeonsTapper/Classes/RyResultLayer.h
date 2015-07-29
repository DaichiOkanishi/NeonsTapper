//
//  RyResultLayer.h
//  NeonsTapper
//
//  Created by okanishi on 2015/07/29.
//
//

#ifndef __NeonsTapper__RyResultLayer__
#define __NeonsTapper__RyResultLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class RyResultLayer : public Layer
{
    // ----------------------------------------
    // 生成
    // ----------------------------------------
public:
    static RyResultLayer* create();
    
    // ----------------------------------------
    // 初期化
    // ----------------------------------------
public:
    virtual bool init() override;
    
    // ----------------------------------------
    // 入退場
    // ----------------------------------------
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    
    // ----------------------------------------
    // タッチイベント
    // ----------------------------------------
public:
    bool onTouchBegan(Touch* pTouch, Event* pEvent);
    void onTouchMoved(Touch* pTouch, Event* pEvent);
    void onTouchEnded(Touch* pTouch, Event* pEvent);
    void onTouchCancelled(Touch* pTouch, Event* pEvent);
};

#endif /* defined(__NeonsTapper__RyResultLayer__) */
