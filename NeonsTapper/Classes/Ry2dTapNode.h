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
public:
    virtual bool init() override;
    void initTexture(const char* filePath);
};

#endif /* defined(__NeonsTapper__Ry2dTapNode__) */
