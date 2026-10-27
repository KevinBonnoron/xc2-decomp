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
  const IDColiInput *current = unknown10;
  if (current->unknown00.x < posData->unknown90.x || current->unknown10.x > posData->unknown80.x || current->unknown00.z < posData->unknown90.z || current->unknown10.z > posData->unknown80.z ||
      current->unknown10.y > posData->unknown80.y || current->unknown00.y < posData->unknown90.y) {
    return false;
  }
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
  const IDColiInput *current = unknown10;
  if (current->unknown00.x < posData->unknown90.x || current->unknown10.x > posData->unknown80.x || current->unknown00.z < posData->unknown90.z || current->unknown10.z > posData->unknown80.z ||
      current->unknown10.y > posData->unknown80.y || current->unknown00.y < posData->unknown90.y) {
    return false;
  }
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
