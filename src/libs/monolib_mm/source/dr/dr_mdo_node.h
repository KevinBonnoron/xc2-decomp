#pragma once
#include <stddef.h>

#include "dr/dr_mdo_anim.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace ml {

// Inferred role: node table header of the model data; original type name unknown.
struct unknown740 {
  u8 _00[0x08 - 0x00];
  u32 unknown08; // Inferred role: offset of the node infos; original member name unknown.
};

static_assert(offsetof(unknown740, unknown08) == 0x08, "");

// Inferred role: node info of the model data; original type name unknown.
struct unknown741 {
  u32 unknown00; // Inferred role: name offset from the node table; original member name unknown.
  u8 _04[0x18 - 0x04];
};

static_assert(sizeof(unknown741) == 0x18, "");

class DrMdoNode : public DrMdoAnim {
public:
  void updateMdlPos();
  void calcOfsMat();
  const char *getNodeName(int index) const;
  int getNodeIdx(const char *name) const;
  void setNodeMatrix(int index, const mm::Mat44 &matrix);
  const mm::Mat44 &getNodeMatrix(int index) const;
  mm::Mat44 *getNodeMatrixPtr(int index);
  int getNodeWorkSize();
  void calcNodeWorkSetup(u8 *work);
};

} // namespace ml
