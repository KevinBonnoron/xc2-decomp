#pragma once
#include "event/fade_ctrl.h"
#include "event/fade_planner.h"
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace event {

class FadeManager : public IManager, public mm::mtl::Singleton<FadeManager> {
public:
  enum {
    FLAG_DISABLE_FADE = 1 << 0,
  };

  FadeManager();
  virtual ~FadeManager() {}
  void clear();
  void update();
  void play(bool isFadeOut, u32 frame, FadeCtrl::PRIO prio, const mm::Col4 *color);
  bool isFading() const;
  void plan(FadePlanner::TYPE type, bool isEnable, u32 frame, u32 wait, FadeCtrl::PRIO prio, const mm::Col4 &color);
  void request(FadePlanner::TYPE type);
  void playEventSkip(bool isFadeOut, int frame);
  bool isSkipFading() const;
  void setDisableFade(bool isDisable);
  bool isDisableFade() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
  FadePlanner mPlanner;
};

static_assert(sizeof(FadeManager) == 0xb8, "");

} // namespace event
