#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"

namespace idcoli {

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

} // namespace idcoli
