// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#pragma warning(disable : 4100)

#include <stdio.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here

// Needs to be in front of everything
#include "cblib/stl_basics.h"


#include <Windows.h>

// TODO: reference additional headers your program requires here
#include <memory>
#include <chrono>
#include <cstdint>
#include <memory>
#include <vector>
#include <cassert>
#include <optional>


// S T L 

#undef min
#undef max

#include <algorithm>
#include <hash_map>


// cblib
#include "cblib/File.h"
#include "cblib/FileUtil.h"
#include "cblib/Link.h"
#include "cblib/Vec3.h"
#include "cblib/Vec3i.h"
#include "cblib/Frame3.h"
#include "cblib/Mat4.h"
#include "cblib/CRC.h"
#include "cblib/Reflection.h"
#include "cblib/AxialBox.h"
#include "cblib/TypeTraits.h"
// all cblib stuff needs to be above here

//Source level compiled in dependencies
#include "util/sptr_util.h"
#include "tinyxml/tinyxml.h"
#include "util/profile/profile.h"
#include "util/concurrentqueue.h"
#include "task/thread_pool.h"
#include "task/ctpl.h"
//#include "async++.h"
#include "math/units.h"
#include "math/units64.h"
#include "util/index.h"
#include "util/id.h"
#include "util/expected_lite.h"
//#include "util/optional.h"
#include "util/markable.h"
#include "util/lvalue_ref.h"
#include "util/not_null.h"
#include "util/out_param.h"
#include "util/tagged_bool.h"
#include "util/util.h"

#include "util/String.h"
#include "util/Symbol.h"

#include "util/Reflection.h"
#include "util/XMLReader.h"

#include "util/Clock.h"


#include "util/Serialization.h"
#include "util/Config.h"


// Mostly frozen project includes
#include "ent/entityId.h"

typedef  uint8_t u8;
typedef   int8_t i8;
typedef uint16_t u16;
typedef  int16_t i16;
typedef uint32_t u32;
typedef  int32_t i32;
typedef uint64_t u64;
typedef  int64_t i64;
typedef  float   f32;
typedef  double  f64;

//
//#include "ent/ent.h"
//#include "df/com.h"
//#include "map/map.h"



/*
#include "application.hpp"
#include "os.hpp"
#include "filesystem.hpp"
#include "window.hpp"
#include "click_button.hpp"
#include "toggle_button.hpp"
#include "Widget.hpp"
#include "Slider.hpp"
#include "material_util.hpp"
#include "async++.h"

namespace gr = Granite;
*/

#include "async++.h"
