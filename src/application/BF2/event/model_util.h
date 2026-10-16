#pragma once

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class ModelUtil {
public:
  static void setupRenderState(gf::GF_OBJ_HANDLE *handle);
};

} // namespace event
