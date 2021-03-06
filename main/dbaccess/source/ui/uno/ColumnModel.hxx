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


#ifndef DBAUI_COLUMNMODEL_HXX
#define DBAUI_COLUMNMODEL_HXX

#ifndef _COM_SUN_STAR_AWT_XCONTROLMODEL_HPP_
#include <com/sun/star/awt/XControlModel.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XCLONEABLE_HPP_
#include <com/sun/star/util/XCloneable.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XPERSISTOBJECT_HPP_
#include <com/sun/star/io/XPersistObject.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_
#include <comphelper/proparrhlp.hxx>
#endif
#ifndef _COMPHELPER_PROPERTYCONTAINER_HXX_
#include <comphelper/propertycontainer.hxx>
#endif
#ifndef _COMPHELPER_BROADCASTHELPER_HXX_
#include <comphelper/broadcasthelper.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _CPPUHELPER_COMPBASE4_HXX_
#include <cppuhelper/compbase4.hxx>
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif

//.........................................................................
namespace dbaui
{
//.........................................................................

//==================================================================
// OColumnControlModel
//==================================================================
typedef ::cppu::WeakAggComponentImplHelper4 <	::com::sun::star::awt::XControlModel
										,	::com::sun::star::lang::XServiceInfo
										,	::com::sun::star::util::XCloneable
										,	::com::sun::star::io::XPersistObject
										>	OColumnControlModel_BASE;
 
class OColumnControlModel;

class OColumnControlModel :  public ::comphelper::OMutexAndBroadcastHelper
							,public ::comphelper::OPropertyContainer
							,public ::comphelper::OPropertyArrayUsageHelper< OColumnControlModel >
							,public OColumnControlModel_BASE
{

	::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory> m_xORB;
// [properties]
	::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>			m_xConnection;
	::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >		m_xColumn;
	::rtl::OUString					m_sDefaultControl;
	::com::sun::star::uno::Any		m_aTabStop;
	sal_Bool						m_bEnable;
	sal_Int16						m_nBorder;
	sal_Int32						m_nWidth;
// [properties]

	inline ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory> getORB() const { return m_xORB; }
	void registerProperties();
protected:

	virtual ~OColumnControlModel();
	OColumnControlModel(const OColumnControlModel* _pSource
						,const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& _rxFactory);
public:
	OColumnControlModel(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& _rxFactory);

// UNO Anbindung
	DECLARE_XINTERFACE( )

// ::com::sun::star::lang::XServiceInfo
	DECLARE_SERVICE_INFO_STATIC();

// XTypeProvider
	DECLARE_TYPEPROVIDER( );

// com::sun::star::uno::XAggregation
	virtual ::com::sun::star::uno::Any SAL_CALL queryAggregation( const ::com::sun::star::uno::Type& aType ) throw(::com::sun::star::uno::RuntimeException);

//  ::com::sun::star::io::XPersistObject
	virtual ::rtl::OUString SAL_CALL getServiceName() throw ( ::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL write(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectOutputStream>& _rxOutStream) throw ( ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL read(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectInputStream>& _rxInStream) throw ( ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);


// OPropertyArrayUsageHelper
	DECLARE_PROPERTYCONTAINER_DEFAULTS( );

	virtual ::com::sun::star::uno::Reference< ::com::sun::star::util::XCloneable > SAL_CALL createClone(  ) throw (::com::sun::star::uno::RuntimeException);
};

//.........................................................................
}	// namespace dbaui
//.........................................................................
#endif // DBAUI_COLUMNMODEL_HXX
