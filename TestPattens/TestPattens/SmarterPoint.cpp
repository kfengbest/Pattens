//
//  SmarterPoint.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/23/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include "SmarterPoint.h"

using namespace SmartPointer1;

GameLayer::GameLayer()
{
    std::cout << "GameLayer()" << std::endl;
}

GameLayer::~GameLayer()
{
    std::cout << "~GameLayer()" << std::endl;
}

void GameLayer::print()
{
    std::cout << "void GameLayer::print() \n";    
}

Background::Background()
{
    std::cout << "Background()" << std::endl;
}

Background::~Background()
{
    std::cout << "~Background()" << std::endl;
}

void Background::print()
{
    std::cout << "void Background::print() \n";
}

void Client::start()
{
    // OK
    {
        std::shared_ptr<GameLayer> pLayer(new GameLayer);
        pLayer->print();
        
        std::shared_ptr<Background> pBg(new Background);
        pBg->print();
    }
    
    // OK
    {
        std::shared_ptr<GameLayer> pLayer(new GameLayer);
        pLayer->print();
        
        std::shared_ptr<Background> pBg(new Background);
        pBg->print();
        
        pLayer->mBackgroud = pBg;
    }
    
    // shared + weak, ok!
    {
        std::shared_ptr<GameLayer> pLayer(new GameLayer);
        pLayer->print();
        
        std::shared_ptr<Background> pBg(new Background);
        pBg->print();
        
        pLayer->mBackgroud = pBg;
        pBg->mWeak2Parent = pLayer;
    }
    
    
    // shared + shared, recursively referenced, memory leak!
    {
        std::shared_ptr<GameLayer> pLayer(new GameLayer);
        pLayer->print();
        
        std::shared_ptr<Background> pBg(new Background);
        pBg->print();
        
        pLayer->mBackgroud = pBg;
        pBg->mStrong2Parent = pLayer;
    }
    
}