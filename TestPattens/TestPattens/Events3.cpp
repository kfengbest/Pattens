//
//  Events3.cpp
//  TestPattens
//
//  Created by Kaven Feng on 8/25/13.
//  Copyright (c) 2013 Kaven Feng. All rights reserved.
//

#include "Events3.h"

using namespace Event3;

void EventSource::subscribe(EventSite* pSite)
{
    m_eventSites.push_back(pSite);
}

void EventSource::unsubscribe(EventSite* pSite)
{
    auto it = std::find(m_eventSites.begin(), m_eventSites.end(), pSite);
    if (it != m_eventSites.end()) {
        m_eventSites.erase(it);
    }
}

