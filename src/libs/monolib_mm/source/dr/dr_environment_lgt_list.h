#pragma once
#include <stddef.h>

namespace ml {
class DrLightObj;
struct LgtObjData;
struct LgtPosData;

class DrEnvironmentLgtList {
public:
  void setLgtObjData(const LgtObjData *data);
  void setLgtPosData(const LgtPosData *data);
  void setLightObj(DrLightObj *lightObj);

  const LgtObjData *unknown00; // Inferred role: light object data; original member name unknown.
  const LgtPosData *unknown08; // Inferred role: light position data; original member name unknown.
  DrLightObj *unknown10;       // Inferred role: light object; original member name unknown.
};

static_assert(offsetof(DrEnvironmentLgtList, unknown08) == 0x08, "");
static_assert(offsetof(DrEnvironmentLgtList, unknown10) == 0x10, "");

} // namespace ml
