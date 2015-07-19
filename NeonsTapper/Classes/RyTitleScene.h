//
//  RyTitleScene.h
//  NeonsTapper
//
//  Created by okanishi on 2015/07/19.
//
//

#ifndef __NeonsTapper__RyTitleScene__
#define __NeonsTapper__RyTitleScene__

#include <stdio.h>
#include "cocos2d.h"

class RyTitleScene : public cocos2d::Scene
{
// ----------------------------------------
// 生成
// ----------------------------------------
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(RyTitleScene);
    
// ----------------------------------------
// 初期化
// ----------------------------------------
public:
    virtual bool init();
};

#endif /* defined(__NeonsTapper__RyTitleScene__) */
