#include "ptlib/particle_hash.h"

#include "mm/mm_std_base.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/emitter/particle_emitter_manager.h"
#include "ptlib/particle_intrusive_list.h"
#include "ptlib/particle_math.h"
#include "ptlib/particle_system.h"

namespace ptlib {

namespace {
HashManager *s_hashInstance;
} // namespace

HashManager *HashManager::get() {
#line 19
  MM_ASSERT(getPtr());
  return getPtr();
}

HashManager *&HashManager::getPtr() { return s_hashInstance; }

bool HashManager::isValid() { return getPtr() != nullptr; }

void HashManager::init() {
#line 56
  s_hashInstance = static_cast<HashManager *>(ParticleManager::sysAlloc(sizeof(HashManager), 0x10, __FILE__, __LINE__));
  u32 key = math::fxMath_RandI() + 1;
  if (key == 0) {
    key++;
  }
  getPtr()->unknown17708 = key;
  getPtr()->reset();
}

void HashManager::term() {
  if (getPtr() != nullptr) {
    ParticleManager::sysFree(getPtr());
    getPtr() = nullptr;
  }
}

void HashManager::build(emitter::EmitterObj *emitter) {
  unknown001 *entry = unknown00;
  for (long remaining = TABLE_MAX; remaining != 0; remaining--) {
    entry->unknown00 = nullptr;
    entry->unknown08 = 0;
    entry++;
  }
  unknown17700 = 0;
  unknown17704 = 0;
  emitter::EmitterManager *manager = emitter::EmitterManager::get();
  IntrusiveList<emitter::EmitterObj> &activeList = manager->getEmitterActiveList();
  u32 previousHash = 0;
  for (IntrusiveList<emitter::EmitterObj>::iterator it = activeList.begin(); it != activeList.end(); ++it) {
    u32 hash = it->unknown264;
    if (hash != 0 && previousHash != hash && !it->unknown26c_4) {
      emitter::EmitterArg *arg = it->unknown98;
      add_core(hash, reinterpret_cast<const char *>(arg->unknown24c));
      previousHash = it->unknown264;
      if (arg != nullptr) {
        addDead(previousHash, arg->unknownfd);
      }
    }
  }
}

void HashManager::reset() {
  unknown001 *entry = unknown00;
  for (long remaining = TABLE_MAX; remaining != 0; remaining--) {
    entry->unknown00 = nullptr;
    entry->unknown08 = 0;
    entry++;
  }
  unknown17704 = 0;
}

void HashManager::add_core(u32 hash, const char *name) {
  unknown00[unknown17704].unknown08 = hash;
  unknown00[unknown17704].unknown00 = name;
  unknown17704++;
  unknown00[unknown17704].unknown08 = 0;
  unknown00[unknown17704].unknown00 = nullptr;
}

void HashManager::addDead(u32 hash, int value) {
  unknown002 &dead = unknownfa00[unknown17700];
  dead.unknown00 = hash;
  dead.unknown04 = value;
  unknown17700++;
}

void HashManager::add(u32 hash) {
  if (hash != 0) {
    add_core(hash, nullptr);
  }
}

u32 HashManager::check_core(u32 hash) {
  for (u32 i = 0; i < unknown17704; i++) {
    if (unknown00[i].unknown08 == hash) {
      return i;
    }
  }
  return 0;
}

bool HashManager::check(u32 hash) {
  if (hash != 0) {
    if (unknown00[check_core(hash)].unknown08 == hash) {
      return true;
    }
  }
  return false;
}

u32 HashManager::get_create_key() {
  u32 key = unknown17708;
  u32 next = key + 1;
  if (next == 0) {
    next++;
  }
  unknown17708 = next;
  if (key != 0) {
    add(key);
  }
  return key;
}

void HashManager::dump() {
  for (u32 i = 0; i < unknown17704; i++) {
    efMsg(" hash tbl %4d:%08x:%08x:%s", i, unknown00[i].unknown08, unknown00[i].unknown00);
  }
}

int HashManager::searchDead(u32 hash) {
  for (u32 i = 0; i < unknown17700; i++) {
    if (unknownfa00[i].unknown00 == hash) {
      return unknownfa00[i].unknown04;
    }
  }
  return -1;
}

} // namespace ptlib
