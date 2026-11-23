#pragma once
#include <stddef.h>

#include "dr/dr_res_chank_list.h"
#include "types.h"

namespace ml {
class DrEnvColiMan;
class DrEnvironmentObj;
class DrFogMan;
class DrLightMan;
class DrMan;

class DrEnvironmentMan {
public:
  DrEnvironmentMan(DrMan *drMan, DrLightMan *lightMan, DrFogMan *fogMan, int screen);
  ~DrEnvironmentMan();
  DrEnvironmentObj *createObj(const void *data);
  void releaseObj(DrEnvironmentObj *obj);
  void renderLgt();
  void releaseAll();
  void setZoneObj(DrEnvironmentObj *obj, bool isOn);
  void updateCameraLight();
  void update();

  DrMan *m_drMan;               // Inferred role: dr man; original member name unknown.
  DrLightMan *m_drLightMan;     // Inferred role: light man; original member name unknown.
  DrFogMan *m_drFogMan;         // Inferred role: fog man; original member name unknown.
  DrEnvColiMan *m_drEnvColiMan; // Inferred role: env coli man; original member name unknown.
  int unknown20;                // Inferred role: screen index; original member name unknown.
  u8 _24[0x28 - 0x24];
  DrResChankList<DrEnvironmentObj> unknown28[2]; // Inferred role: request list per buffer; original member name unknown.
  DrResChankList<DrEnvironmentObj> unknown48;    // Inferred role: object list; original member name unknown.
  DrResChankList<DrEnvironmentObj> unknown58;    // Inferred role: release list; original member name unknown.
  DrEnvironmentObj *unknown68;                   // Inferred role: camera light object; original member name unknown.
};

static_assert(offsetof(DrEnvironmentMan, m_drLightMan) == 0x08, "");
static_assert(offsetof(DrEnvironmentMan, m_drFogMan) == 0x10, "");
static_assert(offsetof(DrEnvironmentMan, m_drEnvColiMan) == 0x18, "");
static_assert(offsetof(DrEnvironmentMan, unknown20) == 0x20, "");
static_assert(offsetof(DrEnvironmentMan, unknown28) == 0x28, "");
static_assert(offsetof(DrEnvironmentMan, unknown48) == 0x48, "");
static_assert(offsetof(DrEnvironmentMan, unknown58) == 0x58, "");
static_assert(offsetof(DrEnvironmentMan, unknown68) == 0x68, "");
static_assert(sizeof(DrEnvironmentMan) == 0x70, "");

} // namespace ml
