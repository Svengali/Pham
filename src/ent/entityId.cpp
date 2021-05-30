//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez

#include "../stdafx.h"

#include "ent.h"




const ent::EntityId ent::EntityId::invalid = ent::EntityId( 0 );

std::atomic_uint64_t ent::EntityId::s_nextId = 1024;

//ent::EntityId ent::EntityId::s_nextId = ent::EntityId::initStartingEntityId( 1024 );