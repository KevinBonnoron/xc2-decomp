#include "mm_mtl/singleton.h" // IWYU pragma: keep

// The game has the class (vtable _ZTVN2tl8TitleAppE at 0x7101176d28, destructors at 0x7100142a9c to 0x7100142abc and their thunks) but it is not
// decompiled yet: the singleton destructors (0x7100142bd4 and 0x7100142bf4) do not need the complete type.
namespace tl {
class TitleApp; // IWYU pragma: keep
} // namespace tl

template mm::mtl::PtrSingleton<tl::TitleApp>::~PtrSingleton();
