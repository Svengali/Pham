//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once

//class TiXmlElement;

namespace CEGUI
{
	class Window;
}

class CEGUIWrapper
{
public:
	CEGUIWrapper( CEGUI::Window *window )
		:
		m_window( window )
	{
	}

	~CEGUIWrapper()
	{
		//Blah
	}

	CEGUI::Window *operator ->()
	{
		return m_window;
	}

	CEGUI::Window *m_window;
};

PtrDef( CEGUIWrapper );


#define AS_REG_RC_CLASS( _CLASS ) \
ResScript::Engine()->RegisterObjectType( #_CLASS, 0, asOBJ_CLASS_CDA ); \
ResScript::Engine()->RegisterObjectBehaviour( #_CLASS, asBEHAVE_ADDREF,	 "void f()", asMETHOD( _CLASS, RefCounted_TakeRef), asCALL_THISCALL); \
ResScript::Engine()->RegisterObjectBehaviour( #_CLASS, asBEHAVE_RELEASE, "void f()", asMETHOD( _CLASS, RefCounted_FreeRef), asCALL_THISCALL); \
//#end #define AS_REG_CLASS( _CLASS )

#define AS_REG_CEGUI_CLASS( _CLASS ) \
ResScript::Engine()->RegisterObjectType( #_CLASS, 0, asOBJ_CLASS_CDA ); \
ResScript::Engine()->RegisterObjectBehaviour( #_CLASS, asBEHAVE_ADDREF,	 "void f()", asMETHOD( CEGUIWrapper, RefCounted_TakeRef), asCALL_THISCALL); \
ResScript::Engine()->RegisterObjectBehaviour( #_CLASS, asBEHAVE_RELEASE, "void f()", asMETHOD( CEGUIWrapper, RefCounted_FreeRef), asCALL_THISCALL); \
//#end #define AS_REG_CLASS( _CLASS )
