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
  u32 unknown10;          // Inferred role: flags; original member name unknown.
  u32 unknown14;          // Inferred role: talker type; original member name unknown.
  SelectWindow unknown18; // Inferred role: window; original member name unknown.
  u8 _30[0x38 - 0x30];
  int unknown38; // Inferred role: selected; original member name unknown.
  int m_result;
  s32 unknown40; // Inferred role: wait; original member name unknown.
};

static_assert(sizeof(SelectManager) == 0x48, "");

} // namespace event
