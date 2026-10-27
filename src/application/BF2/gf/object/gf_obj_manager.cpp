#include "gf/object/gf_obj_manager.h"

namespace gf {

bool GfObjManager::hasReloadObjForDebug() { return false; }

void GfObjManager::addHandle(GF_OBJ_HANDLE *handle) { setStateLoading(handle); }

} // namespace gf
