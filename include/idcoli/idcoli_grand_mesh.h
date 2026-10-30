#pragma once
#include <stddef.h>

#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {
struct IDCmfNormalData;
struct IDCmfPoliData;
struct IDCmfPosData;
struct wrkIDCmfWork;

class IDColiGrandMesh {
public:
  IDColiGrandMesh();
  static void calNomParm(mm::Vec3 &normal, const IDCmfNormalData *data);
  void stockAaBbParm(const mm::Vec3 &point);
  bool meshLine(u32 index);
  bool meshSphere(u32 index);
  bool meshCapsule(u32 index);
  bool meshAaBb(u32 index);
  bool meshOBB(u32 index);
  bool lenghtLine(f32 value);
  bool lenghtRay(f32 value);
  bool lenghtSphere(f32 value);
  bool lenghtWallSphere(f32 value);
  void stockNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance);
  void stockSecNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance);
  void stockInstNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance);
  void stockInstSecNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance);
  void stockTbl(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance);
  void stockInstTbl(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance);
  void vecotrNon(IDColiCallArg &arg, const IDCmfPoliData *poli);
  void vecotrDef(IDColiCallArg &arg, const IDCmfPoliData *poli);
  void vecotrInst(IDColiCallArg &arg, const IDCmfPoliData *poli);

  // Inferred helper: stores the material data of a front hit and notifies the vector callback; original name unknown.
  void unknown015(const IDColiCallArg &arg, const IDCmfPoliData *poli) {
    unknown08->unknown10.unknown30 = arg.unknown30;
    unknown08->unknownb0 = true;
    unknown08->unknown98 = unknown08->unknownf0;
    (this->*unknown70)(unknown08->unknown10, poli);
  }

  // Inferred helper: stores a front hit; original name unknown.
  void unknown016(const IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
    unknown08->unknown10.unknown00 = arg.unknown00;
    unknown08->unknown10.unknown10 = arg.unknown10;
    unknown08->unknown90 = distance;
    unknown015(arg, poli);
  }

  // Inferred helper: stores the material data of a front hit and notifies the vector callback; original name unknown.
  void unknown011(const IDColiCallArg &arg, const IDCmfPoliData *poli) {
    unknown08->unknown10.unknown30 = arg.unknown30;
    unknown08->unknownb0 = true;
    unknown08->unknown98 = unknown08->unknownf0;
    (this->*unknown70)(unknown08->unknown10, poli);
  }

  // Inferred helper: stores the material data of a back hit and notifies the vector callback; original name unknown.
  void unknown012(const IDColiCallArg &arg, const IDCmfPoliData *poli) {
    unknown08->unknown50.unknown30 = arg.unknown30;
    unknown08->unknownb1 = true;
    unknown08->unknowna8 = unknown08->unknownf0;
    (this->*unknown70)(unknown08->unknown50, poli);
  }

  // Inferred helper: distance scaled by the matrix of the moved instance; original name unknown.
  f32 unknown090(f32 distance) const;

  // Inferred helper: stores the position and the normal of a hit of a moved instance in world space as the front hit; original name unknown.
  void unknown091(const IDColiCallArg &arg);

  wrkIDCmfWork *unknown00;                                                         // Inferred role: work; original member name unknown.
  IDColiResult *unknown08;                                                         // Inferred role: result; original member name unknown.
  const IDColiInput *unknown10;                                                    // Inferred role: input; original member name unknown.
  const IDCmfPosData *unknown18;                                                   // Inferred role: position data; original member name unknown.
  bool (IDColiGrandMesh::*unknown20)(u32);                                         // Inferred role: mesh test; original member name unknown.
  void (IDColiGrandMesh::*unknown30)(IDColiCallArg &, const IDCmfPoliData *, f32); // Inferred role: stock; original member name unknown.
  void (IDColiGrandMesh::*unknown40)(IDColiCallArg &, const IDCmfPoliData *, f32); // Inferred role: stock for a moved instance; original member name unknown.
  bool (IDColiGrandMesh::*unknown50)(f32);                                         // Inferred role: length check; original member name unknown.
  bool (IDColiGrandMesh::*unknown60)(f32);                                         // Inferred role: second length check; original member name unknown.
  void (IDColiGrandMesh::*unknown70)(IDColiCallArg &, const IDCmfPoliData *);      // Inferred role: vector; original member name unknown.
  void (IDColiGrandMesh::*unknown80)(IDColiCallArg &, const IDCmfPoliData *);      // Inferred role: vector for a moved instance; original member name unknown.
};

static_assert(offsetof(IDColiGrandMesh, unknown10) == 0x10, "");
static_assert(offsetof(IDColiGrandMesh, unknown18) == 0x18, "");
static_assert(offsetof(IDColiGrandMesh, unknown20) == 0x20, "");
static_assert(offsetof(IDColiGrandMesh, unknown30) == 0x30, "");
static_assert(offsetof(IDColiGrandMesh, unknown40) == 0x40, "");
static_assert(offsetof(IDColiGrandMesh, unknown50) == 0x50, "");
static_assert(offsetof(IDColiGrandMesh, unknown60) == 0x60, "");
static_assert(offsetof(IDColiGrandMesh, unknown70) == 0x70, "");
static_assert(offsetof(IDColiGrandMesh, unknown80) == 0x80, "");
static_assert(sizeof(IDColiGrandMesh) == 0x90, "");

} // namespace idcoli
