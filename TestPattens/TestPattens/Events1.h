//
//  Events1.h
//  TestPattens
//
//  Created by Kaven Feng on 8/25/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Events1__
#define __TestPattens__Events1__

#include <iostream>
#include <memory>
#include <functional>

namespace Events1 {
    
    class Button{
    public:
        std::function<void(int)> onClick;
    };
    
    class GameLayer{
    public:
        void start(void* sender, int pos)
        {
            std::cout << "GameLayer::start() " << pos << std::endl;
        }
        
        void end(void* sender, int pos)
        {
            std::cout << "GameLayer::end() " << pos << std::endl;
        }
    };
    
    class Client{
    public:
        void run()
        {
            // Init
            Button btn1, btn2;
            GameLayer layer;
            
            // connect.
            btn1.onClick = std::bind(&GameLayer::start, &layer, &btn1, std::placeholders::_1);
            btn2.onClick = std::bind(&GameLayer::end, &layer, &btn2, std::placeholders::_1);
            
            // invoke
            btn1.onClick(0);
            btn2.onClick(1);
        }
    };
    
}

#endif /* defined(__TestPattens__Events1__) */
