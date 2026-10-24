#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm
namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

class RchaChrEff {
public:
  RchaChrEff();
  virtual ~RchaChrEff();
  virtual void setup(mtl::ALLOC_HANDLE handle, const void *data);
  void getVolumeFade(int &type, f32 frame) const;
  void getVolumeFadeId(int &id, f32 frame) const;
  void getVolumeFadeUVWScale(mm::Vec3 &scale, f32 frame) const;
  void getVolumeFadeCenterPos(mm::Vec3 &pos, f32 frame) const;
  void getVolumeFadeDistance(f32 &distance, f32 frame) const;
  void getVolumeFadeDirectivity(f32 &directivity, f32 frame) const;
  void getVolumeFadeMesh(int &mesh, f32 frame) const;
  void getVolumeFadeRatio(f32 &ratio, f32 frame) const;
  void getRimBloom(int &type, f32 frame) const;
  void getRimBloomId(int &id, f32 frame) const;
  void getAfterImage(int &type, f32 frame) const;
  void getAfterImageId1(int &id, f32 frame) const;
  void getAfterImageId2(int &id, f32 frame) const;
  void getAfterImageCaptureFrame(f32 &captureFrame, f32 frame) const;
  void getAfterImageExistFrame(f32 &existFrame, f32 frame) const;
  void getAfterImageFadeOutFrame(f32 &fadeOutFrame, f32 frame) const;

  int getFrameCount() const { return unknown199c; }

private:
  u8 _8[0x199c - 0x8];
  int unknown199c; // Inferred role: frame count; original member name unknown.
  u8 _19a0[0x19f8 - 0x19a0];
};

static_assert(sizeof(RchaChrEff) == 0x19f8, "");
