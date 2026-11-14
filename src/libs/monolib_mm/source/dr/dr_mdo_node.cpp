#include "dr/dr_mdo_node.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "mm_math/mm_mat44.h"

namespace ml {

// Inferred role: node table of the model data; original name unknown.
static const unknown740 *unknown067(const MdoWrkMatRes *matRes) { return reinterpret_cast<const unknown740 *>(reinterpret_cast<const u8 *>(matRes->unknown20) + matRes->unknown20->unknown28); }

// Inferred role: node infos of the node table; original name unknown.
static const unknown741 *unknown065(const unknown740 *table) { return reinterpret_cast<const unknown741 *>(reinterpret_cast<const u8 *>(table) + table->unknown08); }

int DrMdoNode::getNodeWorkSize() { return m_nodeMax << 7; }

void DrMdoNode::calcNodeWorkSetup(u8 *work) {
  unknown60[0] = reinterpret_cast<mm::Mat44 *>(work);
  unknown60[1] = reinterpret_cast<mm::Mat44 *>(work + (m_nodeMax << 6));
}

const char *DrMdoNode::getNodeName(int index) const {
  const unknown740 *table = unknown067(unknown30);
  return reinterpret_cast<const char *>(table) + unknown065(table)[index].unknown00;
}

int DrMdoNode::getNodeIdx(const char *name) const {
  if (m_nodeMax != 0) {
    const unknown740 *table = unknown067(unknown30);
    const unknown741 *infos = unknown065(table);
    for (int index = 0; index < m_nodeMax; index++) {
      if (strcmp(name, reinterpret_cast<const char *>(table) + infos[index].unknown00) == 0) {
        return index;
      }
    }
  }
  return -1;
}

void DrMdoNode::setNodeMatrix(int index, const mm::Mat44 &matrix) {
  if (m_nodeMax != 0) {
    memcpy(&unknown60[DrMan::s_nDblStockIdx][index], &matrix, sizeof(mm::Mat44));
  }
}

const mm::Mat44 &DrMdoNode::getNodeMatrix(int index) const { return unknown60[DrMan::s_nDblStockIdx][index]; }

mm::Mat44 *DrMdoNode::getNodeMatrixPtr(int index) { return &unknown60[DrMan::s_nDblStockIdx][index]; }

} // namespace ml
