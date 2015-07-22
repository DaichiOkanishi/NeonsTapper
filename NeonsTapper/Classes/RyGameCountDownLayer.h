//
//  RyGameCountDownLayer.h
//  NeonsTapper
//
//  Created by okanishi on 2015/07/22.
//
//

#ifndef __NeonsTapper__RyGameCountDownLayer__
#define __NeonsTapper__RyGameCountDownLayer__

#include <stdio.h>

USING_NS_CC;

class Ry2dTapNode;

class RyGameCountDownLayer : public cocos2d::Layer
{
    // ----------------------------------------
    // 生成
    // ----------------------------------------
public:
    static RyGameCountDownLayer* create();
    
private:
    /// コンストラクタ
    RyGameCountDownLayer();
    /// デストラクタ
    virtual ~RyGameCountDownLayer();
    
    // ----------------------------------------
    // ステート
    // ----------------------------------------
    enum STATUS
    {
        WAIT = 0,
        THREE,
        TWO,
        ONE,
        ZERO,
        END
    };
    
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
    float                   m_elapsedTime;    // 経過時間
    
private:
    Label*                  m_countDownLabel;
    
private:
    STATUS                  m_status;
    
    // ----------------------------------------
    // メソッド
    // ----------------------------------------
public:
    inline bool isEnd()
    {
        if (m_status == END)
        {
            return true;
        }
        return false;
    }
    
    inline void play()
    {
        this->scheduleUpdate();
        m_status = THREE;
    }
    
    void CountDownEffect(STATUS state);
};

#endif /* defined(__NeonsTapper__RyGameCountDownLayer__) */
