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
#include "SimpleFactory.h"
#include "FactoryMethod.h"
#include "AbstractFactory.h"
#include "Events1.h"
#include "Strategy2.h"
#include "Flyweight.h"
#include "Interfaces1.h"


int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "\n ===test Visitor1\n";
    Visitor1::Client c1;
    c1.buildObjects();
    c1.save();

    std::cout << "\n ===test Prototype1 \n";
    Prototype1::Client pc;
    pc.run();
    
    std::cout << "\n ===test SmartPointer1 \n";
    SmartPointer1::Client sc;
    sc.run();
    
    std::cout << "\n ===test Strategy1 \n";
    Strategy1::Client stc;
    stc.run();
    
    std::cout << "\n ===test Strategy2 \n";
    Strategy2::Client stc2;
    stc2.run();
    
    std::cout << "\n ===test SimpleFactory1 \n";
    SimpleFactory1::Client sf1c;
    sf1c.run();
    
    std::cout << "\n ===test SimpleFactory2 \n";
    SimpleFactory2::Client sf2c;
    sf2c.run();
    
    std::cout << "\n ===test Events1 \n";
    Events1::Client dc;
    dc.run();
    
    std::cout << "\n ===test Flyweight \n";
    Flyweight1::Client fwc;
    fwc.run();

    std::cout << "\n ===test Interfaces \n";
    Interfaces1::Client itf1;
    itf1.run();
    
    return 0;
}

