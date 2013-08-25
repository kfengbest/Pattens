//
//  Flyweight.h
//  TestPattens
//
//  Created by Kaven Feng on 8/25/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Flyweight__
#define __TestPattens__Flyweight__

#include <iostream>
#include <map>
#include <memory>
namespace Flyweight1 {
    
    enum TowerType{
        eUnknow = 0,
        eStar,
        eSun,
        eIce,
        eRain,
        eFire,
        eStone,
        eShit,
        eIron
    };
    
    enum Grade{
        eGrade1 = 1,
        eGrade2,
        eGrade3,
        eGradeMax
    };
    
    class TowerConfig;
    typedef std::shared_ptr<TowerConfig> TowerConfigPtr;
    typedef std::map<TowerType, TowerConfigPtr> TowerConfigMap;
    
    class TowerConfig{
        
    public:
        virtual ~TowerConfig(){
            std::cout << "~TowerConfig \n";
        }
        // flyweight, using local static map as cache.
        static TowerConfigPtr getConfig(TowerType type)
        {
            static TowerConfigMap towermap;
            auto it = towermap.find(type);
            if (it != towermap.end()) {
                return it->second; 
            }
            
            TowerConfigPtr newTower(new TowerConfig(type));
            towermap[type] = newTower;
            
            std::cout << "New Tower Config " << "total towers:" << towermap.size() << std::endl;
            
            return newTower;
        }
        
        void dump(){

            std::cout << "Tower Config: " << "type: " << mType << "Icon: " << mIcon << "Grade: " << mGrade << "price: " << mPrice[mGrade] << "mDamage: " << mDamage[mGrade] << std::endl;
        }
        
    private:
        TowerConfig(TowerType type) : mType(type), mGrade(eGrade1){
            std::cout << "TowerConfig \n";

            // load tower config.
            mIcon = "icon";
            for (int i = eGrade1; i < eGradeMax; i++) {
                mPrice[i] = 100 + i;
                mDamage[i] = 200 + i;
            }
        } 
        
    public:
        TowerType mType;
        std::string mIcon;
        float mPrice[eGradeMax];
        float mDamage[eGradeMax];
        Grade mGrade;
    };
    
    class Tower{
    public:
        Tower(TowerType t){
            
        }
    };
    
    class Client{
    public:
        void run()
        {
            TowerConfigPtr t1 = TowerConfig::getConfig(eSun);
            t1->dump();
            
            TowerConfigPtr t2 = TowerConfig::getConfig(eFire);
            t2->dump();
            
            TowerConfigPtr t3 = TowerConfig::getConfig(eSun);
            t3->dump();
            
        }
    };
    
}

#endif /* defined(__TestPattens__Flyweight__) */
