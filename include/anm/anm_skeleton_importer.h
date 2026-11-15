#pragma once

namespace anm {

class Skeleton;

class SkeletonImporter {
public:
  // Returns the Skeleton stored at +0x8 of the resolved binary; the game checks the SKEL magic first.
  static Skeleton *import(void *data);
  static bool restore(void *data);
};

} // namespace anm
