#pragma once
#include <stddef.h>

#include "grlib/cglib_vtx_fetch.h"
#include "types.h"

namespace ml {
class DrShdLgtGlobalIBL;
class DrShdLgtHybrid;
class DrShdLgtObj;

class DrShdLgtMan {
public:
  enum COMP_SHADER_TYPE {};
  enum GIBL_SHADER_TYPE {};
  enum DECLARATION {};

  static const char *s_DeclarationNames[19];

  DrShdLgtHybrid *getHybridLight();
  const char *getDeclarationName(DECLARATION type) const;
  void renderBegin();
  DrShdLgtObj *getGlobalIBLShader(GIBL_SHADER_TYPE type);
  DrShdLgtObj *getComputeShader(COMP_SHADER_TYPE type);
  void beforeUpdateCate(int viewNum);
  void resetColorBuff(int index);
  void setupLocalIBLShader(DrShdLgtObj *obj);
  void setupGlobalIBLShader(DrShdLgtObj *obj);

  u8 _00[0x20 - 0x00];
  DrShdLgtObj *unknown20;         // Inferred role: global IBL shaders; original member name unknown.
  DrShdLgtObj *unknown28;         // Inferred role: compute shaders; original member name unknown.
  grlib::CGLibVtxFetch unknown30; // Inferred role: IBL vertex fetch; original member name unknown.
  u16 unknown40;                  // Inferred role: light buffer count; original member name unknown.
  u16 unknown42;                  // Inferred role: light buffer index; original member name unknown.
  u16 unknown44;                  // Inferred role: light buffer previous index; original member name unknown.
  u16 _46;
  u32 unknown48; // Inferred role: light buffer state; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  DrShdLgtHybrid *m_hybridLight;
  DrShdLgtGlobalIBL *unknown58; // Inferred role: global IBL; original member name unknown.
};

static_assert(offsetof(DrShdLgtMan, unknown20) == 0x20, "");
static_assert(offsetof(DrShdLgtMan, unknown28) == 0x28, "");
static_assert(offsetof(DrShdLgtMan, unknown30) == 0x30, "");
static_assert(offsetof(DrShdLgtMan, unknown40) == 0x40, "");
static_assert(offsetof(DrShdLgtMan, unknown48) == 0x48, "");
static_assert(offsetof(DrShdLgtMan, m_hybridLight) == 0x50, "");
static_assert(offsetof(DrShdLgtMan, unknown58) == 0x58, "");

} // namespace ml
