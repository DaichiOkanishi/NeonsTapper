//
//  RyGameLayer.cpp
//  NeonsTapper
//
//  Created by okanishi on 2015/07/20.
//
//

#include "RyGameLayer.h"
#include "Ry2dTapNode.h"

USING_NS_CC;

RyGameLayer* RyGameLayer::create()
{
    RyGameLayer *ret = new (std::nothrow) RyGameLayer();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool RyGameLayer::init()
{
    if ( Layer::init() == false )
    {
        return false;
    }
    
    return true;
}

void RyGameLayer::onEnter()
{
    if (auto pTapNode = Ry2dTapNode::create())
    {
        pTapNode->initTexture("");
        
        this->addChild(pTapNode);
    }
}