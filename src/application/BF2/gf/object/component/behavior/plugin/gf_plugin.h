#pragma once
#include <stddef.h>

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComBehavior;

class Plugin {
public:
  static mm::mtl::RTTI m_rtti;

  Plugin();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~Plugin();
  virtual void onActivate();
  virtual void onDeactivate();
  virtual bool onSetup(GfComBehavior &behavior) = 0;
  virtual void onCleanup(GfComBehavior &behavior) = 0;
  virtual void onUpdate(GfComBehavior &behavior, const fw::UpdateInfo &info) = 0;

  void setActivate(bool isActive);

  bool unknown08; // Inferred role: active; original member name unknown.
};

static_assert(offsetof(Plugin, unknown08) == 0x08, "");

#define GF_PLUGIN(Behavior)                                                                                                                                                                            \
public:                                                                                                                                                                                                \
  static mm::mtl::RTTI m_rtti;                                                                                                                                                                         \
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }                                                                                                                                    \
  bool onSetup(GfComBehavior &behavior) override { return setup(static_cast<Behavior &>(behavior)); }                                                                                                  \
  void onCleanup(GfComBehavior &behavior) override { cleanup(static_cast<Behavior &>(behavior)); }                                                                                                     \
  void onUpdate(GfComBehavior &behavior, const fw::UpdateInfo &info) override { update(static_cast<Behavior &>(behavior), info); }

} // namespace gf
