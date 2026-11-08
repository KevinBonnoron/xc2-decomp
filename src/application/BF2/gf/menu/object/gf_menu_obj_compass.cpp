#include "gf/menu/object/gf_menu_obj_compass.h"

#include "gf/menu/gf_menu_types.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x42;

mm::mtl::FixedVector<GfMenuObjCompass::unknown004, 32> GfMenuObjCompass::m_IconObjList;

GfMenuObjCompass::GfMenuObjCompass(u32 handle) : GfMenuObject(handle) { m_IconObjList.clear(); }

GfMenuObjCompass::~GfMenuObjCompass() { ; }

void GfMenuObjCompass::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCompass::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjCompass::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
