//
//  OGS.h
//  TestPattens
//
//  Created by Kaven Feng on 8/25/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__OGS__
#define __TestPattens__OGS__

#include <iostream>

namespace Devices {
    class RenderItem{
        
    };
}

namespace Graphics {
    class Node{
        
    };
    
    class Agent{
    public:
        
    };
    
    class Stage{
        
    };
}

namespace Objects {

    typedef Graphics::Node World;
    
    enum EChangePacketType{
        eNone = 0,
        eAddItem = 0x4000,
        eRemoveItem = 0x8000,
        eShow = 0x0001,
        eHide = 0x0002,
        eSelected = 0x0004,
        eUnSelected = 0x0008
    };
    
    class ChangePacket{
    public:
        ChangePacket(Graphics::Node* pNode) : mNode(pNode){}
        virtual ~ChangePacket() {}
        
        EChangePacketType changeType() const {return mChangeType;}
        void changeType(EChangePacketType type) {mChangeType = type;}
        
        virtual Graphics::Node* getNode() const { return mNode;}
        
        virtual bool updateNode() { return true;}
        ChangePacket* mergeChanges(ChangePacket* newChanges) {return newChanges;}
        
    private:
        EChangePacketType mChangeType;
        Graphics::Node* mNode;
    };
    
    class ObjectManager{
    public:
        // Add a node to world.Can be call at anytime from any thread. Deffed handling is taking care by object manager.
        virtual void addNode(Graphics::Node* node){}
        
        // Remove a node from world.Can be call at anytime from any thread. Deffed handling is taking care by object manager.
        virtual void removeNode(Graphics::Node* node){}
        
        // Signal that a node has changed. pass in a change packet to describe the change.
        virtual void nodeChanged(ChangePacket* package){}
        
        // Update the world at the beginning of the frame Sync all pending changes.
        virtual void syncChanges(){}
        
        virtual Graphics::Node* world() const { return nullptr;}
        virtual void world(Graphics::Node* node){}
        
    private:
        Graphics::Node* mWorld;
    };
}

namespace OgsClient {
    
}


#endif /* defined(__TestPattens__OGS__) */
