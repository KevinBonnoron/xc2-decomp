#include "event/memory_manager.h"
#include "event/script_effect_anim.h"
#include "event/script_effect_cast.h"
#include "event/script_effect_color.h"
#include "event/script_effect_kill.h"
#include "event/script_effect_mount.h"
#include "event/script_effect_play.h"
#include "event/script_effect_scale.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {
class ITodo;

ITodo *ScriptEffectPlay::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptEffectPlay; }

ITodo *ScriptEffectCast::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptEffectCast; }

ITodo *ScriptEffectMount::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptEffectMount; }

ITodo *ScriptEffectKill::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptEffectKill; }

ITodo *ScriptEffectAnim::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptEffectAnim; }

ITodo *ScriptEffectScale::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptEffectScale; }

ITodo *ScriptEffectColor::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptEffectColor; }

} // namespace event
