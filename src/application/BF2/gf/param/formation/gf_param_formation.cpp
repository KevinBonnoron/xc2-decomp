// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/formation/gf_param_formation.cpp.
#include <stddef.h>

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/game/gf_game_player_formation.h"
#include "types.h"

namespace gf {

void FormationParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 14
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(FormationParam));
#line 15
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("player1OffsetX", offsetof(FormationParam, offsets[0].x), -1000.0f, 1000.0f, 1.0f));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("player1OffsetZ", offsetof(FormationParam, offsets[0].y), -1000.0f, 1000.0f, -1.0f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("player2OffsetX", offsetof(FormationParam, offsets[1].x), -1000.0f, 1000.0f, -3.0f));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("player2OffsetZ", offsetof(FormationParam, offsets[1].y), -1000.0f, 1000.0f, -3.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("player3OffsetX", offsetof(FormationParam, offsets[2].x), -1000.0f, 1000.0f, 1.0f));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("player3OffsetZ", offsetof(FormationParam, offsets[2].y), -1000.0f, 1000.0f, -1.0f));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("player4OffsetX", offsetof(FormationParam, offsets[3].x), -1000.0f, 1000.0f, 3.0f));
#line 22
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("player4OffsetZ", offsetof(FormationParam, offsets[3].y), -1000.0f, 1000.0f, -3.0f));
#line 23
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("player5OffsetX", offsetof(FormationParam, offsets[4].x), -1000.0f, 1000.0f, 1.0f));
#line 24
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("player5OffsetZ", offsetof(FormationParam, offsets[4].y), -1000.0f, 1000.0f, -1.0f));
  reflection->setReflectionStruct(index, value);
}

void WarpForRandomTalkParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 27
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(WarpForRandomTalkParam));
#line 28
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distVert", offsetof(WarpForRandomTalkParam, distVert), 0.0f, 1000.0f, 5.0f));
#line 29
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distHorz", offsetof(WarpForRandomTalkParam, distHorz), 0.0f, 1000.0f, 5.0f));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
