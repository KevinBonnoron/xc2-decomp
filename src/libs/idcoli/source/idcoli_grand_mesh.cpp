#include <math.h>

#include "idcoli/idcoli.h"
#include "idcoli/idcoli_grand_mesh.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

void IDColiGrandMesh::calNomParm(mm::Vec3 &normal, const IDCmfNormalData *data) {
  normal.x = data->unknown00 * 6.1035156e-05f;
  normal.y = data->unknown02 * 6.1035156e-05f;
  normal.z = data->unknown04 * 6.1035156e-05f;
}

void IDColiGrandMesh::stockAaBbParm(const mm::Vec3 &point) {
  mm::Vec3 &max = unknown08->unknown50.unknown00;
  max.x = max.x > point.x ? max.x : point.x;
  max.y = max.y > point.y ? max.y : point.y;
  max.z = max.z > point.z ? max.z : point.z;
  mm::Vec3 &min = unknown08->unknown50.unknown10;
  min.x = min.x < point.x ? min.x : point.x;
  min.y = min.y < point.y ? min.y : point.y;
  min.z = min.z < point.z ? min.z : point.z;
}

bool IDColiGrandMesh::lenghtLine(f32 value) { return 0.0f <= value && value <= 1.0f; }

bool IDColiGrandMesh::lenghtRay(f32 value) { return unknown10->unknown94 <= value && value <= unknown10->unknown90; }

bool IDColiGrandMesh::lenghtSphere(f32 value) { return fabsf(value) <= unknown10->unknown90; }

bool IDColiGrandMesh::lenghtWallSphere(f32 value) { return 0.0f <= value && value < unknown10->unknown90; }

void IDColiGrandMesh::stockNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  if (distance < unknown08->unknown90) {
    unknown016(arg, poli, distance);
  }
}

void IDColiGrandMesh::stockSecNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  if (distance < 0.0f) {
    if (unknown08->unknowna0 <= distance) {
      unknown08->unknown50.unknown00 = arg.unknown00;
      unknown08->unknown50.unknown10 = arg.unknown10;
      unknown08->unknowna0 = distance;
      unknown08->unknown50.unknown30 = arg.unknown30;
      unknown08->unknownb1 = true;
      unknown08->unknowna8 = unknown08->unknownf0;
      (this->*unknown70)(unknown08->unknown50, poli);
    }
  } else if (distance < unknown08->unknown90) {
    unknown016(arg, poli, distance);
  }
}

// Inferred role: distance scaled by the matrix of the moved instance; original name unknown.
inline f32 IDColiGrandMesh::unknown090(f32 distance) const {
  f32 scaleX = unknown18->unknown00[0][0] + unknown18->unknown00[0][1] + unknown18->unknown00[0][2];
  f32 scaleY = unknown18->unknown00[1][0] + unknown18->unknown00[1][1] + unknown18->unknown00[1][2];
  f32 scaleZ = unknown18->unknown00[2][0] + unknown18->unknown00[2][1] + unknown18->unknown00[2][2];
  f32 scale = sqrtf(scaleX * scaleX + scaleY * scaleY + scaleZ * scaleZ);
  f32 scaledDistance = scale * 0.57735056f;
  scaledDistance *= distance;
  return scaledDistance;
}

// Inferred role: normalizes a vector, zero when too short; original name unknown.
inline void unknown092(mm::Vec3 &vector) {
  f32 length = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
  if (length <= 0.000001f) {
    vector = mm::Vec3::zero;
  } else {
    f32 inverse = 1.0f / length;
    vector.x = inverse * vector.x;
    vector.y = inverse * vector.y;
    vector.z = inverse * vector.z;
  }
}

// Inferred role: stores the position and the normal of a hit of a moved instance in world space as the front hit; original name unknown.
inline void IDColiGrandMesh::unknown091(const IDColiCallArg &arg) {
  unknown08->unknown10.unknown00.x = arg.unknown00.x * unknown18->unknown00[0][0] + arg.unknown00.y * unknown18->unknown00[0][1] + arg.unknown00.z * unknown18->unknown00[0][2];
  unknown08->unknown10.unknown00.y = arg.unknown00.x * unknown18->unknown00[1][0] + arg.unknown00.y * unknown18->unknown00[1][1] + arg.unknown00.z * unknown18->unknown00[1][2];
  unknown08->unknown10.unknown00.z = arg.unknown00.x * unknown18->unknown00[2][0] + arg.unknown00.y * unknown18->unknown00[2][1] + arg.unknown00.z * unknown18->unknown00[2][2];
  const IDCmfPosData *posData = unknown18;
  mm::Vec3 &position = unknown08->unknown10.unknown00;
  f32 tx = posData->unknown00[0][3];
  f32 ty = posData->unknown00[1][3];
  f32 tz = posData->unknown00[2][3];
  position.x = tx + position.x;
  position.y = ty + position.y;
  position.z = tz + position.z;
  unknown08->unknown10.unknown10.x = arg.unknown10.x * unknown18->unknown00[0][0] + arg.unknown10.y * unknown18->unknown00[0][1] + arg.unknown10.z * unknown18->unknown00[0][2];
  unknown08->unknown10.unknown10.y = arg.unknown10.x * unknown18->unknown00[1][0] + arg.unknown10.y * unknown18->unknown00[1][1] + arg.unknown10.z * unknown18->unknown00[1][2];
  unknown08->unknown10.unknown10.z = arg.unknown10.x * unknown18->unknown00[2][0] + arg.unknown10.y * unknown18->unknown00[2][1] + arg.unknown10.z * unknown18->unknown00[2][2];
}

void IDColiGrandMesh::stockInstNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  f32 scaledDistance = unknown090(distance);
  if (unknown08->unknown90 > scaledDistance) {
    unknown08->unknown90 = scaledDistance;
    unknown091(arg);
    unknown092(unknown08->unknown10.unknown10);
    unknown015(arg, poli);
  }
}

void IDColiGrandMesh::stockInstSecNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  f32 scaledDistance = unknown090(distance);
  if (scaledDistance < 0.0f) {
    if (unknown08->unknowna0 <= scaledDistance) {
      unknown08->unknowna0 = scaledDistance;
      unknown08->unknown50.unknown00.x = arg.unknown00.x * unknown18->unknown00[0][0] + arg.unknown00.y * unknown18->unknown00[0][1] + arg.unknown00.z * unknown18->unknown00[0][2];
      unknown08->unknown50.unknown00.y = arg.unknown00.x * unknown18->unknown00[1][0] + arg.unknown00.y * unknown18->unknown00[1][1] + arg.unknown00.z * unknown18->unknown00[1][2];
      unknown08->unknown50.unknown00.z = arg.unknown00.x * unknown18->unknown00[2][0] + arg.unknown00.y * unknown18->unknown00[2][1] + arg.unknown00.z * unknown18->unknown00[2][2];
      const IDCmfPosData *posData = unknown18;
      mm::Vec3 &position = unknown08->unknown50.unknown00;
      f32 tx = posData->unknown00[0][3];
      f32 ty = posData->unknown00[1][3];
      f32 tz = posData->unknown00[2][3];
      position.x = tx + position.x;
      position.y = ty + position.y;
      position.z = tz + position.z;
      unknown08->unknown50.unknown10.x = arg.unknown10.x * unknown18->unknown00[0][0] + arg.unknown10.y * unknown18->unknown00[0][1] + arg.unknown10.z * unknown18->unknown00[0][2];
      unknown08->unknown50.unknown10.y = arg.unknown10.x * unknown18->unknown00[1][0] + arg.unknown10.y * unknown18->unknown00[1][1] + arg.unknown10.z * unknown18->unknown00[1][2];
      unknown08->unknown50.unknown10.z = arg.unknown10.x * unknown18->unknown00[2][0] + arg.unknown10.y * unknown18->unknown00[2][1] + arg.unknown10.z * unknown18->unknown00[2][2];
      unknown092(unknown08->unknown50.unknown10);
      unknown012(arg, poli);
    }
  } else if (unknown08->unknown90 > scaledDistance) {
    unknown08->unknown90 = scaledDistance;
    unknown091(arg);
    unknown092(unknown08->unknown10.unknown10);
    unknown015(arg, poli);
  }
}

void IDColiGrandMesh::stockTbl(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  (this->*unknown70)(arg, poli);
  if (unknown08->unknowne4 > unknown08->unknowne0) {
    if (unknown08->unknownb8 != nullptr) {
      unknown08->unknownb8[unknown08->unknowne0] = arg.unknown00;
    }
    if (unknown08->unknownc0 != nullptr) {
      unknown08->unknownc0[unknown08->unknowne0] = arg.unknown10;
    }
    if (unknown08->unknownc8 != nullptr) {
      unknown08->unknownc8[unknown08->unknowne0] = arg.unknown20;
    }
    if (unknown08->unknownd0 != nullptr) {
      unknown08->unknownd0[unknown08->unknowne0] = arg.unknown30;
    }
    unknown08->unknownb0 = true;
    unknown08->unknowne0++;
  }
  if (unknown08->unknown100 != nullptr) {
    unknown08->unknown100->unknown01(unknown08->unknownf0, &arg);
  }
}

void IDColiGrandMesh::stockInstTbl(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  if (unknown08->unknown100 != nullptr) {
    unknown091(arg);
    unknown08->unknown10.unknown30 = arg.unknown30;
    unknown092(unknown08->unknown10.unknown10);
    (this->*unknown70)(unknown08->unknown10, poli);
    unknown08->unknown100->unknown01(unknown08->unknownf0, &unknown08->unknown10);
    if (unknown08->unknowne4 > unknown08->unknowne0) {
      if (unknown08->unknownb8 != nullptr) {
        unknown08->unknownb8[unknown08->unknowne0] = unknown08->unknown10.unknown00;
      }
      if (unknown08->unknownc0 != nullptr) {
        unknown08->unknownc0[unknown08->unknowne0] = unknown08->unknown10.unknown10;
      }
      if (unknown08->unknownc8 != nullptr) {
        unknown08->unknownc8[unknown08->unknowne0] = unknown08->unknown10.unknown20;
      }
      if (unknown08->unknownd0 != nullptr) {
        unknown08->unknownd0[unknown08->unknowne0] = unknown08->unknown10.unknown30;
      }
      unknown08->unknownb0 = true;
      unknown08->unknowne0++;
    }
  } else if (unknown08->unknowne4 > unknown08->unknowne0) {
    if (unknown08->unknownb8 != nullptr) {
      mm::Vec3 position(arg.unknown00.x * unknown18->unknown00[0][0] + arg.unknown00.y * unknown18->unknown00[0][1] + arg.unknown00.z * unknown18->unknown00[0][2],
                        arg.unknown00.x * unknown18->unknown00[1][0] + arg.unknown00.y * unknown18->unknown00[1][1] + arg.unknown00.z * unknown18->unknown00[1][2],
                        arg.unknown00.x * unknown18->unknown00[2][0] + arg.unknown00.y * unknown18->unknown00[2][1] + arg.unknown00.z * unknown18->unknown00[2][2]);
      unknown08->unknownb8[unknown08->unknowne0] = position + mm::Vec3(unknown18->unknown00[0][3], unknown18->unknown00[1][3], unknown18->unknown00[2][3]);
    }
    if (unknown08->unknownc0 != nullptr) {
      unknown08->unknownc0[unknown08->unknowne0].x = arg.unknown10.x * unknown18->unknown00[0][0] + arg.unknown10.y * unknown18->unknown00[0][1] + arg.unknown10.z * unknown18->unknown00[0][2];
      unknown08->unknownc0[unknown08->unknowne0].y = arg.unknown10.x * unknown18->unknown00[1][0] + arg.unknown10.y * unknown18->unknown00[1][1] + arg.unknown10.z * unknown18->unknown00[1][2];
      unknown08->unknownc0[unknown08->unknowne0].z = arg.unknown10.x * unknown18->unknown00[2][0] + arg.unknown10.y * unknown18->unknown00[2][1] + arg.unknown10.z * unknown18->unknown00[2][2];
      unknown092(unknown08->unknownc0[unknown08->unknowne0]);
    }
    if (unknown08->unknownc8 != nullptr) {
      (this->*unknown70)(arg, poli);
      unknown08->unknownc8[unknown08->unknowne0] = arg.unknown20;
    }
    if (unknown08->unknownd0 != nullptr) {
      unknown08->unknownd0[unknown08->unknowne0] = arg.unknown30;
    }
    (this->*unknown70)(arg, poli);
    unknown08->unknownb0 = true;
    unknown08->unknowne0++;
  }
}

void IDColiGrandMesh::vecotrDef(IDColiCallArg &arg, const IDCmfPoliData *poli) {
  const f32 *vector = &mm::Vec3::zero.x;
  if (arg.unknown30[2] & 0x80) {
    const u16 *index = reinterpret_cast<const u16 *>(unknown00->unknown00 + poli->unknown00) + poli->unknown04 * 2 + 2;
    vector = &unknown00->unknown28[poli->unknown05][*index].unknown00;
    arg.unknown20.x = vector[0];
    arg.unknown20.y = vector[1];
  } else {
    arg.unknown20.x = mm::Vec3::zero.x;
    arg.unknown20.y = mm::Vec3::zero.y;
  }
  arg.unknown20.z = vector[2];
}

void IDColiGrandMesh::vecotrNon(IDColiCallArg &arg, const IDCmfPoliData *poli) {}

void IDColiGrandMesh::vecotrInst(IDColiCallArg &arg, const IDCmfPoliData *poli) {
  if (!(arg.unknown30[2] & 0x80)) {
    arg.unknown20 = mm::Vec3::zero;
    return;
  }

  const u16 *index = reinterpret_cast<const u16 *>(unknown00->unknown00 + poli->unknown00) + poli->unknown04 * 2 + 2;
  unknown014 vector = unknown00->unknown28[poli->unknown05][*index];
  arg.unknown20.x = vector.unknown00 * unknown18->unknown00[0][0] + vector.unknown04 * unknown18->unknown00[0][1] + vector.unknown08 * unknown18->unknown00[0][2];
  arg.unknown20.y = vector.unknown00 * unknown18->unknown00[1][0] + vector.unknown04 * unknown18->unknown00[1][1] + vector.unknown08 * unknown18->unknown00[1][2];
  arg.unknown20.z = vector.unknown00 * unknown18->unknown00[2][0] + vector.unknown04 * unknown18->unknown00[2][1] + vector.unknown08 * unknown18->unknown00[2][2];
}

} // namespace idcoli

// Same order as in the game executable.
// clang-format off
#include "idcoli_grand_tree.cpp"
#include "idcoli_grd_move_obj.cpp"
#include "idcoli_obj_grand.cpp"
#include "idcoli_obj_grd_char.cpp"
// clang-format on
