#pragma once
#include <stddef.h>

#include "dr/dr_man.h"
#include "dr/dr_res_chank_list.h"
#include "types.h"

namespace ml {
class DrGpuCheckBase;
class DrGpuCheckObj;
class DrGpuCheckRender;
class DrMdlBase;
class DrMdlObj;
class DrMdoGrpObj;
class DrMdoMpfMan;
class DrMdoSamplerMan;
class DrMdoSmlShadowMan;
class DrMdoTexSimpleMan;
class DrMdoTextureMan;
class DrMdoVertexMan;
class DrMdoZSortMan;
class DrPixlShadowCacheObj;
class DrPixlShadowObj;
class DrResEtcUniformObj;
class DrResOccUniformObj;
class DrStmReadObj;

class DrMdlMan {
public:
  // Inferred role: resource header start; original type name unknown.
  struct unknown003 {
    u32 unknown00; // Inferred role: magic; original member name unknown.
    u32 unknown04; // Inferred role: version; original member name unknown.
  };

  // Inferred role: model resource header; original type name unknown.
  struct unknown005 {
    u32 unknown00; // Inferred role: magic; original member name unknown.
    u8 _04[0x1c - 0x04];
    u32 unknown1c; // Inferred role: texture stream info presence; original member name unknown.
    u8 _20[0x24 - 0x20];
    u32 unknown24; // Inferred role: texture stream info offset; original member name unknown.
  };

  // Inferred role: model texture stream info; original type name unknown.
  struct unknown006 {
    u8 _00[0x1c - 0x00];
    u32 unknown1c; // Inferred role: middle texture count; original member name unknown.
    u32 unknown20; // Inferred role: texture size; original member name unknown.
    u32 unknown24; // Inferred role: middle texture size; original member name unknown.
  };

  // Inferred role: per category render flags; original type name unknown.
  struct unknown004 {
    bool unknown00; // Inferred role: bloom model rendered; original member name unknown.
    bool unknown01; // Inferred role: alpha bloom model rendered; original member name unknown.
    bool unknown02; // Inferred role: volume model rendered; original member name unknown.
    bool unknown03; // Inferred role: light pre pass model rendered; original member name unknown.
    bool unknown04; // Inferred role: refraction model rendered; original member name unknown.
    bool unknown05; // Inferred role: cleared by DrMdlMan::apply; original member name unknown.
    bool unknown06; // Inferred role: simple shadow displayed; original member name unknown.
    bool unknown07; // Inferred role: full screen shadow model rendered; original member name unknown.
    bool unknown08; // Inferred role: model flag 8 rendered; original member name unknown.
    bool unknown09; // Inferred role: model flag 9 rendered; original member name unknown.
    bool unknown0a; // Inferred role: cleared by DrMdlMan::apply; original member name unknown.
    bool unknown0b; // Inferred role: cleared by DrMdlMan::apply; original member name unknown.
    bool unknown0c; // Inferred role: seam model updated; original member name unknown.
  };

  ~DrMdlMan();
  void deleteAll();
  void DepthCheckRender(bool isDblDepth);
  void setupCate(int cate);
  void setupEnd();
  void applyDispOff(u32 view);
  void apply();
  void addMpfObj();
  void delMpfObj();
  void renderBegin();
  void render();
  bool shadowRender(DrPixlShadowObj *shadow);
  void occRender(bool isFirst);
  bool shadowCacheRender(DrPixlShadowCacheObj &cache);
  void shadowCacheAddRender(int index);
  void callShadowCacheUpdate(u64 flags);
  void setGroupsDisp(s32 group, bool disp);
  void lightPrePassRender();
  void alphaRender();
  void spAlphaRender();
  void GBuffRender();
  void setupRender();
  void beginApply();
  void endApply();
  void ZPrePassRender();
  void ThicknessRenderFirst();
  void ThicknessRenderSecond();
  void refractionRender();
  void simpleShadowRender();
  static int headerChek(const void *data);
  static bool getTextureStreamInfo(u32 &size, u32 &count, const void *data, bool isMiddle);
  void addViewInfo(int cate);
  void delViewInfo(int cate);
  DrMdlObj *createMdl(const void *data, const char *name, int index);
  DrMdlObj *createInstantMdl(const void *data, const char *name, int index);
  DrMdoGrpObj *createGrp(int num, u32 flags);
  DrMdoGrpObj *createInstantGrp(int num, u32 flags);
  DrGpuCheckBase *createGpuCheckObj(int type);
  DrGpuCheckBase *createEffGpuCheckObj(int type);
  DrStmReadObj *createStmLoadObj(const char *path);
  DrStmReadObj *createStmSizeObj(u32 size);

  // Inferred role: true when the DrMan skips the view renders of this category; original name unknown.
  bool unknown001() const {
    u32 cate = unknown238;
    return (unknown000->unknown1c9c & (1 << cate)) != 0;
  }

  DrMan *unknown000;              // Inferred role: dr man; original member name unknown.
  DrMdoVertexMan *unknown008;     // Inferred role: vertex man; original member name unknown.
  DrMdoTextureMan *unknown010;    // Inferred role: texture man; original member name unknown.
  DrMdoSamplerMan *unknown018;    // Inferred role: sampler man; original member name unknown.
  DrMdoMpfMan *unknown020;        // Inferred role: mpf man; original member name unknown.
  DrMdoTexSimpleMan *unknown028;  // Inferred role: simple texture man; original member name unknown.
  DrMdoSmlShadowMan *unknown030;  // Inferred role: small shadow man; original member name unknown.
  DrResOccUniformObj *unknown038; // Inferred role: occ uniform; original member name unknown.
  DrResEtcUniformObj *unknown040; // Inferred role: etc uniform; original member name unknown.
  DrGpuCheckRender *unknown048;   // Inferred role: gpu check render; original member name unknown.
  DrMdoZSortMan *unknown050[4];   // Inferred role: z sort men per category; original member name unknown.
  unknown004 unknown070[4];       // Inferred role: render flags per category; original member name unknown.
  u8 _0a4[0x0a8 - 0x0a4];
  DrResChankList<DrMdlBase> unknown0a8[4]; // Inferred role: models per view; original member name unknown.
  DrResChankList<DrMdlBase> unknown0e8[2]; // Inferred role: models created per buffer; original member name unknown.
  u8 _108[0x148 - 0x108];
  DrResChankList<DrGpuCheckObj> unknown148[4]; // Inferred role: gpu check objects per view; original member name unknown.
  DrResChankList<DrGpuCheckObj> unknown188[2]; // Inferred role: gpu check objects created per buffer; original member name unknown.
  u8 _1a8[0x1e8 - 0x1a8];
  DrResChankList<DrStmReadObj> unknown1e8;    // Inferred role: stream read objects; original member name unknown.
  DrResChankList<DrStmReadObj> unknown1f8[2]; // Inferred role: stream read objects created per buffer; original member name unknown.
  DrMdoZSortMan *unknown218;                  // Inferred role: z sort man; original member name unknown.
  DrResChankList<DrMdlBase> *unknown220;      // Inferred role: model list; original member name unknown.
  DrResChankList<DrGpuCheckObj> *unknown228;  // Inferred role: gpu check object list; original member name unknown.
  unknown004 *unknown230;                     // Inferred role: current category render flags; original member name unknown.
  u32 unknown238;                             // Inferred role: cate; original member name unknown.
  u32 unknown23c;                             // Inferred role: groups disp; original member name unknown.
  u32 unknown240;                             // Inferred role: views whose gpu check objects render; original member name unknown.
};

static_assert(offsetof(DrMdlMan, unknown000) == 0x000, "");
static_assert(offsetof(DrMdlMan, unknown008) == 0x008, "");
static_assert(offsetof(DrMdlMan, unknown010) == 0x010, "");
static_assert(offsetof(DrMdlMan, unknown018) == 0x018, "");
static_assert(offsetof(DrMdlMan, unknown020) == 0x020, "");
static_assert(offsetof(DrMdlMan, unknown028) == 0x028, "");
static_assert(offsetof(DrMdlMan, unknown030) == 0x030, "");
static_assert(offsetof(DrMdlMan, unknown038) == 0x038, "");
static_assert(offsetof(DrMdlMan, unknown040) == 0x040, "");
static_assert(offsetof(DrMdlMan, unknown050) == 0x050, "");
static_assert(offsetof(DrMdlMan, unknown048) == 0x048, "");
static_assert(offsetof(DrMdlMan, unknown0a8) == 0x0a8, "");
static_assert(offsetof(DrMdlMan, unknown0e8) == 0x0e8, "");
static_assert(offsetof(DrMdlMan, unknown148) == 0x148, "");
static_assert(offsetof(DrMdlMan, unknown188) == 0x188, "");
static_assert(offsetof(DrMdlMan, unknown1e8) == 0x1e8, "");
static_assert(offsetof(DrMdlMan, unknown1f8) == 0x1f8, "");
static_assert(offsetof(DrMdlMan, unknown218) == 0x218, "");
static_assert(offsetof(DrMdlMan, unknown220) == 0x220, "");
static_assert(offsetof(DrMdlMan, unknown230) == 0x230, "");
static_assert(offsetof(DrMdlMan, unknown238) == 0x238, "");
static_assert(offsetof(DrMdlMan, unknown23c) == 0x23c, "");
static_assert(offsetof(DrMdlMan, unknown240) == 0x240, "");
static_assert(sizeof(DrMdlMan) == 0x248, "");
static_assert(sizeof(DrMdlMan::unknown004) == 0x0d, "");
static_assert(offsetof(DrMdlMan::unknown005, unknown1c) == 0x1c, "");
static_assert(offsetof(DrMdlMan::unknown005, unknown24) == 0x24, "");
static_assert(offsetof(DrMdlMan::unknown006, unknown1c) == 0x1c, "");
static_assert(offsetof(DrMdlMan::unknown006, unknown24) == 0x24, "");
static_assert(offsetof(DrMdlMan::unknown004, unknown04) == 0x04, "");
static_assert(offsetof(DrMdlMan::unknown004, unknown07) == 0x07, "");
static_assert(offsetof(DrMdlMan::unknown004, unknown0c) == 0x0c, "");

} // namespace ml
