#pragma once
#include "event/i_manager.h"
#include "event/select_window.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CharaObj;

class SelectManager : public IManager, public mm::mtl::Singleton<SelectManager> {
public:
  enum {
    FLAG_ACTIVE = 1 << 0,
    FLAG_SELECT = 1 << 1,
    FLAG_WAIT = 1 << 2,
  };

  SelectManager();
  virtual ~SelectManager() {}
  void clear();
  void update();
  virtual void OnEventProc(MSG_TYPE type);
  bool play(SELECT_TYPE type, const char *label, mm::mtl::FixedVector<const char *, 16> &items, CharaObj *chara);
  int getResult() const;
  bool isActive() const;

private:
  u32 flags;
  u32 talkerType;
  SelectWindow window;
  u8 _30[0x38 - 0x30];
  int selected;
  int result;
  s32 wait;
};

static_assert(sizeof(SelectManager) == 0x48, "");

} // namespace event
