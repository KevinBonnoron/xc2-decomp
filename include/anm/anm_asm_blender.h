#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class Blender;
class Control;
class ResASM;
class ResClipData;
class AsmListener;
struct QsTransform;

class AsmClip : public mm::mtl::IntrusiveListNode<AsmClip> {
public:
  AsmClip();
  ~AsmClip();
  void destroyControl();
  void createControl(const ResClipData &resClipData, mm::mtl::IAllocator &allocator);
  bool update(f32 deltaTime, AsmListener *listener);
  void setLocalTime(f32 time);
  f32 getLocalTime() const;
  void setSpeed(f32 speed);
  void setWeight(f32 weight);

  Control *unknown10;           // Inferred role: p control; original member name unknown.
  const ResClipData *unknown18; // Inferred role: p res clip data; original member name unknown.
};

static_assert(offsetof(AsmClip, unknown10) == 0x10, "");
static_assert(sizeof(AsmClip) == 0x20, "");

class AsmBlender {
public:
  AsmBlender();
  ~AsmBlender();
  void setup(const ResASM &resAsm, mm::mtl::IAllocator &allocator);
  void cleanup();
  bool addClip(AsmClip &clip);
  void removeClip(AsmClip &clip);
  void sampleTrucks(u32 count, QsTransform *transforms);
  void sampleTrucksMS(u32 count, QsTransform *transforms);
  void sampleExtraTrucks(u16 slot, u32 count, f32 *values);

  Blender *m_pBlender;
  mm::mtl::IntrusiveList<AsmClip> unknown08; // Inferred role: clips; original member name unknown.
  bool unknown20;                            // Inferred role: skip sample; original member name unknown.
};

static_assert(offsetof(AsmBlender, unknown08) == 0x8, "");
static_assert(offsetof(AsmBlender, unknown20) == 0x20, "");

} // namespace anm
