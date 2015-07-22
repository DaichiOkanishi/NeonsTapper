//
//  Ry2dTapNode.cpp
//  NeonsTapper
//
//  Created by okanishi on 2015/07/19.
//
//

#include "Ry2dTapNode.h"
#include <random>

Ry2dTapNode::Ry2dTapNode()
: m_elapsedTime(0.0f)
, m_status(UNEXIST)
, m_imgFrame(nullptr)
, m_label(nullptr)
, m_listener(nullptr)
, m_gameLayer(nullptr)
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
    
    this->scheduleUpdate();
    
    return true;
}

void Ry2dTapNode::initsAll()
{
    initTexture("");
    initColor();
    initPosition();
    initFrame();
    initLabel();
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

void Ry2dTapNode::initColor()
{
    // メルセンヌ・ツイスターの分布生成器を使う
    // 参考：http://siv3d.hateblo.jp/entry/2013/02/17/231829
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> randList(0,5);
    
    int rand = randList(mt);
    
    Color3B color;
    switch (rand)
    {
        case 0:
        {
            color = Color3B::RED;
            break;
        }
        case 1:
        {
            color = Color3B::BLUE;
            break;
        }
        case 2:
        {
            color = Color3B::GREEN;
            break;
        }
        case 3:
        {
            color = Color3B::YELLOW;
            break;
        }
        case 4:
        {
            color = Color3B::ORANGE;
            break;
        }
        case 5:
        {
            color = Color3B::MAGENTA;
            break;
        }
        default:
            break;
    }
    this->setColor(color);
}

void Ry2dTapNode::initPosition()
{
    Size size = Director::getInstance()->getVisibleSize();
    Size thisSize = this->getContentSize();
    float scale = this->getScale();
    
    std::random_device rd;
    std::uniform_int_distribution<int> widthList((thisSize.width*scale)/2, size.width - (thisSize.width*scale)/2);
    std::uniform_int_distribution<int> heightList((thisSize.height*scale)/2 + 50, size.height - (thisSize.height*scale)/2);
    
    std::mt19937 mt1(rd());
    int randWidth = widthList(mt1);
    
    std::mt19937 mt2(rd());
    int randHeight = heightList(mt2);
    
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->setPosition(Vec2(randWidth, randHeight));
}

void Ry2dTapNode::initFrame()
{
    m_imgFrame = ImageView::create();
    m_imgFrame->loadTexture("circleFrame.png");
    m_imgFrame->setScale(0.0f);
    
    Size thisSize = this->getContentSize();
    float scale = this->getScale();
    m_imgFrame->setPosition(Vec2((thisSize.width*scale)/2, (thisSize.height*scale)/2));
    
    this->addChild(m_imgFrame);
}

void Ry2dTapNode::initLabel()
{
    m_label = Label::create();
    m_label->setSystemFontName("fonts/lovelolinelight.ttf");
    m_label->setSystemFontSize(60);
    m_label->setColor(Color3B::RED);
    
    Size thisSize = this->getContentSize();
    float scale = this->getScale();
    m_label->setPosition(Vec2((thisSize.width*scale)/2, (thisSize.height*scale)/2));
    
    this->addChild(m_label);
}

void Ry2dTapNode::onEnter()
{
    Button::onEnter();
    setScale(0.5f);
    setOpacity(0);
    m_status = SPAWN;
}

void Ry2dTapNode::onExit()
{
    this->unscheduleUpdate();
    
    Button::onExit();
}

void Ry2dTapNode::update(float delta)
{
    switch (m_status)
    {
        case SPAWN:
        {
            runAction(CCFadeIn::create(0.5f));
            
            m_imgFrame->setScale(2.0f);
            m_imgFrame->setOpacity(0);
            
            m_imgFrame->runAction(CCSpawn::create(CCFadeIn::create(0.5f), CCScaleTo::create(1.5f, 0.0f), NULL));
            
            setTouchEvent();
            
            m_gameLayer->addNodeCount();
            
            m_status = APPEAR;
            break;
        }
            
        case APPEAR:
        {
            m_elapsedTime += delta;
            if (m_elapsedTime >= 0.5f)
            {
                m_elapsedTime = 0.0f;
                m_status = LIVED;
            }
            break;
        }
            
        case LIVED:
        {
            float scale = m_imgFrame->getScale();
            
            if (scale <= 0.5f)
            {
                m_label->setString("MISS");
                // タッチ判定の削除
                if (auto dispatcher = Director::getInstance()->getEventDispatcher())
                {
                    dispatcher->removeEventListener(m_listener);
                    m_listener = nullptr;
                }
                m_gameLayer->addMissCount();
                m_status = MISSED;
            }
            break;
        }
            
        case TOUCHED:
        {
            m_elapsedTime = 0.0f;
            float scale = m_imgFrame->getScale();
            
            if (scale >= 1.2f)
            {
                m_label->setString("MISS");
                m_gameLayer->addMissCount();
                m_status = MISSED;
            }
            else if(scale >= 1.1f)
            {
                m_label->setString("300");
                m_gameLayer->addScore(300);
                m_imgFrame->setVisible(false);
                m_status = SUCCESS;
            }
            else if(scale >= 0.9f)
            {
                m_label->setString("500");
                m_gameLayer->addScore(500);
                m_imgFrame->setVisible(false);
                m_status = SUCCESS;
            }
            else if(scale >= 0.7f)
            {
                m_label->setString("300");
                m_gameLayer->addScore(300);
                m_imgFrame->setVisible(false);
                m_status = SUCCESS;
            }
            else if(scale >= 0.5f)
            {
                m_label->setString("100");
                m_gameLayer->addScore(100);
                m_imgFrame->setVisible(false);
                m_status = SUCCESS;
            }
            else
            {
                m_label->setString("MISS");
                m_gameLayer->addMissCount();
                m_status = MISSED;
            }
            break;
        }
            
        case MISSED:
        {
            m_elapsedTime += delta;
            float opacity = this->getOpacity();
            opacity -= m_elapsedTime;
            if (opacity <= 0)
            {
                opacity = 0;
            }
            setOpacity(opacity);
            
            if (opacity <= 0.0f)
            {
                m_status = DEAD;
            }
            break;
        }
            
        case SUCCESS:
        {
            this->runAction(CCSpawn::create(CCFadeOut::create(0.2f), CCScaleTo::create(0.2f, 1.1f), NULL));
            m_label->runAction(CCSpawn::create(CCFadeOut::create(0.5f), CCScaleTo::create(0.5f, 1.1f), NULL));
            m_status = END;
            break;
        }
            
        case END:
        {
            m_elapsedTime += delta;
            
            if (m_elapsedTime >= 0.5f)
            {
                m_status = DEAD;
            }
            break;
        }
            
        case DEAD:
        {
            break;
        }
        
        default:
            break;
    }
}

bool Ry2dTapNode::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    Vec2 p = pTouch->getLocation();
    Rect rect = this->getBoundingBox();
    
    if(rect.containsPoint(p))
    {
        m_status = TOUCHED;
        // タッチ判定の削除
        if (auto dispatcher = Director::getInstance()->getEventDispatcher())
        {
            dispatcher->removeEventListener(m_listener);
            m_listener = nullptr;
        }
        this->setTouchEnabled(false);
        
        return true; // to indicate that we have consumed it.
    }
    
    return false; // we did not consume this event, pass thru.
}

void Ry2dTapNode::onTouchMoved(Touch *pTouch, Event *pEvent)
{
}

void Ry2dTapNode::onTouchEnded(Touch *pTouch, Event *pEvent)
{
}

void Ry2dTapNode::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
}

void Ry2dTapNode::setTouchEvent()
{
    // タッチ判定
    if (auto listener = EventListenerTouchOneByOne::create())
    {
        listener->setSwallowTouches(true);
        listener->onTouchBegan		= CC_CALLBACK_2(Ry2dTapNode::onTouchBegan, this);
        listener->onTouchMoved		= CC_CALLBACK_2(Ry2dTapNode::onTouchMoved, this);
        listener->onTouchEnded		= CC_CALLBACK_2(Ry2dTapNode::onTouchEnded, this);
        listener->onTouchCancelled	= CC_CALLBACK_2(Ry2dTapNode::onTouchCancelled, this);
        
        auto dispatcher = this->getEventDispatcher();
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        m_listener = listener;
    }
}