#include "gf/param/pccoli/gf_param_pccoli.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_param_manager.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {

void PcColiParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 18
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(PcColiParam));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("radiusCapsule", offsetof(PcColiParam, radiusCapsule), 0.01f, 1000.0f, 0.5f));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("heightCapsule", offsetof(PcColiParam, heightCapsule), 0.01f, 1000.0f, 2.0f));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("radiusShpere", offsetof(PcColiParam, radiusShpere), 0.01f, 1000.0f, 1.5f));
#line 22
  fw::ReflectionValueEnum *type = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueEnum("type", offsetof(PcColiParam, type));
#line 23
  type->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueEnumElem("capsule", 0));
#line 24
  type->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueEnumElem("sphere", 1));
  value->add(type);
#line 26
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("bakkyoHeadDist", offsetof(PcColiParam, bakkyoHeadDist), 0.0f, 10.0f, 0.9f));
  reflection->setReflectionStruct(index, value);
}

const PcColiParam *getPcColiParameter() {
  const fw::ParamList *paramList = fw::ParamManager::get()->unknown408[17].operator->();
  const fw::ParamList::unknown005 *entry = paramList->unknown0c > 0 ? &paramList->unknown10[0] : nullptr;
  return entry != nullptr ? static_cast<const PcColiParam *>(entry->param) : nullptr;
}

} // namespace gf
