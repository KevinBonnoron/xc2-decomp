#include "event/script_set_active.h"

#include "event/object_list.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptSetActive::doit(const Param &param) {
  const char *path = param.val(0).getStr();
  unknown08 = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  mm::mtl::Singleton<ObjectManager>::getPtr()->setActivePath(path);
}

void ScriptSetActive::undo(const Param &param) {
  Object *prevActive = unknown08;
  mm::mtl::Singleton<ObjectManager>::getPtr()->getCurrent()->setActive(prevActive);
}

} // namespace event
