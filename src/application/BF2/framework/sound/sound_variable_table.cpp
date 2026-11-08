#include "framework/sound/sound_variable_table.h"

#include "framework/memory/allocator.h"
#include "mm_mtl/fixstr.h"

namespace fw {

SoundVariableTable::SoundVariableTable() : unknown00(Allocator::getProcAllocator()) {}

SoundVariableTable::~SoundVariableTable() {}

} // namespace fw
