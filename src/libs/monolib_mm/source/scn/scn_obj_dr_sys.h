#pragma once
#include <stddef.h>

#include "ml/scn_obj_clip.h"
#include "ml/scn_obj_env_coli.h"
#include "ml/scn_obj_ibl.h"
#include "ml/scn_obj_light.h"
#include "mm_mtl/fixstr.h"
#include "scn/scn_obj_model_dr_sys.h"
#include "types.h"

namespace ml {
class DrCalcClipObj;
class DrEnvColiObj;
class DrEnvironmentObj;
class DrGlobalIBLPack;
class Scn;
class ScnObj;

class ScnObjClipDySys : public ScnObjClip {
public:
  ScnObjClipDySys(Scn *scn, const void *data, int screen);
  void createClipObj(const void *data);
  ~ScnObjClipDySys() override;
  static ScnObj *create(Scn *scn, const void *data, int screen);
  const char *getName() const override;

  DrCalcClipObj *m_drCalcClipObj; // Inferred role: clip object; original member name unknown.
  int unknown60;                  // Inferred role: screen; original member name unknown.
  mm::mtl::FixStr<64> m_name;
};

static_assert(offsetof(ScnObjClipDySys, m_drCalcClipObj) == 0x58, "");
static_assert(offsetof(ScnObjClipDySys, unknown60) == 0x60, "");
static_assert(offsetof(ScnObjClipDySys, m_name) == 0x64, "");

class ScnObjEnvColiDr : public ScnObjEnvColi {
public:
  ScnObjEnvColiDr(Scn *scn, const void *data, int screen);
  ~ScnObjEnvColiDr() override;
  void setPause(bool isPause);
  bool isPause() const;
  static ScnObj *create(Scn *scn, const void *data, int screen);

  DrEnvColiObj *m_drEnvColiObj; // Inferred role: env coli object; original member name unknown.
};

static_assert(offsetof(ScnObjEnvColiDr, m_drEnvColiObj) == 0x58, "");

class ScnObjIBLDr : public ScnObjIBL {
public:
  ScnObjIBLDr(Scn *scn, const void *data, int screen);
  void createIBLObj(const void *data);
  ~ScnObjIBLDr() override;
  static ScnObj *create(Scn *scn, const void *data, int screen);
  void setReferencePos(const mm::Vec3 &position) override;
  const mm::Vec3 &getReferencePos() const override;
  void setFromCaptureTool() override;
  void dispDebugWindow(bool isOpen, const char *title, WinProc *window) override;
  void apply() override;
  void setName(const char *name) override;
  const char *getName() const override;

  DrGlobalIBLPack *m_drGlobalIBLPack; // Inferred role: pack; original member name unknown.
  int unknown20;                      // Inferred role: screen; original member name unknown.
};

static_assert(offsetof(ScnObjIBLDr, m_drGlobalIBLPack) == 0x18, "");
static_assert(offsetof(ScnObjIBLDr, unknown20) == 0x20, "");

class ScnObjLightDrSys : public ScnObjLight {
public:
  ScnObjLightDrSys(Scn *scn, const void *data, int screen);
  void createDrLgt();
  ~ScnObjLightDrSys() override;
  void apply() override;
  void tail() override;
  f32 getFrame() const override;
  void setFrame(f32 frame) override;
  f32 getMaxFrame() const override;
  void setFrameSpd(f32 speed) override;
  f32 getFrameSpd() const override;
  void setGroup(int group) override;
  int getGroup() const override;
  void setOffsetPos(const mm::Vec3 &position) override;
  const mm::Vec3 &getOffsetPos() const override;
  void setDeugDisp2D(bool isDisp) override;
  void setFromCaptureTool() override;
  void setLocalIBLName(const char *name) override;
  static ScnObj *create(Scn *scn, const void *data, int screen);
  bool isEnv() const override;

  const void *m_data;
  DrEnvironmentObj *m_drEnvironmentObj; // Inferred role: dr env; original member name unknown.
  int unknown328;                       // Inferred role: screen; original member name unknown.
};

static_assert(offsetof(ScnObjLightDrSys, m_data) == 0x318, "");
static_assert(offsetof(ScnObjLightDrSys, m_drEnvironmentObj) == 0x320, "");
static_assert(offsetof(ScnObjLightDrSys, unknown328) == 0x328, "");

class ScnObjModelDrSysStandard : public ScnObjModelDrSys {
public:
  ScnObjModelDrSysStandard(Scn *scn, const void *data, const char *name, int screen);
  void createScnMdl(int screen);
  ~ScnObjModelDrSysStandard() override;
  void update() override;
  void apply() override;
  void tail() override;
  static ScnObjModelDrSysStandard *create(Scn *scn, const void *data, const char *name, int screen);

  void *_438;
};

static_assert(offsetof(ScnObjModelDrSysStandard, _438) == 0x438, "");

} // namespace ml
