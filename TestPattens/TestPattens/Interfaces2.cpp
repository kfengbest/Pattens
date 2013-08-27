//
//  Interfaces2.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/27/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include "Interfaces2.h"

using namespace Interfaces2;

void* InterfaceID::GetInterface(int tag)
{
    return nullptr;
}

DEFINE_INTERFACE_ID(InterfaceID, Object, eObject)

void Object::ObjectMethod(){
    std::cout << "Object::ObjectMethod() \n";
}


DEFINE_INTERFACE_ID(Object, Animal, eObject)

void Animal::AnimalMethod(){
    std::cout << "Animal::AnimalMethod() \n";
}

DEFINE_INTERFACE_ID(Animal, Person, ePerson)

void Person::PersonMethod(){
    std::cout << "Person::PersonMethod() \n";
}
