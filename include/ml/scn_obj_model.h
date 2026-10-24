#pragma once
#include <stddef.h>

#include "ml/attr_transform.h"
#include "ml/scn_obj.h"
#include "ml/threadval.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {

class Scn;
class WinProc;

class ScnObjModel : public ScnObj {
public:
  struct RENDER_INFO {
    AttrTransform unknown00; // Inferred role: transform; original member name unknown.
  };

  struct RENDER_OFFSET_INFO {
    mm::Vec3 unknown00; // Inferred role: offset; original member name unknown.
  };

  enum Flag {
    FLAG_DISP = 1 << 0,
    FLAG_CLIP = 1 << 1,
    FLAG_WARP = 1 << 4,
    FLAG_SEAM = 1 << 5,
    FLAG_FRAME_SPD = 1 << 6,
    FLAG_DISP_NEXT = 1 << 16,
  };

  ScnObjModel(Scn *scn, const char *name);
  void setDelete() override;
  void setFrameSpd(f32 speed);
  void setDisp(bool isDisp);
  void setClip(bool isClip);
  AttrTransform *getTrans(bool isBack);
  const AttrTransform *getTrans(bool isBack) const;
  RENDER_OFFSET_INFO *getOffsetInfo(bool isBack);
  const RENDER_OFFSET_INFO *getOffsetInfo(bool isBack) const;
  bool isDisp() const;
  bool isClip() const;
  void renderDebug(DebDraw *debDraw) override;
  void tail() override;
  ~ScnObjModel() override {}
  const char *getName() const override { return m_name.c_str(); }

  virtual void setPos(const mm::Vec3 &position) { unknown20.m_back->unknown00.unknown00 = position; }

  virtual void setPosWarp(const mm::Vec3 &position) {
    unknown20.m_back->unknown00.unknown00 = position;
    unknown34c |= FLAG_WARP;
  }

  virtual void addPos(const mm::Vec3 &position) { unknown20.m_back->unknown00.unknown00 += position; }
  virtual void setRot(const mm::Vec3 &rotation) { unknown20.m_back->unknown00.unknownf0 = rotation; }
  virtual void addRot(const mm::Vec3 &rotation) { unknown20.m_back->unknown00.unknownf0 += rotation; }

  virtual void addRot(const mm::Quat &rotation) {
    AttrTransform &transform = unknown20.m_back->unknown00;
    transform.unknown110 = rotation;
    transform.unknown130 |= AttrTransform::FLAG_QUAT;
  }

  virtual void setScl(const mm::Vec3 &scale) { unknown20.m_back->unknown00.unknown20 = scale; }

  virtual void addScl(const mm::Vec3 &scale);

  virtual void setMat(const mm::Mat44 &matrix) {
    AttrTransform &transform = unknown20.m_back->unknown00;
    transform.unknown30 = matrix;
    transform.unknown130 |= AttrTransform::FLAG_MATRIX;
  }

  virtual void setAlpha(f32 alpha) = 0;
  virtual f32 getAlpha() const = 0;
  virtual void setWriteStencil(bool isWriteStencil) = 0;
  virtual void setAlwaysTexStm(bool isAlwaysTexStm) = 0;
  virtual bool isMdlTexStm() const = 0;
  virtual bool isMemTexStm() const = 0;
  virtual const mm::Vec3 &getAABBMax() const = 0;
  virtual const mm::Vec3 &getAABBMin() const = 0;
  virtual const mm::Vec3 &getCenter() const = 0;
  virtual f32 getLength() const = 0;
  virtual void setGroups(int groups) = 0;
  virtual int getGroups() = 0;
  virtual void dispDebugWindow(bool isOpen, const char *title, WinProc *window) {}

  threadval<RENDER_INFO> unknown20;         // Inferred role: render info; original member name unknown.
  threadval<RENDER_OFFSET_INFO> unknown2d0; // Inferred role: offset info; original member name unknown.
  mm::mtl::FixStr<32> m_name;
  f32 m_frameSpd;
  f32 _348;
  u32 unknown34c;                  // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<128> unknown350; // Inferred role: stream path; original member name unknown.
};

static_assert(offsetof(ScnObjModel, unknown20) == 0x20, "");
static_assert(offsetof(ScnObjModel, unknown2d0) == 0x2d0, "");
static_assert(offsetof(ScnObjModel, m_name) == 0x320, "");
static_assert(offsetof(ScnObjModel, unknown34c) == 0x34c, "");
static_assert(offsetof(ScnObjModel, unknown350) == 0x350, "");

} // namespace ml
