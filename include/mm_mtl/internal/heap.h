#pragma once
#include <stddef.h>

namespace mm {
namespace mtl {

class HeapAllocUtil {
public:
  enum {
    SL_INDEX_COUNT_LOG2 = 5,
    ALIGN_SIZE_LOG2 = 3,
    ALIGN_SIZE = 1 << ALIGN_SIZE_LOG2,
    FL_INDEX_MAX = 32,
    SL_INDEX_COUNT = 1 << SL_INDEX_COUNT_LOG2,
    FL_INDEX_SHIFT = SL_INDEX_COUNT_LOG2 + ALIGN_SIZE_LOG2,
    FL_INDEX_COUNT = FL_INDEX_MAX - FL_INDEX_SHIFT + 1,
    SMALL_BLOCK_SIZE = 1 << FL_INDEX_SHIFT,
  };

  struct block_header_t {
    block_header_t *prev_phys_block;
    size_t size;
    block_header_t *next_free;
    block_header_t *prev_free;
  };

  struct control_t {
    block_header_t block_null;
    unsigned int fl_bitmap;
    unsigned int sl_bitmap[FL_INDEX_COUNT];
    block_header_t *blocks[FL_INDEX_COUNT][SL_INDEX_COUNT];
  };

  typedef void (*heap_walker)(void *ptr, size_t size, bool used, void *user, size_t index);

  static void buildChecker();
  static size_t block_size(const block_header_t *block);
  static void block_set_size(block_header_t *block, size_t size);
  static bool block_is_last(const block_header_t *block);
  static bool block_is_free(const block_header_t *block);
  static void block_set_free(block_header_t *block);
  static void block_set_used(block_header_t *block);
  static bool block_is_prev_free(const block_header_t *block);
  static void block_set_prev_free(block_header_t *block);
  static void block_set_prev_used(block_header_t *block);
  static block_header_t *block_from_ptr(const void *ptr);
  static void *block_to_ptr(const block_header_t *block);
  static block_header_t *offset_to_block(const void *ptr, ptrdiff_t size);
  static block_header_t *block_prev(const block_header_t *block);
  static block_header_t *block_next(const block_header_t *block);
  static block_header_t *block_link_next(block_header_t *block);
  static void block_mark_as_free(block_header_t *block);
  static void block_mark_as_used(block_header_t *block);
  static size_t align_up(size_t x, size_t align);
  static size_t align_down(size_t x, size_t align);
  static void *align_ptr(const void *ptr, size_t align);
  static size_t adjust_request_size(size_t size, size_t align);
  static size_t heap_block_size_min();
  static void mapping_insert(size_t size, int *fli, int *sli);
  static void mapping_search(size_t size, int *fli, int *sli);
  static block_header_t *search_suitable_block(control_t *control, int *fli, int *sli);
  static void remove_free_block(control_t *control, block_header_t *block, int fl, int sl);
  static void insert_free_block(control_t *control, block_header_t *block, int fl, int sl);
  static void block_remove(control_t *control, block_header_t *block);
  static void block_insert(control_t *control, block_header_t *block);
  static bool block_can_split(block_header_t *block, size_t size);
  static block_header_t *block_split(block_header_t *block, size_t size);
  static block_header_t *block_absorb(block_header_t *prev, block_header_t *block);
  static block_header_t *block_merge_prev(control_t *control, block_header_t *block);
  static block_header_t *block_merge_next(control_t *control, block_header_t *block);
  static void block_trim_free(control_t *control, block_header_t *block, size_t size);
  static void block_trim_used(control_t *control, block_header_t *block, size_t size);
  static block_header_t *block_trim_free_leading(control_t *control, block_header_t *block, size_t size);
  static block_header_t *block_locate_free(control_t *control, size_t size);
  static void *block_prepare_used(control_t *control, block_header_t *block, size_t size);
  static void control_construct(control_t *control);
  static void integrity_walker(void *ptr, size_t size, bool used, void *user, size_t index);
  static int heap_check(void *heap);
  static void default_walker(void *ptr, size_t size, bool used, void *user, size_t index);
  static size_t heap_walk_pool(void *pool, heap_walker walker, void *user);
  static size_t heap_block_size(const void *ptr);
  static int heap_check_pool(void *pool);
  static size_t heap_size();
  static size_t heap_align_size();
  static size_t heap_block_size_max();
  static size_t heap_pool_overhead();
  static size_t heap_alloc_overhead();
  static size_t heap_alloc_max();
  static void *heap_add_pool(void *heap, void *mem, size_t bytes);
  static void heap_remove_pool(void *heap, void *pool);
  static void *heap_create(void *mem);
  static void heap_destroy(void *heap);
  static void *heap_malloc(void *heap, size_t size);
  static void *heap_memalign(void *heap, size_t align, size_t size);
  static void heap_free(void *heap, void *ptr);
  static void *heap_realloc(void *heap, void *ptr, size_t size);
  static bool valid_ptr(void *pool, const void *ptr);
};

} // namespace mtl
} // namespace mm
