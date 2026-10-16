#pragma once
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class BlurManager : public IManager, public mm::mtl::Singleton<BlurManager> {
public:
  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  BlurManager();
  virtual ~BlurManager() {}
  void clear();
  void stop();
  void update();
  void render();
  void play();
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 dispFlags;
  u32 flags;
};

static_assert(sizeof(BlurManager) == 0x18, "");

} // namespace event
