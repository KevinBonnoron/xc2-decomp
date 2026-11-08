#pragma once

namespace fw {

// Declared from the parameter type of gf::checkSoundTriggerPlayer; only the leading name is read so far.
struct ResSoundTriggerInfo {
  const char *unknown00; // Inferred role: trigger name; original member name unknown.
};

class SoundResTriggerImporter {
public:
  // Inferred role: sound triggers of one animation set, from the loop of GfExtendPacking::registerSoundTrigger over three arrays; original type name unknown.
  struct unknown001;

  static unknown001 *importBinary(void *data);
};

} // namespace fw
