//
//  Interfaces3.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/27/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include "Interfaces3.h"

using namespace Interfaces3;

UniqueString::UniqueStrings UniqueString::s_uniqueStrings;


const UniqueString*
Object::interfaceId()
{
	static const UniqueString* s_id = UniqueString::find("Object");
	return s_id;
}

void*
Object::queryInterface(const UniqueString* id)
{
	if (id == Object::interfaceId()) {
		return static_cast<Object*>(this);
	} else {
		return NULL;
	}
}

const UniqueString* UniqueString::interfaceId()
{
    static const UniqueString* s_id = UniqueString::find("UniqueString");
	return s_id;
}

void* UniqueString::queryInterface(const UniqueString* id)
{
    if (id == UniqueString::interfaceId()) {
		return static_cast<UniqueString*>(this);
	} else if (void* pInterface = Object::queryInterface(id)) {
		return pInterface;
	} else {
		return NULL;
	}
}

UniqueString*
UniqueString::find(const std::string& theName, bool bCreateIfNotFound)
{
    auto a = s_uniqueStrings.find(theName);
	if (a != s_uniqueStrings.end())
		return a->second.get();
	
	if (!bCreateIfNotFound)
		return NULL;

    UniqueString* pRet = new UniqueString(theName);
    s_uniqueStrings[theName] = UniqueStringPtr(pRet);
    
	return pRet;
}

const UniqueString*
Animal::interfaceId()
{
	static const UniqueString* s_id = UniqueString::find("Animal");
	return s_id;
}

void*
Animal::queryInterface(const UniqueString* id)
{
    if (id == Animal::interfaceId()) {
		return static_cast<Animal*>(this);
	} else if (void* pInterface = Object::queryInterface(id)) {
		return pInterface;
	} else {
		return NULL;
	}
}

const UniqueString*
Person::interfaceId()
{
	static const UniqueString* s_id = UniqueString::find("Person");
	return s_id;
}

void*
Person::queryInterface(const UniqueString* id)
{
    if (id == Person::interfaceId()) {
		return static_cast<Person*>(this);
	} else if (void* pInterface = Animal::queryInterface(id)) {
		return pInterface;
	} else {
		return NULL;
	}
}