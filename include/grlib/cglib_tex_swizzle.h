#pragma once
#include "types.h"

namespace grlib {

// Provenance: the name CGLibTexSwizzle comes from the mangled game symbol of grlib::CGLibTexture::createTextureImagePtrs; the members are
// the four component selectors passed by ptlib::material::MaterialManager::createTexture.
struct CGLibTexSwizzle {
  u32 unknown00; // Inferred role: red source; original member name unknown.
  u32 unknown04; // Inferred role: green source; original member name unknown.
  u32 unknown08; // Inferred role: blue source; original member name unknown.
  u32 unknown0c; // Inferred role: alpha source; original member name unknown.
};

static_assert(sizeof(CGLibTexSwizzle) == 0x10, "");

} // namespace grlib
