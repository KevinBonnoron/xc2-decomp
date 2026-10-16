#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrMdlObj;
class DrMdoSmlShadowMan;
class DrPixlShadowCacheObj;

enum DrMdlType {
  DR_MDL_TYPE_NORMAL,
  DR_MDL_TYPE_POSITION,
  DR_MDL_TYPE_MPF,
  DR_MDL_TYPE_SEAM,
  DR_MDL_TYPE_CLOUD_MODEL,
};

class DrMdlBase {
public:
  virtual ~DrMdlBase() {}
  virtual void update() = 0;
  virtual void dispOffUpdate();
  virtual void noOffScreenUpdate();
  virtual void resourceInit() = 0;
  virtual void shadowRender();
  virtual void shadowCacheRender(DrPixlShadowCacheObj &cache);
  virtual void shadowCacheAddRender(int index);
  virtual void shadowCacheOnlyRender();
  virtual void shadowPartsRender(int index);
  virtual void callShadowCacheUpdate(u64 flags);
  virtual void occRender();
  virtual void cloneMdlObj(DrMdlObj *source);
  virtual void chageShadowObject(DrMdoSmlShadowMan *shadowMan);
  virtual void setDisp(bool isDisp);
  virtual void setDeleteCall(int deleteCall);

  u8 _08[0x18 - 0x08];
  s16 m_groups;
  s16 m_viewNum;
  u8 m_type;
  u8 m_changeViewNum;
  u8 _1e[0x20 - 0x1e];
  u32 m_updateFlags;
};

static_assert(offsetof(DrMdlBase, m_groups) == 0x18, "");
static_assert(offsetof(DrMdlBase, m_viewNum) == 0x1a, "");
static_assert(offsetof(DrMdlBase, m_type) == 0x1c, "");
static_assert(offsetof(DrMdlBase, m_changeViewNum) == 0x1d, "");
static_assert(offsetof(DrMdlBase, m_updateFlags) == 0x20, "");

} // namespace ml
