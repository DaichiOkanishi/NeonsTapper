//
//  RyGameLayer.h
//  NeonsTapper
//
//  Created by okanishi on 2015/07/20.
//
//

#ifndef __NeonsTapper__RyGameLayer__
#define __NeonsTapper__RyGameLayer__

#include <stdio.h>
#include "cocos2d.h"

class RyGameLayer : public cocos2d::Layer
{
    // ----------------------------------------
    // 生成
    // ----------------------------------------
public:
    static RyGameLayer* create();
    
    // ----------------------------------------
    // 初期化
    // ----------------------------------------
public:
    virtual bool init() override;
    
    // ----------------------------------------
    // 準備ができたら入る関数
    // ----------------------------------------
public:
    virtual void onEnter() override;
};

#endif /* defined(__NeonsTapper__RyGameLayer__) */
