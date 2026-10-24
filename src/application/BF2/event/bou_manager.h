#pragma once
#include "event/bou_rect.h"
#include "event/i_manager.h"
#include "ml/work_event.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace mm {
template <typename T> struct Pnt;
}

namespace ml {
class EventView;
}

namespace event {

class IBouCallback;

class BouManager : public IManager, public mm::mtl::NoncopyableBase, public ml::IWorkEvent {
public:
  static constexpr u32 CALLBACK_COUNT = 1024;

  enum {
    FLAG_ENABLE = 0,
    FLAG_ATTACHED = 1,
    FLAG_ACTIVE = 2,
    FLAG_KEY_DOWN = 3,
  };

  enum {
    DEBUG_FLAG_ENABLE = 0,
  };

  BouManager();
  virtual ~BouManager() {}
  void create();
  void clear();
  void endActive();
  void render();
  void startActive(const mm::Pnt<int> &point);
  void updateActive(const mm::Pnt<int> &point);
  virtual bool OnMouseButtonDown(ml::EventView *view);
  virtual bool OnMouseMove(ml::EventView *view);
  virtual bool OnMouseButtonUp(ml::EventView *view);
  virtual bool OnKeyDown(ml::EventView *view);
  virtual bool OnKeyUp(ml::EventView *view);
  void push(IBouCallback *callback);
  void pop(IBouCallback *callback);
  void setEnable(bool isEnable);
  void setDebugEnable(bool isEnable);
  virtual void OnEventProc(MSG_TYPE type);

private:
  bool isEnable() const { return unknown18.test(FLAG_ENABLE); }
  bool isDebugEnable() const { return unknown1c.test(DEBUG_FLAG_ENABLE); }

  mm::mtl::BitFlag<32> unknown18;                                   // Inferred role: flags; original member name unknown.
  mm::mtl::BitFlag<32> unknown1c;                                   // Inferred role: debug flags; original member name unknown.
  BouRect unknown20;                                                // Inferred role: rect; original member name unknown.
  mm::mtl::FixedVector<IBouCallback *, CALLBACK_COUNT> unknown38;   // Inferred role: callbacks; original member name unknown.
  mm::mtl::FixedVector<IBouCallback *, CALLBACK_COUNT> unknown2040; // Inferred role: selected; original member name unknown.
};

static_assert(sizeof(BouManager) == 0x4048, "");

} // namespace event
