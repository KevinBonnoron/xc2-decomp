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

  // Inferred role: camera interface of a screen id; original name unknown.
  CamInterface *unknown001(u32 index) { return unknown60[index]; }

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown10 |= flag;
    } else {
      unknown10 &= ~flag;
    }
  }

  void setDispFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown14 |= flag;
    } else {
      unknown14 &= ~flag;
    }
  }

  u32 unknown10;                                                   // Inferred role: flags; original member name unknown.
  u32 unknown14;                                                   // Inferred role: disp flags; original member name unknown.
  mm::mtl::FixedVector<CamObj *, CAM_COUNT> unknown18;             // Inferred role: cams; original member name unknown.
  mm::mtl::FixedVector<CamInterface *, INTERFACE_COUNT> unknown60; // Inferred role: interfaces; original member name unknown.
  CamObj *unknown88;                                               // Inferred role: main cam; original member name unknown.
  CamFree m_freeCam;
  u32 m_offscrID;
};

static_assert(sizeof(CamManager) == 0x100, "");

} // namespace event
