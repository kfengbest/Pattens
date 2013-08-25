//
//  Behavior.h
//  TestPattens
//
//  Created by Kaven Feng on 8/25/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Behavior__
#define __TestPattens__Behavior__

#include <iostream>
#include <memory>
#include <vector>

namespace  Stategy4{

    class Behavior;
    class Control;
    
    class Point{
    public:
        Point(int _x, int _y) : x(_x), y(_y){}
        virtual ~Point(){}
        
        int x;
        int y;
    };
    
    typedef std::shared_ptr<Control> ControlPtr;
    typedef std::shared_ptr<Behavior> BehaviorPtr;
    
    class Control{
    
    public:
        virtual void show(const Point& pos){}
        
    protected:
        BehaviorPtr mBehavior;
    };
    

    
    // Behavior is a small chunk of reusable logic that
    // can be shared by UI elements for behavior such as
    // position, closing, opacity etc.
    class Behavior{
    public:
        Behavior(ControlPtr control) : mControl(control){ }
        virtual ~Behavior(){}
        
        const ControlPtr& control() const {return mControl;}
        
        virtual void begin(){}
        virtual void end(){}
        
    private:
        ControlPtr mControl;
        
    };
    
    // allow multiple behaviors to be composited for UI.
    class CompositeBehavior : public Behavior{
        typedef std::vector<BehaviorPtr> Behaviors;
        
    public:
        CompositeBehavior(ControlPtr control) : Behavior(control){}
        virtual ~CompositeBehavior(){}
        
        void add(const BehaviorPtr& behavior){
            mBehaviors.push_back(behavior);
        }
        
        void remove(const BehaviorPtr& behavior){
            auto it = std::find(mBehaviors.begin(), mBehaviors.end(), behavior);
            if (it != mBehaviors.end()) {
                mBehaviors.erase(it);
            }
        }

        virtual void begin() override{
            std::for_each(mBehaviors.begin(), mBehaviors.end(), [](BehaviorPtr behavior){
                behavior->begin();
            });
        }
        
        virtual void end() override {
            std::for_each(mBehaviors.begin(), mBehaviors.end(), [](BehaviorPtr behavior){
                behavior->end();
            });
        }
        
    protected:
        Behaviors mBehaviors;
    };
    
    class DockBehavior : public Behavior{
    public:
        DockBehavior(ControlPtr control) : Behavior(control){}
        virtual ~DockBehavior(){}
        
        virtual void begin() override{
            std::cout << "DockBehavior::begin() \n";
        }
        
        virtual void end() override {
            std::cout << "DockBehavior::end() \n";
        }
    };
    
    class SnapBehavior : public Behavior{
    public:
        SnapBehavior(ControlPtr control) : Behavior(control){}
        virtual ~SnapBehavior(){}
        
        virtual void begin() override{
            std::cout << "SnapBehavior::begin() \n";
        }
        
        virtual void end() override {
            std::cout << "SnapBehavior::end() \n";
        }
    };
    
    class SmartLayoutBehavior : public Behavior{
    public:
        SmartLayoutBehavior(ControlPtr control) : Behavior(control){}
        virtual ~SmartLayoutBehavior(){}
        
        virtual void begin() override{
            std::cout << "SmartLayoutBehavior::begin() \n";
        }
        
        virtual void end() override {
            std::cout << "SmartLayoutBehavior::end() \n";
        }
    };

    class ProximityBehavior : public Behavior{
    public:
        ProximityBehavior(ControlPtr control) : Behavior(control){}
        virtual ~ProximityBehavior(){}
        
        virtual void begin() override{
             std::cout << "ProximityBehavior::begin() \n";
        }
        
        virtual void end() override {
             std::cout << "ProximityBehavior::end() \n";
        }
    };
    
    class FadeBehavior : public ProximityBehavior{
    public:
        FadeBehavior(ControlPtr control) : ProximityBehavior(control){}
        virtual ~FadeBehavior(){}
      
        virtual void begin() override{
            std::cout << "FadeBehavior::begin() \n";
        }
        
        virtual void end() override {
            std::cout << "FadeBehavior::end() \n";
        }
    };
    
    class DismissBehavior : public ProximityBehavior{
    public:
        DismissBehavior(ControlPtr control) : ProximityBehavior(control){}
        virtual ~DismissBehavior(){}
        
        virtual void begin() override{
            std::cout << "DismissBehavior::begin() \n";
        }
        
        virtual void end() override {
            std::cout << "DismissBehavior::end() \n";
        }
    };
    
    class CloseOnEscapeBehavior: public Behavior{
    public:
        CloseOnEscapeBehavior(ControlPtr control) : Behavior(control){}
        virtual ~CloseOnEscapeBehavior(){}
      
        virtual void begin() override{
            std::cout << "CloseOnEscapeBehavior::begin() \n";
        }
        
        virtual void end() override {
            std::cout << "CloseOnEscapeBehavior::end() \n";
        }
    };
    
    class CloseOnSelectBehavior: public Behavior{
    public:
        CloseOnSelectBehavior(ControlPtr control) : Behavior(control){}
        virtual ~CloseOnSelectBehavior(){}
        
        virtual void begin() override{
             std::cout << "CloseOnSelectBehavior::begin() \n";
        }
        
        virtual void end() override {
             std::cout << "CloseOnSelectBehavior::end() \n";
        }
    };
    
    class Menu : public Control{
    public:
        virtual void show(const Point& pos){
            
            // config behaviors.
            ControlPtr thisPtr(this);
            std::shared_ptr<CompositeBehavior> behavior(new CompositeBehavior(thisPtr));
            behavior->add(BehaviorPtr(new DockBehavior(thisPtr)));
            behavior->add(BehaviorPtr(new SnapBehavior(thisPtr)));
            behavior->add(BehaviorPtr(new SmartLayoutBehavior(thisPtr)));
            behavior->add(BehaviorPtr(new FadeBehavior(thisPtr)));
            
            // start behaviors.
            mBehavior = behavior;
            mBehavior->begin();
            
            // Add this to UI layer.
        }
    };
    
    class Client
    {
    public:
        void run()
        {
            Menu m;
            m.show(Point(2,3));
        }
    };
    
    
};

#endif /* defined(__TestPattens__Behavior__) */
