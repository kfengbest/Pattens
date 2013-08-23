//
//  SmarterPoint.h
//  TestPattens
//
//  Created by Kaven Feng on 8/23/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__SmarterPoint__
#define __TestPattens__SmarterPoint__

#include <iostream>
#include <memory>

namespace SmartPointer1 {
    
    class Background;
    
    class GameLayer
    {
    public:
        GameLayer();
        virtual ~GameLayer();
        
        void print();
        
    public:
        std::shared_ptr<Background> mBackgroud;
    };
    
    class Background
    {
    public:
        Background();
        virtual ~Background();
        
        void print();
        
    public:
        std::shared_ptr<GameLayer> mStrong2Parent;
        std::weak_ptr<GameLayer> mWeak2Parent;

        
    };
    
    class Client
    {
    public:
        void start();
    };
}

#endif /* defined(__TestPattens__SmarterPoint__) */
