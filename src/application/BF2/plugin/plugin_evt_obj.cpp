#include "event/memory_manager.h"
#include "event/script_set_active.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {
class ITodo;

ITodo *ScriptSetActive::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptSetActive; }

} // namespace event

// The game emits them right after ScriptSetActive::exec, at the end of this file.
template mm::mtl::FixedVector<u32, 16>::~FixedVector();
template mm::mtl::FixedVector<const char *, 16>::~FixedVector();
