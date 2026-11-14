#include "gf/param/enemy/gf_param_enemy.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_param_manager.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {

void EnemyMoveParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 18
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(EnemyMoveParam));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accel0", offsetof(EnemyMoveParam, accel0), 0.0f, 10000.0f, 30.0f));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accel1", offsetof(EnemyMoveParam, accel1), 0.0f, 10000.0f, 30.0f));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accel2", offsetof(EnemyMoveParam, accel2), 0.0f, 10000.0f, 30.0f));
#line 22
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("brake0", offsetof(EnemyMoveParam, brake0), 0.0f, 10000.0f, 10.0f));
#line 23
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("brake1", offsetof(EnemyMoveParam, brake1), 0.0f, 10000.0f, 10.0f));
#line 24
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("brake2", offsetof(EnemyMoveParam, brake2), 0.0f, 10000.0f, 10.0f));
  reflection->setReflectionStruct(index, value);
}

const EnemyMoveParam *getEnemeyMoveParam(u32 index) {
  const fw::ParamList *paramList = fw::ParamManager::get()->unknown408[21].operator->();
  const fw::ParamList::unknown005 *entry = index < paramList->unknown0c ? &paramList->unknown10[index] : nullptr;
  return entry != nullptr ? static_cast<const EnemyMoveParam *>(entry->param) : nullptr;
}

} // namespace gf
