//
//  Interfaces2.h
//  TestPattens
//
//  Created by Kaven Feng on 8/27/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Interfaces2__
#define __TestPattens__Interfaces2__

#include <iostream>
#include <type_traits>

namespace Interfaces2 {
    
    // The type id is the drawback of this solution.
    // We have to change this enum everytime we introduced a new Class.
    // This is not extensible as a framework.
    enum EIds{
        eInterface = 0,
        eObject,
        eAnimal,
        ePerson
    };
    
    class InterfaceID{
    public:
        virtual ~InterfaceID() {}
        
        virtual void* GetInterface(int tag) = 0;
    };
    
#define DECLARE_INTERFACE_ID()\
public:\
	static int InterfaceID();\
    virtual void* GetInterface(int) override
    
#define DEFINE_INTERFACE_ID(parentCls,cls,tag)\
	int cls::InterfaceID()\
	{\
		return tag;\
	}\
	void* cls::GetInterface(int t)\
	{\
		if (InterfaceID() == t)\
			return this;\
		return parentCls::GetInterface(t); \
	}
    
    template <typename T, typename S>
    inline bool IsType(S* st){
        static_assert(std::is_convertible<S*, InterfaceID*>::value,"type S must inherited from Interface!");
        static_assert(std::is_convertible<T*, InterfaceID*>::value,"type T must inherited from Interface!");
        return st->GetInterface(T::InterfaceID()) != nullptr;
    }
    
    template <typename T, typename S>
    inline T* CastInterface(S* st){
        static_assert(std::is_convertible<S*, InterfaceID*>::value,"type S must inherited from Interface!");
        static_assert(std::is_convertible<T*, InterfaceID*>::value,"type T must inherited from Interface!");
        return (T*)st->GetInterface(T::InterfaceID());
    }
    
/////////////////////////////////////////////////
    
    class Item : public InterfaceID{
    public:
        static int InterfaceID(){return eObject;}
        virtual void* GetInterface(int tag) override {
            if (tag == Item::InterfaceID()) {
                return this;
            }else{
                return InterfaceID::GetInterface(tag);
            }
        }
    };

    class Object : public InterfaceID{
        DECLARE_INTERFACE_ID();
        
    public:
        virtual ~Object(){}
        void ObjectMethod();
    };
    
    class Animal : public Object{
        DECLARE_INTERFACE_ID();
        
    public:
        virtual ~Animal(){}
        void AnimalMethod();
    };
    
    class Person : public Animal{
        DECLARE_INTERFACE_ID();
        
    public:
        virtual ~Person(){}
        void PersonMethod();
    };
    
    class Client{
      
    public:
        void run(){
            Animal* pAni = new Animal;
            pAni->AnimalMethod();
            
            Object* pObj = pAni;
            std::cout << "pObj is type of Animal? " << IsType<Animal>(pObj) << std::endl;;
            
            Animal* pAni2 = CastInterface<Animal>(pObj);  // true;
            if (pAni2) {
                pAni2->AnimalMethod();
            }
            
            std::cout << "pObj is type of Animal? " << IsType<Person>(pObj) << std::endl;  // false;
            Person* pPer = CastInterface<Person>(pObj);
            if (pPer) { // pPer should be nullptr;
                pPer->PersonMethod();     
            }
            
            delete pAni;
        }
    };
    
}

#endif /* defined(__TestPattens__Interfaces2__) */
