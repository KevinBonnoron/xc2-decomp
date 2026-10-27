#include "idcoli/idcoli.h"
#include "mm_math/mm_mat44.h"

namespace idcoli {

IDColiGrdMoveObj::IDColiGrdMoveObj() {
  unknown1c8[0].unknown00.unknown00 = nullptr;
  unknown1c8[0].unknown00.unknown08 = nullptr;
  unknown1c8[0].unknown10 = this;
  unknown1c8[1].unknown00.unknown00 = nullptr;
  unknown1c8[1].unknown00.unknown08 = nullptr;
  unknown1c8[1].unknown10 = this;
  unknown1c0 = 0;
  unknown1b8 = nullptr;
}

void IDColiGrdMoveObj::setMat(const mm::Mat44 &matrix) {
  unknown00[IDColiManager::s_nStkIdx] = matrix;
  unknown1c0 |= 1 << IDColiManager::s_nStkIdx;
}

void IDColiGrdMoveObj::treeUpdate(IDColiTreeTop *tree, int index) { tree->setupTreeList(&unknown1c8[index].unknown00, unknown100.unknown80, unknown100.unknown90); }

} // namespace idcoli
