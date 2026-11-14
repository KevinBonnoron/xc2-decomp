#include "gf/field/gf_dropitem_param.h"

#include "bdat.h"
#include "ml/rand.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h" // IWYU pragma: keep

namespace gf {
namespace {

f32 getValF32(u8 *bdat, const char *name, int id) {
  Bdat::Value value;
  value.valueU32 = Bdat::getValCheck(bdat, name, id, 8);
  return value.valueF32;
}

} // namespace

GfDropitemParam::GfDropitemParam()
    : unknown00(2.0f), unknown04(0.0f), unknown08(1.0f), unknown0c(0.0f), unknown10(0.5f), unknown14(0.5f), unknown18(0.0f), unknown1c(5.0f), unknown20(9.0f), unknown24(0.5f), unknown28(0.5f),
      unknown2c(0.2f), unknown30(0.05f), unknown34(0.1f), unknown38(0.0f), unknown3c(0.0f), unknown40(1.0f), unknown44(0.5f), unknown48(false), unknown4c(360.0f), unknown50(0), unknown54(1.0f),
      unknown58(2) {}

void GfDropitemParam::loadFromBdat(int &id) {
  u8 *bdat = Bdat::getFP("RSC_dropitemParam");
  if (bdat != nullptr) {
    unknown00 = getValF32(bdat, "height", id);
    unknown04 = getValF32(bdat, "heightRand", id);
    unknown08 = getValF32(bdat, "distance", id);
    unknown0c = getValF32(bdat, "distanceRand", id);
    unknown10 = getValF32(bdat, "time", id);
    unknown14 = getValF32(bdat, "speedAtte", id);
    unknown18 = getValF32(bdat, "rotYRand", id);
    unknown1c = getValF32(bdat, "lifeTime", id);
    unknown20 = getValF32(bdat, "flashTime", id);
    unknown24 = getValF32(bdat, "flashInterval1", id);
    unknown28 = getValF32(bdat, "flashInterval2", id);
    unknown2c = getValF32(bdat, "vanishTime1", id);
    unknown30 = getValF32(bdat, "vanishTime2", id);
    unknown34 = getValF32(bdat, "radius", id);
    unknown38 = getValF32(bdat, "initHeight", id);
    unknown3c = getValF32(bdat, "startScale", id);
    unknown40 = getValF32(bdat, "endScale", id);
    unknown44 = getValF32(bdat, "scaleTime", id);
    unknown48 = static_cast<u8>(Bdat::getValCheck(bdat, "isSpin", id, 1));
    unknown4c = getValF32(bdat, "spinSpeed", id);
    unknown50 = static_cast<u8>(Bdat::getValCheck(bdat, "startSpinBound", id, 1));
    unknown54 = getValF32(bdat, "startSpinTime", id);
    unknown58 = static_cast<u8>(Bdat::getValCheck(bdat, "boundNum", id, 1));
  }
}

} // namespace gf

// The game builds GfDropitemParams in the same unit, between GfDropitemParam and GfDropitemParamInst (0x71002f6cc0 to 0x71002f6f08).
#include "gf/field/gf_dropitem_params.cpp"

namespace gf {

GfDropitemParamInst::GfDropitemParamInst(const GfDropitemParam *param, f32 height) : unknown00(nullptr), unknown08(0.0f), unknown0c(0.0f) {
  if (param != nullptr) {
    create(*param, height);
  }
}

void GfDropitemParamInst::create(const GfDropitemParam &param, f32 height) {
  unknown00 = &param;
  unknown08 = param.unknown00 + param.unknown04 * ml::mtRandf1();
  unknown0c = param.unknown08 + param.unknown0c * ml::mtRandf1() + height;
}

f32 GfDropitemParamInst::getGravity() const {
  f32 time = unknown00->unknown10 * 0.5f;
  return unknown08 / (time * time) * (2.0f / 3.0f);
}

mm::Vec3 &GfDropitemParamInst::getInitVelocity(mm::Vec3 &velocity) const {
  f32 gravity = getGravity();
  velocity.x = 0.0f;
  velocity.y = (unknown08 - unknown00->unknown34 - unknown00->unknown38) / unknown00->unknown10 + gravity * 0.5f * unknown00->unknown10;
  velocity.z = unknown0c / unknown00->unknown10 * 0.5f;
  return velocity;
}

} // namespace gf

template void mm::mtl::Vector<gf::GfDropitemParam>::extend(size_t, size_t);
template void mm::mtl::Vector<gf::GfDropitemParam>::resize(size_t);
