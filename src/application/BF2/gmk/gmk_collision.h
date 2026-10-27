#pragma once
#include <stddef.h>

#include "framework/coli/coli_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gmk {

class GmkCollision : public fw::ColiUserData, public fw::IColiEventListener {
public:
  static mm::mtl::RTTI m_rtti;

  ~GmkCollision() override { dispose(); }
  void dispose();
  void update(f32 deltaTime);
  void enter(const EnterInfo &info) override;
  void leave(const LeaveInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  u8 _10[0x50 - 0x10];
  u64 unknown50;             // Role and original member name unknown.
  fw::ColiObject *unknown58; // Inferred role: collision object; original member name unknown.
  bool unknown60;            // Role and original member name unknown.
  bool unknown61;            // Role and original member name unknown.
  bool unknown62;            // Role and original member name unknown.
  u8 _63[0x68 - 0x63];
};

static_assert(offsetof(GmkCollision, unknown50) == 0x50, "");
static_assert(offsetof(GmkCollision, unknown58) == 0x58, "");
static_assert(offsetof(GmkCollision, unknown60) == 0x60, "");
static_assert(offsetof(GmkCollision, unknown61) == 0x61, "");
static_assert(offsetof(GmkCollision, unknown62) == 0x62, "");
static_assert(sizeof(GmkCollision) == 0x68, "");

} // namespace gmk
