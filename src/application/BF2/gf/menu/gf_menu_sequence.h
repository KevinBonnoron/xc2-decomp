#pragma once
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/type_traits.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace mm {
namespace mtl {

// The game moves the queued steps with memmove when one is dropped (GfMenuObjChapterTelop::update).
template <> struct is_pod<Delegate<bool()>> {
  static const bool unknown001 = true; // Inferred role: whether the type is plain old data, so it is copied with memcpy; original name unknown.
};

} // namespace mtl
} // namespace mm

namespace gf {

// Steps queued by a menu object (_ZN2gf14GfMenuSequence...). The member offsets named below are the ones of
// GfMenuSequence<T, 8> (GfMenuObjQuestLog: sequences at 0x60, 0x2f0 and 0x580, owner at +0x278); N = 4 gives
// the jobs at 0x0, the waits at 0x88, the animations at 0xa0 and the owner at 0x148 (GfMenuObjChapterTelop at 0x28).
template <typename T, int N> class GfMenuSequence {
public:
  // Inferred role: animation job, the UI object and the animation it plays; original name unknown.
  struct unknown001 {
    unknown001(u32 handle, const char *name) : unknown00(handle), unknown04(name) {}

    u32 unknown00;                 // Inferred role: UI object handle; original member name unknown.
    mm::mtl::FixStr<32> unknown04; // Inferred role: animation name; original member name unknown.
  };

  GfMenuSequence(T *owner) : unknown278(owner), unknown280(false), unknown288(false) {}

  // Inferred helper: queues a step of the owner; original name unknown.
  void unknown002(bool (T::*step)()) {
    mm::mtl::Delegate<bool()> job;
    job.bind(unknown278, step);
    unknown00.push_back(job);
  }

  // Inferred helper: runs the first queued step and drops it once it reports its end; original name unknown.
  void unknown003() {
    if (!unknown00.empty()) {
      if (unknown00.front()()) {
        unknown00.erase(unknown00.begin());
      }
    }
  }

  // Inferred helper: queues a wait of a number of frames; original name unknown.
  void unknown004(int frames) {
    unknown108.push_back(frames);
    mm::mtl::Delegate<bool()> job;
    job.bind(this, &GfMenuSequence::wait);
    unknown00.push_back(job);
  }

  // Inferred helper: drops every queued step, wait and animation; original name unknown.
  void unknown005() {
    unknown00.clear();
    unknown108.clear();
    unknown130.clear();
    unknown288 = false;
    unknown280 = false;
    unknown284 = 0;
  }

  void addAnimJob(u32 handle, const char *name) {
    unknown130.push_back(unknown001(handle, name));
    mm::mtl::Delegate<bool()> job;
    job.bind(this, &GfMenuSequence::wait_anim);
    unknown00.push_back(job);
  }

  bool wait() {
    if (unknown108.empty()) {
      return true;
    }
    if (!unknown280) {
      unknown284 = unknown108.front();
      unknown280 = true;
      return false;
    }
    if (--unknown284 != 0) {
      return false;
    }
    unknown108.erase(unknown108.begin());
    unknown284 = 0;
    unknown280 = false;
    return true;
  }

  bool wait_anim() {
    if (unknown130.empty()) {
      return true;
    }
    ui::UIObjectAcc acc(unknown130.front().unknown00);
    bool isEnd;
    if (!unknown288) {
      acc.startAnimation(unknown130.front().unknown04.c_str(), false);
      isEnd = false;
      unknown288 = true;
    } else if (!acc.isPlayingAnimation()) {
      unknown130.erase(unknown130.begin());
      isEnd = true;
      unknown288 = false;
    } else {
      isEnd = false;
    }
    return isEnd;
  }

  mm::mtl::FixedVector<mm::mtl::Delegate<bool()>, N> unknown00; // Inferred role: queued steps; original member name unknown.
  mm::mtl::FixedVector<int, N> unknown108;                      // Inferred role: queued wait frame counts; original member name unknown.
  mm::mtl::FixedVector<unknown001, N> unknown130;               // Inferred role: queued animation jobs; original member name unknown.
  T *unknown278;                                                // Inferred role: owner the steps run on; original member name unknown.
  bool unknown280;                                              // Inferred role: wait started flag; original member name unknown.
  int unknown284;                                               // Inferred role: remaining wait frames; original member name unknown.
  bool unknown288;                                              // Inferred role: animation started flag; original member name unknown.
};

} // namespace gf
