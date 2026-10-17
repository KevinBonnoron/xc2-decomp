#pragma once

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfObj;

class GfObjUpdate {
public:
  static void updateComponent(GfObj *obj, const fw::UpdateInfo &info);
};

} // namespace gf
