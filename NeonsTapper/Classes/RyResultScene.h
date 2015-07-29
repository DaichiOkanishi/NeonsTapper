//
//  RyResultScene.h
//  NeonsTapper
//
//  Created by okanishi on 2015/07/29.
//
//

#ifndef __NeonsTapper__RyResultScene__
#define __NeonsTapper__RyResultScene__

#include <stdio.h>
#include "cocos2d.h"

class RyResultScene : public cocos2d::Scene
{
    // ----------------------------------------
    // 生成
    // ----------------------------------------
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(RyResultScene);
    
    // ----------------------------------------
    // 初期化
    // ----------------------------------------
public:
    virtual bool init();
};

#endif /* defined(__NeonsTapper__RyResultScene__) */
