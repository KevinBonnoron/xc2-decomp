#pragma once
#include <stddef.h>

#include "dr/dr_res_fetch.h"
#include "grlib/cglib_shd_list.h"
#include "types.h"

namespace mm {
struct Col3;
struct Quat;
struct Vec3;
} // namespace mm

namespace ml {
class DrLightObjPnt;
class DrLightObjSpt;
class DrMan;
class FileResTh;
class DrShdLgtClustered;
class DrShdLgtGlobalIBL;
class DrShdLgtHybrid;
class DrShdLgtObj;

class DrShdLgtMan {
public:
  enum COMP_SHADER_TYPE {};
  enum GIBL_SHADER_TYPE {};
  enum DECLARATION {};
  enum RENDER_DEBUG_TYPE {
    RENDER_DEBUG_TYPE_UNKNOWN_0 = 0, // Inferred role: point light.
  };

  static const char *s_DeclarationNames[19]; // Name from the game symbol _ZN2ml11DrShdLgtMan18s_DeclarationNamesE; also in torna and xc1de.

  DrShdLgtMan(DrMan *drMan);
  ~DrShdLgtMan();
  void renderDebugPnt(DrLightObjPnt *light);
  void renderDebugSpt(DrLightObjSpt *light);
  void renderDebug(RENDER_DEBUG_TYPE type, const mm::Vec3 &position, const mm::Quat &rotation, const mm::Vec3 &scale, const mm::Col3 &color);
  DrShdLgtHybrid *getHybridLight();
  void releaseLightShader();
  void reloadShader(int);
  bool createLightShader();
  const char *getDeclarationName(DECLARATION type) const;
  void renderBegin();
  DrShdLgtObj *getGlobalIBLShader(GIBL_SHADER_TYPE type);
  DrShdLgtObj *getComputeShader(COMP_SHADER_TYPE type);
  void beforeUpdateCate(int viewNum);
  void resetColorBuff(int index);
  void setupLocalIBLShader(DrShdLgtObj *obj);
  void setupGlobalIBLShader(DrShdLgtObj *obj);
  void stockBegin();
  void stockEnd();
  void setupLgtBuff();
  void updateCate(int cate);
  void setupCate(int cate);
  void addViewInfo(int cate);
  void delViewInfo(int cate);

  DrMan *unknown00;                                // Inferred role: dr man; original member name unknown.
  FileResTh *unknown08;                            // Inferred role: shader file resource; original member name unknown.
  grlib::CGLibShdListBase<DrShdLgtObj> *unknown10; // Inferred role: shader list; original member name unknown.
  DrShdLgtObj *unknown18[3];                       // Inferred role: first shader of each shader group ([1] global IBL, [2] compute); original member name unknown.
  DrResFetch unknown30;                            // Inferred role: IBL vertex fetch; original member name unknown.
  u16 unknown40;                                   // Inferred role: light buffer count; original member name unknown.
  u16 unknown42;                                   // Inferred role: light buffer index; original member name unknown.
  u16 unknown44;                                   // Inferred role: light buffer previous index; original member name unknown.
  u16 _46;
  u32 unknown48; // Inferred role: light buffer state; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  DrShdLgtHybrid *m_hybridLight;
  DrShdLgtGlobalIBL *unknown58; // Inferred role: global IBL; original member name unknown.
  DrShdLgtClustered *unknown60; // Inferred role: clustered light; original member name unknown.
};

static_assert(offsetof(DrShdLgtMan, unknown00) == 0x00, "");
static_assert(offsetof(DrShdLgtMan, unknown08) == 0x08, "");
static_assert(offsetof(DrShdLgtMan, unknown10) == 0x10, "");
static_assert(offsetof(DrShdLgtMan, unknown18) == 0x18, "");
static_assert(offsetof(DrShdLgtMan, unknown30) == 0x30, "");
static_assert(offsetof(DrShdLgtMan, unknown40) == 0x40, "");
static_assert(offsetof(DrShdLgtMan, unknown48) == 0x48, "");
static_assert(offsetof(DrShdLgtMan, m_hybridLight) == 0x50, "");
static_assert(offsetof(DrShdLgtMan, unknown58) == 0x58, "");
static_assert(offsetof(DrShdLgtMan, unknown60) == 0x60, "");

} // namespace ml
