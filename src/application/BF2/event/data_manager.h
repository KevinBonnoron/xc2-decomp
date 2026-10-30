#pragma once
#include <stddef.h>

#include "event/i_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class DataManager : public IManager, public mm::mtl::Singleton<DataManager> {
public:
  static constexpr u32 SCENE_COUNT = 16;

  struct OfsInfo {
    OfsInfo(const char *name);

    mm::mtl::FixStr<64> unknown00; // Inferred role: name; original member name unknown.
    mm::Mat44 unknown50;           // Inferred role: src matrix; original member name unknown.
    mm::Mat44 unknown90;           // Inferred role: des matrix; original member name unknown.
    mm::Mat44 unknownd0;           // Inferred role: offset matrix; original member name unknown.
    mm::Vec3 unknown110;           // Inferred role: offset vector; original member name unknown.
    mm::Mat44 unknown120;          // Inferred role: keep matrix; original member name unknown.
    mm::Vec3 unknown160;           // Inferred role: keep vector; original member name unknown.
  };

  DataManager();
  virtual ~DataManager();
  void clear();
  void setupScene();
  void updateCurrent();
  void startScene();
  OfsInfo *getCurrent();
  OfsInfo *searchScene(const char *name) const;
  OfsInfo *createScene(const char *name);
  size_t getCharaNum() const;
  bool checkRadianTar(u32 axis);
  mm::Vec3 axis2pos(u32 axis, f32 x, f32 y, f32 z);
  mm::Mat44 getPosAxis(u32 axis);
  f32 getRotOfsY(u32 axis, const mm::Vec3 &rot);
  mm::Mat44 getTarAxis(u32 axis);
  mm::Vec3 axis2rot(u32 axis, f32 x, f32 y, f32 z, const mm::Vec3 &rot);
  mm::Vec3 axis2tar(u32 axis, f32 x, f32 y, f32 z, const mm::Vec3 &pos);
  const char *getPosName(u32 axis);
  const char *getRotName(u32 axis);
  const char *getTarName(u32 axis);
  void setOffsetSrc(const mm::Vec3 &pos, f32 rotY, bool isKeep);
  void setOffsetDes(const mm::Vec3 &pos, f32 rotY, bool isKeep);
  virtual void OnEventProc(MSG_TYPE type);

private:
  // Inferred helper: transforms the point (x, y, z) by mat; original name unknown.
  static mm::Vec3 unknown001(const mm::Mat44 &mat, f32 x, f32 y, f32 z) {
    return mm::Vec3(mat.rows[0][0] * x + mat.rows[1][0] * y + mat.rows[2][0] * z + mat.rows[3][0],
                    mat.rows[0][1] * x + mat.rows[1][1] * y + mat.rows[2][1] * z + mat.rows[3][1],
                    mat.rows[0][2] * x + mat.rows[1][2] * y + mat.rows[2][2] * z + mat.rows[3][2]);
  }

  // Inferred helper: unknown001 on a matrix taken by value (the game keeps each getPosAxis/getTarAxis result in its own
  // stack slot, which a reference parameter would let the compiler share); original name unknown.
  static mm::Vec3 unknown002(mm::Mat44 mat, f32 x, f32 y, f32 z) { return unknown001(mat, x, y, z); }

  // Inferred helper: the point one unit along -z of the rotation (rotX, rotY), from pos; original name unknown.
  static mm::Vec3 unknown003(f32 rotX, f32 rotY, const mm::Vec3 &pos) {
    mm::Mat44 mat;
    mat.setRotXYZ(mm::Vec3(rotX, rotY, 0.0f));
    return unknown001(mat, 0.0f, 0.0f, -1.0f) + pos;
  }

  mm::mtl::FixedVector<OfsInfo *, SCENE_COUNT> unknown10; // Inferred role: scenes; original member name unknown.
  mm::mtl::FixStr<64> unknown98;                          // Inferred role: scene name; original member name unknown.
  mm::mtl::FixStr<64> unknowndc;                          // Inferred role: current scene name; original member name unknown.
  OfsInfo *unknown120;                                    // Inferred role: current; original member name unknown.
};

static_assert(sizeof(DataManager::OfsInfo) == 0x170, "");
static_assert(sizeof(DataManager) == 0x128, "");

} // namespace event
