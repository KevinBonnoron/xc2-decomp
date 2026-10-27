#include "anm/anm_animation_importer.h"

#include "bin/bin_binary_resolver.h"

namespace anm {

bool AnimationImporter::restore(void *data) { return bin::BinaryResolver::restore(data); }

} // namespace anm
