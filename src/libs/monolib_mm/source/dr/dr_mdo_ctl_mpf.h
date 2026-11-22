#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "types.h"

namespace ml {

class DrMan;
class DrMdoCtlMpfAuto;
class DrMdoCtlMpfInst;
class DrMdoCtlMpfWork;
class DrResMdoSeamWrkPosMpf;
class DrResMdoSortMpf;

class DrMdoCtlMpf : public DrMdlObj {
public:
  DrMdoCtlMpf(const void *data, const char *path, DrMan *drMan, int viewNum);
  ~DrMdoCtlMpf() override;
  void setupMpf(const u8 *data);
  void releaseMpf();
  void update() override;
  void resourceInit() override;
  void callZPrepassRender();
  void updateMpf();
  void calcMpfRenderList();
  bool calcMpfMatSetup();
  void callRenderMpf();
  void defMpfZPreRender();
  void defMpfrender();
  void createDisplaList();

  s32 unknown1a4; // Inferred role: object count; original member name unknown.
  u8 _1a8[0x1b0 - 0x1a8];
  u8 *unknown1b0;                                 // Inferred role: work memory; original member name unknown.
  u8 *unknown1b8;                                 // Inferred role: second work memory, released with the first; original member name unknown.
  u32 unknown1c0;                                 // Inferred role: unknown value cleared by the constructor; original member name unknown.
  DrMdoCtlMpfWork *m_drMdoCtlMpfWork;             // Inferred role: render list work, at the start of the work memory; original member name unknown.
  DrMdoCtlMpfAuto *m_drMdoCtlMpfAuto;             // Inferred role: auto mpf, in the work memory; original member name unknown.
  DrMdoCtlMpfInst *m_drMdoCtlMpfInst;             // Inferred role: instance mpf, in the work memory; original member name unknown.
  DrResMdoSeamWrkPosMpf *m_drResMdoSeamWrkPosMpf; // Inferred role: positions, in the work memory; original member name unknown.
  DrResMdoSortMpf *m_drResMdoSortMpf;             // Inferred role: z sort object, at the end of the work memory; original member name unknown.
  u8 _1f0[0x200 - 0x1f0];
};

static_assert(offsetof(DrMdoCtlMpf, unknown1a4) == 0x1a4, "");
static_assert(offsetof(DrMdoCtlMpf, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DrMdoCtlMpf, m_drMdoCtlMpfWork) == 0x1c8, "");
static_assert(offsetof(DrMdoCtlMpf, m_drResMdoSortMpf) == 0x1e8, "");
static_assert(sizeof(DrMdoCtlMpf) == 0x200, "");

} // namespace ml
