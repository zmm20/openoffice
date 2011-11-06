/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef EVENT_EVENT_HXX
#define EVENT_EVENT_HXX

#include <sal/types.h>

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/xml/dom/events/XEvent.hpp>
#include <com/sun/star/xml/dom/events/XEventTarget.hpp>
#include <com/sun/star/util/Time.hpp>

#include <cppuhelper/implbase1.hxx>

#include "../dom/node.hxx"


using namespace com::sun::star::uno;
using namespace com::sun::star::xml::dom;
using namespace com::sun::star::xml::dom::events;


namespace DOM {namespace events
{
class CEvent : public cppu::WeakImplHelper1< XEvent >
{
friend class CEventDispatcher;

protected:
    ::osl::Mutex m_Mutex;
    sal_Bool m_canceled;
    OUString m_eventType;
    Reference< XEventTarget > m_target;
    Reference< XEventTarget > m_currentTarget;
    PhaseType m_phase;
    sal_Bool m_bubbles;
    sal_Bool m_cancelable;
    com::sun::star::util::Time m_time;

public:

    explicit CEvent();

    virtual ~CEvent();
    virtual OUString SAL_CALL getType() throw (RuntimeException);
    virtual Reference< XEventTarget > SAL_CALL getTarget() throw (RuntimeException);
    virtual Reference< XEventTarget > SAL_CALL getCurrentTarget() throw (RuntimeException);
    virtual PhaseType SAL_CALL getEventPhase() throw (RuntimeException);
    virtual sal_Bool SAL_CALL getBubbles() throw (RuntimeException);
    virtual sal_Bool SAL_CALL getCancelable() throw (RuntimeException);
    virtual com::sun::star::util::Time SAL_CALL getTimeStamp() throw (RuntimeException);
    virtual void SAL_CALL stopPropagation() throw (RuntimeException);
    virtual void SAL_CALL preventDefault() throw (RuntimeException);
    virtual void SAL_CALL initEvent(
        const OUString& eventTypeArg,
        sal_Bool canBubbleArg,
        sal_Bool cancelableArg)  throw (RuntimeException);
};
}}
#endif
