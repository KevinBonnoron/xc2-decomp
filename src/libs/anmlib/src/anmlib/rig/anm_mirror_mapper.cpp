#include "anm/anm_mirror_mapper.h"

#include <string.h>

#include "anm/anm_skeleton.h"
#include "mm_math/mm_quat.h"

namespace anm {

void MirrorMapper::setBonePairTable(s16 *pBonePairTable) { memcpy(unknown20.m_buffer, pBonePairTable, unknown20.size() * sizeof(s16)); }

MirrorMapper::~MirrorMapper() { unknown001(unknown18); }

} // namespace anm
