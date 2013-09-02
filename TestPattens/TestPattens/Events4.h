//
//  Events4.h
//  TestPattens
//
//  Created by Kaven Feng on 9/2/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Events4__
#define __TestPattens__Events4__

#include <iostream>
#include <vector>

// Delegate/Dispatcher events system in Cocos2dx

namespace Events4 {
    
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
    
    class Touch{
    public:
        Touch(const Point& p) : mPos(p){}
        virtual ~Touch(){}
        
    public:
        Point mPos;
    };
    
    class TouchDelegate{
    public:
        TouchDelegate(){}
        virtual ~TouchDelegate(){}
        
        virtual void touchBegin(Touch* t){ std::cout << "TouchDelegate::touchBegin() \n";}
        virtual void touchMove(Touch* t){ std::cout << "TouchDelegate::touchMove() \n";}
        virtual void touchEnd(Touch* t){ std::cout << "TouchDelegate::touchEnd() \n";}
    };
    
    class TouchDispatcher{
        typedef std::vector<TouchDelegate*> Delegates;
    public:
        TouchDispatcher(){}
        virtual ~TouchDispatcher(){}
        
        void addDelegate(TouchDelegate* pDeletate){ mDelegates.push_back(pDeletate);}
        void removeDelegate(TouchDelegate* pDeletate){
            auto it = std::find(mDelegates.begin(), mDelegates.end(), pDeletate);
            if (it != mDelegates.end()) {
                mDelegates.erase(it);
            }
        }
        
        
    public:
        void fireTouchBegin(Touch* t){
            std::for_each(mDelegates.begin(), mDelegates.end(), [&](TouchDelegate* delegate){
                delegate->touchBegin(t);
            });
        }
        void fireTouchMove(Touch* t){
            std::for_each(mDelegates.begin(), mDelegates.end(), [&](TouchDelegate* delegate){
                delegate->touchMove(t);
            });
        }
        void fireTouchEnd(Touch* t){
            std::for_each(mDelegates.begin(), mDelegates.end(), [&](TouchDelegate* delegate){
                delegate->touchEnd(t);
            });
        }
        
    private:
        Delegates mDelegates;
    };
    
    class KeyboardDelegate{
    public:
        KeyboardDelegate(){}
        virtual ~KeyboardDelegate(){}
        
        virtual void keyPressed(Touch* t){ std::cout << "KeyboardDelegate::keyPressed() \n";}
        virtual void keyReleased(Touch* t){ std::cout << "KeyboardDelegate::keyReleased() \n";}
    };
    
    class KeyboardDispatcher{
        typedef std::vector<KeyboardDelegate*> Delegates;
    public:
        KeyboardDispatcher(){}
        virtual ~KeyboardDispatcher(){}
        
        void addDelegate(KeyboardDelegate* pDeletate){ mDelegates.push_back(pDeletate);}
        void removeDelegate(KeyboardDelegate* pDeletate){
            auto it = std::find(mDelegates.begin(), mDelegates.end(), pDeletate);
            if (it != mDelegates.end()) {
                mDelegates.erase(it);
            }
        }
        
        
    public:
        void fireKeyPressed(Touch* t){
            std::for_each(mDelegates.begin(), mDelegates.end(), [&](KeyboardDelegate* delegate){
                delegate->keyPressed(t);
            });
        }
        void fireKeyReleased(Touch* t){
            std::for_each(mDelegates.begin(), mDelegates.end(), [&](KeyboardDelegate* delegate){
                delegate->keyReleased(t);
            });
        }

        
    private:
        Delegates mDelegates;
    };
    

    class Director{
      
    public:
        static Director* get(){ static Director ins; return &ins;}
        TouchDispatcher* getTouchDispatcher() const {return mTouchDispatcher;}
        KeyboardDispatcher* getKeyboardDispatcher() const {return mKeyboardDispatcher;}
        
    private:
        Director()
        {
            mTouchDispatcher = new TouchDispatcher;
            mKeyboardDispatcher = new KeyboardDispatcher;
        }
        
    private:
        TouchDispatcher* mTouchDispatcher;
        KeyboardDispatcher* mKeyboardDispatcher;
    };
    
    class Layer : public TouchDelegate, public KeyboardDelegate
    {
    public:
        Layer(){
            Director::get()->getTouchDispatcher()->addDelegate(this);
            Director::get()->getKeyboardDispatcher()->addDelegate(this);
        }
        virtual ~Layer(){
            Director::get()->getTouchDispatcher()->removeDelegate(this);
            Director::get()->getKeyboardDispatcher()->removeDelegate(this);
        }
    protected:
        virtual void touchBegin(Touch* t){ std::cout << this << " View::touchBegin() \n";}
        virtual void touchMove(Touch* t){ std::cout << this << " View::touchMove() \n";}
        virtual void touchEnd(Touch* t){ std::cout << this << " View::touchEnd() \n";}
        
        virtual void keyPressed(Touch* t){ std::cout << this << "Layer::keyPressed() \n";}
        virtual void keyReleased(Touch* t){ std::cout << this << "Layer::keyReleased() \n";}
    };
    
    class Client{
    public:
        void run()
        {
            Touch t(Point(1,2,3));
            Layer l1;
            Layer l2;
            
            Director::get()->getTouchDispatcher()->fireTouchBegin(&t);
            Director::get()->getTouchDispatcher()->fireTouchMove(&t);
            Director::get()->getTouchDispatcher()->fireTouchMove(&t);
            Director::get()->getTouchDispatcher()->fireTouchEnd(&t);
            
            Director::get()->getKeyboardDispatcher()->fireKeyPressed(&t);
            Director::get()->getKeyboardDispatcher()->fireKeyReleased(&t);
            
        }
    };
}

#endif /* defined(__TestPattens__Events4__) */
