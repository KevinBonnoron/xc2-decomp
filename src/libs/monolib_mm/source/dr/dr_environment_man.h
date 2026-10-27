#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrEnvColiMan;
class DrEnvironmentObj;

class DrEnvironmentMan {
public:
  DrEnvironmentObj *createObj(const void *data);
  void releaseObj(DrEnvironmentObj *obj);
  void renderLgt();
  void releaseAll();
  void setZoneObj(DrEnvironmentObj *obj, bool isOn);

  u8 _00[0x18 - 0x00];
  DrEnvColiMan *unknown18; // Inferred role: env coli man; original member name unknown.
  u8 _20[0x28 - 0x20];
  DrEnvironmentObj *unknown28[4]; // Inferred role: first and last object of the request list per buffer; original member name unknown.
  DrEnvironmentObj *unknown48;    // Inferred role: first object of the list; original member name unknown.
  DrEnvironmentObj *unknown50;    // Inferred role: last object of the list; original member name unknown.
  DrEnvironmentObj *unknown58;    // Inferred role: first object of the release list; original member name unknown.
  DrEnvironmentObj *unknown60;    // Inferred role: last object of the release list; original member name unknown.
};

static_assert(offsetof(DrEnvironmentMan, unknown18) == 0x18, "");
static_assert(offsetof(DrEnvironmentMan, unknown28) == 0x28, "");
static_assert(offsetof(DrEnvironmentMan, unknown48) == 0x48, "");
static_assert(offsetof(DrEnvironmentMan, unknown60) == 0x60, "");

} // namespace ml
