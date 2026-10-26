#include "ml/rom_mount.h"

namespace ml {

namespace {

// Inferred role: ROM mount mode flag; original name unknown.
bool unknown001;

} // namespace

void setRomMountMode(bool mode) { unknown001 = mode; }

bool isRomMountMode() { return unknown001; }

} // namespace ml
