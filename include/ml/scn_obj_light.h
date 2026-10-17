#pragma once
#include <stddef.h>

#include "ml/attr_transform.h"
#include "ml/scn_obj.h"
#include "ml/threadval.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {

class Scn;

class ScnObjLight : public ScnObj {
public:
  struct RENDER_INFO {
    AttrTransform transform;
  };

  enum Flag {
    FLAG_DISP = 1 << 0,
    FLAG_OFS_MATRIX = 1 << 1,
  };

  ScnObjLight(Scn *scn);
  const AttrTransform *getTrans(bool isBack) const;
  AttrTransform *getTrans(bool isBack);
  void setDisp(bool isDisp);
  bool isDisp() const;
  void setOfsMatrix(bool isOfsMatrix);
  bool isOfsMatrix() const;
  ~ScnObjLight() override {}
  const char *getName() const override { return m_name.c_str(); }
  virtual bool isEnv() const { return false; }
  virtual f32 getFrame() const = 0;
  virtual void setFrame(f32 frame) = 0;
  virtual f32 getMaxFrame() const = 0;
  virtual void setFrameSpd(f32 speed) = 0;
  virtual f32 getFrameSpd() const = 0;
  virtual void setGroup(int group) = 0;
  virtual int getGroup() const = 0;
  virtual void setOffsetPos(const mm::Vec3 &position) = 0;
  virtual const mm::Vec3 &getOffsetPos() const = 0;
  virtual void setPos(const mm::Vec3 &position) { m_renderInfo.m_back->transform.m_pos = position; }
  virtual void setRot(const mm::Vec3 &rotation) { m_renderInfo.m_back->transform.m_rot = rotation; }
  virtual void setScl(const mm::Vec3 &scale) { m_renderInfo.m_back->transform.m_scl = scale; }

  virtual void setMat(const mm::Mat44 &matrix) {
    AttrTransform &transform = m_renderInfo.m_back->transform;
    transform.m_matrix = matrix;
    transform.m_flags |= AttrTransform::FLAG_MATRIX;
  }

  virtual void setDeugDisp2D(bool isDisp) {}
  virtual void setFromCaptureTool() = 0;
  virtual void setLocalIBLName(const char *name) = 0;

  mm::mtl::FixStr<64> m_name;
  threadval<RENDER_INFO> m_renderInfo;
  u32 m_flags;
};

static_assert(offsetof(ScnObjLight, m_name) == 0x14, "");
static_assert(offsetof(ScnObjLight, m_renderInfo) == 0x60, "");
static_assert(offsetof(ScnObjLight, m_flags) == 0x310, "");

} // namespace ml
