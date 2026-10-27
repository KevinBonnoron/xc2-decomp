#include "anm/anm_skeleton_importer.h"

#include "bin/bin_binary_resolver.h"

namespace anm {

bool SkeletonImporter::restore(void *data) { return bin::BinaryResolver::restore(data); }

} // namespace anm
