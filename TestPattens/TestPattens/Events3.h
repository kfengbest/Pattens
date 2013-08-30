//
//  Events3.h
//  TestPattens
//
//  Created by Kaven Feng on 8/25/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#ifndef __TestPattens__Events3__
#define __TestPattens__Events3__

#include <vector>
#include <iostream>

// Neturon Events.

namespace Event3 {
    
    class Event{
        
    };
    
    class EventSite{
    public:
        virtual ~EventSite(){}
    };
    
    class EventSource{
        typedef std::vector<EventSite*> EventSites;
        
    protected:
        EventSource(){}
        
    protected:
        void subscribe(EventSite* pSite);
        void unsubscribe(EventSite* pSite);

    public:
        template<typename TEventSite, typename TEvent>
        inline void fireEvent(void(TEventSite::*fire)(TEvent* event), TEvent* event)
        {
            std::for_each(m_eventSites.begin(), m_eventSites.end(), [&](EventSite* pSite){
                TEventSite* appSite = dynamic_cast<TEventSite*>(pSite);
                (appSite->*fire)(event);
            });
        }
                
    private:
        EventSites m_eventSites;
    };
    
    class TouchEvent : public Event{
        
    };
    
    class TouchEventSite : public EventSite{
    public:
        virtual void onTouchBegin(TouchEvent* pEvent){ std::cout << "EventSite1::onTouchBegin \n";}
        virtual void onTouchMove(TouchEvent* pEvent){ std::cout << "EventSite1::onTouchMove \n";}
        virtual void onTouchEnd(TouchEvent* pEvent){ std::cout << "EventSite1::onTouchEnd \n";}

    };
    
    class TouchEventSource : public EventSource{
    public:
        void subscribe(TouchEventSite* pSite){ EventSource::subscribe(pSite);}
        void unsubscribe(TouchEventSite* pSite) {EventSource::unsubscribe(pSite);}
        
        static TouchEventSource* get(){
            static TouchEventSource theOnlyOne;
            return &theOnlyOne;
        }
        
        void fireTouchBegin(TouchEvent* e){ EventSource::fireEvent(&TouchEventSite::onTouchBegin, e);}
        void fireTouchMove(TouchEvent* e){ EventSource::fireEvent(&TouchEventSite::onTouchMove, e);}
        void fireTouchEnd(TouchEvent* e){ EventSource::fireEvent(&TouchEventSite::onTouchEnd, e);}
    };
    
    class Window : public TouchEventSite{
    public:
        void begin(){TouchEventSource::get()->subscribe(this);}
        void end(){TouchEventSource::get()->unsubscribe(this);}
        
        virtual void onTouchBegin(TouchEvent* pEvent){ std::cout << "Window::onTouchBegin \n";}
        virtual void onTouchMove(TouchEvent* pEvent){ std::cout << "Window::onTouchMove \n";}
        virtual void onTouchEnd(TouchEvent* pEvent){ std::cout << "Window::onTouchEnd \n";}
    };
    
    class Client{
    public:
        void run()
        {
            Window w1;
            w1.begin();
            
            Window w2;
            w2.begin();
            
            TouchEvent e;
            TouchEventSource::get()->fireTouchBegin(&e);
            TouchEventSource::get()->fireTouchMove(&e);
            TouchEventSource::get()->fireTouchMove(&e);
            TouchEventSource::get()->fireTouchEnd(&e);
        }
    };
    
}

#endif /* defined(__TestPattens__Events3__) */
