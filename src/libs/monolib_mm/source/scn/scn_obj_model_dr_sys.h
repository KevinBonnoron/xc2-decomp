#pragma once
#include <stddef.h>

#include "ml/scn_obj_model.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {
class DrMan;
class DrMdlObj;
class Scn;

class ScnObjModelDrSys : public ScnObjModel {
public:
  ScnObjModelDrSys(Scn *scn, const void *data, const char *name);
  void update() override;
  void apply() override;
  void setGroups(int groups) override;
  int getGroups() override;
  void setAlpha(f32 alpha) override;
  f32 getAlpha() const override;
  void setWriteStencil(bool isWriteStencil) override;
  void setAlwaysTexStm(bool isAlwaysTexStm) override;
  bool isMdlTexStm() const override;
  bool isMemTexStm() const override;
  const mm::Vec3 &getAABBMax() const override;
  const mm::Vec3 &getAABBMin() const override;
  const mm::Vec3 &getCenter() const override;
  f32 getLength() const override;

  DrMdlObj *m_drMdl;
  DrMan *m_drMan;
  const void *m_data;
  mm::mtl::FixStr<64> _3f0;
};

static_assert(offsetof(ScnObjModelDrSys, m_drMdl) == 0x3d8, "");
static_assert(offsetof(ScnObjModelDrSys, m_data) == 0x3e8, "");
static_assert(offsetof(ScnObjModelDrSys, _3f0) == 0x3f0, "");

} // namespace ml
