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
#include "Ry2dTapNode.h"

class RyGameLayer : public cocos2d::Layer
{
    // ----------------------------------------
    // 生成
    // ----------------------------------------
public:
    static RyGameLayer* create();
    
private:
    /// コンストラクタ
    RyGameLayer();
    /// デストラクタ
    virtual ~RyGameLayer();
    
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
    // 更新
    // ----------------------------------------
public:
    void update(float delta) override;
    
    // ----------------------------------------
    // プロパティ
    // ----------------------------------------
private:
    float m_elapsedTime;    // 経過時間
    float m_respawnTime;    // 出現時間
    Vector<Ry2dTapNode *> m_nodeList;
};

#endif /* defined(__NeonsTapper__RyGameLayer__) */
