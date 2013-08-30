//
//  Decorator1.h
//  TestPattens
//
//  Created by Kaven Feng on 8/28/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Decorator1__
#define __TestPattens__Decorator1__

#include <iostream>

namespace Decorator1 {
    
    class Tower{
    public:
        Tower() : mDamage(10), mSpeed(100){}
        virtual ~Tower(){}
        virtual void fire(){
            std::cout << "Tower::fire() " << " damage: " << this->damage()
                                          << " speed: " << this->speed() << std::endl;
        }
        
        virtual int damage() const{return mDamage;}
        virtual int speed() const{return mSpeed;}

    protected:
        int mDamage;
        int mSpeed;
    };

    class Behavior : public Tower{
    public:
        Behavior(Tower* t) : Tower(), mTower(t){}
        virtual ~Behavior(){}

        virtual void fire() override { mTower->fire();}
        
    protected:
        Tower* mTower;
    };
    
    class Slow : public Behavior{
    public:
        Slow(Tower* t) : Behavior(t), mSlowDamage(2){}
        virtual ~Slow(){}
        
        virtual void fire() override {
            std::cout << "Slow::fire()" << " damage: " << this->damage()
            << " speed: " << this->speed() << std::endl;
            mTower->fire();
        }
        
        virtual int damage() const override {
            return mDamage - mSlowDamage;
        }
    
    private:
        int mSlowDamage;
    };
    
    class Freeze : public Behavior{
    public:
        Freeze(Tower* t) : Behavior(t){}
        virtual ~Freeze(){}
        
        virtual void fire() override {
            std::cout << "Freeze::fire()" << " damage: " << this->damage()
            << " speed: " << this->speed() << std::endl;
            
            mTower->fire();
        }
        
        virtual int speed() const{return mSpeed  - 10 ;}

    };
    
    class Small : public Behavior{
    public:
        Small(Tower* t) : Behavior(t){}
        virtual ~Small(){}
        
        virtual void fire() override {
            std::cout << "Small::fire() \n";
            mTower->fire();
        }
    };
    
    class Client{
    public:
        void run(){
            Tower* t1 = new Tower;
            
            Slow* s = new Slow(t1);
            s->fire();
            
            Freeze* f = new Freeze(s);
            f->fire();
            
            Small* sm = new Small(f);
            sm->fire();
            
        }
    };
    
    
}


#endif /* defined(__TestPattens__Decorator1__) */
