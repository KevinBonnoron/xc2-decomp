#include <math.h>

#include "idcoli/idcoli.h"
#include "idcoli/idcoli_grand_mesh.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

IDColiGrandMesh::IDColiGrandMesh() {}

IDColiGrandTree::IDColiGrandTree() {}

bool IDColiGrandTree::instLineHit(u32 index) { return instLineHitParts(&unknown00->unknown30[index], &unknown00->unknown38[index]); }

bool IDColiGrandTree::instRayHit(u32 index) { return instRayHitParts(&unknown00->unknown30[index], &unknown00->unknown38[index]); }

bool IDColiGrandTree::instSphereHit(u32 index) { return instSphereHitParts(&unknown00->unknown30[index], &unknown00->unknown38[index]); }

bool IDColiGrandTree::instCapsuleHit(u32 index) { return instCapsuleHitParts(&unknown00->unknown30[index], &unknown00->unknown38[index]); }

bool IDColiGrandTree::instAaBbHit(u32 index) { return instAaBbHitParts(&unknown00->unknown30[index], &unknown00->unknown38[index]); }

bool IDColiGrandTree::isLineAaBb(const float *max, const float *min) {
  if (isAaBbToAaBb(max, min)) {
    return true;
  }
  const IDColiInput *input = unknown10;
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
  if (IDColiManager::get()->isGblId(posInfo->unknown02)) {
    return false;
  }
  if (isLineAaBb(&posData->unknown80.x, &posData->unknown90.x)) {
    return false;
  }
  const IDColiInput *current = unknown10;
  if (current->unknowna0 != 0.0f && isRangeAaBb(&posData->unknown80, &posData->unknown90)) {
    return false;
  }
  const IDCmfPosData *savedPosData = unknown18;
  decltype(unknown30) savedStock = unknown30;
  decltype(unknown70) savedVector = unknown70;
  IDColiInput input;
  IDColiInputUtil::getLine(input, *current, posData, false);
  unknown10 = &input;
  unknown18 = posData;
  unknown30 = unknown40;
  unknown70 = unknown80;
  bool isHit = (this->*unknown90)(unknown00->unknown08[posInfo->unknown00].unknown0c);
  unknown10 = current;
  unknown18 = savedPosData;
  unknown30 = savedStock;
  unknown70 = savedVector;
  return isHit;
}

bool IDColiGrandTree::instRayHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo) {
  if (IDColiManager::get()->isGblId(posInfo->unknown02)) {
    return false;
  }
  if (isLineAaBb(&posData->unknown80.x, &posData->unknown90.x)) {
    return false;
  }
  const IDColiInput *current = unknown10;
  if (current->unknowna0 != 0.0f && isRangeAaBb(&posData->unknown80, &posData->unknown90)) {
    return false;
  }
  const IDCmfPosData *savedPosData = unknown18;
  decltype(unknown30) savedStock = unknown30;
  decltype(unknown70) savedVector = unknown70;
  IDColiInput input;
  IDColiInputUtil::getRay(input, *current, posData, false);
  unknown10 = &input;
  unknown18 = posData;
  unknown30 = unknown40;
  unknown70 = unknown80;
  bool isHit = (this->*unknown90)(unknown00->unknown08[posInfo->unknown00].unknown0c);
  unknown10 = current;
  unknown18 = savedPosData;
  unknown30 = savedStock;
  unknown70 = savedVector;
  return isHit;
}

bool IDColiGrandTree::instSphereHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo) {
  if (IDColiManager::get()->isGblId(posInfo->unknown02)) {
    return false;
  }
  if (isAaBbToAaBb(&posData->unknown80.x, &posData->unknown90.x)) {
    return false;
  }
  const IDColiInput *current = unknown10;
  if (current->unknowna0 != 0.0f && isRangeAaBb(&posData->unknown80, &posData->unknown90)) {
    return false;
  }
  const IDCmfPosData *savedPosData = unknown18;
  decltype(unknown30) savedStock = unknown30;
  decltype(unknown70) savedVector = unknown70;
  IDColiInput input;
  IDColiInputUtil::getSphere(input, *current, posData, false);
  unknown30 = unknown40;
  unknown70 = unknown80;
  unknown10 = &input;
  unknown18 = posData;
  bool isHit = (this->*unknown90)(unknown00->unknown08[posInfo->unknown00].unknown0c);
  unknown10 = current;
  unknown18 = savedPosData;
  unknown30 = savedStock;
  unknown70 = savedVector;
  return isHit;
}

bool IDColiGrandTree::instCapsuleHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo) {
  if (IDColiManager::get()->isGblId(posInfo->unknown02)) {
    return false;
  }
  if (isAaBbToAaBb(&posData->unknown80.x, &posData->unknown90.x)) {
    return false;
  }
  const IDColiInput *current = unknown10;
  if (current->unknowna0 != 0.0f && isRangeAaBb(&posData->unknown80, &posData->unknown90)) {
    return false;
  }
  const IDCmfPosData *savedPosData = unknown18;
  decltype(unknown30) savedStock = unknown30;
  decltype(unknown70) savedVector = unknown70;
  IDColiInput input;
  IDColiInputUtil::getCapsule(input, *current, posData, false);
  unknown10 = &input;
  unknown18 = posData;
  unknown30 = unknown40;
  unknown70 = unknown80;
  bool isHit = (this->*unknown90)(unknown00->unknown08[posInfo->unknown00].unknown0c);
  unknown10 = current;
  unknown18 = savedPosData;
  unknown30 = savedStock;
  unknown70 = savedVector;
  return isHit;
}

bool IDColiGrandTree::instAaBbHitParts(const IDCmfPosData *posData, const IDCmfPosInfo *posInfo) {
  if (IDColiManager::get()->isGblId(posInfo->unknown02)) {
    return false;
  }
  if (isAaBbToAaBb(&posData->unknown80.x, &posData->unknown90.x)) {
    return false;
  }
  const IDColiInput *current = unknown10;
  if (current->unknowna0 != 0.0f && isRangeAaBb(&posData->unknown80, &posData->unknown90)) {
    return false;
  }
  const IDCmfPosData *savedPosData = unknown18;
  IDColiInput input;
  IDColiInputUtil::getOBB(input, current->unknown00, current->unknown10, posData);
  unknown10 = &input;
  unknown18 = posData;
  unknown20 = &IDColiGrandMesh::meshOBB;
  bool isHit = (this->*unknown90)(unknown00->unknown08[posInfo->unknown00].unknown0c);
  unknown10 = current;
  unknown18 = savedPosData;
  unknown20 = &IDColiGrandMesh::meshAaBb;
  return isHit;
}

bool IDColiGrandTree::isRangeAaBb(const mm::Vec3 *max, const mm::Vec3 *min) {
  mm::Vec3 half = (*max - *min) * 0.5f;
  return half.x * half.x + half.y * half.y + half.z * half.z <= unknown10->unknowna0;
}

bool IDColiGrandTree::isAaBbToAaBb(const float *max, const float *min) {
  const IDColiInput *input = unknown10;
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

IDColiGrandObj::IDColiGrandObj(wrkIDCmfWork *work) {
  unknown00 = work;
  unknown18 = nullptr;
}

IDColiGrandObj::~IDColiGrandObj() {}

bool IDColiGrandObj::coliCallCheck(unknown020 function) {
  if (unknown00->unknown88 == 0) {
    if ((this->*unknown90)(0)) {
      return true;
    }
  } else {
    const unknown094 *record = unknown00->unknown80;
    for (int i = 0; i < unknown00->unknown88; i++, record++) {
      if (record->unknown00 != 0 && IDColiManager::get()->isGblId(record->unknown00)) {
        continue;
      }
      if ((record->unknown08 & 1) && (record->unknown08 >> 8) != IDColiManager::get()->unknownf0) {
        continue;
      }
      if ((this->*unknown90)(record->unknown04)) {
        return true;
      }
    }
  }
  if (unknown00->unknown78 != 0) {
    IDColiUtilTreeAcc tree(unknown00->unknown90[unknown00->unknowna0]);
    tree.startTreeAaBbMode(unknown10->unknown00, unknown10->unknown10);
    for (ColiLinkList<IDColiTreeObj> *list = tree.unknown033(); list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiGrdMoveObj *moveObj = reinterpret_cast<unknown006 *>(node)->unknown10;
        unknown08->unknownf0 = reinterpret_cast<u64>(moveObj->unknown1b8);
        if ((this->*function)(&moveObj->unknown100, &moveObj->unknown1a0)) {
          return true;
        }
      }
    }
  }
  return false;
}

bool IDColiGrandObj::testLine(IDColiResult &result, const IDColiInput &input, const IDCmfPosData *posData) {
  unknown18 = posData;
  IDColiInput line;
  IDColiInputUtil::getLine(line, input, posData, false);
  return testLine(result, line);
}

bool IDColiGrandObj::testRay(IDColiResult &result, const IDColiInput &input, const IDCmfPosData *posData) {
  unknown18 = posData;
  IDColiInput ray;
  IDColiInputUtil::getRay(ray, input, posData, false);
  return testRay(result, ray);
}

bool IDColiGrandObj::testSphere(IDColiResult &result, const IDColiInput &input, bool isWall, const IDCmfPosData *posData) {
  unknown18 = posData;
  IDColiInput sphere;
  IDColiInputUtil::getSphere(sphere, input, posData, false);
  return testSphere(result, sphere, isWall);
}

bool IDColiGrandObj::testCapsule(IDColiResult &result, const IDColiInput &input, bool isWall, const IDCmfPosData *posData) {
  unknown18 = posData;
  IDColiInput capsule;
  IDColiInputUtil::getCapsule(capsule, input, posData, false);
  return testCapsule(result, capsule, isWall);
}

bool IDColiGrandObj::testAaBb(IDColiResult &result, const IDColiInput &input) {
  unknown08 = &result;
  unknown10 = &input;
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
  unknown08 = &result;
  unknown10 = &input;
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
