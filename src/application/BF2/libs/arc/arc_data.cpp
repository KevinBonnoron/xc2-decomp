// No game string names this file: named after its header arc/arc_data.h. The game places arc::CArcData between the
// gmk objects and CsvReader/MediaClock, so it sits in application/BF2/libs next to movie/cmovie_nx.cpp
// (game string C:/Monolithsoft/BF2/prog/application/BF2/libs/movie/cmovie_nx.cpp).
#include "arc/arc_data.h"

#include "mm_mtl/vector.h" // IWYU pragma: keep

template void mm::mtl::Vector<arc::CArcData>::extend(size_t, size_t);
template void mm::mtl::Vector<arc::CArcData>::resize(size_t);
