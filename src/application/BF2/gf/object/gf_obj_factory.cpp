#include "gf/object/gf_obj_factory.h"

#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

void GfObjFactory::destroyObj(GF_OBJ_HANDLE *handle) { GfObjUtil::destroy(handle); }

GF_OBJ_HANDLE *GfObjFactory::createDebugMap(const GfInitParamMap &) { return INVALID_HANDLE; }

} // namespace gf
