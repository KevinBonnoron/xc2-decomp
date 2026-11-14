#pragma once
#include <stddef.h>

#include "rcha/rcha_node.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

class RchaCam : public RchaNode {
public:
  static const int NAME_COUNT = 30; // Range marker, kept: the enum below has 30 enumerators, 0 to 29, and the array it sizes is indexed by them.

  // Slots of unknown19a4, in the order of the names (cam/ and camAtr/ tracks) that setup looks for.
  enum {
    CAM_UNKNOWN_0 = 0,      // Inferred role: cam translate x; original name unknown.
    CAM_UNKNOWN_1 = 1,      // Inferred role: cam translate y; original name unknown.
    CAM_UNKNOWN_2 = 2,      // Inferred role: cam translate z; original name unknown.
    CAM_UNKNOWN_3 = 3,      // Inferred role: cam rotate x; original name unknown.
    CAM_UNKNOWN_4 = 4,      // Inferred role: cam rotate y; original name unknown.
    CAM_UNKNOWN_5 = 5,      // Inferred role: cam rotate z; original name unknown.
    CAM_UNKNOWN_6 = 6,      // Inferred role: cam rotate order; original name unknown.
    CAMATR_UNKNOWN_7 = 7,   // Inferred role: camatr near (camAtr/translate_x); original name unknown.
    CAMATR_UNKNOWN_8 = 8,   // Inferred role: camatr far (camAtr/translate_y); original name unknown.
    CAMATR_UNKNOWN_9 = 9,   // Inferred role: camatr fov (camAtr/translate_z); original name unknown.
    CAMATR_UNKNOWN_10 = 10, // Inferred role: camatr dof; original name unknown.
    CAMATR_UNKNOWN_11 = 11, // Inferred role: camatr dof distance; original name unknown.
    CAMATR_UNKNOWN_12 = 12, // Inferred role: camatr dof range; original name unknown.
    CAMATR_UNKNOWN_13 = 13, // Inferred role: camatr dof pixel; original name unknown.
    CAMATR_UNKNOWN_14 = 14, // Inferred role: camatr dof lens; original name unknown.
    CAMATR_UNKNOWN_15 = 15, // Inferred role: camatr dof strength; original name unknown.
    CAMATR_UNKNOWN_16 = 16, // Inferred role: camatr dof blend; original name unknown.
    CAMATR_UNKNOWN_17 = 17, // Inferred role: camatr dof pixel lv; original name unknown.
    CAMATR_UNKNOWN_18 = 18, // Inferred role: camatr dof hlv; original name unknown.
    CAMATR_UNKNOWN_19 = 19, // Inferred role: camatr mblur; original name unknown.
    CAMATR_UNKNOWN_20 = 20, // Inferred role: camatr mblur str; original name unknown.
    CAMATR_UNKNOWN_21 = 21, // Inferred role: camatr mblur sub; original name unknown.
    CAMATR_UNKNOWN_22 = 22, // Inferred role: camatr sm vis; original name unknown.
    CAMATR_UNKNOWN_23 = 23, // Inferred role: camatr clock; original name unknown.
    CAMATR_UNKNOWN_24 = 24, // Inferred role: camatr clock hour; original name unknown.
    CAMATR_UNKNOWN_25 = 25, // Inferred role: camatr wtr; original name unknown.
    CAMATR_UNKNOWN_26 = 26, // Inferred role: camatr wtr type; original name unknown.
    CAMATR_UNKNOWN_27 = 27, // Inferred role: camatr wtr fade; original name unknown.
    CAMATR_UNKNOWN_28 = 28, // Inferred role: camatr cam lgt; original name unknown.
    CAMATR_UNKNOWN_29 = 29, // Inferred role: camatr near far; original name unknown.
  };

  RchaCam();
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  static bool hasAnm(const void *data);
  f32 getValue(int slot, f32 frame, f32 defaultValue) const;
  int getValueInt(int slot, f32 frame, int defaultValue) const;
  bool getPos(mm::Vec3 *pos, f32 frame) const;
  bool getRot(mm::Vec3 *rot, f32 frame) const;
  int getRotOrder(f32 frame) const;
  f32 getFov(f32 frame) const;
  f32 getNear(f32 frame) const;
  f32 getFar(f32 frame) const;
  f32 getMBlurStr(f32 frame) const;
  bool isEnableMBlur(f32 frame) const;
  f32 getMBlurSub(f32 frame) const;
  bool isEnableDOF(f32 frame) const;
  f32 getDistanceDOF(f32 frame) const;
  f32 getRangeDOF(f32 frame) const;
  f32 getPixelDOF(f32 frame) const;
  f32 getLensDOF(f32 frame) const;
  f32 getStrengthDOF(f32 frame) const;
  f32 getBlendDOF(f32 frame) const;
  int getPixelLvDOF(f32 frame) const;
  bool isHlvDOF(f32 frame) const;
  bool isSMapVis(f32 frame) const;
  bool isEnableTime(f32 frame) const;
  f32 getTimeVal(f32 frame) const;
  bool isEnableWeather(f32 frame) const;
  bool isCamLgtStop(f32 frame) const;
  int getNearFarType(f32 frame) const;
  int getWeatherType(f32 frame) const;
  int getWeatherFrame(f32 frame) const;

private:
  bool unknown19a0;            // Inferred role: has any named track; original member name unknown.
  int unknown19a4[NAME_COUNT]; // Inferred role: track index of each name; original member name unknown.

  friend struct RchaCamLayout;
};

struct RchaCamLayout {
  static_assert(offsetof(RchaCam, unknown19a0) == 0x19a0, "");
  static_assert(offsetof(RchaCam, unknown19a4) == 0x19a4, "");
  static_assert(sizeof(RchaCam) == 0x1a20, "");
};
