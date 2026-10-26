#include "ml/fixed_size_alloc.h"

namespace gf {
struct AssetPackInfo;
struct GFOBJ_INFO;
struct GfSearchInfo;
namespace _gfdac {
struct ACCMEM;
} // namespace _gfdac
} // namespace gf

namespace ml {

template class fixed_size_alloc_inside<gf::AssetPackInfo, 1024>;
template class fixed_size_alloc_inside<gf::GFOBJ_INFO, 4096>;
template class fixed_size_alloc_inside<gf::GfSearchInfo, 1024>;
template class fixed_size_alloc_inside<gf::_gfdac::ACCMEM, 128>;
template class fixed_size_alloc_inside<unsigned int, 64>;

} // namespace ml
