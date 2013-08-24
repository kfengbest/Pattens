//
//  Strategy1.h
//  TestPattens
//
//  Created by Kaven Feng on 8/24/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Strategy1__
#define __TestPattens__Strategy1__

#include <iostream>
#include <memory>
#include <map>

namespace Strategy1 {
    
    class Point;
    class Command;
    class CommandMgr;
    class View;
    
    class Point{
    public:
        Point(float x, float y)
        : mX(x), mY(y)
        {}
        
        float mX;
        float mY;
    };
    
    class Tool
    {
        friend class ToolMgr;
        
    public:
        Tool(const std::string& toolId);
        virtual ~Tool();
        
        const std::string& toolId() const;
        
        // Template Method
        void touchBegin(const Point& point);
        void touchMove(const Point& point);
        void touchEnd(const Point& point);
    
    protected:
        virtual void onTouchBegin(const Point& point) = 0;
        virtual void onTouchMove(const Point& point) = 0;
        virtual void onTouchEnd(const Point& point) = 0;
    
    private:
        void begin();
        void end();
        
    private:
        std::string mToolId;
    };
    
    typedef std::shared_ptr<Tool> ToolPtr;
    typedef std::map<std::string, ToolPtr> ToolsMap;
    typedef std::map<std::string, ToolPtr>::iterator ToolMapItr;
    
    class ToolMgr{
        
    public:
        virtual ~ToolMgr();
        
        // Singleton
        static ToolMgr* get();
        
        // Strategy
        void switchTool(const std::string& toolId);
        
        void registerTool(const ToolPtr& tool);
        const ToolPtr& activeTool() const;
        ToolPtr findTool(const std::string& toolId) const;
        
        void touchBegin(const Point& point);
        void touchMove(const Point& point);
        void touchEnd(const Point& point);
        
    private:
        ToolMgr();
        
    private:
        ToolsMap mTools;
        ToolPtr mActiveTool;
    };
    
    
    class View{
    public:
    
        // inherited from view
        virtual void onTouchBegin(const Point& point) ;
        virtual void onTouchMove(const Point& point) ;
        virtual void onTouchEnd(const Point& point) ;
    
    };
   
    class Client
    {
    public:
        void start();
    };
    
    //
    class LineTool : public Tool{
    public:
        LineTool(): Tool("LineTool"){}
        ~LineTool(){};
    
    protected:
        virtual void onTouchBegin(const Point& point) override;
        virtual void onTouchMove(const Point& point) override;
        virtual void onTouchEnd(const Point& point) override;
    };
    
    class RectangleTool : public Tool{
    public:
        RectangleTool(): Tool("RectangleTool"){}
        ~RectangleTool(){}
        
    protected:
        virtual void onTouchBegin(const Point& point) override;
        virtual void onTouchMove(const Point& point) override;
        virtual void onTouchEnd(const Point& point) override;
    };
    
    class CircleTool : public Tool{
    public:
        CircleTool(): Tool("CircleTool"){}
        ~CircleTool(){}
        
    protected:
        virtual void onTouchBegin(const Point& point) override;
        virtual void onTouchMove(const Point& point) override;
        virtual void onTouchEnd(const Point& point) override;
    };
    
}

#endif /* defined(__TestPattens__Strategy1__) */
