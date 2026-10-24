#pragma once
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"

namespace event {

class Extend : public mm::mtl::Singleton<Extend> {
public:
  const char *mdo(const char *name);
  const char *arc(const char *name);
  const char *anm(const char *name);
  const char *anm2eva(const char *name);
  const char *eva(const char *name);
  const char *effeva(const char *name);
  const char *efb(const char *name);
  const char *lgt(const char *name);
  const char *wav(const char *name);
  const char *acb(const char *name);
  const char *lip(const char *name);
  const char *xxlip(const char *name);
  const char *evpa(const char *name);
  const char *pack_efb(const char *name);
  const char *sar(const char *name);
  const char *webm(const char *name);
  const char *dirname(const char *path);
  const char *filename(const char *path);
  const char *replaceString(const char *string, const char *from, const char *to);

private:
  mm::mtl::FixStr<256> unknown08; // Inferred role: path; original member name unknown.
};

static_assert(sizeof(Extend) == 0x110, "");

} // namespace event
