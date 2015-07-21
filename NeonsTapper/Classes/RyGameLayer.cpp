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

RyGameLayer::RyGameLayer()
: m_elapsedTime(0.0f)
, m_respawnTime(1.2f)
, m_nodeCount(0)
{
    m_nodeList.clear();
}

RyGameLayer::~RyGameLayer()
{
    
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
    this->scheduleUpdate();
    
    Layer::onEnter();
}

void RyGameLayer::onExit()
{
    Layer::onExit();
}

void RyGameLayer::update(float delta)
{
    m_elapsedTime += delta;
    
    if (m_elapsedTime > m_respawnTime)
    {
        m_elapsedTime = 0.0f;
        
        if (auto pTapNode = Ry2dTapNode::create())
        {
            pTapNode->initsAll();
            pTapNode->setGameLayer(this);
            this->addChild(pTapNode);
            m_nodeList.pushBack(pTapNode);
        }
    }
    
    Vector<Ry2dTapNode *>::iterator it = m_nodeList.begin();
    while (it != m_nodeList.end())
    {
        if ((*it)->isAlive() == false)
        {
            this->removeChild(*it);
            it = m_nodeList.erase(it);
            continue;
        }
        ++it;
    }
}