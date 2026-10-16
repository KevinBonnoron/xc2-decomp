#pragma once
#include "mm_mtl/singleton.h"

namespace btl {

class TalkManager : public mm::mtl::PtrSingleton<TalkManager> {
public:
  enum TRIGGER {
    TRIGGER_ENEMY_WIN = 26,
  };

  bool IsEnableFieldBladeChange() const;
  bool IsPlayingEnemyVoice() const;
  bool IsPlayingEnemyWinVoice() const;
  int GetPlayVoiceID(int id) const;
  bool NotifyTrigger(int id, TRIGGER trigger, int, int);
  void PlayVoice(int id, int voice);
};

} // namespace btl
