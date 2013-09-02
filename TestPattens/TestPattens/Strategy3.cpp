//
//  Strategy3.cpp
//  TestPattens
//
//  Created by Kaven Feng on 9/2/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include "Strategy3.h"

using namespace Strategy3;

void Node::runAction(Action* a)
{
    ActionManager::get()->addAction(this, a);
}

void ActionManager::addAction(Node* n, Action* a){
    a->setTarget(n);
    mActions.push_back(a);
}