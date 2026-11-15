#pragma once

namespace anm {

class ResASM;

class AsmImporter {
public:
  // Returns the ResASM stored at +0x8 of the resolved binary; the game checks the ASMB magic first.
  static ResASM *import(void *data);
  static bool restore(void *data);
};

} // namespace anm
