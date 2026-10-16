#include "event/memory_manager.h"
#include "event/script_chara_action.h"
#include "event/script_chara_facial.h"
#include "event/script_chara_fade.h"
#include "event/script_chara_head.h"
#include "event/script_chara_motion.h"
#include "event/script_chara_motion_abc.h"
#include "event/script_chara_mount.h"
#include "event/script_chara_set_idle.h"
#include "event/script_chara_talk.h"
#include "event/script_chara_wink.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {
class ITodo;

ITodo *ScriptCharaSetIdle::exec() {
  return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCharaSetIdle;
}

ITodo *ScriptCharaAction::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCharaAction; }

ITodo *ScriptCharaMotion::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCharaMotion; }

ITodo *ScriptCharaMotionABC::exec() {
  return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCharaMotionABC;
}

ITodo *ScriptCharaHead::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCharaHead; }

ITodo *ScriptCharaFacial::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCharaFacial; }

ITodo *ScriptCharaTalk::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCharaTalk; }

ITodo *ScriptCharaWink::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCharaWink; }

ITodo *ScriptCharaMount::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCharaMount; }

ITodo *ScriptCharaFade::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCharaFade; }

} // namespace event
