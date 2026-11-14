#pragma once
#include <stddef.h>

#include "rcha/rcha_anm.h"
#include "rcha/rcha_node.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

// Declared from the symbols _ZN7CRchaExC1Ev (0x710069eb34), _ZN7CRchaEx5setupEN3mtl12ALLOC_HANDLEEPKv (0x710069f438) and
// the vtable _ZTV7CRchaEx (0x71011a77c0); its size is the allocation size in CharaEvaPlayer::play.
class CRchaEx : public RchaNode {
public:
  static const int NAME_COUNT = 29; // Range marker, kept: the enum below has 29 enumerators, 0 to 28, and the array it sizes is indexed by them.

  // Slots of unknown19a4, in the order of the names (dmy and the ptExAnm/ tracks) that setup looks for.
  enum {
    ANM_UNKNOWN_0 = 0,   // Inferred role: anm dmy; original name unknown.
    ANM_UNKNOWN_1 = 1,   // Inferred role: anm dynamics blend; original name unknown.
    ANM_UNKNOWN_2 = 2,   // Inferred role: anm weapon disp; original name unknown.
    ANM_UNKNOWN_3 = 3,   // Inferred role: anm weapon mount; original name unknown.
    ANM_UNKNOWN_4 = 4,   // Inferred role: anm weapon battle; original name unknown.
    ANM_UNKNOWN_5 = 5,   // Inferred role: anm weapon sp mot; original name unknown.
    ANM_UNKNOWN_6 = 6,   // Inferred role: anm weapon translate x; original name unknown.
    ANM_UNKNOWN_7 = 7,   // Inferred role: anm weapon translate y; original name unknown.
    ANM_UNKNOWN_8 = 8,   // Inferred role: anm weapon translate z; original name unknown.
    ANM_UNKNOWN_9 = 9,   // Inferred role: anm weapon rotate x; original name unknown.
    ANM_UNKNOWN_10 = 10, // Inferred role: anm weapon rotate y; original name unknown.
    ANM_UNKNOWN_11 = 11, // Inferred role: anm weapon rotate z; original name unknown.
    ANM_UNKNOWN_12 = 12, // Inferred role: anm weapon scale; original name unknown.
    ANM_UNKNOWN_13 = 13, // Inferred role: anm foot effect l; original name unknown.
    ANM_UNKNOWN_14 = 14, // Inferred role: anm foot effect r; original name unknown.
    ANM_UNKNOWN_15 = 15, // Inferred role: anm ao actionid; original name unknown.
    ANM_UNKNOWN_16 = 16, // Inferred role: anm ao face priset type; original name unknown.
    ANM_UNKNOWN_17 = 17, // Inferred role: anm ao eye type; original name unknown.
    ANM_UNKNOWN_18 = 18, // Inferred role: anm ao translate x; original name unknown.
    ANM_UNKNOWN_19 = 19, // Inferred role: anm ao translate y; original name unknown.
    ANM_UNKNOWN_20 = 20, // Inferred role: anm ao translate z; original name unknown.
    ANM_UNKNOWN_21 = 21, // Inferred role: anm ao rotate x; original name unknown.
    ANM_UNKNOWN_22 = 22, // Inferred role: anm ao rotate y; original name unknown.
    ANM_UNKNOWN_23 = 23, // Inferred role: anm ao rotate z; original name unknown.
    ANM_UNKNOWN_24 = 24, // Inferred role: anm ao scale; original name unknown.
    ANM_UNKNOWN_25 = 25, // Inferred role: anm aotgt enable; original name unknown.
    ANM_UNKNOWN_26 = 26, // Inferred role: anm aotgt translate x; original name unknown.
    ANM_UNKNOWN_27 = 27, // Inferred role: anm aotgt translate y; original name unknown.
    ANM_UNKNOWN_28 = 28, // Inferred role: anm aotgt translate z; original name unknown.
  };

  CRchaEx();
  virtual void clear();
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  static bool hasAnm(const void *data);
  f32 getValue(int slot, f32 frame, f32 defaultValue) const;
  int getValueInt(int slot, f32 frame, int defaultValue) const;
  bool getVisible(int &visible, const char *name, f32 frame) const;
  bool getDynamicsBlend(f32 &blend, f32 frame) const;
  bool getWeaponDisp(int &disp, f32 frame) const;
  bool getWeaponMount(int &mount, f32 frame) const;
  bool getWeaponBattle(int &battle, f32 frame) const;
  bool getWeaponSpMotion(f32 frame) const;
  void getWeaponPos(mm::Vec3 &pos, f32 frame) const;
  void getWeaponRot(mm::Vec3 &rot, f32 frame) const;
  void getWeaponScl(f32 &scale, f32 frame) const;
  bool getFootEffectL(int &effect, f32 frame) const;
  bool getFootEffectR(int &effect, f32 frame) const;
  int getActionType(f32 frame) const;
  int getFacePrisetType(f32 frame) const;
  int getEyeType(f32 frame) const;
  void getObjPos(mm::Vec3 &pos, f32 frame) const;
  void getObjRot(mm::Vec3 &rot, f32 frame) const;
  void getObjScl(f32 &scale, f32 frame) const;
  bool isTargetEnable(f32 frame) const;
  void getTarget(mm::Vec3 &target, f32 frame) const;

private:
  // Inferred helper: reads the track of a slot as an int when the resource has it; original name unknown.
  bool unknown001(int &value, int slot, f32 frame) const {
    int index = unknown19a4[slot];
    if (index >= 0) {
      value = unknown10[index].getValueInt(frame);
      return true;
    }
    return false;
  }

  bool unknown19a0;            // Inferred role: set up; original member name unknown.
  int unknown19a4[NAME_COUNT]; // Inferred role: track index of each name; original member name unknown.

  friend struct CRchaExLayout;
};

struct CRchaExLayout {
  static_assert(offsetof(CRchaEx, unknown19a0) == 0x19a0, "");
  static_assert(offsetof(CRchaEx, unknown19a4) == 0x19a4, "");
  static_assert(sizeof(CRchaEx) == 0x1a18, "");
};
