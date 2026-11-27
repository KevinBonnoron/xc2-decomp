#include <math.h>

#include "idcoli/idcoli.h"
#include "idcoli/idcoli_grand_mesh.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

IDColiGrandMesh::IDColiGrandMesh() {}

IDColiGrandTree::IDColiGrandTree() {}

bool IDColiGrandTree::instLineHit(u32 index) { return instLineHitParts(&m_wrkIDCmfWork->m_iDCmfPosData[index], &m_wrkIDCmfWork->m_iDCmfPosInfo[index]); }

bool IDColiGrandTree::instRayHit(u32 index) { return instRayHitParts(&m_wrkIDCmfWork->m_iDCmfPosData[index], &m_wrkIDCmfWork->m_iDCmfPosInfo[index]); }

bool IDColiGrandTree::instSphereHit(u32 index) { return instSphereHitParts(&m_wrkIDCmfWork->m_iDCmfPosData[index], &m_wrkIDCmfWork->m_iDCmfPosInfo[index]); }

bool IDColiGrandTree::instCapsuleHit(u32 index) { return instCapsuleHitParts(&m_wrkIDCmfWork->m_iDCmfPosData[index], &m_wrkIDCmfWork->m_iDCmfPosInfo[index]); }

bool IDColiGrandTree::instAaBbHit(u32 index) { return instAaBbHitParts(&m_wrkIDCmfWork->m_iDCmfPosData[index], &m_wrkIDCmfWork->m_iDCmfPosInfo[index]); }

bool IDColiGrandTree::isLineAaBb(const float *max, const float *min) {
  if (isAaBbToAaBb(max, min)) {
    return true;
  }
  const IDColiInput *input = m_iDColiInput;
  mm::Vec3 boxMax(max[0], max[1], max[2]);
  mm::Vec3 boxMin(min[0], min[1], min[2]);
  mm::Vec3 half = (boxMax - boxMin) * 0.5f;
  mm::Vec3 center = boxMin + half;
  mm::Vec3 distance = input->unknown40 - center;
  if (fabsf(distance.y * input->unknown50.z - distance.z * input->unknown50.y) > half.y * input->unknown60.z + half.z * input->unknown60.y) {
    return true;
  }
  if (fabsf(distance.z * input->unknown50.x - distance.x * input->unknown50.z) > half.x * input->unknown60.z + half.z * input->unknown60.x) {
    return true;
  }
  return fabsf(distance.x * input->unknown50.y - distance.y * input->unknown50.x) > half.x * input->unknown60.y + half.y * input->unknown60.x;
}

bool IDColiGrandTree::instLineHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo) {
  if (IDColiManager::get()->isGblId(posInfo->m_iD)) {
    return false;
  }
  if (isLineAaBb(&posData->unknown80.x, &posData->unknown90.x)) {
    return false;
  }
  const IDColiInput *current = m_iDColiInput;
  if (current->unknowna0 != 0.0f && isRangeAaBb(&posData->unknown80, &posData->unknown90)) {
    return false;
  }
  const IDCmfPosData *savedPosData = m_iDCmfPosData;
  decltype(unknown30) savedStock = unknown30;
  decltype(unknown70) savedVector = unknown70;
  IDColiInput input;
  IDColiInputUtil::getLine(input, *current, posData, false);
  m_iDColiInput = &input;
  m_iDCmfPosData = posData;
  unknown30 = unknown40;
  unknown70 = unknown80;
  bool isHit = (this->*unknown90)(m_wrkIDCmfWork->unknown08[posInfo->unknown00].unknown0c);
  m_iDColiInput = current;
  m_iDCmfPosData = savedPosData;
  unknown30 = savedStock;
  unknown70 = savedVector;
  return isHit;
}

bool IDColiGrandTree::instRayHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo) {
  if (IDColiManager::get()->isGblId(posInfo->m_iD)) {
    return false;
  }
  if (isLineAaBb(&posData->unknown80.x, &posData->unknown90.x)) {
    return false;
  }
  const IDColiInput *current = m_iDColiInput;
  if (current->unknowna0 != 0.0f && isRangeAaBb(&posData->unknown80, &posData->unknown90)) {
    return false;
  }
  const IDCmfPosData *savedPosData = m_iDCmfPosData;
  decltype(unknown30) savedStock = unknown30;
  decltype(unknown70) savedVector = unknown70;
  IDColiInput input;
  IDColiInputUtil::getRay(input, *current, posData, false);
  m_iDColiInput = &input;
  m_iDCmfPosData = posData;
  unknown30 = unknown40;
  unknown70 = unknown80;
  bool isHit = (this->*unknown90)(m_wrkIDCmfWork->unknown08[posInfo->unknown00].unknown0c);
  m_iDColiInput = current;
  m_iDCmfPosData = savedPosData;
  unknown30 = savedStock;
  unknown70 = savedVector;
  return isHit;
}

bool IDColiGrandTree::instSphereHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo) {
  if (IDColiManager::get()->isGblId(posInfo->m_iD)) {
    return false;
  }
  if (isAaBbToAaBb(&posData->unknown80.x, &posData->unknown90.x)) {
    return false;
  }
  const IDColiInput *current = m_iDColiInput;
  if (current->unknowna0 != 0.0f && isRangeAaBb(&posData->unknown80, &posData->unknown90)) {
    return false;
  }
  const IDCmfPosData *savedPosData = m_iDCmfPosData;
  decltype(unknown30) savedStock = unknown30;
  decltype(unknown70) savedVector = unknown70;
  IDColiInput input;
  IDColiInputUtil::getSphere(input, *current, posData, false);
  unknown30 = unknown40;
  unknown70 = unknown80;
  m_iDColiInput = &input;
  m_iDCmfPosData = posData;
  bool isHit = (this->*unknown90)(m_wrkIDCmfWork->unknown08[posInfo->unknown00].unknown0c);
  m_iDColiInput = current;
  m_iDCmfPosData = savedPosData;
  unknown30 = savedStock;
  unknown70 = savedVector;
  return isHit;
}

bool IDColiGrandTree::instCapsuleHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo) {
  if (IDColiManager::get()->isGblId(posInfo->m_iD)) {
    return false;
  }
  if (isAaBbToAaBb(&posData->unknown80.x, &posData->unknown90.x)) {
    return false;
  }
  const IDColiInput *current = m_iDColiInput;
  if (current->unknowna0 != 0.0f && isRangeAaBb(&posData->unknown80, &posData->unknown90)) {
    return false;
  }
  const IDCmfPosData *savedPosData = m_iDCmfPosData;
  decltype(unknown30) savedStock = unknown30;
  decltype(unknown70) savedVector = unknown70;
  IDColiInput input;
  IDColiInputUtil::getCapsule(input, *current, posData, false);
  m_iDColiInput = &input;
  m_iDCmfPosData = posData;
  unknown30 = unknown40;
  unknown70 = unknown80;
  bool isHit = (this->*unknown90)(m_wrkIDCmfWork->unknown08[posInfo->unknown00].unknown0c);
  m_iDColiInput = current;
  m_iDCmfPosData = savedPosData;
  unknown30 = savedStock;
  unknown70 = savedVector;
  return isHit;
}

bool IDColiGrandTree::instAaBbHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo) {
  if (IDColiManager::get()->isGblId(posInfo->m_iD)) {
    return false;
  }
  if (isAaBbToAaBb(&posData->unknown80.x, &posData->unknown90.x)) {
    return false;
  }
  const IDColiInput *current = m_iDColiInput;
  if (current->unknowna0 != 0.0f && isRangeAaBb(&posData->unknown80, &posData->unknown90)) {
    return false;
  }
  const IDCmfPosData *savedPosData = m_iDCmfPosData;
  IDColiInput input;
  IDColiInputUtil::getOBB(input, current->unknown00, current->unknown10, posData);
  m_iDColiInput = &input;
  m_iDCmfPosData = posData;
  unknown20 = &IDColiGrandMesh::meshOBB;
  bool isHit = (this->*unknown90)(m_wrkIDCmfWork->unknown08[posInfo->unknown00].unknown0c);
  m_iDColiInput = current;
  m_iDCmfPosData = savedPosData;
  unknown20 = &IDColiGrandMesh::meshAaBb;
  return isHit;
}

bool IDColiGrandTree::isRangeAaBb(const mm::Vec3 *max, const mm::Vec3 *min) {
  mm::Vec3 half = (*max - *min) * 0.5f;
  return half.x * half.x + half.y * half.y + half.z * half.z <= m_iDColiInput->unknowna0;
}

bool IDColiGrandTree::isAaBbToAaBb(const float *max, const float *min) {
  const IDColiInput *input = m_iDColiInput;
  if (input->unknown00.x < min[0]) {
    return true;
  }
  if (input->unknown10.x > max[0]) {
    return true;
  }
  if (input->unknown00.z < min[2]) {
    return true;
  }
  if (input->unknown10.z > max[2]) {
    return true;
  }
  if (input->unknown10.y > max[1]) {
    return true;
  }
  return input->unknown00.y < min[1];
}

// Each run adds the id from the cell record to a table entry; the table is read first and `start` is the loop's own induction variable, so
// the preheader keeps the game's `ids + table` order (a `start + i` argument is rebuilt by LSR as `table + ids`).
bool IDColiGrandTree::treeHitDef(u32 index) {
  const unknown263 *bounds = &m_wrkIDCmfWork->unknown60[index];
  if ((this->*unknownb0)(&bounds->unknown00.x, &bounds->unknown10.x)) {
    return false;
  }
  const unknown262 *nodes = m_wrkIDCmfWork->unknown68;
  const u16 *ids = reinterpret_cast<const u16 *>(m_wrkIDCmfWork->unknown00 + nodes[index].unknown00);
  bool isHit = false;
  u8 count = nodes[index].unknown05;
  if (count != 0) {
    u32 start = *(m_wrkIDCmfWork->unknown48 + nodes[index].unknown08) + *ids++;
    u8 hit = 0;
    for (u32 i = 0; i < count; i++, start++) {
      hit |= (this->*unknown20)(start);
    }
    isHit = hit != 0;
  }
  count = nodes[index].unknown06;
  if (count != 0) {
    u32 start = *(m_wrkIDCmfWork->unknown50 + nodes[index].unknown09) + *ids++;
    for (u32 i = 0; i < count; i++, start++) {
      isHit |= (this->*unknowna0)(start);
    }
  }
  count = nodes[index].unknown04;
  if (count != 0) {
    u32 start = *(m_wrkIDCmfWork->unknown58 + nodes[index].unknown07) + *ids;
    for (u32 i = 0; i < count; i++, start++) {
      isHit |= (this->*unknown90)(start);
    }
  }
  return isHit;
}

IDColiGrandObj::IDColiGrandObj(wrkIDCmfWork *work) {
  m_wrkIDCmfWork = work;
  m_iDCmfPosData = nullptr;
}

IDColiGrandObj::~IDColiGrandObj() {}

bool IDColiGrandObj::testLine(IDColiResult &result, const IDColiInput &input) {
  m_iDColiResult = &result;
  m_iDColiInput = &input;
  unknown20 = &IDColiGrandMesh::meshLine;
  unknownb0 = &IDColiGrandTree::isLineAaBb;
  unknowna0 = &IDColiGrandTree::instLineHit;
  unknown50 = &IDColiGrandMesh::lenghtLine;
  if (result.unknown00 == 0) {
    unknown099();
    return coliCallCheck(&IDColiGrandTree::instLineHitParts);
  }
  unknown90 = &IDColiGrandTree::treeHitDef;
  // The game repeats the block below in the six test functions (testLine, testRay, testSphere, testCapsule, testMoveSphere and
  // testMoveCapsule): an inline helper turns the result type branch into selects, which the game does not have.
  if (result.unknown00 == 2) {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstTbl;
    } else {
      unknown30 = &IDColiGrandMesh::stockTbl;
    }
    unknown40 = &IDColiGrandMesh::stockInstTbl;
  } else {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstNear;
    } else {
      unknown30 = &IDColiGrandMesh::stockNear;
    }
    unknown40 = &IDColiGrandMesh::stockInstNear;
  }
  if (result.unknownb3) {
    if (m_iDCmfPosData != nullptr) {
      unknown70 = &IDColiGrandMesh::vecotrInst;
    } else {
      unknown70 = &IDColiGrandMesh::vecotrDef;
    }
    unknown80 = &IDColiGrandMesh::vecotrInst;
  } else {
    unknown70 = &IDColiGrandMesh::vecotrNon;
    unknown80 = &IDColiGrandMesh::vecotrNon;
  }
  return coliCallResl(&IDColiGrandTree::instLineHitParts);
}

bool IDColiGrandObj::coliCallCheck(unknown020 function) {
  if (m_wrkIDCmfWork->unknown88 == 0) {
    if ((this->*unknown90)(0)) {
      return true;
    }
  } else {
    const unknown094 *record = m_wrkIDCmfWork->unknown80;
    for (int i = 0; i < m_wrkIDCmfWork->unknown88; i++, record++) {
      if (record->unknown00 != 0 && IDColiManager::get()->isGblId(record->unknown00)) {
        continue;
      }
      if ((record->unknown08 & 1) && (record->unknown08 >> 8) != IDColiManager::get()->m_subNum) {
        continue;
      }
      if ((this->*unknown90)(record->unknown04)) {
        return true;
      }
    }
  }
  if (m_wrkIDCmfWork->m_moveMax != 0) {
    IDColiUtilTreeAcc tree(m_wrkIDCmfWork->unknown90[m_wrkIDCmfWork->unknowna0]);
    tree.startTreeAaBbMode(m_iDColiInput->unknown00, m_iDColiInput->unknown10);
    for (ColiLinkList<IDColiTreeObj> *list = tree.unknown033(); list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiGrdMoveObj *moveObj = reinterpret_cast<unknown006 *>(node)->m_iDColiGrdMoveObj;
        m_iDColiResult->unknownf0 = moveObj->m_userData;
        if ((this->*function)(&moveObj->m_iDCmfPosData, &moveObj->m_iDCmfPosInfo)) {
          return true;
        }
      }
    }
  }
  return false;
}

bool IDColiGrandObj::testLine(IDColiResult &result, const IDColiInput &input, const IDCmfPosData *posData) {
  m_iDCmfPosData = posData;
  IDColiInput line;
  IDColiInputUtil::getLine(line, input, posData, false);
  return testLine(result, line);
}

bool IDColiGrandObj::testRay(IDColiResult &result, const IDColiInput &input, const IDCmfPosData *posData) {
  m_iDCmfPosData = posData;
  IDColiInput ray;
  IDColiInputUtil::getRay(ray, input, posData, false);
  return testRay(result, ray);
}

bool IDColiGrandObj::testRay(IDColiResult &result, const IDColiInput &input) {
  m_iDColiResult = &result;
  m_iDColiInput = &input;
  unknown20 = &IDColiGrandMesh::meshLine;
  unknownb0 = &IDColiGrandTree::isLineAaBb;
  unknowna0 = &IDColiGrandTree::instRayHit;
  unknown50 = &IDColiGrandMesh::lenghtRay;
  if (result.unknown00 == 0) {
    unknown099();
    return coliCallCheck(&IDColiGrandTree::instRayHitParts);
  }
  unknown90 = &IDColiGrandTree::treeHitDef;
  if (result.unknown00 == 2) {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstTbl;
    } else {
      unknown30 = &IDColiGrandMesh::stockTbl;
    }
    unknown40 = &IDColiGrandMesh::stockInstTbl;
  } else {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstSecNear;
    } else {
      unknown30 = &IDColiGrandMesh::stockSecNear;
    }
    unknown40 = &IDColiGrandMesh::stockInstSecNear;
  }
  if (result.unknownb3) {
    if (m_iDCmfPosData != nullptr) {
      unknown70 = &IDColiGrandMesh::vecotrInst;
    } else {
      unknown70 = &IDColiGrandMesh::vecotrDef;
    }
    unknown80 = &IDColiGrandMesh::vecotrInst;
  } else {
    unknown70 = &IDColiGrandMesh::vecotrNon;
    unknown80 = &IDColiGrandMesh::vecotrNon;
  }
  return coliCallResl(&IDColiGrandTree::instRayHitParts);
}

bool IDColiGrandObj::testSphere(IDColiResult &result, const IDColiInput &input, bool isWall, const IDCmfPosData *posData) {
  m_iDCmfPosData = posData;
  IDColiInput sphere;
  IDColiInputUtil::getSphere(sphere, input, posData, false);
  return testSphere(result, sphere, isWall);
}

bool IDColiGrandObj::testSphere(IDColiResult &result, const IDColiInput &input, bool isWall) {
  m_iDColiResult = &result;
  m_iDColiInput = &input;
  unknown20 = &IDColiGrandMesh::meshSphere;
  unknowna0 = &IDColiGrandTree::instSphereHit;
  unknownb0 = &IDColiGrandTree::isAaBbToAaBb;
  unknown50 = isWall ? &IDColiGrandMesh::lenghtWallSphere : &IDColiGrandMesh::lenghtSphere;
  if (result.unknown00 == 0) {
    unknown099();
    return coliCallCheck(&IDColiGrandTree::instSphereHitParts);
  }
  unknown90 = &IDColiGrandTree::treeHitDef;
  if (result.unknown00 == 2) {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstTbl;
    } else {
      unknown30 = &IDColiGrandMesh::stockTbl;
    }
    unknown40 = &IDColiGrandMesh::stockInstTbl;
  } else {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstNear;
    } else {
      unknown30 = &IDColiGrandMesh::stockNear;
    }
    unknown40 = &IDColiGrandMesh::stockInstNear;
  }
  if (result.unknownb3) {
    if (m_iDCmfPosData != nullptr) {
      unknown70 = &IDColiGrandMesh::vecotrInst;
    } else {
      unknown70 = &IDColiGrandMesh::vecotrDef;
    }
    unknown80 = &IDColiGrandMesh::vecotrInst;
  } else {
    unknown70 = &IDColiGrandMesh::vecotrNon;
    unknown80 = &IDColiGrandMesh::vecotrNon;
  }
  return coliCallResl(&IDColiGrandTree::instSphereHitParts);
}

bool IDColiGrandObj::testCapsule(IDColiResult &result, const IDColiInput &input, bool isWall, const IDCmfPosData *posData) {
  m_iDCmfPosData = posData;
  IDColiInput capsule;
  IDColiInputUtil::getCapsule(capsule, input, posData, false);
  return testCapsule(result, capsule, isWall);
}

bool IDColiGrandObj::testCapsule(IDColiResult &result, const IDColiInput &input, bool isWall) {
  m_iDColiResult = &result;
  m_iDColiInput = &input;
  unknown20 = &IDColiGrandMesh::meshCapsule;
  unknownb0 = &IDColiGrandTree::isAaBbToAaBb;
  unknowna0 = &IDColiGrandTree::instCapsuleHit;
  unknown50 = &IDColiGrandMesh::lenghtLine;
  unknown60 = isWall ? &IDColiGrandMesh::lenghtWallSphere : &IDColiGrandMesh::lenghtSphere;
  if (result.unknown00 == 0) {
    unknown099();
    return coliCallCheck(&IDColiGrandTree::instCapsuleHitParts);
  }
  unknown90 = &IDColiGrandTree::treeHitDef;
  if (result.unknown00 == 2) {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstTbl;
    } else {
      unknown30 = &IDColiGrandMesh::stockTbl;
    }
    unknown40 = &IDColiGrandMesh::stockInstTbl;
  } else {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstNear;
    } else {
      unknown30 = &IDColiGrandMesh::stockNear;
    }
    unknown40 = &IDColiGrandMesh::stockInstNear;
  }
  if (result.unknownb3) {
    if (m_iDCmfPosData != nullptr) {
      unknown70 = &IDColiGrandMesh::vecotrInst;
    } else {
      unknown70 = &IDColiGrandMesh::vecotrDef;
    }
    unknown80 = &IDColiGrandMesh::vecotrInst;
  } else {
    unknown70 = &IDColiGrandMesh::vecotrNon;
    unknown80 = &IDColiGrandMesh::vecotrNon;
  }
  return coliCallResl(&IDColiGrandTree::instCapsuleHitParts);
}

bool IDColiGrandObj::testMoveSphere(IDColiResult &result, const IDColiInput &input, bool isStop) {
  m_iDColiResult = &result;
  m_iDColiInput = &input;
  unknown20 = &IDColiGrandMesh::meshSphere;
  unknowna0 = &IDColiGrandTree::instSphereHit;
  unknownb0 = &IDColiGrandTree::isAaBbToAaBb;
  unknown50 = &IDColiGrandMesh::lenghtWallSphere;
  unknown90 = &IDColiGrandTree::treeHitDef;
  if (result.unknown00 == 2) {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstTbl;
    } else {
      unknown30 = &IDColiGrandMesh::stockTbl;
    }
    unknown40 = &IDColiGrandMesh::stockInstTbl;
  } else {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstNear;
    } else {
      unknown30 = &IDColiGrandMesh::stockNear;
    }
    unknown40 = &IDColiGrandMesh::stockInstNear;
  }
  if (result.unknownb3) {
    if (m_iDCmfPosData != nullptr) {
      unknown70 = &IDColiGrandMesh::vecotrInst;
    } else {
      unknown70 = &IDColiGrandMesh::vecotrDef;
    }
    unknown80 = &IDColiGrandMesh::vecotrInst;
  } else {
    unknown70 = &IDColiGrandMesh::vecotrNon;
    unknown80 = &IDColiGrandMesh::vecotrNon;
  }
  return coliMoveCallResl(&IDColiGrandTree::instSphereHitParts, isStop);
}

bool IDColiGrandObj::testMoveCapsule(IDColiResult &result, const IDColiInput &input, bool isStop) {
  m_iDColiResult = &result;
  m_iDColiInput = &input;
  unknown20 = &IDColiGrandMesh::meshCapsule;
  unknownb0 = &IDColiGrandTree::isAaBbToAaBb;
  unknowna0 = &IDColiGrandTree::instCapsuleHit;
  unknown50 = &IDColiGrandMesh::lenghtLine;
  unknown60 = &IDColiGrandMesh::lenghtWallSphere;
  unknown90 = &IDColiGrandTree::treeHitDef;
  if (result.unknown00 == 2) {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstTbl;
    } else {
      unknown30 = &IDColiGrandMesh::stockTbl;
    }
    unknown40 = &IDColiGrandMesh::stockInstTbl;
  } else {
    if (m_iDCmfPosData != nullptr) {
      unknown30 = &IDColiGrandMesh::stockInstNear;
    } else {
      unknown30 = &IDColiGrandMesh::stockNear;
    }
    unknown40 = &IDColiGrandMesh::stockInstNear;
  }
  if (result.unknownb3) {
    if (m_iDCmfPosData != nullptr) {
      unknown70 = &IDColiGrandMesh::vecotrInst;
    } else {
      unknown70 = &IDColiGrandMesh::vecotrDef;
    }
    unknown80 = &IDColiGrandMesh::vecotrInst;
  } else {
    unknown70 = &IDColiGrandMesh::vecotrNon;
    unknown80 = &IDColiGrandMesh::vecotrNon;
  }
  return coliMoveCallResl(&IDColiGrandTree::instCapsuleHitParts, isStop);
}

bool IDColiGrandObj::testAaBb(IDColiResult &result, const IDColiInput &input) {
  m_iDColiResult = &result;
  m_iDColiInput = &input;
  unknown30 = nullptr;
  unknown40 = nullptr;
  unknown70 = &IDColiGrandMesh::vecotrNon;
  unknown80 = &IDColiGrandMesh::vecotrNon;
  unknown50 = nullptr;
  unknown20 = &IDColiGrandMesh::meshAaBb;
  unknowna0 = &IDColiGrandTree::instAaBbHit;
  unknownb0 = &IDColiGrandTree::isAaBbToAaBb;
  unknown90 = &IDColiGrandTree::treeHitEnd;
  return treeHitEnd(0);
}

bool IDColiGrandObj::getAaBbPoliAaBb(IDColiResult &result, const IDColiInput &input) {
  m_iDColiResult = &result;
  m_iDColiInput = &input;
  unknown30 = &IDColiGrandMesh::stockTbl;
  unknown40 = &IDColiGrandMesh::stockInstTbl;
  unknown70 = &IDColiGrandMesh::vecotrNon;
  unknown80 = &IDColiGrandMesh::vecotrNon;
  unknown50 = nullptr;
  unknown20 = &IDColiGrandMesh::meshAaBb;
  unknowna0 = &IDColiGrandTree::instAaBbHit;
  unknownb0 = &IDColiGrandTree::isAaBbToAaBb;
  unknown90 = &IDColiGrandTree::treeHitDef;
  return treeHitDef(0);
}

} // namespace idcoli
