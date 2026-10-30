#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace fw {
class SoundPack;
enum SoundCategory : int;
} // namespace fw

namespace gmk {

class GmkCtrlVolSe : public mm::mtl::IntrusiveListNode<GmkCtrlVolSe> {
public:
  struct CreateInfo {
    CreateInfo()
        : unknown00(nullptr), unknown08(0), unknown0c(static_cast<fw::SoundCategory>(6)), unknown10(0.0f), unknown14(10.0f), unknown18(0), unknown19(100), unknown1a(100), unknown20(mm::Vec3::zero),
          unknown30(gf::INVALID_HANDLE) {}

    fw::SoundPack *unknown00;     // Inferred role: sound pack; original member name unknown.
    u16 unknown08;                // Inferred role: sound id; original member name unknown.
    fw::SoundCategory unknown0c;  // Inferred role: sound category; original member name unknown.
    f32 unknown10;                // Inferred role: far distance; original member name unknown.
    f32 unknown14;                // Inferred role: near distance; original member name unknown.
    u8 unknown18;                 // Inferred role: far volume percent; original member name unknown.
    u8 unknown19;                 // Inferred role: near volume percent; original member name unknown.
    u8 unknown1a;                 // Inferred role: room volume percent; original member name unknown.
    mm::Vec3 unknown20;           // Inferred role: position; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown30; // Inferred role: follow target; original member name unknown.
  };

  GmkCtrlVolSe();
  virtual ~GmkCtrlVolSe() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  void createInst();
  void disposeInst(bool isFadeOut);
  void update(f32 deltaTime);
  bool isPlayEnd() const;
  void validateMute() const;
  void debugDraw() const;

  CreateInfo unknown20; // Inferred role: create info; original member name unknown.
  u32 unknown60;        // Inferred role: sound handle; original member name unknown.
  f32 unknown64;        // Inferred role: distance to the controlled mover; original member name unknown.
  bool unknown68;       // Inferred role: mute; original member name unknown.
  mm::Vec3 unknown70;   // Inferred role: sound position; original member name unknown.
};

static_assert(offsetof(GmkCtrlVolSe, unknown20) == 0x20, "");
static_assert(offsetof(GmkCtrlVolSe, unknown60) == 0x60, "");
static_assert(offsetof(GmkCtrlVolSe, unknown68) == 0x68, "");
static_assert(offsetof(GmkCtrlVolSe, unknown70) == 0x70, "");
static_assert(sizeof(GmkCtrlVolSe) == 0x80, "");

class GmkCtrlVolSeManager : public mm::mtl::PtrSingleton<GmkCtrlVolSeManager> {
public:
  GmkCtrlVolSeManager() : unknown20(false) {}
  ~GmkCtrlVolSeManager() override {}
  void update(f32 deltaTime);

  mm::mtl::IntrusiveList<GmkCtrlVolSe> unknown08; // Inferred role: ctrl vol ses; original member name unknown.
  bool unknown20;                                 // Inferred role: updating; original member name unknown.
};

static_assert(offsetof(GmkCtrlVolSeManager, unknown08) == 0x08, "");
static_assert(offsetof(GmkCtrlVolSeManager, unknown20) == 0x20, "");

} // namespace gmk
