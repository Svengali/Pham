//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once



#pragma warning(disable : 4003) //Substitute blank text for missing macro stuffs


#define CLASS( _Class, _Parent )										\
static util::Symbol SClass()	{														\
	static util::Symbol s( #_Class ); return s; }						\
virtual util::Symbol Class() const { return _Class::SClass(); }		\
static util::Symbol SParent()	{														\
	return _Parent::SClass(); }												\
static bool SIsSubclassOf( const util::Symbol &s ) {				\
	if( s == _Class::SClass() ) return true;					\
	  return _Parent::SIsSubclassOf( s ); }							\
\
virtual util::Symbol Parent() const { return _Parent::SClass(); }	\
bool IsSubclassOf( const util::Symbol &s ) {								\
	if( s == _Class::SClass() ) return true;					\
	  return _Parent::SIsSubclassOf( s ); }							\
//end #define CLASS( _Class )												\

#define STRUCT( _Class, _Parent )										\
static util::Symbol SClass()	{														\
	static util::Symbol s( #_Class ); return s; }						\
static util::Symbol SParent()	{														\
	return _Parent::SClass(); }												\
static bool SIsSubclassOf( const util::Symbol &s ) {				\
	if( s == _Class::SClass() ) return true;					\
	  return _Parent::SIsSubclassOf( s ); }							\
bool IsSubclassOf( const util::Symbol &s ) {								\
	if( s == _Class::SClass() ) return true;					\
	  return _Parent::SIsSubclassOf( s ); }							\
//end #define STRUCT( _Class )												\





#define CREATE_BY_NAME( _Class ) \
//end #define CREATE_BY_NAME( _Class )


//#pragma warning(default : 4003) //Substitute blank text for missing macro stuffs

inline bool SIsSubclassOf( const util::Symbol & )
{
	return false;
}

inline util::Symbol SClass()
{
	static util::Symbol s( "" );
	return s;
}


//DONE Define the various visitor classes when needed, instead of always like in the olden days
//     This is working well, so Im continuing its use.  
#define REFLECT_BEGIN( _CLASS, _PARENT ) \
template <class U> void Reflection(U & functor) { _PARENT::Reflection( functor ); \
//end #define REFLECT_BEGIN( _CLASS, _PARENT )

#define REFLECT_BEGIN_ROOT( _CLASS ) \
template <class T> void Reflection(T & functor) { \
//end #define REFLECT_BEGIN_ROOT( _CLASS )


#define REFLECT(x)	functor(#x,x)

#define REFLECT_ARRAYN(what,count)	do{ for(int i=0;i<(count);i++) { char str[80]; sprintf(str,"%s%d",#what,i); functor(str,(what)[i]); } }while(0)

#define REFLECT_ARRAY(what)	REFLECT_ARRAYN(what,ARRAY_SIZE(what))

#define REFLECT_END(  ) }



// We define our reflection at each base class now.  Super simple and allows different 
// use cases per tree
#define OLD_REFLECT_BEGIN( _CLASS, _PARENT ) \
virtual void Reflection( XMLReader &reader ) { Reflection<XMLReader>(reader); } \
template <class U> void Reflection(U & functor) { _PARENT::Reflection( functor ); \
//end #define REFLECT_BEGIN( _CLASS, _PARENT )
