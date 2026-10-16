#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace idcoli {

enum ColiState : int;
enum ColiAtrr : int;

enum ObjType {
  OBJ_TYPE_CHARACTER = 1,
  OBJ_TYPE_PHANTOM = 2,
  OBJ_TYPE_GRAND = 3,
};

class IDColiObj {
public:
  static const u8 FLAG_LANDING = 1 << 0;
  static const u8 FLAG_OUT_RANGE = 1 << 1;
  static const u8 FLAG_CONTACT_WALL = 1 << 2;

  u8 _00[0x20 - 0x00];
  u8 flags;
  u8 _21[0x24 - 0x21];
  ObjType type;
};

class IDColiParmsBase {
public:
  void setPriority(int priority);
  int getPriority() const;
  void setUserData(void *userData);
  bool isAttr(ColiAtrr attribute) const;
  bool isState(ColiState state) const;
  void setState(ColiState state);
  void clearState(ColiState state);
  void setMaterialBit(u32 bit);
  u32 getMaterialBit() const;
  void setOffMaterialBit(u32 bit);
  u32 getOffMaterialBit() const;
  const mm::Vec3 &getMax() const;
  const mm::Vec3 &getMin() const;

  u8 _00[0x10 - 0x00];
};

class IDColiParmsCharacter : public IDColiParmsBase {
public:
  IDColiParmsCharacter(IDColiObj *object);
  void createSphere(f32 radius);
  void createCapsule(f32 radius, f32 height, bool flag);
  void createBox(const mm::Vec3 &size, bool flag);
  void createCharacter(f32 radius, f32 height);
  void setAdsorption(f32 adsorption);
  f32 getAdsorption() const;
};

class IDColiParmsPhantom : public IDColiParmsBase {
public:
  IDColiParmsPhantom(IDColiObj *object);
  void createSphere(f32 radius);
  void createCapsule(f32 radius, f32 height);
  void createBox(const mm::Vec3 &size);
  void createCharacter(f32 radius, f32 height);
};

} // namespace idcoli
