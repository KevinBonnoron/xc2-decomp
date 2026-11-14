#pragma once
#include <stddef.h>

#include "event/anm_f32.h"
#include "event/anm_vec.h"
#include "event/cam_base.h"
#include "event/cam_util.h"
#include "event/curve.h"
#include "event/pos_axis.h"
#include "event/tar_axis.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class CamHands : public CamBase {
public:
  static constexpr u32 KEY_UNKNOWN_16 = 16; // Inferred role: key count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: follow pos flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: follow tar flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: follow tar angle flag; original name unknown.
  };

  CamHands(bool isFocal);
  virtual ~CamHands() {}
  virtual void update(const FrameInfo &info);
  void calcFollowPos();
  void calcFollowTar();
  virtual void render(const mm::Col4 &color);
  void setPos(const PosAxis &pos, CV_TYPE cv);
  void addAnmPos(f32 frame, const PosAxis &pos, CV_TYPE cv);
  void insertAnmPos(size_t index, const PosAxis &pos);
  void setTar(const TarAxis &tar, CV_TYPE cv);
  void addAnmTar(f32 frame, const TarAxis &tar, CV_TYPE cv);
  void insertAnmTar(size_t index, const TarAxis &tar);
  void setFov(f32 fov, CV_TYPE cv);
  void addAnmFov(f32 frame, f32 fov, CV_TYPE cv);
  void insertAnmFov(size_t index, f32 fov);
  void setRotZ(f32 rotZ, CV_TYPE cv);
  void addAnmRotZ(f32 frame, f32 rotZ, CV_TYPE cv);
  void insertAnmRotZ(size_t index, f32 rotZ);
  void replay();
  void followPos(bool isFollow);
  bool isFollowPos() const;
  void followTar(bool isFollow);
  bool isFollowTar() const;
  void setNearfar(f32 nearClip, f32 farClip);
  void setNearfar(EVT_nearfar nearfar);
  void getPosString(mm::mtl::FixStr<256> &string);
  void getTarString(mm::mtl::FixStr<256> &string);
  void getFovString(mm::mtl::FixStr<256> &string);
  void getRotZString(mm::mtl::FixStr<256> &string);

private:
  void setFollowTarAngle(u32 axis) {
    if (axis == TarAxis::AXIS_UNKNOWN_4 || axis == TarAxis::AXIS_UNKNOWN_5) {
      unknown40 |= FLAG_UNKNOWN_2;
    } else {
      unknown40 &= ~FLAG_UNKNOWN_2;
    }
  }

  u32 unknown40;                                            // Inferred role: flags; original member name unknown.
  AnmVec unknown50;                                         // Inferred role: pos anm; original member name unknown.
  AnmVec unknown240;                                        // Inferred role: tar anm; original member name unknown.
  AnmF32 unknown430;                                        // Inferred role: fov anm; original member name unknown.
  AnmF32 unknown540;                                        // Inferred role: rot z anm; original member name unknown.
  mm::mtl::FixedVector<PosAxis, KEY_UNKNOWN_16> unknown650; // Inferred role: pos axes; original member name unknown.
  mm::mtl::FixedVector<TarAxis, KEY_UNKNOWN_16> unknown860; // Inferred role: tar axes; original member name unknown.
  mm::mtl::FixedVector<f32, KEY_UNKNOWN_16> unknowna70;     // Inferred role: fovs; original member name unknown.
  mm::mtl::FixedVector<f32, KEY_UNKNOWN_16> unknownab8;     // Inferred role: rot zs; original member name unknown.
};

static_assert(sizeof(CamHands) == 0xb00, "");

} // namespace event
