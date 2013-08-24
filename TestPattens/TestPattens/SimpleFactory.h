//
//  SimpleFactory.h
//  TestPattens
//
//  Created by Kaven Feng on 8/24/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__SimpleFactory__
#define __TestPattens__SimpleFactory__

#include <iostream>

namespace SimpleFactory1{
    
    class Item{
    };
    
    class Tower : public Item{
    public:
        Tower(){ std::cout << "Tower() in SimpleFactory1 \n"; }
    };
    
    class Obstacle : public Item{
    public:
        Obstacle(){ std::cout << "Obstacle() in SimpleFactory1\n"; }
    };
    
    class Monster : public Item{
    public:
        Monster(){ std::cout << "Monster() in SimpleFactory1\n"; }
    };
    
    class GameObjectFactory{
    public:
        Tower* createTower()        {return new Tower;}
        Obstacle* createObstacle()  {return new Obstacle;}
        Monster* createMonster()    {return new Monster;}
    };
    
    class Client{
    public:
        void start()
        {
            GameObjectFactory* fac = new GameObjectFactory();
            Monster* pm1 = fac->createMonster();
            Obstacle* po1 = fac->createObstacle();
            Tower* pt1 = fac->createTower();
            
            delete pm1; pm1 = nullptr;
            delete po1; po1 = nullptr;
            delete pt1; pt1 = nullptr;
        }
    };
}


namespace SimpleFactory2{
    
    enum ItemType{
        kUnknown = 0,
        kTower,
        kMonster,
        kObstacle
    };
    
    class Item{
    public:
        Item(ItemType t) : mType(t){}
        virtual ~Item(){}
        
        virtual void draw() { std::cout << "Item::draw()\n"; }
        
    private:
        ItemType mType;
    };
    
    class Tower : public Item{
    public:
        Tower(): Item(kTower) { std::cout << "Tower() in SimpleFactory2 \n"; }
        virtual ~Tower(){}
        
        virtual void draw() override { std::cout << "Tower::draw()\n"; }
        void fire() {std::cout << "Tower::fire() \n";}
    };
    
    class Obstacle : public Item{
    public:
        Obstacle() : Item(kObstacle){ std::cout << "Obstacle() in SimpleFactory2\n"; }
        virtual ~Obstacle(){}
        
        virtual void draw() override { std::cout << "Obstacle::draw()\n"; }
    };
    
    class Monster : public Item{
    public:
        Monster(): Item(kMonster){ std::cout << "Monster() in SimpleFactory2\n"; }
        virtual ~Monster(){}
        void attack() {std::cout << "Monster::attack() \n";}
    };
    
    // Simple factory
    class GameObjectFactory{
    public:
        static Item* createItem(int kItemType){
            Item* pItem = nullptr;
            switch (kItemType) {
                case kTower:
                    pItem = new Tower();
                    break;
                case kMonster:
                    pItem = new Monster();
                    break;
                case kObstacle:
                    pItem = new Obstacle();
                    break;
                default:
                    pItem = new Item(kUnknown);
                    break;
            }
            return pItem;
        }
    };
    
    class Client{
    public:
        void start()
        {

            Item* pm1 = GameObjectFactory::createItem(kMonster);
            Item* po1 = GameObjectFactory::createItem(kObstacle);
            Item* pt1 = GameObjectFactory::createItem(kTower);
            
            pt1->draw();
            // pt1->fire();  //Cannot access.
            Tower* pTower = dynamic_cast<Tower*>(pt1);
            pTower->fire(); // ok.
            
            po1->draw();
            
            pm1->draw();
            dynamic_cast<Monster*>(pm1)->attack();
            
            delete pm1; pm1 = nullptr;
            delete po1; po1 = nullptr;
            delete pt1; pt1 = nullptr;
        }
    };
}


#endif /* defined(__TestPattens__SimpleFactory__) */
