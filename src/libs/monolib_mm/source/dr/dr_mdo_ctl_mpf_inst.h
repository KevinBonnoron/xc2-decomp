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

  const MdsMpfObjData *m_mdsMpfObjData;           // Inferred role: instance object data; original member name unknown.
  DrMdoCtlMpfWork *m_drMdoCtlMpfWork;             // Inferred role: mpf work, set by calcInstMpf and calcSeamInstMpf; original member name unknown.
  DrResMdoSeamWrkPosMpf *m_drResMdoSeamWrkPosMpf; // Inferred role: positions, set by calcInstMpf and calcSeamInstMpf; original member name unknown.
};

static_assert(offsetof(DrMdoCtlMpfInst, m_drMdoCtlMpfWork) == 0x08, "");
static_assert(offsetof(DrMdoCtlMpfInst, m_drResMdoSeamWrkPosMpf) == 0x10, "");

} // namespace ml
