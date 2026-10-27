#pragma once
namespace ml {
class DrMdlObj;
class ScnObjModel;
} // namespace ml

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_OBJ_HANDLE;

class MapSeam {
public:
  ~MapSeam();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();
  ml::ScnObjModel *getModel() const;
  ml::DrMdlObj *getDrModel() const;

  GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
};

} // namespace gf
