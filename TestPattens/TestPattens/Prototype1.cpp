//
//  Prototype1.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/23/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include "Prototype1.h"

using namespace Prototype1;

Bullet::Bullet()
: mType("B0")
, mSpeed(0.0f)
, mDamage(0.0f)
, mTarget(nullptr)
{
    std::cout << "Bullet() default: " << " type: " << mType << " speed: " << mSpeed << " damage: " << mDamage << std::endl;
}

Bullet::Bullet(const Bullet& rhs)
: mType(rhs.mType)
, mSpeed(rhs.mSpeed)
, mDamage(rhs.mDamage)
, mTarget(nullptr)
{
    std::cout << "Bullet() Cloned: " << " type: " << mType << " speed: " << mSpeed << " damage: " << mDamage << std::endl;
}

Bullet::~Bullet()
{
    std::cout << " ~Bullet() Current: type: " << mType << " speed: " << mSpeed << " damage: " << mDamage << std::endl;
}

Bullet* Bullet::clone()
{
    return new Bullet(*this);
}

StarBullet::StarBullet()
: Bullet()
, mRange(0.0)
{
    std::cout << "StarBullet() default: " << " mRange: "  << mRange << std::endl;
}

StarBullet::~StarBullet()
{
    std::cout << "~StarBullet() current: " << " mRange: "  << mRange << std::endl;

}

StarBullet::StarBullet(const StarBullet& rhs)
: Bullet(rhs)
, mRange(rhs.mRange)
{
    std::cout << "StarBullet() clone: " << " mRange: "  << mRange << std::endl;

}

Bullet* StarBullet::clone()
{
    return new StarBullet(*this);
}


Tower::Tower()
{
    initBullet();
    std::cout << "Tower()" << std::endl;
}

Tower::~Tower()
{
    std::cout << "~Tower()" << std::endl;
}

void Tower::initBullet()
{
    mBullet = std::shared_ptr<Bullet>(new Bullet());
    mBullet->mType = "B1";
    mBullet->mSpeed = 100;
    mBullet->mDamage = 80;
    mBullet->mTarget = nullptr;
}

void Tower::upgrade()
{
    mBullet->mSpeed += 100;
    mBullet->mDamage += 100;
    std::cout << "Tower upgraded! " << " bullet speed: " << mBullet->mSpeed << " damage: " << mBullet->mDamage << std::endl;
}

void Tower::starBullet()
{
    std::shared_ptr<StarBullet> star(new StarBullet);
    star->mType = "starBullet";
    star->mSpeed = 1000;
    star->mDamage = 800;
    star->mRange = 500;
    star->mTarget = nullptr;
    mBullet = star;
    
}

void Tower::fire()
{
    std::shared_ptr<Bullet> newBullet(mBullet->clone());
    newBullet->mTarget = nullptr; // get a target.
    // gameLayer->addChild(newBullet);
}

void Client::run()
{
    std::cout << "Clone1 Start" << std::endl;
    std::shared_ptr<Tower> pTower(new Tower());
    pTower->fire();
    pTower->upgrade();
//    pTower->fire();
//    pTower->upgrade();
//    pTower->fire();
    std::cout << "create starBullet" << std::endl;
    pTower->starBullet();
    pTower->fire();
//    pTower->upgrade();
//    pTower->fire();
    
    std::cout << "Clone1 end" << std::endl;

}