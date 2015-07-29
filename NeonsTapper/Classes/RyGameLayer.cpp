//
//  RyGameLayer.cpp
//  NeonsTapper
//
//  Created by okanishi on 2015/07/20.
//
//

#include "RyGameLayer.h"
#include "RyResultScene.h"
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
, m_scoreLabel(nullptr)
, m_nodeCount(0)
, m_score(0)
, m_missCount(0)
, m_status(WAIT)
, m_pGameCountDownLayer(nullptr)
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
    
    m_scoreLabel = Label::create();
    m_scoreLabel->setSystemFontName("fonts/lovelolinelight.ttf");
    m_scoreLabel->setSystemFontSize(60);
    m_scoreLabel->setAnchorPoint(Vec2(1.0f, 0.0f));
    m_scoreLabel->setColor(Color3B(127, 255, 212));
    m_scoreLabel->setString("Score : 0");
    
    Size size = Director::getInstance()->getVisibleSize();
    m_scoreLabel->setPosition(Vec2(size.width - 20, size.height*0.9f));
    
    this->addChild(m_scoreLabel);
    
    // カウントダウンレイヤー生成。
    m_pGameCountDownLayer = RyGameCountDownLayer::create();
    this->addChild(m_pGameCountDownLayer);
    
    Layer::onEnter();
}

void RyGameLayer::onExit()
{
    Layer::onExit();
}

void RyGameLayer::update(float delta)
{
    switch (m_status)
    {
        case WAIT:
        {
            m_elapsedTime += delta;
            if (m_elapsedTime >= 1.0f)
            {
                m_status = COUNT_DOWN;
                m_elapsedTime = 0.0f;
            }
            break;
        }
            
        case COUNT_DOWN:
        {
            m_pGameCountDownLayer->play();
            m_status = COUNT_DOWN_WHILE;
            break;
        }
            
        case COUNT_DOWN_WHILE:
        {
            // カウントダウン演出が終わるまで待機。
            if (m_pGameCountDownLayer->isEnd() == true)
            {
                m_status = PLAYING;
            }
            break;
        }
            
        case PLAYING:
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
            
            std::string string = StringUtils::format("Score : %d", getScore());
            m_scoreLabel->setString(string);
            
            if (m_missCount > 10)
            {
                m_status = GAME_OVER;
            }
            
            break;
        }
        
        case GAME_OVER:
        {
            if (Scene* pScene = RyResultScene::createScene())
            {
                TransitionFade* pTrans = TransitionFade::create(1.0f, pScene, Color3B::BLACK);
                Director::getInstance()->replaceScene(pTrans);
                
                if (auto dispatcher = Director::getInstance()->getEventDispatcher())
                {
                    dispatcher->removeAllEventListeners();
                }
            }
            break;
        }
            
        default:
            break;
    }
}