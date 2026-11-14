#include "framework/sound/sound_variable_table.h"

#include "framework/memory/allocator.h"
#include "mm_mtl/fixstr.h"

namespace fw {

SoundVariableTable::SoundVariableTable() : unknown00(Allocator::getProcAllocator()) {}

SoundVariableTable::~SoundVariableTable() {}

void SoundVariableTable::setVariable(const char *name, int value) {
  mm::mtl::FixStr<64> key(name);
  mm::mtl::Map<mm::mtl::FixStr<64>, int>::iterator it = unknown00.find(key);
  if (it != unknown00.end()) {
    it->second = value;
  } else {
    unknown00.insert(mm::mtl::MapPair<mm::mtl::FixStr<64>, int>(key, value));
  }
}

bool SoundVariableTable::getVariable(const char *name, int *value) const {
  mm::mtl::FixStr<64> key(name);
  mm::mtl::Map<mm::mtl::FixStr<64>, int>::const_iterator it = unknown00.find(key);
  if (it == unknown00.end()) {
    return false;
  }
  *value = it->second;
  return true;
}

} // namespace fw
