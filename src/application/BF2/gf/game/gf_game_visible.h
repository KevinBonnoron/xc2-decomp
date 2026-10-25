#pragma once

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfGameVisible {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  void updateImpl(const fw::UpdateInfo &info);
  static void cleanup();
};

} // namespace gf
