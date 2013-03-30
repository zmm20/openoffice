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

#ifndef _SC_SIDEBAR_CELL_LINE_STYLE_POPUP_HXX_
#define _SC_SIDEBAR_CELL_LINE_STYLE_POPUP_HXX_

#include <svx/sidebar/Popup.hxx>
#include <boost/function.hpp>

namespace sc { namespace sidebar {

class CellLineStylePopup : public svx::sidebar::Popup
{
public :
    CellLineStylePopup(
        Window* pParent,
        const ::boost::function<svx::sidebar::PopupControl*(svx::sidebar::PopupContainer*)>& rControlCreator);
    virtual ~CellLineStylePopup(void);

    void SetLineStyleSelect(sal_uInt16 out, sal_uInt16 in, sal_uInt16 dis);
};

} } // end of namespace sc::sidebar

#endif // _SC_SIDEBAR_CELL_LINE_STYLE_POPUP_HXX_

// eof
