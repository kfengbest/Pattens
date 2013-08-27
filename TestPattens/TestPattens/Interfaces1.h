//
//  Interfaces1.h
//  TestPattens
//
//  Created by Kaven Feng on 8/27/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Interfaces1__
#define __TestPattens__Interfaces1__

#include <iostream>
#include <chrono>

namespace Interfaces1 {
    
    enum EIds{
        eInterface = 0,
        eObject,
        eAnimal,
        ePerson
    };
    
    class InterfaceID{
    public:
        static int interfaceID() { return eInterface;}
        virtual ~InterfaceID(){}
        virtual void* getInterface(int tag) { return nullptr;}  // Must return nullptr!
    };
    
    class Object : public InterfaceID{
    public:
        virtual ~Object(){}
        
        static int interfaceID() { return eObject;}
        virtual void* getInterface(int tag) override
        {
            if (tag == Object::interfaceID()) {
                return this;
            }
            else{
                return InterfaceID::getInterface(tag);
            }
        }
        virtual void Dump(){}
        virtual void Print() { std::cout << "Object::Print \n"; }
        void ObjectMethod() {std::cout << "Object::ObjectMethod \n"; }
        
    };
    
    class Animal : public Object{
    public:
        virtual ~Animal(){}
        
        static int interfaceID() {return eAnimal;}
        virtual void* getInterface(int tag) override
        {
            if (tag == Animal::interfaceID()) {
                return this;
            }else
            {
                return Object::getInterface(tag);
            }
        }

        virtual void Print() { std::cout << "Animal::Print \n"; }
        void AnimalMethod() {std::cout << "Animal::AnimalMethod \n"; }

    };
    
    class Person : public Animal{
    public:
        virtual ~Person(){}
        
        static int interfaceID(){return ePerson;}
        virtual void* getInterface(int tag){
            if (tag == Person::interfaceID()) {
                return this;
            }else{
                return Animal::getInterface(tag);
            }
        }
        
        virtual void Print() { std::cout << "Person::Print \n"; }
        void PersonMethod() {std::cout << "Person::PersonMethod \n"; }
        
    };
    
    template <typename T, typename S>
    inline T* CastInterface(S* object)
    {
        if (!object)
            return nullptr;
        return (T*)object->getInterface(T::interfaceID());
    }
    
    class Client{
    public:
        void run(){
            
            Object* pObj = new Object();
            pObj->ObjectMethod();                   // Object::ObjectMethod. ok.
            
            Animal* pAni = new Animal();
            pAni->Print();                          // Animal::Print. ok.
            
            Person* pPer = new Person();
            
            Object* pObj1 = pAni;                   // No need to cast for this case!
            Object* pObj2 = pPer;
            pObj1->Print();                         // Animal::Print. ok.
            pObj1->Object::Print();                 // Object::Print. ok.
            
            //pObj1->AnimalMethod();                // Compile error, must cast to Animal firstly.
            
            Animal* pAni1 = static_cast<Animal*>(pObj1->getInterface(eAnimal));     // Safe casting. pAni1 != null
            pAni1->AnimalMethod();                  // Animal::AnimalMethod. ok.

            
            Person* pPer2 = static_cast<Person*>(pObj1);  // Unsafe, pPer2 != null
            pPer2->Print();                               // Animal::Print .          Ideally it should be Person::Print
            pPer2->PersonMethod();                        // Person::PersonMethod
            
            Person* pPer3 = (Person*)(pObj1);               // Unsafe. pPer3 != null  .  Result like pPer2
            pPer3->Print();                                 // Animal::Print
            pPer3->PersonMethod();                          // Person::PersonMethod 
            
            Person* pPer4 = dynamic_cast<Person*>(pObj1);   // Safe casting. pPer4 = null; But have performance issue.
            // pPer4->Print();                              // runtime error.
            // pPer4->PersonMethod();                       // runtime error.
            
            Person* pPer5 = static_cast<Person*>(pObj1->getInterface(ePerson));     // Safe casting. pPer1 = null. Performance is good.
            // pPer5->Print();                                                       // runtime error!
            // pPer5->PersonMethod();                                                // runtime error!

            Cast(pPer);
            
            
            /* 50000* 50000 Animal to Object to Person. failed
             dynamic_cast: 34713 ms
             static_cast: 8928 ms
             reinterpret_cast: 9317 ms
             (Person*) cast: 8824 ms
             getInterface using static_cast: 30445 ms
             getInterface using (Person*): 30302 ms
             getInterface using reinterpret_cast: 29880 ms
             */
            
            /* 50000* 50000 in Luobo from Item to Bullet success.
            dynamic_cast: 69172 ms
            static_cast: 809 ms
            reinterpret_cast: 784 ms
            (Person*) cast: 784 ms
            CastInterface : 9283 ms
            */
            
            /* 50000* 50000 Person to Object to Person
             dynamic_cast: 46072 ms
             static_cast: 8623 ms
             reinterpret_cast: 8842 ms
             (Person*) cast: 9003 ms
             getInterface using static_cast: 19667 ms
             
             */
            
            /* 50000* 50000 Person to (Object* obj) to Person
             
             dynamic_cast: 46834 ms
             static_cast: 9029 ms
             reinterpret_cast: 9015 ms
             (Person*) cast: 9026 ms
             getInterface using static_cast: 19689 ms
             
             */
            
            /*
             dynamic_cast: 48455 ms
             static_cast: 9418 ms
             reinterpret_cast: 8687 ms
             (Person*) cast: 8741 ms
             getInterface using static_cast: 19445 ms
             getInterface using (Person*): 19314 ms
             getInterface using reinterpret_cast: 19565 ms
             CastInterface<Person>: 29010 ms
             */
            
            delete pObj;
            delete pAni;
            delete pPer;
        }
        
        void Cast(Object* pObj2)
        {
            int m = 50000;
            int n = 50000;
            
            auto t_start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++)
                {
                    Person* pPer6 = dynamic_cast<Person*>(pObj2);
                    if (pPer6 != nullptr) {
                        pPer6->Dump();
                    }
                }
            }
            auto t_end = std::chrono::high_resolution_clock::now();
            std::cout << "dynamic_cast: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
            << " ms\n";
            
            
            t_start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++)
                {
                    Person* pPer6 = static_cast<Person*>(pObj2);
                    if (pPer6 != nullptr) {
                        pPer6->Dump();
                    }
                }
            }
            t_end = std::chrono::high_resolution_clock::now();
            std::cout << "static_cast: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
            << " ms\n";
            
            t_start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++)
                {
                    Person* pPer6 = reinterpret_cast<Person*>(pObj2);
                    if (pPer6 != nullptr) {
                        pPer6->Dump();
                    }
                }
            }
            t_end = std::chrono::high_resolution_clock::now();
            std::cout << "reinterpret_cast: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
            << " ms\n";
            
            
            t_start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++)
                {
                    Person* pPer6 = (Person*)pObj2;
                    if (pPer6 != nullptr) {
                        pPer6->Dump();
                    }
                }
            }
            t_end = std::chrono::high_resolution_clock::now();
            std::cout << "(Person*) cast: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
            << " ms\n";
            
            
            t_start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++)
                {
                    Person* pPer6 = static_cast<Person*>(pObj2->getInterface(ePerson));
                    if (pPer6 != nullptr) {
                        pPer6->Dump();
                    }
                }
            }
            t_end = std::chrono::high_resolution_clock::now();
            std::cout << "getInterface using static_cast: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
            << " ms\n";
            
            
            t_start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++)
                {
                    Person* pPer6 = (Person*)(pObj2->getInterface(ePerson));
                    if (pPer6 != nullptr) {
                        pPer6->Dump();
                    }
                }
            }
            t_end = std::chrono::high_resolution_clock::now();
            std::cout << "getInterface using (Person*): "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
            << " ms\n";
            
            t_start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++)
                {
                    Person* pPer6 = reinterpret_cast<Person*>(pObj2->getInterface(ePerson));
                    if (pPer6 != nullptr) {
                        pPer6->Dump();
                    }
                }
            }
            t_end = std::chrono::high_resolution_clock::now();
            std::cout << "getInterface using reinterpret_cast: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
            << " ms\n";
            
            
            t_start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++)
                {
                    Person* pPer6 = CastInterface<Person>(pObj2);
                    if (pPer6 != nullptr) {
                        pPer6->Dump();
                    }
                }
            }
            t_end = std::chrono::high_resolution_clock::now();
            std::cout << "CastInterface<Person>: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
            << " ms\n";
            
        }
        
    };
    
    
}


#endif /* defined(__TestPattens__Interfaces1__) */
