//
//  Ry2dTapNode.h
//  NeonsTapper
//
//  Created by okanishi on 2015/07/19.
//
//

#ifndef __NeonsTapper__Ry2dTapNode__
#define __NeonsTapper__Ry2dTapNode__

#include <stdio.h>
#include "ui/CocosGUI.h"

USING_NS_CC;

class Ry2dTapNode : public ui::Button
{
protected:
    /// コンストラクタ
    Ry2dTapNode();
    /// デストラクタ
    virtual ~Ry2dTapNode();
    
    // ----------------------------------------
    // 生成
    // ----------------------------------------
public:
    static Ry2dTapNode* create();
    
    // ----------------------------------------
    // 初期化
    // ----------------------------------------
private:
    virtual bool init() override;
    
public:
    void initTexture(const char* filePath);
    void initColor();
    void initPosition();
    
    // ----------------------------------------
    // 入退場
    // ----------------------------------------
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    
    // ----------------------------------------
    // 更新
    // ----------------------------------------
private:
    virtual void update(float delta);
    
    // ----------------------------------------
    // プロパティ
    // ----------------------------------------
private:
    float   m_elapsedTime;
    bool    m_bAlive;
    
    // ----------------------------------------
    // メソッド
    // ----------------------------------------
public:
    inline bool    isAlive()
    {
        return m_bAlive;
    }
};

#endif /* defined(__NeonsTapper__Ry2dTapNode__) */
