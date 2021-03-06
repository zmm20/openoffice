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



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_sc.hxx"



// INCLUDE ---------------------------------------------------------------

#include <svx/svdmark.hxx>
#include <svx/svdview.hxx>
#include <svx/galbrws.hxx>
#include <svx/gallery.hxx>
#include <svx/hlnkitem.hxx>
#include <sfx2/bindings.hxx>
#include <sfx2/request.hxx>
#include <sfx2/viewfrm.hxx>
#include <sfx2/dispatch.hxx>
#include <svl/whiter.hxx>
#include <avmedia/mediaplayer.hxx>

#include "tabvwsh.hxx"
#include "viewdata.hxx"
#include "tabview.hxx"
#include "drwlayer.hxx"
#include "userdat.hxx"
#include "docsh.hxx"

#include <svx/galleryitem.hxx>
#include <com/sun/star/gallery/GalleryItemType.hpp>

// forwards -> imapwrap.cxx (wg. CLOOKs)

class SvxIMapDlg;

sal_uInt16			ScIMapChildWindowId();
SvxIMapDlg*		ScGetIMapDlg();
const void*		ScIMapDlgGetObj( SvxIMapDlg* pDlg );
const ImageMap&	ScIMapDlgGetMap( SvxIMapDlg* pDlg );

//------------------------------------------------------------------

void ScTabViewShell::ExecChildWin(SfxRequest& rReq)
{
	sal_uInt16 nSlot = rReq.GetSlot();
	switch(nSlot)
	{
		case SID_GALLERY:
		{
			SfxViewFrame* pThisFrame = GetViewFrame();
			pThisFrame->ToggleChildWindow( GalleryChildWindow::GetChildWindowId() );
			pThisFrame->GetBindings().Invalidate( SID_GALLERY );
			rReq.Ignore();
		}
		break;
	
		case SID_AVMEDIA_PLAYER:
		{
			SfxViewFrame* pThisFrame = GetViewFrame();
			pThisFrame->ToggleChildWindow( ::avmedia::MediaPlayer::GetChildWindowId() );
			pThisFrame->GetBindings().Invalidate( SID_AVMEDIA_PLAYER );
			rReq.Ignore();
		}
		break;
	}
}

void ScTabViewShell::GetChildWinState( SfxItemSet& rSet )
{
	if( SFX_ITEM_AVAILABLE == rSet.GetItemState( SID_GALLERY ) )
	{
		sal_uInt16 nId = GalleryChildWindow::GetChildWindowId();
		rSet.Put( SfxBoolItem( SID_GALLERY, GetViewFrame()->HasChildWindow( nId ) ) );
	}
	else if( SFX_ITEM_AVAILABLE == rSet.GetItemState( SID_AVMEDIA_PLAYER ) )
	{
		sal_uInt16 nId = ::avmedia::MediaPlayer::GetChildWindowId();
		rSet.Put( SfxBoolItem( SID_AVMEDIA_PLAYER, GetViewFrame()->HasChildWindow( nId ) ) );
	}
}

//------------------------------------------------------------------

void ScTabViewShell::ExecGallery( SfxRequest& rReq )
{
    const SfxItemSet* pArgs = rReq.GetArgs();

    SFX_ITEMSET_ARG( pArgs, pGalleryItem, SvxGalleryItem, SID_GALLERY_FORMATS, sal_False );
    if ( !pGalleryItem )
        return;

    sal_Int8 nType( pGalleryItem->GetType() );
    if ( nType == com::sun::star::gallery::GalleryItemType::GRAPHIC )
    {
        MakeDrawLayer();

        Graphic aGraphic( pGalleryItem->GetGraphic() );
        Point 	aPos     = GetInsertPos();

        String aPath, aFilter;
        if ( pGalleryItem->IsLink() ) // als Link einfuegen?
        {
            aPath = pGalleryItem->GetURL();
            aFilter = pGalleryItem->GetFilterName();
        }

        PasteGraphic( aPos, aGraphic, aPath, aFilter );
    }
    else if ( nType == com::sun::star::gallery::GalleryItemType::MEDIA )
    {
        //	#98115# for sounds (linked or not), insert a hyperlink button,
        //	like in Impress and Writer
        const SfxStringItem aMediaURLItem( SID_INSERT_AVMEDIA, pGalleryItem->GetURL() );
        GetViewFrame()->GetDispatcher()->Execute( SID_INSERT_AVMEDIA, SFX_CALLMODE_SYNCHRON, &aMediaURLItem, 0L );
    }
}

void ScTabViewShell::GetGalleryState( SfxItemSet& /* rSet */ )
{
}

//------------------------------------------------------------------

ScInputHandler* ScTabViewShell::GetInputHandler() const
{
	return pInputHandler;
}

//------------------------------------------------------------------

String __EXPORT ScTabViewShell::GetDescription() const
{
	return String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(" ** Test ** "));
}

void ScTabViewShell::ExecImageMap( SfxRequest& rReq )
{
	sal_uInt16 nSlot = rReq.GetSlot();
	switch(nSlot)
	{
		case SID_IMAP:
		{
			SfxViewFrame* pThisFrame = GetViewFrame();
			sal_uInt16 nId = ScIMapChildWindowId();
			pThisFrame->ToggleChildWindow( nId );
			GetViewFrame()->GetBindings().Invalidate( SID_IMAP );

			if ( pThisFrame->HasChildWindow( nId ) )
			{
				SvxIMapDlg*	pDlg = ScGetIMapDlg();
				if ( pDlg )
				{
					SdrView* pDrView = GetSdrView();
					if ( pDrView )
					{
						const SdrMarkList& rMarkList = pDrView->GetMarkedObjectList();
						if ( rMarkList.GetMarkCount() == 1 )
							UpdateIMap( rMarkList.GetMark( 0 )->GetMarkedSdrObj() );
					}
				}
			}

			rReq.Ignore();
		}
		break;

		case SID_IMAP_EXEC:
		{
			SdrView* pDrView = GetSdrView();
			SdrMark* pMark = pDrView ? pDrView->GetMarkedObjectList().GetMark(0) : 0;

			if ( pMark )
			{
				SdrObject*	pSdrObj = pMark->GetMarkedSdrObj();
				SvxIMapDlg*	pDlg = ScGetIMapDlg();

				if ( ScIMapDlgGetObj(pDlg) == (void*) pSdrObj )
				{
					const ImageMap&	rImageMap = ScIMapDlgGetMap(pDlg);
					ScIMapInfo*		pIMapInfo = ScDrawLayer::GetIMapInfo( pSdrObj );

					if ( !pIMapInfo )
						pSdrObj->InsertUserData( new ScIMapInfo( rImageMap ) );
					else
						pIMapInfo->SetImageMap( rImageMap );

	                GetViewData()->GetDocShell()->SetDrawModified();
				}
			}
		}
		break;
	}
}

void ScTabViewShell::GetImageMapState( SfxItemSet& rSet )
{
	SfxWhichIter aIter(rSet);
	sal_uInt16 nWhich = aIter.FirstWhich();
	while ( nWhich )
	{
		switch ( nWhich )
		{
			case SID_IMAP:
				{
					//	Disabled wird nicht mehr...

					sal_Bool bThere = sal_False;
					SfxViewFrame* pThisFrame = GetViewFrame();
					sal_uInt16 nId = ScIMapChildWindowId();
					if ( pThisFrame->KnowsChildWindow(nId) )
						if ( pThisFrame->HasChildWindow(nId) )
							bThere = sal_True;

					ObjectSelectionType eType=GetCurObjectSelectionType();
					sal_Bool bEnable=(eType==OST_OleObject) ||(eType==OST_Graphic);
					if(!bThere && !bEnable)
					{
					   rSet.DisableItem( nWhich );
					}
					else
					{
						rSet.Put( SfxBoolItem( nWhich, bThere ) );
					}
				}
				break;

			case SID_IMAP_EXEC:
				{
					sal_Bool bDisable = sal_True;

					SdrView* pDrView = GetSdrView();
					if ( pDrView )
					{
						const SdrMarkList& rMarkList = pDrView->GetMarkedObjectList();
						if ( rMarkList.GetMarkCount() == 1 )
							if ( ScIMapDlgGetObj(ScGetIMapDlg()) ==
										(void*) rMarkList.GetMark(0)->GetMarkedSdrObj() )
								bDisable = sal_False;
					}

					rSet.Put( SfxBoolItem( SID_IMAP_EXEC, bDisable ) );
				}
				break;
		}

		nWhich = aIter.NextWhich();
	}
}




