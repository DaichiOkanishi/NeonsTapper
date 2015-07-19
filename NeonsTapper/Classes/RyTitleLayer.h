//
//  RyTitleLayer.h
//  NeonsTapper
//
//  Created by okanishi on 2015/07/19.
//
//

#ifndef __NeonsTapper__RyTitleLayer__
#define __NeonsTapper__RyTitleLayer__

#include <stdio.h>
#include "cocos2d.h"

class RyTitleLayer : public cocos2d::Layer
{
// ----------------------------------------
// 生成
// ----------------------------------------
public:
    static RyTitleLayer* create();

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

#endif /* defined(__NeonsTapper__RyTitleLayer__) */
