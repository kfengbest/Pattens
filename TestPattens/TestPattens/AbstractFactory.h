//
//  AbstractFactory.h
//  TestPattens
//
//  Created by Kaven Feng on 8/24/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__AbstractFactory__
#define __TestPattens__AbstractFactory__

#include <iostream>

namespace AbstractFactory1{
    
    class Item{
        
    };
    
    class Tower : public Item{
        
    };
    
    class Obstacle : public Item{
        
    };
    
    class Monster : public Item{
        
    };
    
    class IGameObjectFactory{
    public:
        virtual Tower* createTower() = 0;
        virtual Obstacle* createObstacle() = 0;
        virtual Monster* createMonster() = 0;
    };
    
    class GameObjectFactory : public IGameObjectFactory{
    public:
        virtual Tower* createTower() override {return new Tower;}
        virtual Obstacle* createObstacle() override { return new Obstacle;}
        virtual Monster* createMonster() override {return new Monster;}
    };
    
    class Client{
        void run()
        {
            IGameObjectFactory* fac = new GameObjectFactory();
            Monster* pm1 = fac->createMonster();
        }
    };
}

#endif /* defined(__TestPattens__AbstractFactory__) */
