#pragma once

namespace anm {

struct ResStateArray;

class AsmImporter {
public:
  // Returns the ResStateArray stored at +0x8 of the resolved binary after the ASMB magic check. It is the first argument of
  // Factory::createASMResource, and ResASM::ResASM stores it at +0x20; the ResASM is the output of createASMResource.
  static ResStateArray *import(void *data);
  static bool restore(void *data);
};

} // namespace anm
