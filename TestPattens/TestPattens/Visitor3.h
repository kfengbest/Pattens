//
//  Visitor3.h
//  TestPattens
//
//  Created by Kaven Feng on 8/28/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Visitor3__
#define __TestPattens__Visitor3__

#include <iostream>
#include <functional>
#include <vector>
#include <memory>

// Visitro + Strategy using funciton
namespace Visitor3 {
    
    class Node;
    class Tower;
    class Monster;
    class Visitor;
    
    typedef std::shared_ptr<Node> NodePtr;
    typedef std::vector<NodePtr> Nodes;
    
    class Node{
        
    public:
        Node(const std::string& n) : mName(n){}
        virtual ~Node(){}
        virtual void accept(Visitor* v);
        
        void add(const NodePtr& node) {mNodes.push_back(node);}
        const std::string& name() const {return mName;}
    private:
        Nodes mNodes;
        std::string mName;
    };
    
    class Tower : public Node{
    public:
        Tower(const std::string& n) : Node(n){}
        virtual ~Tower(){}
        virtual void accept(Visitor* v) override;
    };
    
    class Monster : public Node{
    public:
        Monster(const std::string& n) : Node(n){}
        virtual ~Monster(){}
        virtual void accept(Visitor* v) override;

    };
    
    class Visitor{
        typedef std::function<void(Node*)> _Func;
        
    public:
        void use(const _Func& func){ mFunc = func;}
        
        virtual void onNode(Node* o) { mFunc(o);}
        virtual void onTower(Tower* o) { mFunc(o);}
        virtual void onMonster(Monster* o) { mFunc(o);}
        
    private:
        _Func mFunc;
    };
    
    class Client{
    public:
        void run()
        {
            // build node structure
            NodePtr root(new Node("root"));
            std::shared_ptr<Monster> m1(new Monster("m1"));
            std::shared_ptr<Tower>   t1(new Tower("m2"));
            root->add(m1);
            root->add(t1);
            
            NodePtr doc(new Node("doc"));
            root->add(doc);
            doc->add(m1);
            doc->add(t1);
            
            // define visitor
            auto print = [](Node* o){ std::cout << "print " << o->name() << std::endl; };
            auto save = [](Node* o){ std::cout << "save " << o->name() << std::endl; };
            auto load = [](Node* o){ std::cout << "load " << o->name() << std::endl; };
            
            // operation.
            Visitor viz;
            viz.use(print);
            root->accept(&viz);
            
            viz.use(save);
            root->accept(&viz);
            
            viz.use(load);
            root->accept(&viz);
            
        }
    };
    
}

#endif /* defined(__TestPattens__Visitor3__) */
