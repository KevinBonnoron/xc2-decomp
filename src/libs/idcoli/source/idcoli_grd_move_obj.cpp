#include "idcoli/idcoli.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace idcoli {

IDColiGrdMoveObj::IDColiGrdMoveObj() {
  unknown1c8[0].m_iDColiTreeObj.unknown00 = nullptr;
  unknown1c8[0].m_iDColiTreeObj.unknown08 = nullptr;
  unknown1c8[1].m_iDColiTreeObj.unknown00 = nullptr;
  unknown1c8[1].m_iDColiTreeObj.unknown08 = nullptr;
  unknown1c8[0].m_iDColiGrdMoveObj = this;
  unknown1c0 = 0;
  m_userData = nullptr;
  unknown1c8[1].m_iDColiGrdMoveObj = this;
}

void IDColiGrdMoveObj::setMat(const mm::Mat44 &matrix) {
  unknown00[IDColiManager::s_nStkIdx] = matrix;
  unknown1c0 |= 1 << IDColiManager::s_nStkIdx;
}

void IDColiGrdMoveObj::setMoveData(const u8 *binary, const IDCmfMovePosData *data, const IDCmfMovePosInfo *info) {
  m_iDCmfMovePosData = data;
  m_name = reinterpret_cast<const char *>(binary + info->unknown00);
  for (int row = 0; row < 4; row++) {
    for (int column = 0; column < 4; column++) {
      unknown00[0].rows[row][column] = data->unknown00.rows[row][column];
    }
  }
  unknown00[2] = unknown00[1] = unknown00[0];
  m_iDCmfPosInfo.unknown00 = info->unknown04;
  m_iDCmfPosInfo.m_iD = info->unknown06;
  unknown1c0 |= 1 << IDColiManager::s_nDebIdx;
  update();
}

void IDColiGrdMoveObj::update() {
  if ((unknown1c0 & (1 << IDColiManager::s_nDebIdx)) != 0) {
    // Inverse of the previous matrix (unknown00[2]) read in place, then the product with the new matrix of the debug index stored over it (the
    // game's 0x71008e60f4 matches with the aliased product unknown002; unknown001 on the same object gives 431 instructions, operator* 560).
    unknownc0.unknown014(unknown00[2]);
    unknownc0.unknown002(unknownc0, unknown00[IDColiManager::s_nDebIdx]);
    unknown00[2] = unknown00[IDColiManager::s_nDebIdx];
    IDColiPrimitive::calcPosDataSetup(&m_iDCmfPosData, unknown00[IDColiManager::s_nDebIdx], m_iDCmfMovePosData->unknown50, m_iDCmfMovePosData->unknown60);
    unknown1c0 &= ~(1 << IDColiManager::s_nDebIdx);
  }
}

void IDColiGrdMoveObj::treeUpdate(IDColiTreeTop *tree, int index) { tree->setupTreeList(&unknown1c8[index].m_iDColiTreeObj, m_iDCmfPosData.unknown80, m_iDCmfPosData.unknown90); }

} // namespace idcoli
