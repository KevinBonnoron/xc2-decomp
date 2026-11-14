#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"

namespace cloud {
class CloudMdlDataObj;
} // namespace cloud

namespace ml {
class DrMan;

class DrMdoCtlCldMdl : public DrMdlObj {
public:
  DrMdoCtlCldMdl(const void *data, DrMan *drMan, int viewNum);
  ~DrMdoCtlCldMdl() override;
  void releaseCldMdl();
  void resourceInit() override;
  void update() override;
  void dispOffUpdate() override;

  cloud::CloudMdlDataObj *unknown1a8; // Inferred role: cloud model data; original member name unknown.
  const void *unknown1b0;             // Inferred role: cloud model resource; original member name unknown.
};

static_assert(offsetof(DrMdoCtlCldMdl, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DrMdoCtlCldMdl, unknown1b0) == 0x1b0, "");
static_assert(sizeof(DrMdoCtlCldMdl) == 0x1c0, "");

} // namespace ml
