//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2020 Marc Hernandez
#pragma once






#define PtrDef(BaseClass)	\
typedef std::shared_ptr<BaseClass> BaseClass##Ptr; \
typedef std::weak_ptr<BaseClass> BaseClass##WeakPtr; \
//#define PPtrDef(BaseClass)	

#define PtrFwd(BaseClass) \
class BaseClass; \
typedef std::shared_ptr<BaseClass> BaseClass##Ptr; \
typedef std::weak_ptr<BaseClass> BaseClass##WeakPtr; \
// end #define PPtrFwd(BaseClass)	



