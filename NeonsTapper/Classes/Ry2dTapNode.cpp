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

    setScale(0.5f);
    initColor();
    initPosition();
    
    this->scheduleUpdate();
    
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
            color = Color3B::WHITE;
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
    
    std::random_device rd;
    std::uniform_int_distribution<int> widthList(thisSize.width/2, size.width - thisSize.width/2);
    std::uniform_int_distribution<int> heightList(thisSize.height/2,size.height - thisSize.height/2);
    
    std::mt19937 mt1(rd());
    int randWidth = widthList(mt1);
    
    std::mt19937 mt2(rd());
    int randHeight = heightList(mt2);
    
    this->setPosition(Vec2(randWidth, randHeight));
}

void Ry2dTapNode::onEnter()
{
    Button::onEnter();
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
            m_status = LIVED;
            break;
        }
            
        case TOUCHED:
        {
            m_status = LIVED;
            break;
        }
            
        case LIVED:
        {
            m_elapsedTime += delta;
            if (m_elapsedTime >= 1.0f)
            {
                m_elapsedTime = 0.0f;
                m_status = MISSED;
            }
            break;
        }
            
        case MISSED:
        {
            float opacity = this->getOpacity();
            opacity -= delta;
            setOpacity(opacity);
            
            if (opacity <= 0.0f)
            {
                m_status = DEAD;
            }
            break;
        }
            
        case DEAD:
        {
            // 処理なし。
            break;
        }
        
        default:
            break;
    }
}