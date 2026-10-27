#include "anm/anm_asm_importer.h"

#include "bin/bin_binary_resolver.h"

namespace anm {

bool AsmImporter::restore(void *data) { return bin::BinaryResolver::restore(data); }

} // namespace anm
