//
//  Ry2dTapNode.cpp
//  NeonsTapper
//
//  Created by okanishi on 2015/07/19.
//
//

#include "Ry2dTapNode.h"

Ry2dTapNode::Ry2dTapNode()
{
    
}

Ry2dTapNode::~Ry2dTapNode()
{
    
}

Ry2dTapNode* Ry2dTapNode::create()
{
    Ry2dTapNode* widget = new (std::nothrow) Ry2dTapNode();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;


}

bool Ry2dTapNode::init()
{
    if (Button::init() == false)
    {
        return false;
    }

    return true;
}

void Ry2dTapNode::initTexture(const char *filePath)
{
    // 名前指定が無ければデフォルトの画像を設定する。
    if (strcmp(filePath, "") == 0)
    {
        Button::loadTextureNormal("tapNode.png");
        return;
    }
    
    // 名前指定があれば、その画像を読み込む
    Button::loadTextureNormal(filePath);
}