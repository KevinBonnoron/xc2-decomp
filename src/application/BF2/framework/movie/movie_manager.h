#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "ml/work_background.h"
#include "mm_mtl/singleton.h"
#include "types.h"

class ICMovie;

namespace fw {

class MovieManager : public ManagerObject, public mm::mtl::PtrSingleton<MovieManager>, public ml::IWorkBackground {
public:
  ~MovieManager();
  void stop();
  bool set_file(const char *path);
  f32 get_length();
  f32 pos();
  void play();
  void pause();
  bool isstandby();
  bool ispause();
  bool isplaying();
  void bkgHomeMenu(bool isEnter) override;

  u8 _20[0x30 - 0x20];
  ICMovie *movie;
  bool isPlaying;
};

static_assert(offsetof(MovieManager, movie) == 0x30, "");
static_assert(offsetof(MovieManager, isPlaying) == 0x38, "");

} // namespace fw
