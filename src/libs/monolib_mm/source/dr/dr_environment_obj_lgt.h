#pragma once
#include <stddef.h>

#include "dr/dr_environment_anim.h"
#include "dr/dr_environment_obj.h"
#include "dr/dr_environment_tex.h"
#include "dr/dr_environment_time.h"
#include "dr/dr_man.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class DrCalcViewWork;
class DrEnvironmentLgtList;
class DrFogObjGbl;
class DrLightObj;
class DrLightObjAmb;
class DrLightObjDir;
class DrLightObjLocalIBL;
class DrLightObjPnt;
class DrLightObjSpt;
class DrResWrkClipList;
class DrShdLgtMan;

struct LgtPosData {
  f32 unknown00[16]; // Inferred role: matrix, passed to the setMat of the lights; original member name unknown.
  u8 _40[0x4c - 0x40];
  f32 unknown4c;    // Inferred role: light size; original member name unknown.
  f32 unknown50[3]; // Inferred role: range center; original member name unknown.
  f32 unknown5c;    // Inferred role: range radius; original member name unknown.
  u16 unknown60;    // Inferred role: 1-based index in the clip list, 0 when not clipped; original member name unknown.
  u16 unknown62;    // Inferred role: index in the DrMan global table that hides the light; original member name unknown.
  u8 _64[0x70 - 0x64];
};

static_assert(offsetof(LgtPosData, unknown4c) == 0x4c, "");
static_assert(offsetof(LgtPosData, unknown50) == 0x50, "");
static_assert(offsetof(LgtPosData, unknown5c) == 0x5c, "");
static_assert(offsetof(LgtPosData, unknown60) == 0x60, "");
static_assert(offsetof(LgtPosData, unknown62) == 0x62, "");
static_assert(sizeof(LgtPosData) == 0x70, "");

struct LgtPosTreeRange {
  f32 unknown00[3]; // Inferred role: range max; original member name unknown.
  f32 unknown0c[3]; // Inferred role: range min; original member name unknown.
  u32 unknown18;    // Inferred role: offset of the child range indices; original member name unknown.
  u32 unknown1c;    // Inferred role: offset of the light indices; original member name unknown.
  u16 unknown20;    // Inferred role: child range count; original member name unknown.
  u16 unknown22;    // Inferred role: light count; original member name unknown.
};

static_assert(offsetof(LgtPosTreeRange, unknown0c) == 0x0c, "");
static_assert(offsetof(LgtPosTreeRange, unknown18) == 0x18, "");
static_assert(offsetof(LgtPosTreeRange, unknown22) == 0x22, "");
static_assert(sizeof(LgtPosTreeRange) == 0x24, "");

// Layout from the constructor (1.0.0: 0x71007dff5c), releaseLgt (0x71007e0098) and the callbacks; the class is 0x240 bytes (DrEnvironmentMan::createObj).
class DrEnvironmentObjLgt : public DrEnvironmentObj {
public:
  // Inferred type: fog table of the light file, at LgtFileHeader::unknown14; the original type name is unknown.
  struct unknown001 {
    u32 unknown00; // Inferred role: offset of the LgtGlbFogObj entries; original member name unknown.
    u32 unknown04; // Inferred role: fog count; original member name unknown.
  };

  // Inferred type: directional light data of the light file, at LgtObjData::unknown00; the original type name is unknown.
  struct unknown002 {
    u8 _00;
    u8 unknown01;  // Inferred role: alpha in percent; original member name unknown.
    u16 unknown02; // Inferred role: soft shadow when 1; original member name unknown.
    f32 unknown04; // Inferred role: intensity; original member name unknown.
  };

  // Inferred type: ambient light data of the light file, at LgtObjData::unknown00; the original type name is unknown.
  struct unknown003 {
    f32 unknown00; // Inferred role: toon gradation value; original member name unknown.
  };

  // Inferred type: point light data of the light file, at LgtObjData::unknown00; the original type name is unknown.
  struct unknown004 {
    u16 unknown00; // Inferred role: soft shadow when 1; original member name unknown.
    u8 _02[0x08 - 0x02];
    f32 unknown08; // Inferred role: spe intensity; original member name unknown.
    f32 unknown0c; // Inferred role: light value copied into DrLightObjPnt::unknownac; original member name unknown.
  };

  // Inferred type: spot light data of the light file, at LgtObjData::unknown00; the original type name is unknown.
  struct unknown005 {
    u16 unknown00; // Inferred role: soft shadow when 1; original member name unknown.
    u8 _02[0x08 - 0x02];
    f32 unknown08; // Inferred role: light value copied into DrLightObjSpt::unknowne0; original member name unknown.
    f32 unknown0c; // Inferred role: light value copied into DrLightObjSpt::unknownd0; original member name unknown.
    f32 unknown10; // Inferred role: angle; original member name unknown.
    f32 unknown14; // Inferred role: light value copied into DrLightObjSpt::unknowne4; original member name unknown.
    u8 _18[0x1c - 0x18];
    f32 unknown1c; // Inferred role: light value copied into DrLightObjSpt::unknownd8, 4.0 when not positive; original member name unknown.
    f32 unknown20; // Inferred role: light value copied into DrLightObjSpt::unknowndc; original member name unknown.
  };

  // Inferred type: weather variant list of a fog, at the table of LgtFileHeader offset 0x24; the original type name is unknown.
  struct unknown008 {
    s32 unknown00; // Inferred role: variant count; original member name unknown.
    u32 unknown04; // Inferred role: offset of the variants, pairs of weather and LgtGlbFogObj index; original member name unknown.
    s16 unknown08; // Inferred role: weather of the base fog; original member name unknown.
    u8 _0a[0x14 - 0x0a];
  };

  // Inferred type: light object table of the light file, at LgtFileHeader::unknown08; the original type name is unknown.
  struct unknown010 {
    s32 unknown00; // Inferred role: light object count; original member name unknown.
    s32 unknown04; // Inferred role: offset of the LgtObjData entries; original member name unknown.
    u32 unknown08; // Inferred role: offset of the texture table; original member name unknown.
    s32 unknown0c; // Inferred role: texture count; original member name unknown.
    u32 unknown10; // Inferred role: ambient light count; original member name unknown.
    u32 unknown14; // Inferred role: directional light count; original member name unknown.
    u32 unknown18; // Inferred role: point light count; original member name unknown.
    u32 unknown1c; // Inferred role: spot light count; original member name unknown.
    u8 _20[0x28 - 0x20];
    u32 unknown28; // Inferred role: offset of the animation data; original member name unknown.
    u32 unknown2c; // Inferred role: local IBL light count; original member name unknown.
  };

  // Inferred type: light position table of the light file, at LgtFileHeader::unknown0c; the original type name is unknown.
  struct unknown011 {
    s32 unknown00; // Inferred role: light position count; original member name unknown.
    s32 unknown04; // Inferred role: offset of the LgtPosData entries; original member name unknown.
    u8 _08[0x0c - 0x08];
    s32 unknown0c; // Inferred role: offset of the LgtPosTreeRange entries; original member name unknown.
  };

  // Inferred type: fog weather variant table of the light file, at LgtFileHeader::unknown24; the original type name is unknown.
  struct unknown012 {
    u8 _00[0x04];
    u32 unknown04; // Inferred role: offset of the unknown008 entries; original member name unknown.
  };

  // Inferred role: tells whether the DrMan global table hides the light of index id (0 is never hidden); original name unknown.
  bool unknown006(u32 id) const { return id != 0 && unknown18->isGblIdx(id); }

  // Inferred role: swaps the render list buffers and starts an empty frame list; original name unknown.
  void unknown007() {
    DrEnvironmentLgtList **lists = unknown1a0;
    unknown1a0 = unknown1a8;
    unknown1a8 = lists;
    *unknown1a0 = nullptr;
    unknown1e4 = unknown1e0;
    unknown1e0 = 0;
  }

  ~DrEnvironmentObjLgt() override;
  void releaseLgt();
  void resourceInit() override;
  void setupLgt(int screen);
  void setupFog(DrFogObjGbl *fog, const LgtGlbFogObj *data);
  void setupAmbient(DrEnvironmentLgtList *list, DrLightObjAmb *light, const LgtObjData *data, int screen);
  void setupDirectinal(DrEnvironmentLgtList *list, DrLightObjDir *light, const LgtObjData *data, const LgtPosData *pos);
  void setupPoint(DrEnvironmentLgtList *list, DrLightObjPnt *light, const LgtObjData *data, const LgtPosData *pos);
  void setupSpot(DrEnvironmentLgtList *list, DrLightObjSpt *light, const LgtObjData *data, const LgtPosData *pos);
  void setupBox(DrEnvironmentLgtList *list, DrLightObjSpt *light, const LgtObjData *data, const LgtPosData *pos);
  void setupCapsule(DrEnvironmentLgtList *list, DrLightObjSpt *light, const LgtObjData *data, const LgtPosData *pos);
  void setupOfsPos();
  void setupCalcMatrix();
  void setFrame(f32 frame) override;
  void update() override;
  void updatePosLgt();
  void updateFog();
  void calcLgtPos(DrCalcViewWork *viewWork);
  void calcTreePos(const LgtPosTreeRange *range, DrCalcViewWork *viewWork);
  void calcLgtObj(int index, DrCalcViewWork *viewWork);
  void renderLgt() override;
  void debugRenderLgt() override;
  void debugRenderLgt2D() override;
  void changeMemCall(const void *data) override;
  bool callback_Chk_Ambinet_Directional(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data);
  bool callback_Chk_Point(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data);
  bool callback_Chk_Spot(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data);
  bool callback_Chk_non(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data);
  bool callback_Chk_LocalIBL(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data);
  bool callback_Calc_Ambient(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork);
  bool callback_Calc_Directional(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork);
  bool callback_Calc_Point(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork);
  bool callback_Calc_Spot(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork);
  bool callback_Calc_Non(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork);
  bool callback_Calc_LocalIBL(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork);
  void callback_Ren_Non(DrLightObj *light, DrShdLgtMan *shdLgtMan);
  void callback_Ren_Point(DrLightObj *light, DrShdLgtMan *shdLgtMan);
  void callback_Ren_Spot(DrLightObj *light, DrShdLgtMan *shdLgtMan);
  void callback_Ren2D_Non(DrLightObj *light, DrShdLgtMan *shdLgtMan);
  void callback_Ren2D_LocalIBL(DrLightObj *light, DrShdLgtMan *shdLgtMan);
  void callback_Relase_Non(DrLightObj *light);
  void callback_Relase_Point(DrLightObj *light);
  void callback_Relase_Spot(DrLightObj *light);
  void callback_Fog_Gbl(DrFogObjGbl *fog, DrCalcViewWork *viewWork, const LgtGlbFogObj *data);

  static void (DrEnvironmentObjLgt::*s_pCallEnvRelase[])(DrLightObj *light);
  static bool (DrEnvironmentObjLgt::*s_pCallEnvChk[])(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data);
  static bool (DrEnvironmentObjLgt::*s_pCallCalcEnv[])(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork);
  static void (DrEnvironmentObjLgt::*s_pCallLgtRender[])(DrLightObj *light, DrShdLgtMan *shdLgtMan);
  static void (DrEnvironmentObjLgt::*s_pCallLgtRender2D[])(DrLightObj *light, DrShdLgtMan *shdLgtMan);
  static void (DrEnvironmentObjLgt::*s_pCallFogCall[])(DrFogObjGbl *fog, DrCalcViewWork *viewWork, const LgtGlbFogObj *data);

  DrEnvironmentTex unknown98;  // Inferred role: textures; original member name unknown.
  DrEnvironmentTime unknowna8; // Inferred role: time; original member name unknown.
  u8 _d8[0xe0 - 0xd8];
  DrEnvironmentAnim unknowne0;       // Inferred role: animation; original member name unknown.
  int unknown150;                    // Inferred role: screen, passed to setupLgt; original member name unknown.
  const LgtFileHeader *unknown158;   // Inferred role: light file data; original member name unknown.
  const LgtObjData *unknown160;      // Inferred role: light object data; original member name unknown.
  const LgtGlbFogObj *unknown168;    // Inferred role: fogs of the light file; original member name unknown.
  const LgtPosTreeRange *unknown170; // Inferred role: position tree ranges; original member name unknown.
  const unknown008 *unknown178;      // Inferred role: weather variant lists of the fogs; original member name unknown.
  void *unknown180;                  // Inferred role: work memory of the lights, fogs and lists; original member name unknown.
  u32 *unknown188;                   // Inferred role: bits of the lights checked this frame; original member name unknown.
  DrResWrkClipList *unknown190;      // Inferred role: clip list; original member name unknown.
  DrEnvironmentLgtList *unknown198;  // Inferred role: light lists; original member name unknown.
  DrEnvironmentLgtList **unknown1a0; // Inferred role: lists to render; original member name unknown.
  DrEnvironmentLgtList **unknown1a8; // Inferred role: lists to render of the other buffer; original member name unknown.
  DrLightObjAmb *unknown1b0;         // Inferred role: ambient lights; original member name unknown.
  DrLightObjDir *unknown1b8;         // Inferred role: directional lights; original member name unknown.
  DrLightObjPnt *unknown1c0;         // Inferred role: point lights; original member name unknown.
  DrLightObjSpt *unknown1c8;         // Inferred role: spot lights; original member name unknown.
  DrLightObjLocalIBL *unknown1d0;    // Inferred role: local IBL lights; original member name unknown.
  DrFogObjGbl *unknown1d8;           // Inferred role: global fogs; original member name unknown.
  int unknown1e0;                    // Inferred role: count of the lists to render; original member name unknown.
  int unknown1e4;                    // Inferred role: count of the lists to render of the other buffer; original member name unknown.
  int unknown1e8;                    // Inferred role: ambient light count; original member name unknown.
  int unknown1ec;                    // Inferred role: directional light count; original member name unknown.
  int unknown1f0;                    // Inferred role: point light count; original member name unknown.
  int unknown1f4;                    // Inferred role: spot light count; original member name unknown.
  int unknown1f8;                    // Inferred role: local IBL light count; original member name unknown.
  int unknown1fc;                    // Inferred role: light count; original member name unknown.
  int unknown200;                    // Inferred role: fog count; original member name unknown.
  int unknown204;                    // Inferred role: set to 1 by the constructor, cleared by update; original member name unknown.
  int unknown208;                    // Inferred role: weather value seen by update; original member name unknown.
  u8 _20c[0x210 - 0x20c];
  mm::Vec3 unknown210; // Inferred role: camera position in the object space; original member name unknown.
  mm::Vec3 unknown220; // Inferred role: previous camera position; original member name unknown.
  mm::Col3 unknown230; // Inferred role: ambient color copied into DrLightMan::unknown12c by updatePosLgt; original member name unknown.
  u8 unknown23c;       // Inferred role: capture tool state; original member name unknown.
};

static_assert(sizeof(DrEnvironmentObjLgt::unknown001) == 0x08, "");
static_assert(offsetof(DrEnvironmentObjLgt::unknown010, unknown28) == 0x28, "");
static_assert(offsetof(DrEnvironmentObjLgt::unknown011, unknown0c) == 0x0c, "");
static_assert(offsetof(DrEnvironmentObjLgt::unknown012, unknown04) == 0x04, "");
static_assert(sizeof(DrEnvironmentObjLgt::unknown008) == 0x14, "");
static_assert(offsetof(DrEnvironmentObjLgt::unknown008, unknown08) == 0x08, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown98) == 0x98, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknowna8) == 0xa8, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknowne0) == 0xe0, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown150) == 0x150, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown180) == 0x180, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown190) == 0x190, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown1d8) == 0x1d8, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown1e8) == 0x1e8, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown1fc) == 0x1fc, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown208) == 0x208, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown210) == 0x210, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown230) == 0x230, "");
static_assert(offsetof(DrEnvironmentObjLgt, unknown23c) == 0x23c, "");
static_assert(sizeof(DrEnvironmentObjLgt) == 0x240, "");

} // namespace ml
