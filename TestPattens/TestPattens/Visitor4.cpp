//
//  Visitor4.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/31/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include "Visitor4.h"

using namespace Visitor4;

void Visitor::onVisit(Area* pArea)
{
    std::cout << "Visitor::onVisit " << pArea->name() << std::endl;
}

void Visitor::onPush(Area* pArea)
{
}

void Visitor::onPop(Area* pArea)
{
}