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

  Control *m_pControl;
  const ResClipData *m_pResClipData;
};

static_assert(offsetof(AsmClip, m_pControl) == 0x10, "");
static_assert(sizeof(AsmClip) == 0x20, "");

class AsmBlender {
public:
  AsmBlender();
  ~AsmBlender();
  void setup(const ResASM &resAsm, mm::mtl::IAllocator &allocator);
  void cleanup();
  bool addClip(AsmClip &clip);
  void removeClip(AsmClip &clip);

  Blender *m_pBlender;
  mm::mtl::IntrusiveList<AsmClip> m_clips;
  bool m_skipSample;
};

static_assert(offsetof(AsmBlender, m_clips) == 0x8, "");
static_assert(offsetof(AsmBlender, m_skipSample) == 0x20, "");

} // namespace anm
