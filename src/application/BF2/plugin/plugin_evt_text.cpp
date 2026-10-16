#include "event/memory_manager.h"
#include "event/script_play_text.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {
class ITodo;

ITodo *ScriptPlayText::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptPlayText; }

} // namespace event
