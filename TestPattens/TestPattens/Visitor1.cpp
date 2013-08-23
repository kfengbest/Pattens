//
//  Visitor1.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/18/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include "Visitor1.h"

using namespace Visitor1;


Node::Node(const std::string& name)
: m_name(name)
{
}

Node::~Node()
{
}

void Node::accept(Visitor1::Visitor *pVisitor)
{
    pVisitor->visit(this);
}

Monster::Monster(const std::string& name)
: Node(name)
{
    
}

Tower::Tower(const std::string& name)
: Node(name)
{
    
}

Obstacle::Obstacle(const std::string& name)
: Node(name)
{
    
}


void Visitor::visit(Node* pNode)
{
    std::cout << pNode->name() << std::endl;
}


void Client::buildObjects(){
    
    Monster* m1 = new Monster("m1");
    this->addChild(m1);
    
    Tower* t1 = new Tower("t1");
    this->addChild(t1);
    
    Obstacle* o1 = new Obstacle("o1");
    this->addChild(o1);
    
    Monster* m2 = new Monster("m2");
    this->addChild(m2);
    
    Tower* t2 = new Tower("t2");
    this->addChild(t2);
    
    Obstacle* o2 = new Obstacle("o2");
    this->addChild(o2);
    
    
}

void Client::save(){
    
    Visitor saver;
    std::for_each(m_nodes.begin(), m_nodes.end(), [&](Node* node){
        node->accept(&saver);
    });
    
}



