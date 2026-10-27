#pragma once
#include "dr/dr_mdo_anim.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace ml {

class DrMdoNode : public DrMdoAnim {
public:
  void updateMdlPos();
  const char *getNodeName(int index) const;
  int getNodeIdx(const char *name) const;
  void setNodeMatrix(int index, const mm::Mat44 &matrix);
  const mm::Mat44 &getNodeMatrix(int index) const;
  mm::Mat44 *getNodeMatrixPtr(int index);
};

} // namespace ml
