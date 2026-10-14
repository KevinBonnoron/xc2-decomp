#pragma once

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfGameTalk {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
};

} // namespace gf
