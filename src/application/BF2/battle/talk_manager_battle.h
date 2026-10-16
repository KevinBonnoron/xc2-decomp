#pragma once
#include "mm_mtl/singleton.h"

namespace btl {

class TalkManager : public mm::mtl::PtrSingleton<TalkManager> {
public:
  bool IsEnableFieldBladeChange() const;
  bool IsPlayingEnemyVoice() const;
  bool IsPlayingEnemyWinVoice() const;
  int GetPlayVoiceID(int id) const;
  void PlayVoice(int id, int voice);
};

} // namespace btl
