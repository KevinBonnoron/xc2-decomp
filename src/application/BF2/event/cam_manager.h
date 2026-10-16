#pragma once
#include "event/cam_free.h"
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CamInterface;
class CamObj;

class CamManager : public IManager, public mm::mtl::Singleton<CamManager> {
public:
  static constexpr u32 CAM_COUNT = 8;
  static constexpr u32 INTERFACE_COUNT = 4;

  enum {
    FLAG_STREAM_MODE = 1 << 0,
    FLAG_OFFSCR_MODE = 1 << 1,
    FLAG_FOCAL = 1 << 2,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
    DISP_FLAG_FREE_CAM = 1 << 1,
  };

  CamManager();
  virtual ~CamManager() {}
  bool isOffscrMode() const;
  u32 getOffscrID() const;
  bool isFreeCam() const;
  void clear();
  void destroyCam(CamObj *cam);
  void init();
  void update();
  void render();
  void setStreamMode(bool isStreamMode);
  void loadResource(const char *name);
  void setOffscrMode(bool isOffscrMode, u32 offscrID);
  CamObj *createCam(u32 screenID);
  CamFree *getFreeCam();
  void setFreeCam(bool isFreeCam);
  void setDisp(bool isDisp);
  bool isDisp() const;
  void setFocal(bool isFocal);
  bool isFocal() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      flags |= flag;
    } else {
      flags &= ~flag;
    }
  }

  void setDispFlag(u32 flag, bool isSet) {
    if (isSet) {
      dispFlags |= flag;
    } else {
      dispFlags &= ~flag;
    }
  }

  u32 flags;
  u32 dispFlags;
  mm::mtl::FixedVector<CamObj *, CAM_COUNT> mCams;
  mm::mtl::FixedVector<CamInterface *, INTERFACE_COUNT> mInterfaces;
  CamObj *mMainCam;
  CamFree mFreeCam;
  u32 mOffscrID;
};

static_assert(sizeof(CamManager) == 0x100, "");

} // namespace event
