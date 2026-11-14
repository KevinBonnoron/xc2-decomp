#pragma once
#include <stddef.h>

#include "ml/ini_parser.h"
#include "mm_mtl/singleton.h"

// Boot options read from the boot ini file. The game keeps one instance in the local static of
// mm::mtl::Singleton<BootOption>::getPtr (_ZZN2mm3mtl9SingletonI10BootOptionE6getPtrEvE10s_instance, 0x9610 bytes) and
// passes it, at offset 8, to ml::IniParser::parse and ml::IniParser::getKeyValue (_ZTV10BootOption, 0x20 bytes: the
// two destructors).
class BootOption : public mm::mtl::Singleton<BootOption> {
public:
  virtual ~BootOption() {}

  ml::IniParser unknown08; // Inferred role: parsed boot ini file; original member name unknown.
};

static_assert(offsetof(BootOption, unknown08) == 0x8, "");
static_assert(sizeof(BootOption) == 0x9610, "");
