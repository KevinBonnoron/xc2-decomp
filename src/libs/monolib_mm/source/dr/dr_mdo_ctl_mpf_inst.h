#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrCalcViewWork;
class DrMdoCtlMpfWork;
class DrResMdoSeamWrkPosMpf;
struct MdsMpfObjData;
struct MdsMpfObjTreeData;

class DrMdoCtlMpfInst {
public:
  DrMdoCtlMpfInst();
  void setupInstMpf(const u8 *resource);
  void calcInstMpf(DrCalcViewWork *view, DrMdoCtlMpfWork *work, DrResMdoSeamWrkPosMpf *pos);
  void calcSeamInstMpf(DrCalcViewWork *view, DrMdoCtlMpfWork *work, DrResMdoSeamWrkPosMpf *pos);
  void calcMpfObjTree(const MdsMpfObjTreeData *tree, DrCalcViewWork *view, f32 range);
  void calcSeamMpfObjTree(const MdsMpfObjTreeData *tree, DrCalcViewWork *view, f32 range);

  const MdsMpfObjData *unknown00;   // Inferred role: instance object data; original member name unknown.
  DrMdoCtlMpfWork *unknown08;       // Inferred role: mpf work, set by calcInstMpf and calcSeamInstMpf; original member name unknown.
  DrResMdoSeamWrkPosMpf *unknown10; // Inferred role: positions, set by calcInstMpf and calcSeamInstMpf; original member name unknown.
};

static_assert(offsetof(DrMdoCtlMpfInst, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoCtlMpfInst, unknown10) == 0x10, "");

} // namespace ml
