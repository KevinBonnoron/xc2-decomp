#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ml {
class Scn;
class ScnObjModel;
} // namespace ml

namespace fw {

class ReferenceFrame;

// Inferred role: element of the per-layer lists of ModelManager, shared by ModelObject and VisibleObject; original name unknown.
// Evidence: ModelObject::~ModelObject and changeLayer, VisibleObject::create, ~VisibleObject and changeLayer link the node at +0x10
// into the same ModelManager::unknown18[layer] list (1.0.0: 0x710018e8c8, 0x710018ea8c, 0x710018ec10, 0x710018ed70, 0x710018eeec),
// ModelManager::update calls the virtual at +0x10 of each node (0x710018e530), and both vtables (0x1178ec8, 0x1178ef0) are 0x28
// bytes: two header words, the destructor pair and update.
class unknown083 : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<unknown083> {
public:
  virtual void update() = 0;
};

static_assert(sizeof(unknown083) == 0x20, "");

class ModelObject : public unknown083 {
public:
  ModelObject();
  virtual ~ModelObject();
  virtual void update();
  void setup();
  void changeLayer(u32 layer);
  bool isRender() const;
  ml::ScnObjModel *getInterface();
  void setActive(bool isActive);
  bool isActive() const;
  void setAddOffsetPos(const mm::Vec3 &offset);
  void setScale(f32 scale);

  u64 unknown20;      // Role and original member name unknown.
  ml::Scn *unknown28; // Inferred role: scn; original member name unknown.
  ml::ScnObjModel *m_interface;
  u32 unknown38; // Inferred role: layer; original member name unknown.
  bool m_active;
  bool unknown3d; // Inferred role: offset dirty; original member name unknown.
  u8 _3e[0x40 - 0x3e];
  mm::mtl::IntrusivePtr<ReferenceFrame> unknown40; // Inferred role: reference frame; original member name unknown.
  u8 _48[0x50 - 0x48];
  mm::Vec3 m_addOffsetPos;
  f32 unknown60; // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(ModelObject, unknown20) == 0x20, "");
static_assert(offsetof(ModelObject, unknown28) == 0x28, "");
static_assert(offsetof(ModelObject, m_interface) == 0x30, "");
static_assert(offsetof(ModelObject, unknown38) == 0x38, "");
static_assert(offsetof(ModelObject, unknown40) == 0x40, "");
static_assert(offsetof(ModelObject, m_active) == 0x3c, "");
static_assert(offsetof(ModelObject, unknown3d) == 0x3d, "");
static_assert(offsetof(ModelObject, m_addOffsetPos) == 0x50, "");
static_assert(offsetof(ModelObject, unknown60) == 0x60, "");

} // namespace fw
