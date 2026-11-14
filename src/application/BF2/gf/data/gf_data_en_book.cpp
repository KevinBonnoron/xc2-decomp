#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_EN_BOOK_UNKNOWN_1892 = 0x764,   // Inferred role: flag en book attack order; original name unknown.
  FLAG_EN_BOOK_UNKNOWN_2892 = 0xb4c,   // Inferred role: flag en book attack order end; original name unknown.
  FLAG_EN_BOOK_UNKNOWN_48590 = 0xbdce, // Inferred role: flag en book attack; original name unknown.
  FLAG_EN_BOOK_UNKNOWN_322 = 0x142,    // Inferred role: flag en book defeat num; original name unknown.
  FLAG_EN_BOOK_UNKNOWN_1323 = 0x52b,   // Inferred role: flag en book dead num; original name unknown.
  FLAG_EN_BOOK_UNKNOWN_2324 = 0x914,   // Inferred role: flag en book clear named time; original name unknown.
};

constexpr u32 COUNTER_UNKNOWN_4294967295 = 0xffffffff; // Inferred role: counter max; original name unknown.

u32 GfDataEnBook::getEnBoolId(u32 enemy) {
  if (enemy == 0) {
    return 0;
  }

  return GfBdatChrEnArrange::get()->getChrEnArrangeBookID(enemy);
}

bool GfDataEnBook::isBook(u32 enemy) { return getEnBoolId(enemy) != 0; }

bool GfDataEnBook::isNamed(u32 enemy) {
  if (GfBdatChrEnArrange::get() == nullptr) {
    return false;
  }

  return GfBdatChrEnArrange::get()->isChrEnArrangeFlagNamed(enemy);
}

bool GfDataEnBook::isAttackFlag(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return false;
  }

  return GfGameFlag::getLocal(1, FLAG_EN_BOOK_UNKNOWN_48590 + book) != 0;
}

void GfDataEnBook::setAttackFlag(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0 || GfGameFlag::getLocal(1, FLAG_EN_BOOK_UNKNOWN_48590 + book) != 0) {
    return;
  }

  GfGameFlag::setLocal(1, FLAG_EN_BOOK_UNKNOWN_48590 + book, 1);
  for (u32 flag = FLAG_EN_BOOK_UNKNOWN_1892; flag < FLAG_EN_BOOK_UNKNOWN_2892; flag++) {
    if (GfGameFlag::getLocal(16, flag) == 0) {
      GfGameFlag::setLocal(16, flag, static_cast<u16>(enemy));
      return;
    }
  }
}

u32 GfDataEnBook::getDefeatNum(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfGameFlag::getLocal(32, FLAG_EN_BOOK_UNKNOWN_322 + book);
}

void GfDataEnBook::incDefeatNum(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return;
  }

  u32 defeatNum = GfGameFlag::getLocal(32, FLAG_EN_BOOK_UNKNOWN_322 + book);
  if (defeatNum != COUNTER_UNKNOWN_4294967295) {
    GfGameFlag::setLocal(32, FLAG_EN_BOOK_UNKNOWN_322 + book, defeatNum + 1);
  }
}

u32 GfDataEnBook::getDeadNum(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfGameFlag::getLocal(32, FLAG_EN_BOOK_UNKNOWN_1323 + book);
}

void GfDataEnBook::incDeadNum(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return;
  }

  u32 deadNum = GfGameFlag::getLocal(32, FLAG_EN_BOOK_UNKNOWN_1323 + book);
  if (deadNum != COUNTER_UNKNOWN_4294967295) {
    GfGameFlag::setLocal(32, FLAG_EN_BOOK_UNKNOWN_1323 + book, deadNum + 1);
  }
}

u32 GfDataEnBook::getClearNamedTime(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfGameFlag::getLocal(32, FLAG_EN_BOOK_UNKNOWN_2324 + book);
}

void GfDataEnBook::setClearNamedTime(u32 enemy, u32 clearNamedTime) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return;
  }

  if (GfGameFlag::getLocal(32, FLAG_EN_BOOK_UNKNOWN_2324 + book) == 0) {
    GfGameFlag::setLocal(32, FLAG_EN_BOOK_UNKNOWN_2324 + book, clearNamedTime);
  }
}

u32 GfDataEnBook::getBaseEnemy(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfBdatChrEnArrange::get()->getBTL_EnBookBaseEnemyID(book);
}

u32 GfDataEnBook::getPopTime(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfBdatChrEnArrange::get()->getBTL_EnBookBOOK_POP_TIME(book);
}

u32 GfDataEnBook::getPopWeather(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfBdatChrEnArrange::get()->getBTL_EnBookBOOK_popWeather(book);
}

} // namespace gf
