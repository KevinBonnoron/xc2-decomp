#pragma once

struct CBdatWrapper;

namespace gf {

struct GF_OBJ_HANDLE;

class GfObjFactory {
public:
  static GF_OBJ_HANDLE *createGmkMapObj(const CBdatWrapper &bdat, int id);
};

} // namespace gf
