//
//  RyTitleLayer.cpp
//  NeonsTapper
//
//  Created by okanishi on 2015/07/19.
//
//

#include "RyTitleLayer.h"

USING_NS_CC;

RyTitleLayer* RyTitleLayer::create()
{
    RyTitleLayer *ret = new (std::nothrow) RyTitleLayer();
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

bool RyTitleLayer::init()
{
    if ( Layer::init() == false )
    {
        return false;
    }
    
    return true;
}

void RyTitleLayer::onEnter()
{
    
    if (auto pTitleLabel = LabelTTF::create("NeonsTapper", "SIMPLIFICA Typeface.ttf", 40))
    {
        this->addChild(pTitleLabel);
    }
}