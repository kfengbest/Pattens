//
//  FactoryMethod.h
//  TestPattens
//
//  Created by Kaven Feng on 8/24/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__FactoryMethod__
#define __TestPattens__FactoryMethod__

#include <iostream>
#include <memory>

namespace FactoryMethod1 {
    
    class Command;
    class CommandDef;

    class Command{
        
    private:
        CommandDef* mCmdDef;
    };
    
    class CommandDef{
    
    public:
        Command* createCommand();
    
    protected:
        virtual Command* onCreateCommand();
        
    };
    
    class CommandDefMgr{
        
    };
    
    class CommandMgr{
    public:
        void execute(const std::string& cmdId)
        {
            
        }
    };
    
    class Client{
        
    };
}

#endif /* defined(__TestPattens__FactoryMethod__) */
