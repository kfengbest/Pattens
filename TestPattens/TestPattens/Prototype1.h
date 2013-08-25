//
//  Prototype1.h
//  TestPattens
//
//  Created by Kaven Feng on 8/23/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Prototype1__
#define __TestPattens__Prototype1__

#include <iostream>
#include <string>
#include <memory>

namespace Prototype1 {
    
    class Object
    {
    public:
        Object(){}
        virtual ~Object(){}
    };
    
    class Bullet : public Object
    {
        friend class Tower;
        
    public:
        Bullet();
        virtual ~Bullet();
        
        // Prototype pattern;
        Bullet(const Bullet& rhs);
        virtual Bullet* clone();
        
    private:
        // private constructor for prototype

    private:
        std::string mType;
        float mSpeed;
        float mDamage;
        std::shared_ptr<Object> mTarget;
    };
    
    class StarBullet : public Bullet
    {
        friend class Tower;
        
    public:
        StarBullet();
        virtual ~StarBullet();
        
        StarBullet(const StarBullet& rhs);
        virtual Bullet* clone() override;
        
    private:
        float mRange;
    };
    
    class Tower : public Object
    {
    public:
        Tower();
        virtual ~Tower();
        
        void fire();
        void upgrade();
        void starBullet();
        
    private:
        void initBullet();
        
    private:
        std::shared_ptr<Bullet> mBullet;
    };
    
    class Client
    {
    public:
        void run();
    };
    
}

#endif /* defined(__TestPattens__Prototype1__) */
