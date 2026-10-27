#pragma once

struct CBdatWrapper;

namespace gf {

struct GF_OBJ_HANDLE;
class GfInitParamMap;

class GfObjFactory {
public:
  static GF_OBJ_HANDLE *createGmkMapObj(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkTbox(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkNpc(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkBlade(const CBdatWrapper &bdat, int id, int param3);
  static GF_OBJ_HANDLE *createGmkCollection(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkMapGimmick(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createDebugMap(const GfInitParamMap &param);
  static void destroyObj(GF_OBJ_HANDLE *handle);
};

} // namespace gf
