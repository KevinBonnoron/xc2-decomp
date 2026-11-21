#include "idcoli/idcoli.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace idcoli {

IDColiGrdMoveObj::IDColiGrdMoveObj() {
  unknown1c8[0].unknown00.unknown00 = nullptr;
  unknown1c8[0].unknown00.unknown08 = nullptr;
  unknown1c8[1].unknown00.unknown00 = nullptr;
  unknown1c8[1].unknown00.unknown08 = nullptr;
  unknown1c8[0].unknown10 = this;
  unknown1c0 = 0;
  unknown1b8 = nullptr;
  unknown1c8[1].unknown10 = this;
}

void IDColiGrdMoveObj::setMat(const mm::Mat44 &matrix) {
  unknown00[IDColiManager::s_nStkIdx] = matrix;
  unknown1c0 |= 1 << IDColiManager::s_nStkIdx;
}

void IDColiGrdMoveObj::setMoveData(const u8 *binary, const IDCmfMovePosData *data, const IDCmfMovePosInfo *info) {
  unknown1a8 = data;
  unknown1b0 = reinterpret_cast<const char *>(binary + info->unknown00);
  for (int row = 0; row < 4; row++) {
    for (int column = 0; column < 4; column++) {
      unknown00[0].rows[row][column] = data->unknown00.rows[row][column];
    }
  }
  unknown00[2] = unknown00[1] = unknown00[0];
  unknown1a0.unknown00 = info->unknown04;
  unknown1a0.unknown02 = info->unknown06;
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
    IDColiPrimitive::calcPosDataSetup(&unknown100, unknown00[IDColiManager::s_nDebIdx], unknown1a8->unknown50, unknown1a8->unknown60);
    unknown1c0 &= ~(1 << IDColiManager::s_nDebIdx);
  }
}

void IDColiGrdMoveObj::treeUpdate(IDColiTreeTop *tree, int index) { tree->setupTreeList(&unknown1c8[index].unknown00, unknown100.unknown80, unknown100.unknown90); }

} // namespace idcoli
