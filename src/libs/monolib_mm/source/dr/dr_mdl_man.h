#pragma once
#include <stddef.h>

#include "dr/dr_man.h"
#include "types.h"

namespace ml {
class DrGpuCheckBase;
class DrMdlBase;
class DrMdlObj;
class DrMdoGrpObj;
class DrMdoMpfMan;
class DrMdoSamplerMan;
class DrMdoSmlShadowMan;
class DrMdoVertexMan;
class DrMdoZSortMan;
class DrResEtcUniformObj;
class DrResOccUniformObj;
class DrStmReadObj;

class DrMdlMan {
public:
  // Inferred role: list of models; original type name unknown.
  struct unknown002 {
    DrMdlBase *unknown00; // Inferred role: first model; original member name unknown.
  };

  // Inferred role: resource header start; original type name unknown.
  struct unknown003 {
    u32 unknown00; // Inferred role: magic; original member name unknown.
    u32 unknown04; // Inferred role: version; original member name unknown.
  };

  void addMpfObj();
  void delMpfObj();
  void renderBegin();
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
  static void getTextureStreamInfo(u32 &size, u32 &count, const void *data, bool isMiddle);
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

  DrMan *unknown000;          // Inferred role: dr man; original member name unknown.
  DrMdoVertexMan *unknown008; // Inferred role: vertex man; original member name unknown.
  u8 _010[0x018 - 0x010];
  DrMdoSamplerMan *unknown018; // Inferred role: sampler man; original member name unknown.
  DrMdoMpfMan *unknown020;     // Inferred role: mpf man; original member name unknown.
  u8 _028[0x030 - 0x028];
  DrMdoSmlShadowMan *unknown030;  // Inferred role: small shadow man; original member name unknown.
  DrResOccUniformObj *unknown038; // Inferred role: occ uniform; original member name unknown.
  DrResEtcUniformObj *unknown040; // Inferred role: etc uniform; original member name unknown.
  u8 _048[0x218 - 0x048];
  DrMdoZSortMan *unknown218; // Inferred role: z sort man; original member name unknown.
  unknown002 *unknown220;    // Inferred role: model list; original member name unknown.
  u8 _228[0x238 - 0x228];
  u32 unknown238; // Inferred role: cate; original member name unknown.
  u32 unknown23c; // Inferred role: groups disp; original member name unknown.
};

static_assert(offsetof(DrMdlMan, unknown000) == 0x000, "");
static_assert(offsetof(DrMdlMan, unknown008) == 0x008, "");
static_assert(offsetof(DrMdlMan, unknown018) == 0x018, "");
static_assert(offsetof(DrMdlMan, unknown020) == 0x020, "");
static_assert(offsetof(DrMdlMan, unknown030) == 0x030, "");
static_assert(offsetof(DrMdlMan, unknown038) == 0x038, "");
static_assert(offsetof(DrMdlMan, unknown040) == 0x040, "");
static_assert(offsetof(DrMdlMan, unknown218) == 0x218, "");
static_assert(offsetof(DrMdlMan, unknown220) == 0x220, "");
static_assert(offsetof(DrMdlMan, unknown238) == 0x238, "");
static_assert(offsetof(DrMdlMan, unknown23c) == 0x23c, "");

} // namespace ml
