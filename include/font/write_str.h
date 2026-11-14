#pragma once
#include <stddef.h>

#include "font/write_char.h"
#include "types.h"

class File;

// Layout evidence: WriteStr::WriteStr 0x710078fc10 (the constructor stores the limit width and the draw flags with one store at
// offset 0x34, inside the tail padding of WriteChar) and the accessors 0x7100790424..0x7100790444.
class WriteStr : public WriteChar {
public:
  WriteStr();
  ~WriteStr();
  void print(const char *string, bool draw);
  float calc_string_width(const char *string);
  float calc_string_width_to_new_line(File *file);
  float calc_string_height(const char *string);
  bool is_byte_code(const u8 *code);
  void set_limit_width(float width);
  float get_limit_width() const;
  void reset_limit_width();
  void set_draw_flag(u32 flag);
  u32 get_draw_flag() const;

private:
  float m_limit_width;
  u32 m_draw_flag;

  friend struct WriteStrLayout;
};

struct WriteStrLayout {
  static_assert(offsetof(WriteStr, m_limit_width) == 0x34, "");
  static_assert(offsetof(WriteStr, m_draw_flag) == 0x38, "");
  static_assert(sizeof(WriteStr) == 0x40, "");
};
