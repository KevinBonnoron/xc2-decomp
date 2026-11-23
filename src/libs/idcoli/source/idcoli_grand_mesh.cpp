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

bool IDColiGrandMesh::meshAaBb(u32 index) {
  const IDCmfPoliData *poli = &m_wrkIDCmfWork->m_iDCmfPoliData[index];
  // The table pointer is read before the material index (0x71008e2544 before 0x71008e2548); without the local the index comes first.
  const unknown097 *materials = m_wrkIDCmfWork->unknown40;
  if (materials[poli->unknown0a].unknown04 & m_iDColiResult->unknowne8) {
    return false;
  }
  const mm::Vec3 *vertices = m_wrkIDCmfWork->unknown18[poli->unknown05];
  // The count is read once (ldrb w23, 0x71008e2584) and bounds the loop; with `poli->unknown04` in the condition the call reloads it.
  u8 count = poli->unknown04;
  const u16 *indices = reinterpret_cast<const u16 *>(m_wrkIDCmfWork->unknown00 + poli->unknown00) + count;
  const mm::Vec3 &center = vertices[indices[0]];
  bool isHit = false;
  for (int i = 0; i < count; i++) {
    if (!IDColiUtilMath::isTriangleBoxHitCheck(m_iDColiInput->unknown00, m_iDColiInput->unknown10, center, vertices[indices[1 + i]], vertices[indices[2 + i]])) {
      continue;
    }
    // `unknown30 == nullptr` compares the pointer and the adjustment separately (cset, orr); the game tests `(adj & 1) | ptr` once (0x71008e2770).
    if (!unknown30) {
      return m_iDColiResult->unknown001();
    }
    stockAaBbParm(center);
    isHit = true;
    stockAaBbParm(vertices[indices[1 + i]]);
    stockAaBbParm(vertices[indices[2 + i]]);
  }
  return isHit;
}

void IDColiGrandMesh::stockAaBbParm(const mm::Vec3 &point) {
  mm::Vec3 &max = m_iDColiResult->unknown50.unknown00;
  max.x = max.x > point.x ? max.x : point.x;
  max.y = max.y > point.y ? max.y : point.y;
  max.z = max.z > point.z ? max.z : point.z;
  mm::Vec3 &min = m_iDColiResult->unknown50.unknown10;
  min.x = min.x < point.x ? min.x : point.x;
  min.y = min.y < point.y ? min.y : point.y;
  min.z = min.z < point.z ? min.z : point.z;
}

bool IDColiGrandMesh::lenghtLine(f32 value) { return 0.0f <= value && value <= 1.0f; }

bool IDColiGrandMesh::lenghtRay(f32 value) { return m_iDColiInput->unknown94 <= value && value <= m_iDColiInput->unknown90; }

bool IDColiGrandMesh::lenghtSphere(f32 value) { return fabsf(value) <= m_iDColiInput->unknown90; }

bool IDColiGrandMesh::lenghtWallSphere(f32 value) { return 0.0f <= value && value < m_iDColiInput->unknown90; }

void IDColiGrandMesh::stockNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  if (distance < m_iDColiResult->unknown90) {
    unknown016(arg, poli, distance);
  }
}

void IDColiGrandMesh::stockSecNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  if (distance < 0.0f) {
    if (m_iDColiResult->unknowna0 <= distance) {
      m_iDColiResult->unknown50.unknown00 = arg.unknown00;
      m_iDColiResult->unknown50.unknown10 = arg.unknown10;
      m_iDColiResult->unknowna0 = distance;
      m_iDColiResult->unknown50.unknown30 = arg.unknown30;
      m_iDColiResult->unknownb1 = true;
      m_iDColiResult->unknowna8 = m_iDColiResult->unknownf0;
      (this->*unknown70)(m_iDColiResult->unknown50, poli);
    }
  } else if (distance < m_iDColiResult->unknown90) {
    unknown016(arg, poli, distance);
  }
}

// Inferred role: distance scaled by the matrix of the moved instance; original name unknown.
inline f32 IDColiGrandMesh::unknown090(f32 distance) const {
  f32 scaleX = m_iDCmfPosData->unknown00[0][0] + m_iDCmfPosData->unknown00[0][1] + m_iDCmfPosData->unknown00[0][2];
  f32 scaleY = m_iDCmfPosData->unknown00[1][0] + m_iDCmfPosData->unknown00[1][1] + m_iDCmfPosData->unknown00[1][2];
  f32 scaleZ = m_iDCmfPosData->unknown00[2][0] + m_iDCmfPosData->unknown00[2][1] + m_iDCmfPosData->unknown00[2][2];
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
  m_iDColiResult->unknown10.unknown00.x = arg.unknown00.x * m_iDCmfPosData->unknown00[0][0] + arg.unknown00.y * m_iDCmfPosData->unknown00[0][1] + arg.unknown00.z * m_iDCmfPosData->unknown00[0][2];
  m_iDColiResult->unknown10.unknown00.y = arg.unknown00.x * m_iDCmfPosData->unknown00[1][0] + arg.unknown00.y * m_iDCmfPosData->unknown00[1][1] + arg.unknown00.z * m_iDCmfPosData->unknown00[1][2];
  m_iDColiResult->unknown10.unknown00.z = arg.unknown00.x * m_iDCmfPosData->unknown00[2][0] + arg.unknown00.y * m_iDCmfPosData->unknown00[2][1] + arg.unknown00.z * m_iDCmfPosData->unknown00[2][2];
  const IDCmfPosData *posData = m_iDCmfPosData;
  mm::Vec3 &position = m_iDColiResult->unknown10.unknown00;
  f32 tx = posData->unknown00[0][3];
  f32 ty = posData->unknown00[1][3];
  f32 tz = posData->unknown00[2][3];
  position.x = tx + position.x;
  position.y = ty + position.y;
  position.z = tz + position.z;
  m_iDColiResult->unknown10.unknown10.x = arg.unknown10.x * m_iDCmfPosData->unknown00[0][0] + arg.unknown10.y * m_iDCmfPosData->unknown00[0][1] + arg.unknown10.z * m_iDCmfPosData->unknown00[0][2];
  m_iDColiResult->unknown10.unknown10.y = arg.unknown10.x * m_iDCmfPosData->unknown00[1][0] + arg.unknown10.y * m_iDCmfPosData->unknown00[1][1] + arg.unknown10.z * m_iDCmfPosData->unknown00[1][2];
  m_iDColiResult->unknown10.unknown10.z = arg.unknown10.x * m_iDCmfPosData->unknown00[2][0] + arg.unknown10.y * m_iDCmfPosData->unknown00[2][1] + arg.unknown10.z * m_iDCmfPosData->unknown00[2][2];
}

void IDColiGrandMesh::stockInstNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  f32 scaledDistance = unknown090(distance);
  if (m_iDColiResult->unknown90 > scaledDistance) {
    m_iDColiResult->unknown90 = scaledDistance;
    unknown091(arg);
    unknown092(m_iDColiResult->unknown10.unknown10);
    unknown015(arg, poli);
  }
}

void IDColiGrandMesh::stockInstSecNear(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  f32 scaledDistance = unknown090(distance);
  if (scaledDistance < 0.0f) {
    if (m_iDColiResult->unknowna0 <= scaledDistance) {
      m_iDColiResult->unknowna0 = scaledDistance;
      m_iDColiResult->unknown50.unknown00.x = arg.unknown00.x * m_iDCmfPosData->unknown00[0][0] + arg.unknown00.y * m_iDCmfPosData->unknown00[0][1] + arg.unknown00.z * m_iDCmfPosData->unknown00[0][2];
      m_iDColiResult->unknown50.unknown00.y = arg.unknown00.x * m_iDCmfPosData->unknown00[1][0] + arg.unknown00.y * m_iDCmfPosData->unknown00[1][1] + arg.unknown00.z * m_iDCmfPosData->unknown00[1][2];
      m_iDColiResult->unknown50.unknown00.z = arg.unknown00.x * m_iDCmfPosData->unknown00[2][0] + arg.unknown00.y * m_iDCmfPosData->unknown00[2][1] + arg.unknown00.z * m_iDCmfPosData->unknown00[2][2];
      const IDCmfPosData *posData = m_iDCmfPosData;
      mm::Vec3 &position = m_iDColiResult->unknown50.unknown00;
      f32 tx = posData->unknown00[0][3];
      f32 ty = posData->unknown00[1][3];
      f32 tz = posData->unknown00[2][3];
      position.x = tx + position.x;
      position.y = ty + position.y;
      position.z = tz + position.z;
      m_iDColiResult->unknown50.unknown10.x = arg.unknown10.x * m_iDCmfPosData->unknown00[0][0] + arg.unknown10.y * m_iDCmfPosData->unknown00[0][1] + arg.unknown10.z * m_iDCmfPosData->unknown00[0][2];
      m_iDColiResult->unknown50.unknown10.y = arg.unknown10.x * m_iDCmfPosData->unknown00[1][0] + arg.unknown10.y * m_iDCmfPosData->unknown00[1][1] + arg.unknown10.z * m_iDCmfPosData->unknown00[1][2];
      m_iDColiResult->unknown50.unknown10.z = arg.unknown10.x * m_iDCmfPosData->unknown00[2][0] + arg.unknown10.y * m_iDCmfPosData->unknown00[2][1] + arg.unknown10.z * m_iDCmfPosData->unknown00[2][2];
      unknown092(m_iDColiResult->unknown50.unknown10);
      unknown012(arg, poli);
    }
  } else if (m_iDColiResult->unknown90 > scaledDistance) {
    m_iDColiResult->unknown90 = scaledDistance;
    unknown091(arg);
    unknown092(m_iDColiResult->unknown10.unknown10);
    unknown015(arg, poli);
  }
}

void IDColiGrandMesh::stockTbl(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  (this->*unknown70)(arg, poli);
  if (m_iDColiResult->unknowne4 > m_iDColiResult->unknowne0) {
    if (m_iDColiResult->unknownb8 != nullptr) {
      m_iDColiResult->unknownb8[m_iDColiResult->unknowne0] = arg.unknown00;
    }
    if (m_iDColiResult->unknownc0 != nullptr) {
      m_iDColiResult->unknownc0[m_iDColiResult->unknowne0] = arg.unknown10;
    }
    if (m_iDColiResult->unknownc8 != nullptr) {
      m_iDColiResult->unknownc8[m_iDColiResult->unknowne0] = arg.unknown20;
    }
    if (m_iDColiResult->unknownd0 != nullptr) {
      m_iDColiResult->unknownd0[m_iDColiResult->unknowne0] = arg.unknown30;
    }
    m_iDColiResult->unknownb0 = true;
    m_iDColiResult->unknowne0++;
  }
  if (m_iDColiResult->m_iDColiCallBack != nullptr) {
    m_iDColiResult->m_iDColiCallBack->coli_param_callback(m_iDColiResult->unknownf0, arg);
  }
}

void IDColiGrandMesh::stockInstTbl(IDColiCallArg &arg, const IDCmfPoliData *poli, f32 distance) {
  if (m_iDColiResult->m_iDColiCallBack != nullptr) {
    unknown091(arg);
    m_iDColiResult->unknown10.unknown30 = arg.unknown30;
    unknown092(m_iDColiResult->unknown10.unknown10);
    (this->*unknown70)(m_iDColiResult->unknown10, poli);
    m_iDColiResult->m_iDColiCallBack->coli_param_callback(m_iDColiResult->unknownf0, m_iDColiResult->unknown10);
    if (m_iDColiResult->unknowne4 > m_iDColiResult->unknowne0) {
      if (m_iDColiResult->unknownb8 != nullptr) {
        m_iDColiResult->unknownb8[m_iDColiResult->unknowne0] = m_iDColiResult->unknown10.unknown00;
      }
      if (m_iDColiResult->unknownc0 != nullptr) {
        m_iDColiResult->unknownc0[m_iDColiResult->unknowne0] = m_iDColiResult->unknown10.unknown10;
      }
      if (m_iDColiResult->unknownc8 != nullptr) {
        m_iDColiResult->unknownc8[m_iDColiResult->unknowne0] = m_iDColiResult->unknown10.unknown20;
      }
      if (m_iDColiResult->unknownd0 != nullptr) {
        m_iDColiResult->unknownd0[m_iDColiResult->unknowne0] = m_iDColiResult->unknown10.unknown30;
      }
      m_iDColiResult->unknownb0 = true;
      m_iDColiResult->unknowne0++;
    }
  } else if (m_iDColiResult->unknowne4 > m_iDColiResult->unknowne0) {
    if (m_iDColiResult->unknownb8 != nullptr) {
      mm::Vec3 position(arg.unknown00.x * m_iDCmfPosData->unknown00[0][0] + arg.unknown00.y * m_iDCmfPosData->unknown00[0][1] + arg.unknown00.z * m_iDCmfPosData->unknown00[0][2],
                        arg.unknown00.x * m_iDCmfPosData->unknown00[1][0] + arg.unknown00.y * m_iDCmfPosData->unknown00[1][1] + arg.unknown00.z * m_iDCmfPosData->unknown00[1][2],
                        arg.unknown00.x * m_iDCmfPosData->unknown00[2][0] + arg.unknown00.y * m_iDCmfPosData->unknown00[2][1] + arg.unknown00.z * m_iDCmfPosData->unknown00[2][2]);
      m_iDColiResult->unknownb8[m_iDColiResult->unknowne0] = position + mm::Vec3(m_iDCmfPosData->unknown00[0][3], m_iDCmfPosData->unknown00[1][3], m_iDCmfPosData->unknown00[2][3]);
    }
    if (m_iDColiResult->unknownc0 != nullptr) {
      m_iDColiResult->unknownc0[m_iDColiResult->unknowne0].x =
          arg.unknown10.x * m_iDCmfPosData->unknown00[0][0] + arg.unknown10.y * m_iDCmfPosData->unknown00[0][1] + arg.unknown10.z * m_iDCmfPosData->unknown00[0][2];
      m_iDColiResult->unknownc0[m_iDColiResult->unknowne0].y =
          arg.unknown10.x * m_iDCmfPosData->unknown00[1][0] + arg.unknown10.y * m_iDCmfPosData->unknown00[1][1] + arg.unknown10.z * m_iDCmfPosData->unknown00[1][2];
      m_iDColiResult->unknownc0[m_iDColiResult->unknowne0].z =
          arg.unknown10.x * m_iDCmfPosData->unknown00[2][0] + arg.unknown10.y * m_iDCmfPosData->unknown00[2][1] + arg.unknown10.z * m_iDCmfPosData->unknown00[2][2];
      unknown092(m_iDColiResult->unknownc0[m_iDColiResult->unknowne0]);
    }
    if (m_iDColiResult->unknownc8 != nullptr) {
      (this->*unknown70)(arg, poli);
      m_iDColiResult->unknownc8[m_iDColiResult->unknowne0] = arg.unknown20;
    }
    if (m_iDColiResult->unknownd0 != nullptr) {
      m_iDColiResult->unknownd0[m_iDColiResult->unknowne0] = arg.unknown30;
    }
    (this->*unknown70)(arg, poli);
    m_iDColiResult->unknownb0 = true;
    m_iDColiResult->unknowne0++;
  }
}

void IDColiGrandMesh::vecotrDef(IDColiCallArg &arg, const IDCmfPoliData *poli) {
  const f32 *vector = &mm::Vec3::zero.x;
  if (arg.unknown30->unknown08 & 0x80) {
    const u16 *index = reinterpret_cast<const u16 *>(m_wrkIDCmfWork->unknown00 + poli->unknown00) + poli->unknown04 * 2 + 2;
    vector = &m_wrkIDCmfWork->unknown28[poli->unknown05][*index].unknown00;
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
  if (!(arg.unknown30->unknown08 & 0x80)) {
    arg.unknown20 = mm::Vec3::zero;
    return;
  }

  const u16 *index = reinterpret_cast<const u16 *>(m_wrkIDCmfWork->unknown00 + poli->unknown00) + poli->unknown04 * 2 + 2;
  unknown014 vector = m_wrkIDCmfWork->unknown28[poli->unknown05][*index];
  arg.unknown20.x = vector.unknown00 * m_iDCmfPosData->unknown00[0][0] + vector.unknown04 * m_iDCmfPosData->unknown00[0][1] + vector.unknown08 * m_iDCmfPosData->unknown00[0][2];
  arg.unknown20.y = vector.unknown00 * m_iDCmfPosData->unknown00[1][0] + vector.unknown04 * m_iDCmfPosData->unknown00[1][1] + vector.unknown08 * m_iDCmfPosData->unknown00[1][2];
  arg.unknown20.z = vector.unknown00 * m_iDCmfPosData->unknown00[2][0] + vector.unknown04 * m_iDCmfPosData->unknown00[2][1] + vector.unknown08 * m_iDCmfPosData->unknown00[2][2];
}

} // namespace idcoli

// Same order as in the game executable.
// clang-format off
#include "idcoli_grand_tree.cpp"
#include "idcoli_grd_move_obj.cpp"
#include "idcoli_obj_grand.cpp"
#include "idcoli_obj_grd_char.cpp"
// clang-format on
