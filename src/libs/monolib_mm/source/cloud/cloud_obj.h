#pragma once
#include <stddef.h>

namespace cloud {

// Base of the cloud sea-of-clouds objects. update and alphaRender are pure virtual: both entries of
// the game vtable are __cxa_pure_virtual (vtable for cloud::CloudObj 0x71011b12a8).
class CloudObj {
public:
  CloudObj();
  virtual ~CloudObj() {}
  virtual void update() = 0;
  virtual void alphaRender() = 0;
  virtual void alphaRenderSec();

  CloudObj *unknown08; // Inferred role: previous object; original member name unknown.
  CloudObj *unknown10; // Inferred role: next object; original member name unknown.
  void *unknown18;     // Inferred role: owner, the {head, tail, count} list at the start of CloudObjMan; original member name unknown.
};

static_assert(offsetof(CloudObj, unknown08) == 0x08, "");
static_assert(offsetof(CloudObj, unknown10) == 0x10, "");
static_assert(offsetof(CloudObj, unknown18) == 0x18, "");
static_assert(sizeof(CloudObj) == 0x20, "");

} // namespace cloud
