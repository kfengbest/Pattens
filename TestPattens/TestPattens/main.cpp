//
//  main.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/18/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include <iostream>
#include "Visitor1.h"
#include "Prototype1.h"
#include "SmarterPoint.h"
#include "Strategy1.h"


int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    
    Visitor1::Client c1;
    c1.buildObjects();
    c1.save();

    std::cout << "test Prototype1 \n";
    Prototype1::Client pc;
    pc.start();
    
    std::cout << "test SmartPointer1 \n";
    SmartPointer1::Client sc;
    sc.start();
    
    std::cout << "test Strategy1 \n";
    Strategy1::Client stc;
    stc.start();
    
    return 0;
}

