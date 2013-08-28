//
//  Visitor3.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/28/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include "Visitor3.h"

using namespace Visitor3;

void Node::accept(Visitor* v){
    v->onNode(this);
    std::for_each(mNodes.begin(), mNodes.end(), [&](const NodePtr& n){
        n->accept(v);
    });
}

void Tower::accept(Visitor* v){
    v->onTower(this);
}

void Monster::accept(Visitor* v){
    v->onMonster(this);
}