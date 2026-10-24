#pragma once
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class QuestManager : public IManager, public mm::mtl::Singleton<QuestManager> {
public:
  enum {
    FLAG_ACTIVE = 1 << 0,
  };

  QuestManager();
  virtual ~QuestManager() {}
  void clear();
  virtual void OnEventProc(MSG_TYPE type);
  bool entry(u32 quest, bool *isOrdered);
  u32 getState(u32 quest);
  bool setComp(u32 quest, u32 taskIndex, bool isComp);
  bool getComp(u32 quest, u32 taskIndex);
  bool disp(u32 quest, bool isResult);
  bool isActive() const;

private:
  u32 unknown10; // Inferred role: flags; original member name unknown.
};

static_assert(sizeof(QuestManager) == 0x18, "");

} // namespace event
