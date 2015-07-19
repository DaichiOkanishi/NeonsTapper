//
//  RyTitleScene.cpp
//  NeonsTapper
//
//  Created by okanishi on 2015/07/19.
//
//

#include "RyTitleScene.h"
#include "RyTitleLayer.h"

USING_NS_CC;

Scene* RyTitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = RyTitleLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RyTitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( Node::init() == false )
    {
        return false;
    }
    
    return true;
}