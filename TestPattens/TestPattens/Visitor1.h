//
//  Visitor1.h
//  TestPattens
//
//  Created by Kaven Feng on 8/18/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Visitor1__
#define __TestPattens__Visitor1__

#include <iostream>
#include <vector>


namespace Visitor1 {
    
    class Visitor;
    class Client;
    
    class Node{
    public:
        Node(const std::string& name);
        virtual ~Node();
        
    public:
        virtual void accept(Visitor* pVisitor);
        const std::string& name() const {return m_name;}
        
    private:
        std::string m_name;
    };
    
    class Visitor{
    public:
        Visitor(){}
        virtual ~Visitor(){};
        
    public:
        virtual void visit(Node* pNode);
    
    protected:

    };

    class Monster : public Node{
    public:
        Monster(const std::string& name);
    };
    
    class Tower : public Node{
    public:
        
        Tower(const std::string& name);
    };
    
    class Obstacle : public Node{
    public:
        
        Obstacle(const std::string& name);
        
    };
    
    class Client
    {
        typedef std::vector<Node*> Nodes;
        
    public:
        void addChild(Node* pNode){ m_nodes.push_back(pNode);}
        void buildObjects();
        void save();
        
    private:
        Nodes m_nodes;
    };
};

#endif /* defined(__TestPattens__Visitor1__) */
