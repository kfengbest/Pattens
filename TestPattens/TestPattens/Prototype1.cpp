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

void Tower::fire()
{
    std::shared_ptr<Bullet> newBullet(mBullet->clone());
    newBullet->mTarget = nullptr; // get a target.
    // gameLayer->addChild(newBullet);
}

void Client::start()
{
    std::cout << "Clone1 Start" << std::endl;
    std::shared_ptr<Tower> pTower(new Tower());
    pTower->fire();
    pTower->fire();
    pTower->fire();
    std::cout << "Clone1 end" << std::endl;

}