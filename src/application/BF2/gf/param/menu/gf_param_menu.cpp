#include "gf/param/menu/gf_param_menu.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {

void MenuParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 14
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(MenuParam));
#line 15
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fadeTimeHUD", offsetof(MenuParam, fadeTimeHUD), 0.0f, 1000.0f, 0.5f));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fadeTimeFS", offsetof(MenuParam, fadeTimeFS), 0.0f, 1000.0f, 0.5f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("artsPaletteDisableScale", offsetof(MenuParam, artsPaletteDisableScale), 0.0f, 1.0f, 0.5f));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("moveBGTime", offsetof(MenuParam, moveBGTime), 0.0f, 9.0f, 0.4f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("charSelectScale", offsetof(MenuParam, charSelectScale), 0.0f, 10.0f, 0.9f));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fsWaitTime", offsetof(MenuParam, fsWaitTime), 0.0f, 5.0f, 0.5f));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("chainAttackStartTime", offsetof(MenuParam, chainAttackStartTime), 0.1f, 1.0f, 0.2f));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
