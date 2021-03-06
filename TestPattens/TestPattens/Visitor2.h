//
//  Visitor2.h
//  TestPattens
//
//  Created by Kaven Feng on 8/25/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Visitor2__
#define __TestPattens__Visitor2__

#include <iostream>
#include <vector>
#include <memory>


// Neutron visitor implementation
namespace Visitor2 {
namespace  V1{

    class Node{
    public:
        Node(const std::string& name) : mName(name){}
        virtual ~Node(){}
    public:
        virtual void save(){std::cout<< mName << " Node::save() \n";}
        virtual void load(){std::cout<< mName  << "Node::load() \n";}
        virtual void draw(){std::cout<< mName  << "Node::draw() \n";}
        virtual void select(){std::cout<< mName  << "Node::load() \n";}

        //Add this method in all object structure
        // Dump step 1
        virtual void dump(){std::cout<< mName  << "Node::dump() \n";}

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

        // Dump step 2
        virtual void dump(){std::cout<< mName  << "Node::dump() \n";}
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
        
        // Dump step 3
        virtual void dump(){
            std::cout<< mName  << " GroupNode::dump() \n";
            std::for_each(mNodes.begin(), mNodes.end(), [](const NodePtr& node){
                node->dump();
            });
        }
    private:
        Nodes mNodes;
    };
    
    class Client{
    public:
        void run(){
            // build structure.
            NodePtr ln1(new LeafNode("ln1"));
            NodePtr ln2(new LeafNode("ln2"));
            std::shared_ptr<GroupNode> root(new GroupNode("root"));
            std::shared_ptr<GroupNode> doc(new GroupNode("doc"));
            root->add(doc);
            doc->add(ln1);
            doc->add(ln2);
            
            // behavior
            root->save();
            root->load();
            
            // Dump step 4
            root->dump();
            
        }
    };
    
}

    
    namespace  V2{
        
        class Node;
        class Visitor;
        class LeafNode;
        class GroupNode;
        class Monster;
        
        class Visitor{
        public:
            virtual ~Visitor(){}
            
            virtual void onVisit(Node* node){
                std::cout << "Visitor::onVisit(Node) \n";
            }
            virtual void onVisit(LeafNode* node){
                std::cout << "Visitor::onVisit(LeafNode) \n";
            }
            virtual void onVisit(GroupNode* node){
                std::cout << "Visitor::onVisit(GroupNode) \n";
            }
            
            //Changes 3 Node type changed:
            //step 2 added a new method here.
            virtual void onVisit(Monster* node){
                std::cout << "Visitor::onVisit(Monster) \n";
            }

        };
        
        class Node{
        public:
            Node(const std::string& name) : mName(name){}
            virtual ~Node(){}
        public:
            virtual void accept(Visitor* viz){ viz->onVisit(this);}
            
            const std::string& name() const { return mName; }
            
        public:
            std::string mName;
        };
        
        class LeafNode : public Node{
        public:
            LeafNode(const std::string& name) : Node(name){}
            virtual ~LeafNode(){}
        public:
            virtual void accept(Visitor* viz){ viz->onVisit(this);}
        };
        
        typedef std::shared_ptr<Node> NodePtr;
        typedef std::vector<NodePtr> Nodes;
        
        class GroupNode :public Node{
        public:
            GroupNode(const std::string& name) : Node(name){}
            virtual ~GroupNode(){}
            
            void add(const NodePtr& node) {mNodes.push_back(node);}
            
        public:
            // Visitor实现一： 遍历逻辑封装在Node中，Visitor只负责操作，责任清晰。
            // 优点： 如果只是增加一种新的对node的访问方式，只需要派生一个新的Visitor就行。
            // 缺点： 如果增加了一种node的类型，需要修改所有visitor类。
            virtual void accept(Visitor* viz) override {

                // Visit myself firstly.
                viz->onVisit(this);
                
                // Then visit my children.
                std::for_each(mNodes.begin(), mNodes.end(), [&](const NodePtr& node){
                    node->accept(viz);
                });
            }
            
        private:
            Nodes mNodes;
        };
        
        // Changes 3 Node type changed:
        // step 1, define a new node type.
        class Monster : public LeafNode{
        public:
            Monster(const std::string& name) : LeafNode(name){}
            virtual ~Monster(){}
            
            virtual void accept(Visitor* v){
                v->onVisit(this);
            }
        };
        
        class SaveVisitor : public Visitor{
        public:
            virtual ~SaveVisitor(){}
            
            virtual void onVisit(Node* node){std::cout << "SaveVisitor::onVisit(Node) " << node->name() << std::endl;}
            virtual void onVisit(LeafNode* node){std::cout << "SaveVisitor::onVisit(LeafNode)" << node->name() << std::endl;}
            virtual void onVisit(GroupNode* node){std::cout << "SaveVisitor::onVisit(GroupNode)" << node->name() << std::endl;}
            // Change 3 Node type changed.
            // Step 3: implement onVisit on concrete Visitor.
            virtual void onVisit(Monster* node){std::cout << "SaveVisitor::onVisit(Monster)" << node->name() << std::endl;}

        };
        
        class LoadVisitor : public Visitor{
        public:
            virtual ~LoadVisitor(){}
            virtual void onVisit(Node* node){std::cout << "LoadVisitor::onVisit(Node) "<< node->name() << std::endl;}
            virtual void onVisit(LeafNode* node){std::cout << "LoadVisitor::onVisit(LeafNode) "<< node->name() << std::endl;}
            virtual void onVisit(GroupNode* node){std::cout << "LoadVisitor::onVisit(GroupNode) "<< node->name() << std::endl;}
        };
        
        // Change 1: add a new operation.
        // step 1: just need to inherited from Visitor, that's enough.
        class SelectVisitor : public Visitor{
        public:
            virtual ~SelectVisitor(){}
            virtual void onVisit(Node* node){std::cout << "SelectVisitor::onVisit(Node) "<< node->name() << std::endl;}
            virtual void onVisit(LeafNode* node){std::cout << "SelectVisitor::onVisit(LeafNode) "<< node->name() << std::endl;}
            virtual void onVisit(GroupNode* node){std::cout << "SelectVisitor::onVisit(GroupNode) "<< node->name() << std::endl;}
        };
        
        
        class Client{
        public:
            void run(){
                
                // build structure.
                NodePtr ln1(new LeafNode("ln1"));
                NodePtr ln2(new LeafNode("ln2"));
                std::shared_ptr<GroupNode> root(new GroupNode("root"));
                std::shared_ptr<GroupNode> doc(new GroupNode("doc"));
                root->add(doc);
                doc->add(ln1);
                doc->add(ln2);
                
                // Start operation
                SaveVisitor saver;
                root->accept(&saver);
                
                LoadVisitor loader;
                root->accept(&loader);
                
                // Change 1, step 2: invoke.
                SelectVisitor selector;
                root->accept(&selector);
                
                // Changes 2. only structure changed.
                std::shared_ptr<GroupNode> mons(new GroupNode("mons"));
                std::shared_ptr<Monster> mon1(new Monster("mon1"));
                std::shared_ptr<Monster> mon2(new Monster("mon2"));
                doc->add(mons);
                mons->add(mon1);
                mons->add(mon2);
                
                root->accept(&saver);
                root->accept(&loader);


            }
        };
        
    }

}
#endif /* defined(__TestPattens__Visitor2__) */
