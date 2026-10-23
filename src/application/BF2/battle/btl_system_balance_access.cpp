#include "battle/btl_system_balance_access.h"

#include "gf/gf_allocator.h"

namespace btl {

BtlSystemBalanceAccess::BtlSystemBalanceAccess() {}

BtlSystemBalanceAccess::~BtlSystemBalanceAccess() {}

void BtlSystemBalanceAccess::Create() {
  // __LINE__ must be 47 as in the original file: its value changes the instruction order.
#line 47
  BtlSystemBalanceAccess *balance = new (gf::getAllocator(gf::ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) BtlSystemBalanceAccess();
  balance->Initialize();
}

void BtlSystemBalanceAccess::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void BtlSystemBalanceAccess::Finalize() {}

bool BtlSystemBalanceAccess::IsOneBoundEnemy(u32 enemy) const {
  for (int i = 0; i < 2; i++) {
    if (unknownb6[i] == enemy) {
      return true;
    }
  }

  return false;
}

int BtlSystemBalanceAccess::IsSpSizeEnemy(u32 enemy) const {
  for (int i = 0; i < 1; i++) {
    if (unknownba[i] == enemy) {
      return i;
    }
  }

  return -1;
}

bool BtlSystemBalanceAccess::IsSpKizunaLineEnemy(u32 enemy) const {
  for (int i = 0; i < 2; i++) {
    if (unknownbc[i] == enemy) {
      return true;
    }
  }

  return false;
}

bool BtlSystemBalanceAccess::IsSpForceLandEnemy(u32 enemy) const {
  for (int i = 0; i < 2; i++) {
    if (unknownc0[i] == enemy) {
      return true;
    }
  }

  return false;
}

bool BtlSystemBalanceAccess::IsSpBenkeiWeapondEnemy(u32 enemy) const {
  for (int i = 0; i < 1; i++) {
    if (unknownc4[i] == enemy) {
      return true;
    }
  }

  return false;
}

} // namespace btl
