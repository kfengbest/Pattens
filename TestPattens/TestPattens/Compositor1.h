//
//  Compositor1.h
//  TestPattens
//
//  Created by Kaven Feng on 8/28/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Compositor1__
#define __TestPattens__Compositor1__

#include <iostream>
#include <vector>
#include <memory>

namespace Compositor1 {
    
    class Node{
    public:
        Node(const std::string& name) : mName(name){}
        virtual ~Node(){}
    public:
        virtual void save(){std::cout<< mName << " Node::save() \n";}
        virtual void load(){std::cout<< mName  << "Node::load() \n";}
        virtual void draw(){std::cout<< mName  << "Node::draw() \n";}
        virtual void select(){std::cout<< mName  << "Node::load() \n";}
        
        
    protected:
        std::string mName;
    };
    
    class LeafNode : public Node{
    public:
        LeafNode(const std::string& name) : Node(name){}
        virtual ~LeafNode(){}
    public:
        virtual void save(){std::cout<< mName  << " LeafNode::save() \n";}
        virtual void load(){std::cout<< mName  << " LeafNode::load() \n";}
        virtual void draw(){std::cout<< mName  << " LeafNode::draw() \n";}
        virtual void select(){std::cout<< mName  << " LeafNode::load() \n";}
        
    };
    
    typedef std::shared_ptr<Node> NodePtr;
    typedef std::vector<NodePtr> Nodes;
    
    class GroupNode :public Node{
    public:
        GroupNode(const std::string& name) : Node(name){}
        virtual ~GroupNode(){}
        
        void add(const NodePtr& node) {mNodes.push_back(node);}
        
    public:
        virtual void save(){
            std::cout << mName << " GroupNode::save() \n";
            std::for_each(mNodes.begin(), mNodes.end(), [](const NodePtr& node){
                node->save();
            });
        }
        virtual void load(){
            std::cout << mName << " GroupNode::load() \n";
            std::for_each(mNodes.begin(), mNodes.end(), [](const NodePtr& node){
                node->load();
            });
        }
        virtual void draw(){
            std::cout << mName << " GroupNode::draw() \n";
            std::for_each(mNodes.begin(), mNodes.end(), [](const NodePtr& node){
                node->draw();
            });
        }
        virtual void select(){
            std::cout<< mName  << " GroupNode::select() \n";
            std::for_each(mNodes.begin(), mNodes.end(), [](const NodePtr& node){
                node->select();
            });
        }
        
    private:
        Nodes mNodes;
    };
    
    class Client{
    public:
        void run(){
            NodePtr ln1(new LeafNode("ln1"));
            NodePtr ln2(new LeafNode("ln2"));
            
            std::shared_ptr<GroupNode> root(new GroupNode("root"));
            std::shared_ptr<GroupNode> doc(new GroupNode("doc"));
            
            root->add(doc);
            doc->add(ln1);
            doc->add(ln2);
            
            root->save();
            root->load();
            
        }
    };
    
}

#endif /* defined(__TestPattens__Compositor1__) */
