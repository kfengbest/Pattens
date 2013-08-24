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


int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "\n test Visitor1\n";
    Visitor1::Client c1;
    c1.buildObjects();
    c1.save();

    std::cout << "\n test Prototype1 \n";
    Prototype1::Client pc;
    pc.start();
    
    std::cout << "\n test SmartPointer1 \n";
    SmartPointer1::Client sc;
    sc.start();
    
    std::cout << "\n test Strategy1 \n";
    Strategy1::Client stc;
    stc.start();
    
    std::cout << "\n test SimpleFactory1 \n";
    SimpleFactory1::Client sf1c;
    sf1c.start();
    
    std::cout << "\n test SimpleFactory2 \n";
    SimpleFactory2::Client sf2c;
    sf2c.start();
    
    return 0;
}

