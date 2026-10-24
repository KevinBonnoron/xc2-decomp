#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class LodManager : public IManager, public mm::mtl::Singleton<LodManager> {
public:
  static constexpr u32 OBJ_COUNT = 8;

  class Obj {
  public:
    Obj(u32 id);
    void clear();
    void exec(bool isReverse, bool isSkip);
    u32 getID() const { return unknown00; }

  private:
    u32 unknown00;  // Inferred role: id; original member name unknown.
    bool unknown04; // Inferred role: is reverse; original member name unknown.
  };

  LodManager();
  virtual ~LodManager() {}
  void clear();
  void resetPlayAnm();
  void update();
  void playAnm(u32 id, bool isReverse, bool isSkip);
  Obj *searchObj(u32 id);
  virtual void OnEventProc(MSG_TYPE type);

private:
  mm::mtl::FixedVector<Obj *, OBJ_COUNT> unknown10; // Inferred role: objs; original member name unknown.
};

static_assert(sizeof(LodManager::Obj) == 0x8, "");
static_assert(sizeof(LodManager) == 0x58, "");

} // namespace event
