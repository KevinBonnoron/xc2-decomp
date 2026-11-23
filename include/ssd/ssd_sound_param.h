#pragma once
#include <stddef.h>

#include "ssd/ssd_hash.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {

class SoundParam {
public:
  struct Name {
    void Init();
    Name &operator=(const TextRef &text);
    bool operator==(const TextRef &text);

    char16_t unknown00[32]; // Inferred role: text; original member name unknown.
    Hash m_hash;            // Inferred role: text hash; original member name unknown.
  };

  struct Base {
    void Init();

    bool unknown00; // Inferred role: flag cleared by Init; original member name unknown.
    u8 unknown01;   // Inferred role: sound group id, set to 1 by Init; original member name unknown.
    u8 unknown02;   // Inferred role: category id, set to 1 by Init; original member name unknown.
    bool unknown03; // Inferred role: flag cleared by Init; original member name unknown.
    f32 unknown04;  // Inferred role: value set to 1.0 by Init; original member name unknown.
    f32 unknown08;  // Inferred role: value cleared by Init; original member name unknown.
    f32 unknown0c;  // Inferred role: value set to 1.0 by Init; original member name unknown.
    f32 unknown10;  // Inferred role: value cleared by Init; original member name unknown.
    f32 unknown14;  // Inferred role: value cleared by Init; original member name unknown.
    f32 unknown18;  // Inferred role: value cleared by Init; original member name unknown.
  };

  struct State {
    void Init();

    bool unknown00; // Inferred role: flag cleared by Init; original member name unknown.
    bool unknown01; // Inferred role: flag set by Init; original member name unknown.
    bool unknown02; // Inferred role: flag set by Init; original member name unknown.
    bool unknown03; // Inferred role: flag cleared by Init; original member name unknown.
    bool unknown04; // Inferred role: flag cleared by Init; original member name unknown.
    bool unknown05; // Inferred role: flag cleared by Init; original member name unknown.
    bool unknown06; // Inferred role: flag cleared by Init; original member name unknown.
    bool unknown07; // Inferred role: flag cleared by Init; original member name unknown.
  };

  // Layout from SoundParam::Surround::Init and ssd::VoiceHandle, which reads the distances.
  struct Surround {
    void Init();

    f32 unknown00; // Inferred role: minimum distance, cleared by Init; original member name unknown.
    f32 unknown04; // Inferred role: value set to 1.0 by Init; original member name unknown.
    f32 unknown08; // Inferred role: maximum distance, set to 100.0 by Init; original member name unknown.
    int unknown0c; // Inferred role: value cleared by Init; original member name unknown.
    f32 unknown10; // Inferred role: value set to 1.0 by Init; original member name unknown.
  };

  struct Effect {
    void Init();

    f32 unknown00; // Inferred role: value cleared by Init; original member name unknown.
    f32 unknown04; // Inferred role: value set to 1.0 by Init; original member name unknown.
  };

  void Init();

  Name m_name;   // Inferred role: name; original member name unknown.
  u16 unknown48; // Inferred role: sound number; original member name unknown.
  u8 _4a[0x4c - 0x4a];
  Base m_base;         // Inferred role: base; original member name unknown.
  State m_state;       // Inferred role: state; original member name unknown.
  Surround m_surround; // Inferred role: surround; original member name unknown.
  Effect m_effect[2];  // Inferred role: effects; original member name unknown.
};

static_assert(offsetof(SoundParam, unknown48) == 0x48, "");
static_assert(offsetof(SoundParam, m_base) == 0x4c, "");
static_assert(offsetof(SoundParam, m_state) == 0x68, "");
static_assert(offsetof(SoundParam, m_surround) == 0x70, "");
static_assert(offsetof(SoundParam, m_effect) == 0x84, "");
static_assert(sizeof(SoundParam) == 0x94, "");

} // namespace ssd
