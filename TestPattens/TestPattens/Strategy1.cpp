//
//  Strategy1.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/24/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include "Strategy1.h"

using namespace Strategy1;

////
Tool::Tool(const std::string& toolId)
: mToolId(toolId)
{
}

Tool::~Tool()
{
    
}

const std::string& Tool::toolId() const
{
    return mToolId;
}

void Tool::begin()
{
    
}

void Tool::end()
{
    
}

void Tool::touchBegin(const Point& point)
{
    this->onTouchBegin(point);
}

void Tool::touchMove(const Point& point)
{
    this->onTouchMove(point);
}

void Tool::touchEnd(const Point& point)
{
    this->onTouchEnd(point);
}


////
ToolMgr::ToolMgr()
: mActiveTool(nullptr)
{
}

ToolMgr::~ToolMgr()
{
    
}

ToolMgr* ToolMgr::get()
{
    static ToolMgr s_theOnlyOne;
    return &s_theOnlyOne;
}

void ToolMgr::registerTool(const ToolPtr& tool)
{
    mTools[tool->toolId()] = tool;
}


void ToolMgr::switchTool(const std::string& toolId)
{
    // init the default tool;
    if (mActiveTool == nullptr) {
        auto it = mTools.find(toolId);
        mActiveTool = it->second;
        mActiveTool->begin();
        return;
    }
    
    // tool strategy
    ToolPtr newTool = findTool(toolId);
    if (newTool->toolId() != activeTool()->toolId()) {
        mActiveTool->end();
        mActiveTool = newTool;
        newTool->begin();
    }
}

const ToolPtr& ToolMgr::activeTool() const
{
    return mActiveTool;
}

ToolPtr ToolMgr::findTool(const std::string& toolId) const
{
    auto it = mTools.find(toolId);
    return it->second;
}

void ToolMgr::touchBegin(const Point& point)
{
    mActiveTool->touchBegin(point);
}

void ToolMgr::touchMove(const Point& point)
{
    mActiveTool->touchMove(point);
}
void ToolMgr::touchEnd(const Point& point)
{
    mActiveTool->touchEnd(point);
}

////
void View::onTouchBegin(const Point& point)
{
    ToolMgr::get()->touchBegin(point);
}

void View::onTouchMove(const Point& point)
{
    ToolMgr::get()->touchMove(point);
}
void View::onTouchEnd(const Point& point)
{
    ToolMgr::get()->touchEnd(point);
}

void Client::run()
{
    View v;
    
    ToolPtr line(new LineTool);
    ToolPtr rect(new RectangleTool);
    ToolPtr circle(new CircleTool);
    ToolMgr::get()->registerTool(line);
    ToolMgr::get()->registerTool(rect);
    ToolMgr::get()->registerTool(circle);
    
    // switch tool.
    ToolMgr::get()->switchTool(line->toolId());
    
    // UI simulation
    v.onTouchBegin(Point(1,1));
    v.onTouchMove(Point(1,2));
    v.onTouchMove(Point(1,3));
    v.onTouchBegin(Point(1,5));
    
    ToolMgr::get()->switchTool(rect->toolId());
    v.onTouchBegin(Point(10,1));
    v.onTouchMove(Point(10,2));
    v.onTouchMove(Point(10,3));
    v.onTouchBegin(Point(10,5));
    
    ToolMgr::get()->switchTool(circle->toolId());
    v.onTouchBegin(Point(100,1));
    v.onTouchMove(Point(100,2));
    v.onTouchMove(Point(100,3));
    v.onTouchBegin(Point(100,5));
}

///
void LineTool::onTouchBegin(const Point& point)
{
    std::cout << "LineTool::onTouchBegin" << std::endl;
}

void LineTool::onTouchMove(const Point& point)
{
    std::cout << "LineTool::onTouchMove" << std::endl;
}

void LineTool::onTouchEnd(const Point& point)
{
    std::cout << "LineTool::onTouchMove" << std::endl;
}

///
void RectangleTool::onTouchBegin(const Point& point)
{
    std::cout << "RectangleTool::onTouchBegin" << std::endl;
}

void RectangleTool::onTouchMove(const Point& point)
{
    std::cout << "RectangleTool::onTouchMove" << std::endl;
}

void RectangleTool::onTouchEnd(const Point& point)
{
    std::cout << "RectangleTool::onTouchMove" << std::endl;
}

///
void CircleTool::onTouchBegin(const Point& point)
{
    std::cout << "CircleTool::onTouchBegin" << std::endl;
}

void CircleTool::onTouchMove(const Point& point)
{
    std::cout << "CircleTool::onTouchMove" << std::endl;
}

void CircleTool::onTouchEnd(const Point& point)
{
    std::cout << "CircleTool::onTouchMove" << std::endl;
}

