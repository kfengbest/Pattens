//
//  main.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/18/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include <iostream>
#include "Visitor1.h"
#include "Visitor2.h"
#include "Visitor3.h"
#include "Visitor4.h"
#include "Prototype1.h"
#include "SmarterPoint.h"
#include "Strategy1.h"
#include "Strategy2.h"
#include "Strategy3.h"
#include "SimpleFactory.h"
#include "FactoryMethod.h"
#include "AbstractFactory.h"
#include "Events1.h"
#include "Events2.h"
#include "Events3.h"
#include "Events4.h"
#include "Flyweight.h"
#include "Interfaces1.h"
#include "Interfaces2.h"
#include "Interfaces3.h"
#include "Compositor1.h"
#include "Decorator1.h"
#include "Adaptor1.h"



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

//    std::cout << "\n ===test Interfaces1 \n";
//    Interfaces1::Client itf1;
//    itf1.run();
    
    std::cout << "\n ===test Interfaces2 \n";
    Interfaces2::Client itf2;
    itf2.run();
    
    std::cout << "\n ===test Interfaces3 \n";
    Interfaces3::Client itf3;
    itf3.run();
    
    std::cout << "\n ===test Visitor2::V1 \n";
    Visitor2::V1::Client vzc2;
    vzc2.run();
    
    std::cout << "\n ===test Visitor2::V2 \n";
    Visitor2::V2::Client vzcv2;
    vzcv2.run();
    
    
    std::cout << "\n ===test Compositor1 \n";
    Compositor1::Client comv1;
    comv1.run();
    
    std::cout << "\n ===test Visitor3 \n";
    Visitor3::Client vz3;
    vz3.run();

    std::cout << "\n ===test Decorator1 \n";
    Decorator1::Client dcc1;
    dcc1.run();
    
    std::cout << "\n ===test Event2 \n";
    Event3::Client ev3;
    ev3.run();
    
    std::cout << "\n ===test Visitor4 \n";
    Visitor4::Client viz4;
    viz4.run();

    std::cout << "\n ===test Adaptor1 \n";
    Adaptor1::Client adt1;
    adt1.run();

    std::cout << "\n ===test Stategy2 \n";
    Strategy3::Client st3;
    st3.run();
    
    std::cout << "\n ===test Event4 \n";
    Events4::Client ev4;
    ev4.run();
    
    return 0;
}

