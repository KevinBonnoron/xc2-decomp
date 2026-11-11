#pragma once
#include <stddef.h>

#include "framework/coli/coli_object.h"
#include "gmk/gmk_phantom.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gmk {
class AGmkBase;

class GmkCollision : public fw::ColiUserData, public fw::IColiEventListener {
public:
  struct CreateInfo {
    CreateInfo() : unknown00(GmkPhantom::SHAPE_TYPE_UNKNOWN_0), unknown10(0.0f, 0.0f, 0.0f), unknown20(0.0f, 0.0f, 0.0f), unknown30(false) {
      for (u32 i = 0; i < 3; i++) {
        unknown34[i] = 0.0f;
      }
    }

    GmkPhantom::ShapeType unknown00; // Inferred role: shape type; original member name unknown.
    mm::Vec3 unknown10;              // Inferred role: position; original member name unknown.
    mm::Vec3 unknown20;              // Inferred role: rotation; original member name unknown.
    bool unknown30;                  // Inferred role: shape flag, turns the shape into a capsule; original member name unknown.
    f32 unknown34[3];                // Inferred role: size; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  explicit GmkCollision(const CreateInfo *info = nullptr);
  virtual ~GmkCollision() { dispose(); }
  void create(const CreateInfo &info);
  void create(const AGmkBase &gmk, bool flag);
  void dispose();
  void update(f32 deltaTime);
  void enter(const EnterInfo &info) override;
  void leave(const LeaveInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  CreateInfo unknown10;      // Inferred role: create info; original member name unknown.
  const char *unknown50;     // Inferred role: name; original member name unknown.
  fw::ColiObject *unknown58; // Inferred role: collision object; original member name unknown.
  bool unknown60;            // Role and original member name unknown.
  bool unknown61;            // Role and original member name unknown.
  bool unknown62;            // Role and original member name unknown.
};

static_assert(offsetof(GmkCollision::CreateInfo, unknown10) == 0x10, "");
static_assert(offsetof(GmkCollision::CreateInfo, unknown20) == 0x20, "");
static_assert(offsetof(GmkCollision::CreateInfo, unknown30) == 0x30, "");
static_assert(offsetof(GmkCollision::CreateInfo, unknown34) == 0x34, "");
static_assert(sizeof(GmkCollision::CreateInfo) == 0x40, "");
static_assert(offsetof(GmkCollision, unknown10) == 0x10, "");
static_assert(offsetof(GmkCollision, unknown50) == 0x50, "");
static_assert(offsetof(GmkCollision, unknown58) == 0x58, "");
static_assert(offsetof(GmkCollision, unknown60) == 0x60, "");
static_assert(offsetof(GmkCollision, unknown61) == 0x61, "");
static_assert(offsetof(GmkCollision, unknown62) == 0x62, "");
static_assert(sizeof(GmkCollision) == 0x70, "");

} // namespace gmk
