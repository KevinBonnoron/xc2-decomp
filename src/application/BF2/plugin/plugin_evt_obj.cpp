#include "event/memory_manager.h"
#include "event/script_set_active.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {
class ITodo;

ITodo *ScriptSetActive::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptSetActive; }

} // namespace event
