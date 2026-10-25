#pragma once
#include <stddef.h>

#include "dr/dr_man.h"
#include "types.h"

namespace ml {
class DrGpuCheckBase;
class DrMdlObj;
class DrMdoGrpObj;
class DrMdoSmlShadowMan;
class DrMdoZSortMan;
class DrStmReadObj;

class DrMdlMan {
public:
  void renderBegin();
  void setGroupsDisp(s32 group, bool disp);
  void lightPrePassRender();
  void alphaRender();
  void spAlphaRender();
  void GBuffRender();
  void setupRender();
  void ZPrePassRender();
  void ThicknessRenderFirst();
  void ThicknessRenderSecond();
  void refractionRender();
  void simpleShadowRender();
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

  DrMan *unknown000; // Inferred role: dr man; original member name unknown.
  u8 _008[0x030 - 0x008];
  DrMdoSmlShadowMan *unknown030; // Inferred role: small shadow man; original member name unknown.
  u8 _038[0x218 - 0x038];
  DrMdoZSortMan *unknown218; // Inferred role: z sort man; original member name unknown.
  u8 _220[0x238 - 0x220];
  u32 unknown238; // Inferred role: cate; original member name unknown.
  u32 unknown23c; // Inferred role: groups disp; original member name unknown.
};

static_assert(offsetof(DrMdlMan, unknown000) == 0x000, "");
static_assert(offsetof(DrMdlMan, unknown030) == 0x030, "");
static_assert(offsetof(DrMdlMan, unknown218) == 0x218, "");
static_assert(offsetof(DrMdlMan, unknown238) == 0x238, "");
static_assert(offsetof(DrMdlMan, unknown23c) == 0x23c, "");

} // namespace ml
