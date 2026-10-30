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

void IDColiGrdMoveObj::treeUpdate(IDColiTreeTop *tree, int index) { tree->setupTreeList(&unknown1c8[index].unknown00, unknown100.unknown80, unknown100.unknown90); }

} // namespace idcoli
