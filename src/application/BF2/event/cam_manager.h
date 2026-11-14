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
  static constexpr u32 CAM_UNKNOWN_8 = 8;       // Inferred role: cam count; original name unknown.
  static constexpr u32 INTERFACE_UNKNOWN_4 = 4; // Inferred role: interface count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: stream mode flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: offscr mode flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: focal flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp flag; original name unknown.
    DISP_FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: free cam flag; original name unknown.
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
  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md, decision 2026-11-14 #26): inline flag helper, no game symbol gives its name; rename if a sibling build gives a symbol.
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown10 |= flag;
    } else {
      unknown10 &= ~flag;
    }
  }

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md, decision 2026-11-14 #26): inline flag helper, no game symbol gives its name; rename if a sibling build gives a symbol.
  void setDispFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown14 |= flag;
    } else {
      unknown14 &= ~flag;
    }
  }

  u32 unknown10;                                                       // Inferred role: flags; original member name unknown.
  u32 unknown14;                                                       // Inferred role: disp flags; original member name unknown.
  mm::mtl::FixedVector<CamObj *, CAM_UNKNOWN_8> unknown18;             // Inferred role: cams; original member name unknown.
  mm::mtl::FixedVector<CamInterface *, INTERFACE_UNKNOWN_4> unknown60; // Inferred role: interfaces; original member name unknown.
  CamObj *unknown88;                                                   // Inferred role: main cam; original member name unknown.
  CamFree m_freeCam;
  u32 m_offscrID;
};

static_assert(sizeof(CamManager) == 0x100, "");

} // namespace event
