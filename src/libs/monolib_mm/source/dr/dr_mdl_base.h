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
  enum UpdateFlag {
    UPDATE_FLAG_DISP = 1 << 0,
    UPDATE_FLAG_CLIP = 1 << 1,
    UPDATE_FLAG_DELETE_CALL = 1 << 3,
  };

  virtual ~DrMdlBase() {}
  virtual void update() = 0;
  virtual void dispOffUpdate();
  virtual void noOffScreenUpdate();
  virtual void resourceInit() = 0;
  virtual void shadowRender();
  virtual bool shadowCacheRender(DrPixlShadowCacheObj &cache);
  virtual void shadowCacheAddRender(int index);
  virtual void shadowCacheOnlyRender();
  virtual void shadowPartsRender(int index);
  virtual void callShadowCacheUpdate(u64 flags);
  virtual void occRender();
  virtual bool cloneMdlObj(DrMdlObj *source);
  virtual void chageShadowObject(DrMdoSmlShadowMan *shadowMan);
  virtual void setDisp(bool isDisp);
  virtual void setDeleteCall(int deleteCall);

  void setClip(bool isClip) {
    if (isClip) {
      unknown20 |= UPDATE_FLAG_CLIP;
    } else {
      unknown20 &= ~UPDATE_FLAG_CLIP;
    }
  }

  u8 _08[0x10 - 0x08];
  DrMdlBase *unknown10; // Inferred role: next model; original member name unknown.
  s16 unknown18;        // Inferred role: groups; original member name unknown.
  s16 unknown1a;        // Inferred role: view num; original member name unknown.
  u8 unknown1c;         // Inferred role: type; original member name unknown.
  u8 unknown1d;         // Inferred role: change view num; original member name unknown.
  u8 _1e[0x20 - 0x1e];
  u32 unknown20; // Inferred role: update flags; original member name unknown.
};

static_assert(offsetof(DrMdlBase, unknown10) == 0x10, "");
static_assert(offsetof(DrMdlBase, unknown18) == 0x18, "");
static_assert(offsetof(DrMdlBase, unknown1a) == 0x1a, "");
static_assert(offsetof(DrMdlBase, unknown1c) == 0x1c, "");
static_assert(offsetof(DrMdlBase, unknown1d) == 0x1d, "");
static_assert(offsetof(DrMdlBase, unknown20) == 0x20, "");

} // namespace ml
