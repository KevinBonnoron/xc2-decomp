#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrMdlObj;
class DrMdoSmlShadowMan;
class DrPixlShadowCacheObj;

// Inferred role: mdl type; original type name unknown.
enum unknown037 {
  unknown037_0, // Inferred role: normal; original name unknown.
  unknown037_1, // Inferred role: position; original name unknown.
  unknown037_2, // Inferred role: mpf; original name unknown.
  unknown037_3, // Inferred role: seam; original name unknown.
  unknown037_4, // Inferred role: cloud model; original name unknown.
};

class DrMdlBase {
public:
  // Inferred role: update flag; original type name unknown.
  enum unknown038 {
    unknown038_0 = 1 << 0, // Inferred role: disp; original name unknown.
    unknown038_1 = 1 << 1, // Inferred role: clip; original name unknown.
    unknown038_3 = 1 << 3, // Inferred role: delete call; original name unknown.
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
      unknown20 |= unknown038_1;
    } else {
      unknown20 &= ~unknown038_1;
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
