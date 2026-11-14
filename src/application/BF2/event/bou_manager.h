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
  static constexpr u32 CALLBACK_UNKNOWN_1024 = 1024; // Inferred role: callback count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 0, // Inferred role: enable flag; original name unknown.
    FLAG_UNKNOWN_1 = 1, // Inferred role: attached flag; original name unknown.
    FLAG_UNKNOWN_2 = 2, // Inferred role: active flag; original name unknown.
    FLAG_UNKNOWN_3 = 3, // Inferred role: key down flag; original name unknown.
  };

  enum {
    DEBUG_FLAG_UNKNOWN_0 = 0, // Inferred role: enable flag; original name unknown.
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
  // Inferred role: a selection is being dragged; original name unknown.
  bool unknown001() const { return isEnable() && isDebugEnable() && unknown18.test(FLAG_UNKNOWN_2) && !unknown18.test(FLAG_UNKNOWN_3); }
  // Inferred role: no key is held down; original name unknown.
  bool unknown002() const { return !unknown18.test(FLAG_UNKNOWN_3); }
  bool isEnable() const { return unknown18.test(FLAG_UNKNOWN_0); }
  bool isDebugEnable() const { return unknown1c.test(DEBUG_FLAG_UNKNOWN_0); }

  mm::mtl::unknown027<32> unknown18;                                       // Inferred role: flags; original member name unknown.
  mm::mtl::unknown027<32> unknown1c;                                       // Inferred role: debug flags; original member name unknown.
  BouRect unknown20;                                                       // Inferred role: rect; original member name unknown.
  mm::mtl::FixedVector<IBouCallback *, CALLBACK_UNKNOWN_1024> unknown38;   // Inferred role: callbacks; original member name unknown.
  mm::mtl::FixedVector<IBouCallback *, CALLBACK_UNKNOWN_1024> unknown2040; // Inferred role: selected; original member name unknown.
};

static_assert(sizeof(BouManager) == 0x4048, "");

} // namespace event
