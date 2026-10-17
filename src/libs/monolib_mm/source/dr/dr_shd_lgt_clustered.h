#pragma once
#include <stddef.h>

#include "dr/dr_shd_lgt_dynamic.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "types.h"

namespace grlib {
class CGLibTexture;
} // namespace grlib

namespace ml {

class DrShdLgtClustered : public DrShdLgtDynamic {
public:
  struct ClusterSetting {
    s32 divX;
    s32 divY;
    s32 divZ;
    u8 _0c[0x14 - 0xc];
  };

  struct ViewInfo {
    grlib::CGLibDblUniformBlock pntLight;
    grlib::CGLibDblUniformBlock sptLight;
    grlib::CGLibDblUniformBlock pointerList;
    grlib::CGLibDblUniformBlock lightList;
    u8 _e0[0x118 - 0xe0];
    grlib::CGLibDblUniformBlock param;
    u8 _150[0x188 - 0x150];
    u8 *lightListData;
  };

  ~DrShdLgtClustered() override;
  const ClusterSetting *getClusterSetting(u32 cate) const;
  void update() override;
  void delViewInfo(int cate) override;
  void setPntLightUniformBlock(u32 cate, u32 index);
  void setSptLightUniformBlock(u32 cate, u32 index);
  void setPointerListUniformBlock(u32 cate, u32 index);
  void setLightListUniformBlock(u32 cate, u32 index);
  void setParamUniformBlock(u32 cate, u32 index);
  void setPntLightStorageBuffer(u32 cate, u32 index);
  void setSptLightStorageBuffer(u32 cate, u32 index);
  void setPointerListStorageBuffer(u32 cate, u32 index);
  void setLightListStorageBuffer(u32 cate, u32 index);
  void setParamStorageBuffer(u32 cate, u32 index);
  grlib::CGLibTexture *getLightListTexture(u32 cate) const;
  void beginLightList();
  void setLightListData(u32 index, int data);
  u8 getLightListData(u32 index);
  void endLightList();
  void debugRender() override;

  static const ClusterSetting c_ClusterSettings[4];

  bool m_isLowResolution;
  ViewInfo m_viewInfos[3];
};

static_assert(sizeof(DrShdLgtClustered::ViewInfo) == 0x190, "");
static_assert(offsetof(DrShdLgtClustered, m_isLowResolution) == 0x18, "");
static_assert(offsetof(DrShdLgtClustered, m_viewInfos) == 0x20, "");

} // namespace ml
