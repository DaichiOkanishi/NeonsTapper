//
//  RyGameScene.h
//  NeonsTapper
//
//  Created by okanishi on 2015/07/19.
//
//

#ifndef __NeonsTapper__RyGameScene__
#define __NeonsTapper__RyGameScene__

#include <stdio.h>
#include "cocos2d.h"

class RyGameScene : public cocos2d::Node
{
    // ----------------------------------------
    // 生成
    // ----------------------------------------
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(RyGameScene);
    
    // ----------------------------------------
    // 初期化
    // ----------------------------------------
public:
    virtual bool init();
};

#endif /* defined(__NeonsTapper__RyGameScene__) */
