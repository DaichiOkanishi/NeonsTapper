//
//  RyResultScene.cpp
//  NeonsTapper
//
//  Created by okanishi on 2015/07/29.
//
//

#include "RyResultScene.h"
#include "RyResultLayer.h"

USING_NS_CC;

Scene* RyResultScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = RyResultScene::create();
    
    // 'layer' is an autorelease object
    auto layer = RyResultLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RyResultScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( Node::init() == false )
    {
        return false;
    }
    
    return true;
}