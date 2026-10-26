#pragma once
#include "bdat.h"
#include "types.h"

struct CBdatWrapper {
  CBdatWrapper() {}
  CBdatWrapper(u8 *bdat) : unknown00(bdat) {}

  unsigned long getValCheck(const char *name, int id, int type) const { return Bdat::getValCheck(unknown00, name, id, type); }
  Bdat::Value getValCheck(u8 *member, u32 id, int type) const { return Bdat::getValCheck(unknown00, member, id, type); }
  Bdat::Value getArrayValCheck(u8 *member, u32 id, u32 index, int type) const { return Bdat::getArrayValCheck(unknown00, member, id, index, type); }
  int getFlagVal(u8 *member, u32 id, u8 *flag) const { return Bdat::getFlagVal(unknown00, member, id, flag); }

  u8 *unknown00; // Inferred role: raw bdat data; original member name unknown.
};

namespace gf {

class GfBdatRefresh {
public:
  virtual void bdatRefresh() = 0;
};

} // namespace gf
