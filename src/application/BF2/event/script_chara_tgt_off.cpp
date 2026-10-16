#include "event/script_chara_tgt_off.h"

#include "event/object_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCharaTgtOff::doit(const Param &param) { mm::mtl::Singleton<ObjectManager>::getPtr(); }

void ScriptCharaTgtOff::undo(const Param &param) { mm::mtl::Singleton<ObjectManager>::getPtr(); }

void ScriptCharaTgtOff::redo(const Param &param) { mm::mtl::Singleton<ObjectManager>::getPtr(); }

} // namespace event
