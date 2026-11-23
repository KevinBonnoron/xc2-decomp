#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

struct EventBgmSetup {
  EventBgmSetup()
      : m_playBgmVolume(1.0f), unknown48(0.0f), unknown4c(0.0f), unknown50(0.0f), unknown54(0.0f), unknown58(0.0f), unknown5c(0.0f), unknown60(false), unknown61(false), unknown62(false),
        unknown63(false), unknown64(false), unknown65(false) {}

  mm::mtl::FixStr<64> unknown00; // Inferred role: name; original member name unknown.
  f32 m_playBgmVolume;           // Inferred role: volume; named after the game accessor gf::GfEvtBgm::setPlayBgmVolume.
  f32 unknown48;                 // Inferred role: volume seconds; original member name unknown.
  f32 unknown4c;                 // Inferred role: fade seconds; original member name unknown.
  f32 unknown50;                 // Inferred role: start seconds; original member name unknown.
  f32 unknown54;                 // Inferred role: delay seconds; original member name unknown.
  f32 unknown58;                 // Inferred role: fade out seconds; original member name unknown.
  f32 unknown5c;                 // Inferred role: over time seconds; original member name unknown.
  bool unknown60;                // Inferred role: keep flag; original member name unknown.
  bool unknown61;                // Inferred role: hand over flag; original member name unknown.
  bool unknown62;                // Inferred role: event flag; original member name unknown.
  bool unknown63;                // Inferred role: restart flag; original member name unknown.
  bool unknown64;                // Inferred role: audible flag; original member name unknown.
  bool unknown65;                // Inferred role: silent flag; original member name unknown.
};

static_assert(sizeof(EventBgmSetup) == 0x68, "");

} // namespace gf
