//
//  Interfaces3.h
//  TestPattens
//
//  Created by Kaven Feng on 8/27/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Interfaces3__
#define __TestPattens__Interfaces3__

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <chrono>

// The improvement of Interfaces2.
// Use unique string instead of the unsigned int as ID.
// 

// Further improvement:
// 1. Using multi-thread.
// 2. Using macro.

namespace Interfaces3 {

    class Object;
    class UniqueString;

    class Object{
    public:
        // Every interface must declare the  following static function.  When
		// querying for interfaces, always use the static interfaceId()
		// function since comparisons are done by pointer-value not string.
        static const UniqueString* interfaceId();
        
        // Derived classes must override this method and forward the query on
		// to all the base classes so they have a chance to respond.
		virtual void* queryInterface(const UniqueString* id);
        
        // Simple query...
		template <class T>
		T* query()
		{
			void* pIf = this->queryInterface(T::interfaceId());
			if (pIf == NULL)
				return NULL;
			else
				return static_cast<T*>(pIf);
		}
    };
    
    class UniqueString : public Object{
    private:
        // we don't allow this staff.
        UniqueString(const UniqueString&);
        UniqueString& operator=(const UniqueString& rhs);
        
    public:
        virtual ~UniqueString(){}
        
    public:
        static const UniqueString* interfaceId();
		virtual void* queryInterface(const UniqueString* id);
        
        // Find the unique string object by the name.
		// The return value can be NULL if not found,
		// But it can create one if the bCreateIfNotFound is true.
		static UniqueString* find(const std::string& theName, bool bCreateIfNotFound = true);
        
    protected:
        UniqueString(const std::string& theName) : m_name(theName) {}
        
    private:
        std::string m_name;
        typedef std::shared_ptr<UniqueString> UniqueStringPtr;
		typedef std::map<std::string, UniqueStringPtr> UniqueStrings;
		static UniqueStrings s_uniqueStrings;

    };
    
    // This form is available so that we can go from an
	// interface (that does not derive from Object,
	// and hence does not necessarily have "query" defined
	// inside it to) to all the other interfaces.
	template <class T, class CLS>
	inline T* QueryInterface(CLS* pCLS)
	{
		void* pIf = pCLS->queryInterface(T::interfaceId());
		if (pIf == NULL)
			return NULL;
		else
			return static_cast<T*>(pIf);
	}
    
    
    ///////////////////////////////////////////////////////
    
    class Animal: public Object{
    public:
        static const UniqueString* interfaceId();
		virtual void* queryInterface(const UniqueString* id);
        
        virtual void Dump(){}
        void AnimalMethod(){ std::cout << "Animal::AnimalMethod() \n";}
    };
    
    class Person : public Animal{
    public:
        static const UniqueString* interfaceId();
		virtual void* queryInterface(const UniqueString* id);
        
        void PersonMethod(){ std::cout << "Person::PersonMethod() \n";}
    };
    
    class Client{
    public:
        void run()
        {
            Person* pPer = new Person;            
            Object* pObj = pPer;
            
            Person* pPer1 = pObj->query<Person>();
            if (pPer1) {
                pPer1->PersonMethod();  // Should be fine.
            }
            
            Person* pPer2 = QueryInterface<Person>(pObj);
            if (pPer2) {
                pPer2->PersonMethod();  // Should be fine.
            }
            
            Animal* pAni1 = QueryInterface<Animal>(pObj);
            if (pAni1) {
                pAni1->AnimalMethod();  // Should be fine.
            }
            
            Animal* pAni = new Animal;
            pObj = pAni;
            
            Person* pPer3 = pObj->query<Person>();
            if (pPer3) {
                pPer3->PersonMethod();  // Shouldn't be called!
            }
            
            Person* pPer4 = QueryInterface<Person>(pObj);
            if (pPer4) {
                pPer4->PersonMethod();  // Shouldn't be called!
            }

            pObj = pPer;
            //PerformanceTest(pObj);
           
            delete pAni;
            delete pPer;
        }
        
        void PerformanceTest(Object* pObj2)
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
                    Person* pPer6 = pObj2->query<Person>();
                    if (pPer6 != nullptr) {
                        pPer6->Dump();
                    }
                }
            }
            t_end = std::chrono::high_resolution_clock::now();
            std::cout << "query<Person>: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
            << " ms\n";
            
            
            t_start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++)
                {
                    Person* pPer6 = QueryInterface<Person>(pObj2);
                    if (pPer6 != nullptr) {
                        pPer6->Dump();
                    }
                }
            }
            t_end = std::chrono::high_resolution_clock::now();
            std::cout << "QueryInterface<Person>: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
            << " ms\n";
        }
    };
}

#endif /* defined(__TestPattens__Interfaces3__) */
