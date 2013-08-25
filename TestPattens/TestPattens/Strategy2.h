//
//  Strategy2.h
//  TestPattens
//
//  Created by Kaven Feng on 8/25/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Strategy2__
#define __TestPattens__Strategy2__

#include <iostream>
#include <functional>
#include <vector>

//Using std::function for strategy.

namespace Strategy2 {
    
    class Node
    {
    public:
        Node() : mName("N0"), mType(0) {}
        Node(const std::string& name, int type) : mName(name), mType(type){}
        
        const std::string& name() const {return mName;}
        void name(const std::string& name) {mName = name;}
        
        int type() const {return mType;}
        void type(int t) {mType = t;}
        
    private:
        std::string mName;
        int mType;
    };
    
    class Agent{
        typedef std::function<bool(Node*)> _Func;
        
    public:
        
        Agent(const _Func& func) : mFunc(func) {}
        virtual ~Agent() {}
        
        // change strategy
        void switchTo(const _Func& func){
            mFunc = func;
        }
        
        bool visit(Node* node){
            return mFunc(node);
        }
        
    private:
        _Func mFunc;
    };
    
    class Agents{
        typedef std::function<bool(Node*)> _Func;
        typedef std::vector<_Func> _Funcs;
        
    public:
        
        Agents(){}
        virtual ~Agents(){}
        
        // push the strategy
        void add(const _Func& func){
            mFuncs.push_back(func);
        }
        
        // run the pipeline.
        bool visit(Node* node){
            std::for_each(mFuncs.begin(), mFuncs.end(), [&](const _Func& func){
                func(node);
            });
            return true;
        }
        
    private:
        _Funcs mFuncs;
    };
    
    
    class Client{
    public:
        void run()
        {
            Node node("n1", 1);
            
            auto print = [](Node* node)->bool{
                std::cout << "Print agent: " << node->name() << " " << node->type() << std::endl;
                return true;
            };
            
            auto increase = [](Node* node)->bool{
                node->type(node->type() + 1);
                std::cout << "Increase agent: " << node->name() << " " << node->type() << std::endl;
                return true;
            };
            
            auto rename = [](Node* node)->bool{
                node->name(node->name() + "-new");
                std::cout << "Rename agent: " << node->name() << " " << node->type() << std::endl;
                return true;
            };
            
            std::cout << "Now using one Agent \n ";
            Agent agent(print);
            agent.visit(&node);
            
            agent.switchTo(increase);
            agent.visit(&node);
            
            agent.switchTo(rename);
            agent.visit(&node);
            
            agent.switchTo(print);
            agent.visit(&node);
            
            std::cout << "Now using Agents\n ";
            Agents agents;
            
            //config the pipeline.
            agents.add(print);
            agents.add(increase);
            agents.add(rename);
            agents.add(print);
            
            // do the job in batch.
            agents.visit(&node);
            
        }
    };
    
}

#endif /* defined(__TestPattens__Strategy2__) */
