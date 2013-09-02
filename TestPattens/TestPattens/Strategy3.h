//
//  Strategy3.h
//  TestPattens
//
//  Created by Kaven Feng on 9/2/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Strategy3__
#define __TestPattens__Strategy3__

#include <iostream>
#include <map>
#include <vector>

// Action system in Cocos2dx
namespace Strategy3 {
    
    class Point
    {
    public:
        virtual ~Point(){}
        Point() : x(0),y(0),z(0){}
        Point(int _x, int _y, int _z) : x(_x), y(_y), z(_z){}
        Point(const Point& rhs) : x(0), y(0), z(0) { x = rhs.x; y = rhs.y; z = rhs.z;}
        
        Point& operator= (const Point& rhs)
        {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            return *this;
        }
        
        int x;
        int y;
        int z;
    };
    
    class Action;
    class ActionManager;
    
    class Node
    {
    public:
        Node(): mPos(Point(0,0,0)){}
        virtual ~Node(){}
        
        void position(const Point& p){ mPos = p;}
        Point position() const { return mPos;}
        
        void name(const std::string& n){ mName = n;}
        std::string name() const {return mName;}
        
        void runAction(Action* action);
        
        void print() const { std::cout << "Node: " << mName << " " << mPos.x << " " << mPos.y << std::endl;}
        
    private:
        Point mPos;
        std::string mName;
    };
    
    class Action
    {
    public:
        virtual void update(float dt){}
        
        void setTarget(Node* n){mTarget = n;}
        
    protected:
        Node* mTarget;
    };
    
    class ActionManager
    {
        typedef std::vector<Action*> Actions;
        
    public:
        static ActionManager* get()
        {
            static ActionManager ins;
            return &ins;
        }
    
        void update(float dt){
            std::for_each(mActions.begin(), mActions.end(), [&](Action* a){
                a->update(dt);
            });
        }
        
        void addAction(Node* n, Action* a);
        
    private:
        Actions mActions;
    };

    class Move : public Action
    {
    public:
        virtual void update(float dt){
            Point pos = mTarget->position();
            pos.x += 10;
            pos.y += 100;
            mTarget->position(pos);
        }
    };
    
    class Rotate : public Action
    {
    public:
        virtual void update(float dt){
            Point pos = mTarget->position();
            pos.x += 10000;
            pos.y += 10000;
            pos.z += 10000;
            mTarget->position(pos);
        }
    };
    
    class Scale : public Action
    {
    public:
        virtual void update(float dt){
            Point pos = mTarget->position();
            pos.z += 1000;
            mTarget->position(pos);
        }
    };
    
    class Client
    {
    public:
        void run()
        {
            Node n1;
            n1.position(Point(1,1,1));
            n1.name("n1");
            
            std::cout << "begin state: \n";
            n1.print();
            
            Move m1;
            n1.runAction(&m1);
            ActionManager::get()->update(0);

            std::cout << "run move \n";
            n1.print();
            
            Rotate r1;
            n1.runAction(&r1);
            ActionManager::get()->update(0);
            
            std::cout << "run move, rotate \n";
            n1.print();
        }
    };
    
}

#endif /* defined(__TestPattens__Strategy3__) */
