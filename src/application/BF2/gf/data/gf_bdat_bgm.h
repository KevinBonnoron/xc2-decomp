#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatBgm : public mm::mtl::PtrSingleton<GfBdatBgm>, public GfBdatRefresh {
public:
  GfBdatBgm();
  virtual ~GfBdatBgm();
  void destroyFP();
  void createFP();
  void bdatRefresh() override;
  u32 getBgmListStart() const;
  u32 getBgmListEnd() const;
  const char *getBgmListfilename(u32 id) const;
  u32 getBgmConditionStart() const;
  u32 getBgmConditionEnd() const;
  u32 getBgmConditionConditionA(u32 id) const;
  u32 getBgmConditionBgmIDA(u32 id) const;
  u32 getBgmConditionConditionB(u32 id) const;
  u32 getBgmConditionBgmIDB(u32 id) const;
  u32 getBgmConditionConditionC(u32 id) const;
  u32 getBgmConditionBgmIDC(u32 id) const;
  u32 getBgmConditionConditionD(u32 id) const;
  u32 getBgmConditionBgmIDD(u32 id) const;
  u32 getBgmConditionPriority(u32 id) const;
  u32 getBgmConditionCondition(u32 id, u32 index) const;
  u32 getBgmConditionBgmID(u32 id, u32 index) const;

private:
  CBdatWrapper *unknown10; // Inferred label: mBgmList; original member name unknown.
  CBdatWrapper *unknown18; // Inferred label: mBgmCondition; original member name unknown.
};

} // namespace gf
