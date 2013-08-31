//
//  Visitor4.h
//  TestPattens
//
//  Created by Kaven Feng on 8/31/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Visitor4__
#define __TestPattens__Visitor4__

#include <iostream>
#include <vector>


// visitor with push/pop

namespace Visitor4 {
    
    class Area;
    class Visitor;
    
    typedef std::vector<Area*> Areas;
    
    class Visitor{
    public:
        void visit(Area* pArea) { this->onVisit(pArea);}
        void push(Area* pArea) {this->onPush(pArea);}
        void pop(Area* pArea) {this->onPop(pArea);}
        
    protected:
        virtual void onVisit(Area* pArea);
        virtual void onPush(Area* pArea);
        virtual void onPop(Area* pArea);
    };
    
    class Area{
        
    public:
        
        Area(const std::string& name) : mName(name){}
        virtual ~Area(){}
    
        const std::string& name() {return mName;}
        
    public:
        
        void addChild(Area* pArea){ mChildren.push_back(pArea);}
        
        void removeChild(Area* pArea){
            auto it = std::find(mChildren.begin(), mChildren.end(), pArea);
            if(it != mChildren.end()){
                mChildren.erase(it);
            }
        }
        
        virtual void accept(Visitor* viz) {
            
            viz->push(this);
            
            // make a copy in case child is destored while in traversing.
            Areas areas = mChildren;
            std::for_each(areas.begin(), areas.end(), [&](Area* pArea){
                pArea->accept(viz);
            });
    
            viz->pop(this);
        }
        
    private:
        std::string mName;
        Areas mChildren;
    };
    
    class TopDownVisitor : public Visitor{
    protected:
        virtual void onPush(Area* pArea){ this->visit(pArea);}
    };
    
    class BottomUpVisitor : public Visitor{
    protected:
        virtual void onPop(Area* pArea){ this->visit(pArea);}
    };
    
    class Client{
        
    public:
        void run(){
            Area root("root");
            Area w("w0");
            root.addChild(&w);
            
            Area w1("w1");
            w.addChild(&w1);
            Area w2("w2");
            w.addChild(&w2);
            
            Area w21("w21");
            w2.addChild(&w21);
            
            TopDownVisitor td;
            root.accept(&td);
            
            BottomUpVisitor bu;
            root.accept(&bu);
            
        }
    };
    
}

#endif /* defined(__TestPattens__Visitor4__) */
