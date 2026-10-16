#pragma once
#include "event/i_manager.h"
#include "ml/work_event.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

enum EVT_judge {};
enum EVT_change {};

namespace event {

class StatusManager : public IManager, public ml::IWorkEvent, public mm::mtl::Singleton<StatusManager> {
public:
  static constexpr u32 CHANGE_COUNT = 32;

  enum MATH {
    MATH_SET = 0,
    MATH_ADD = 1,
  };

  enum {
    FLAG_CHANGE_FROM_BDAT = 1 << 0,
  };

  struct Change {
    EVT_change type;
    int id;
    int value0;
    int value1;
    int value2;
    const char *string0;
  };

  u32 getHomuriFlag() const;
  StatusManager();
  virtual ~StatusManager() {}
  void init();
  void clear();
  bool judge(EVT_judge type, int id, int value0, int value1, int value2, bool &result);
  void log(const char *tag, const char *format, ...);
  bool change(EVT_change type, int id, int value0, int value1, int value2, const char *string0);
  const char *math2str(u32 math) const;
  void setGameFlag8(u32 flag, int value, u32 math) const;
  void setGameFlag4(u32 flag, int value, u32 math) const;
  void setGameFlag1(u32 flag, int value) const;
  void setGameFlag2(u32 flag, int value, u32 math) const;
  void setExtDisp(u32 chara, const char *name, bool isDisp) const;
  void addMoney(int money) const;
  void addTrustPoint(u32 blade, int point) const;
  void setExtParam(u32 chara, const char *name, f32 value) const;
  void setExtDispWeapon(u32 chara, const char *name, bool isDisp) const;
  bool changeFromBdat(u32 id);
  u32 getDriverByBladeId(u32 blade) const;
  void setHomuriFlag(int flag);
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
  mm::mtl::FixedVector<Change, CHANGE_COUNT> mChanges;
};

static_assert(sizeof(StatusManager) == 0x428, "");

} // namespace event
