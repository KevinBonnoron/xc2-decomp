#include "mm_mtl/internal/heap.h"

#include "mm/mm_std_base.h"
#include <string.h>

#define HEAP_INSIST(x)                                                                                                                                                                                 \
  {                                                                                                                                                                                                    \
    MM_ASSERT(x);                                                                                                                                                                                      \
    if (!(x)) {                                                                                                                                                                                        \
      status--;                                                                                                                                                                                        \
    }                                                                                                                                                                                                  \
  }

namespace mm {
namespace mtl {

namespace {

const size_t block_header_free_bit = 1 << 0;
const size_t block_header_prev_free_bit = 1 << 1;
const size_t block_header_overhead = sizeof(size_t);
const size_t block_start_offset = offsetof(HeapAllocUtil::block_header_t, size) + sizeof(size_t);
const size_t block_size_max = static_cast<size_t>(1) << HeapAllocUtil::FL_INDEX_MAX;

struct integrity_t {
  int prev_status;
  int status;
};

int heap_fls_generic(unsigned int word) {
  int bit = 32;
  if (!word) {
    bit -= 1;
  }
  if (!(word & 0xffff0000)) {
    word <<= 16;
    bit -= 16;
  }
  if (!(word & 0xff000000)) {
    word <<= 8;
    bit -= 8;
  }
  if (!(word & 0xf0000000)) {
    word <<= 4;
    bit -= 4;
  }
  if (!(word & 0xc0000000)) {
    word <<= 2;
    bit -= 2;
  }
  if (!(word & 0x80000000)) {
    word <<= 1;
    bit -= 1;
  }
  return bit;
}

int heap_ffs(unsigned int word) { return heap_fls_generic(word & (~word + 1)) - 1; }

int heap_fls(unsigned int word) { return heap_fls_generic(word) - 1; }

int heap_fls_sizet(size_t size) {
  int high = static_cast<int>(size >> 32);
  int bits = 0;
  if (high) {
    bits = 32 + heap_fls(high);
  } else {
    bits = heap_fls(static_cast<int>(size) & 0xffffffff);
  }
  return bits;
}

} // namespace

void HeapAllocUtil::buildChecker() {}

size_t HeapAllocUtil::block_size(const block_header_t *block) { return block->size & ~(block_header_free_bit | block_header_prev_free_bit); }

void HeapAllocUtil::block_set_size(block_header_t *block, size_t size) {
  const size_t oldsize = block->size;
  block->size = size | (oldsize & (block_header_free_bit | block_header_prev_free_bit));
}

bool HeapAllocUtil::block_is_last(const block_header_t *block) { return block_size(block) == 0; }

bool HeapAllocUtil::block_is_free(const block_header_t *block) { return block->size & block_header_free_bit; }

void HeapAllocUtil::block_set_free(block_header_t *block) { block->size |= block_header_free_bit; }

void HeapAllocUtil::block_set_used(block_header_t *block) { block->size &= ~block_header_free_bit; }

bool HeapAllocUtil::block_is_prev_free(const block_header_t *block) { return block->size & block_header_prev_free_bit; }

void HeapAllocUtil::block_set_prev_free(block_header_t *block) { block->size |= block_header_prev_free_bit; }

void HeapAllocUtil::block_set_prev_used(block_header_t *block) { block->size &= ~block_header_prev_free_bit; }

HeapAllocUtil::block_header_t *HeapAllocUtil::block_from_ptr(const void *ptr) {
  return reinterpret_cast<block_header_t *>(const_cast<unsigned char *>(static_cast<const unsigned char *>(ptr)) - block_start_offset);
}

void *HeapAllocUtil::block_to_ptr(const block_header_t *block) { return const_cast<unsigned char *>(reinterpret_cast<const unsigned char *>(block)) + block_start_offset; }

HeapAllocUtil::block_header_t *HeapAllocUtil::offset_to_block(const void *ptr, ptrdiff_t size) { return reinterpret_cast<block_header_t *>(reinterpret_cast<ptrdiff_t>(ptr) + size); }

HeapAllocUtil::block_header_t *HeapAllocUtil::block_prev(const block_header_t *block) { return block->prev_phys_block; }

HeapAllocUtil::block_header_t *HeapAllocUtil::block_next(const block_header_t *block) {
  block_header_t *next = offset_to_block(block_to_ptr(block), block_size(block) - block_header_overhead);
// The assert line of the game: it is the line argument of the assert.
#line 161
  MM_ASSERT(!block_is_last(block));
  return next;
}

HeapAllocUtil::block_header_t *HeapAllocUtil::block_link_next(block_header_t *block) {
  block_header_t *next = block_next(block);
  next->prev_phys_block = block;
  return next;
}

void HeapAllocUtil::block_mark_as_free(block_header_t *block) {
  block_header_t *next = block_link_next(block);
  block_set_prev_free(next);
  block_set_free(block);
}

void HeapAllocUtil::block_mark_as_used(block_header_t *block) {
  block_header_t *next = block_next(block);
  block_set_prev_used(next);
  block_set_used(block);
}

size_t HeapAllocUtil::align_up(size_t x, size_t align) {
// The assert line of the game: it is the line argument of the assert.
#line 188
  MM_ASSERT(0 == (align & (align - 1)) && "must align to a power of two");
  return (x + (align - 1)) & ~(align - 1);
}

size_t HeapAllocUtil::align_down(size_t x, size_t align) {
// The assert line of the game: it is the line argument of the assert.
#line 194
  MM_ASSERT(0 == (align & (align - 1)) && "must align to a power of two");
  return x - (x & (align - 1));
}

void *HeapAllocUtil::align_ptr(const void *ptr, size_t align) {
  const ptrdiff_t aligned = (reinterpret_cast<ptrdiff_t>(ptr) + (align - 1)) & ~(align - 1);
// The assert line of the game: it is the line argument of the assert.
#line 202
  MM_ASSERT(0 == (align & (align - 1)) && "must align to a power of two");
  return reinterpret_cast<void *>(aligned);
}

size_t HeapAllocUtil::adjust_request_size(size_t size, size_t align) {
  size_t adjust = 0;
  if (size && size < block_size_max) {
    const size_t aligned = align_up(size, align);
    adjust = aligned > heap_block_size_min() ? aligned : heap_block_size_min();
  }
  return adjust;
}

void HeapAllocUtil::mapping_insert(size_t size, int *fli, int *sli) {
  int fl, sl;
  if (size < SMALL_BLOCK_SIZE) {
    fl = 0;
    sl = static_cast<int>(size) / (SMALL_BLOCK_SIZE / SL_INDEX_COUNT);
  } else {
    fl = heap_fls_sizet(size);
    sl = static_cast<int>(size >> (fl - SL_INDEX_COUNT_LOG2)) ^ (1 << SL_INDEX_COUNT_LOG2);
    fl -= (FL_INDEX_SHIFT - 1);
  }
  *fli = fl;
  *sli = sl;
}

void HeapAllocUtil::mapping_search(size_t size, int *fli, int *sli) {
  if (size >= (1 << SL_INDEX_COUNT_LOG2)) {
    const size_t round = (1 << (heap_fls_sizet(size) - SL_INDEX_COUNT_LOG2)) - 1;
    size += round;
  }
  mapping_insert(size, fli, sli);
}

HeapAllocUtil::block_header_t *HeapAllocUtil::search_suitable_block(control_t *control, int *fli, int *sli) {
  int fl = *fli;
  int sl = *sli;
  unsigned int sl_map = control->sl_bitmap[fl] & (~0 << sl);
  if (!sl_map) {
    const unsigned int fl_map = control->fl_bitmap & (~0 << (fl + 1));
    if (!fl_map) {
      return nullptr;
    }
    fl = heap_ffs(fl_map);
    *fli = fl;
    sl_map = control->sl_bitmap[fl];
  }
// The assert line of the game: it is the line argument of the assert.
#line 263
  MM_ASSERT(sl_map && "internal error - second level bitmap is null");
  sl = heap_ffs(sl_map);
  *sli = sl;
  return control->blocks[fl][sl];
}

void HeapAllocUtil::remove_free_block(control_t *control, block_header_t *block, int fl, int sl) {
  block_header_t *prev = block->prev_free;
  block_header_t *next = block->next_free;
// The assert lines of the game: they are the line arguments of the asserts.
#line 274
  MM_ASSERT(prev && "prev_free field can not be null");
  MM_ASSERT(next && "next_free field can not be null");
  next->prev_free = prev;
  prev->next_free = next;
  if (control->blocks[fl][sl] == block) {
    control->blocks[fl][sl] = next;
    if (next == &control->block_null) {
      control->sl_bitmap[fl] &= ~(1 << sl);
      if (!control->sl_bitmap[fl]) {
        control->fl_bitmap &= ~(1 << fl);
      }
    }
  }
}

void HeapAllocUtil::insert_free_block(control_t *control, block_header_t *block, int fl, int sl) {
  block_header_t *current = control->blocks[fl][sl];
// The assert lines of the game: they are the line arguments of the asserts.
#line 298
  MM_ASSERT(current && "free list cannot have a null entry");
  MM_ASSERT(block && "cannot insert a null entry into the free list");
  block->next_free = current;
  block->prev_free = &control->block_null;
  current->prev_free = block;
// The assert line of the game: it is the line argument of the assert.
#line 305
  MM_ASSERT(block_to_ptr(block) == align_ptr(block_to_ptr(block), HeapAllocUtil::ALIGN_SIZE) && "block not aligned properly");
  control->blocks[fl][sl] = block;
  control->fl_bitmap |= (1 << fl);
  control->sl_bitmap[fl] |= (1 << sl);
}

void HeapAllocUtil::block_remove(control_t *control, block_header_t *block) {
  int fl, sl;
  mapping_insert(block_size(block), &fl, &sl);
  remove_free_block(control, block, fl, sl);
}

void HeapAllocUtil::block_insert(control_t *control, block_header_t *block) {
  int fl, sl;
  mapping_insert(block_size(block), &fl, &sl);
  insert_free_block(control, block, fl, sl);
}

bool HeapAllocUtil::block_can_split(block_header_t *block, size_t size) { return block_size(block) >= sizeof(block_header_t) + size; }

HeapAllocUtil::block_header_t *HeapAllocUtil::block_split(block_header_t *block, size_t size) {
  block_header_t *remaining = offset_to_block(block_to_ptr(block), size - block_header_overhead);
  const size_t remain_size = block_size(block) - (size + block_header_overhead);
// The assert lines of the game: they are the line arguments of the asserts.
#line 339
  MM_ASSERT(block_to_ptr(remaining) == align_ptr(block_to_ptr(remaining), HeapAllocUtil::ALIGN_SIZE) && "remaining block not aligned properly");
  MM_ASSERT(block_size(block) == remain_size + size + block_header_overhead);
  block_set_size(remaining, remain_size);
// The assert line of the game: it is the line argument of the assert.
#line 343
  MM_ASSERT(block_size(remaining) >= heap_block_size_min() && "block split with invalid size");
  block_set_size(block, size);
  block_mark_as_free(remaining);
  return remaining;
}

HeapAllocUtil::block_header_t *HeapAllocUtil::block_absorb(block_header_t *prev, block_header_t *block) {
// The assert line of the game: it is the line argument of the assert.
#line 353
  MM_ASSERT(!block_is_last(prev) && "previous block can't be last!");
  prev->size += block_size(block) + block_header_overhead;
  block_link_next(prev);
  return prev;
}

HeapAllocUtil::block_header_t *HeapAllocUtil::block_merge_prev(control_t *control, block_header_t *block) {
  if (block_is_prev_free(block)) {
    block_header_t *prev = block_prev(block);
// The assert lines of the game: they are the line arguments of the asserts.
#line 365
    MM_ASSERT(prev && "prev physical block can't be null");
    MM_ASSERT(block_is_free(prev) && "prev block is not free though marked as such");
    block_remove(control, prev);
    block = block_absorb(prev, block);
  }
  return block;
}

HeapAllocUtil::block_header_t *HeapAllocUtil::block_merge_next(control_t *control, block_header_t *block) {
  block_header_t *next = block_next(block);
// The assert line of the game: it is the line argument of the assert.
#line 377
  MM_ASSERT(next && "next physical block can't be null");
  if (block_is_free(next)) {
// The assert line of the game: it is the line argument of the assert.
#line 381
    MM_ASSERT(!block_is_last(block) && "previous block can't be last!");
    block_remove(control, next);
    block = block_absorb(block, next);
  }
  return block;
}

void HeapAllocUtil::block_trim_free(control_t *control, block_header_t *block, size_t size) {
// The assert line of the game: it is the line argument of the assert.
#line 391
  MM_ASSERT(block_is_free(block) && "block must be free");
  if (block_can_split(block, size)) {
    block_header_t *remaining_block = block_split(block, size);
    block_link_next(block);
    block_set_prev_free(remaining_block);
    block_insert(control, remaining_block);
  }
}

void HeapAllocUtil::block_trim_used(control_t *control, block_header_t *block, size_t size) {
// The assert line of the game: it is the line argument of the assert.
#line 403
  MM_ASSERT(!block_is_free(block) && "block must be used");
  if (block_can_split(block, size)) {
    block_header_t *remaining_block = block_split(block, size);
    block_set_prev_used(remaining_block);
    remaining_block = block_merge_next(control, remaining_block);
    block_insert(control, remaining_block);
  }
}

HeapAllocUtil::block_header_t *HeapAllocUtil::block_trim_free_leading(control_t *control, block_header_t *block, size_t size) {
  block_header_t *remaining_block = block;
  if (block_can_split(block, size)) {
    remaining_block = block_split(block, size - block_header_overhead);
    block_set_prev_free(remaining_block);
    block_link_next(block);
    block_insert(control, block);
  }
  return remaining_block;
}

HeapAllocUtil::block_header_t *HeapAllocUtil::block_locate_free(control_t *control, size_t size) {
  int fl = 0, sl = 0;
  block_header_t *block = nullptr;
  if (size) {
    mapping_search(size, &fl, &sl);
    block = search_suitable_block(control, &fl, &sl);
  }
  if (block) {
// The assert line of the game: it is the line argument of the assert.
#line 442
    MM_ASSERT(block_size(block) >= size);
    remove_free_block(control, block, fl, sl);
  }
  return block;
}

void *HeapAllocUtil::block_prepare_used(control_t *control, block_header_t *block, size_t size) {
  void *p = nullptr;
  if (block) {
    block_trim_free(control, block, size);
    block_mark_as_used(block);
    p = block_to_ptr(block);
  }
  return p;
}

void HeapAllocUtil::control_construct(control_t *control) {
  int i, j;
  control->block_null.next_free = &control->block_null;
  control->block_null.prev_free = &control->block_null;
  control->fl_bitmap = 0;
  for (i = 0; i < FL_INDEX_COUNT; ++i) {
    control->sl_bitmap[i] = 0;
    for (j = 0; j < SL_INDEX_COUNT; ++j) {
      control->blocks[i][j] = &control->block_null;
    }
  }
}

void HeapAllocUtil::integrity_walker(void *ptr, size_t size, bool used, void *user, size_t index) {
  block_header_t *block = block_from_ptr(ptr);
  integrity_t *integ = static_cast<integrity_t *>(user);
  const int this_prev_status = block_is_prev_free(block) ? 1 : 0;
  const int this_status = block_is_free(block) ? 1 : 0;
  const size_t this_block_size = block_size(block);
  int status = 0;
// The assert lines of the game: they are the line arguments of the asserts.
#line 499
  HEAP_INSIST(integ->prev_status == this_prev_status && "prev status incorrect");
  HEAP_INSIST(size == this_block_size && "block size incorrect");
  integ->prev_status = this_status;
  integ->status += status;
}

int HeapAllocUtil::heap_check(void *heap) {
  int i, j;
  control_t *control = static_cast<control_t *>(heap);
  int status = 0;
  for (i = 0; i < FL_INDEX_COUNT; ++i) {
    for (j = 0; j < SL_INDEX_COUNT; ++j) {
      const int fl_map = control->fl_bitmap & (1 << i);
      const int sl_list = control->sl_bitmap[i];
      const int sl_map = sl_list & (1 << j);
      const block_header_t *block = control->blocks[i][j];
      if (!fl_map) {
// The assert line of the game: it is the line argument of the assert.
#line 525
        HEAP_INSIST(!sl_map && "second-level map must be null");
      }
      if (!sl_map) {
// The assert line of the game: it is the line argument of the assert.
#line 530
        HEAP_INSIST(block == &control->block_null && "block list must be null");
        continue;
      }
// The assert lines of the game: they are the line arguments of the asserts.
#line 534
      HEAP_INSIST(sl_list && "no free blocks in second-level map");
      HEAP_INSIST(block != &control->block_null && "block should not be null");
      while (block != &control->block_null) {
        int fli, sli;
// The assert lines of the game: they are the line arguments of the asserts.
#line 540
        HEAP_INSIST(block_is_free(block) && "block should be free");
        HEAP_INSIST(!block_is_prev_free(block) && "blocks should have coalesced");
        HEAP_INSIST(!block_is_free(block_next(block)) && "blocks should have coalesced");
        HEAP_INSIST(block_is_prev_free(block_next(block)) && "block should be free");
        HEAP_INSIST(block_size(block) >= heap_block_size_min() && "block not minimum size");
        mapping_insert(block_size(block), &fli, &sli);
// The assert line of the game: it is the line argument of the assert.
#line 547
        HEAP_INSIST(fli == i && sli == j && "block size indexed in wrong list");
        block = block->next_free;
      }
    }
  }
  return status;
}

void HeapAllocUtil::default_walker(void *ptr, size_t size, bool used, void *user, size_t index) {
  MMStdBase::mmPrint("\tblk:%d %p %s size: %x (%p)\n", index, ptr, used ? "used" : "free", static_cast<unsigned int>(size), block_from_ptr(ptr));
}

size_t HeapAllocUtil::heap_walk_pool(void *pool, heap_walker walker, void *user) {
  heap_walker pool_walker = walker ? walker : default_walker;
  block_header_t *block = offset_to_block(pool, -static_cast<int>(block_header_overhead));
  size_t index = 0;
  while (block && !block_is_last(block)) {
    pool_walker(block_to_ptr(block), block_size(block), !block_is_free(block), user, index);
    block = block_next(block);
    index++;
  }
  return index;
}

size_t HeapAllocUtil::heap_block_size(const void *ptr) {
  size_t size = 0;
  if (ptr) {
    const block_header_t *block = block_from_ptr(ptr);
    size = block_size(block);
  }
  return size;
}

int HeapAllocUtil::heap_check_pool(void *pool) {
  integrity_t integ = {0, 0};
  heap_walk_pool(pool, integrity_walker, &integ);
  return integ.status;
}

size_t HeapAllocUtil::heap_size() { return sizeof(control_t); }

size_t HeapAllocUtil::heap_align_size() { return ALIGN_SIZE; }

size_t HeapAllocUtil::heap_block_size_min() { return sizeof(block_header_t) - sizeof(block_header_t *); }

size_t HeapAllocUtil::heap_block_size_max() { return block_size_max; }

size_t HeapAllocUtil::heap_pool_overhead() { return 2 * block_header_overhead; }

size_t HeapAllocUtil::heap_alloc_overhead() { return block_header_overhead; }

size_t HeapAllocUtil::heap_alloc_max() { return FL_INDEX_COUNT * SL_INDEX_COUNT; }

void *HeapAllocUtil::heap_add_pool(void *heap, void *mem, size_t bytes) {
  block_header_t *block;
  block_header_t *next;
  const size_t pool_overhead = heap_pool_overhead();
  const size_t pool_bytes = align_down(bytes - pool_overhead, ALIGN_SIZE);
  if ((reinterpret_cast<ptrdiff_t>(mem) % ALIGN_SIZE) != 0) {
    MMStdBase::mmPrint("heap_add_pool: Memory must be aligned by %u bytes.\n", static_cast<unsigned int>(ALIGN_SIZE));
    return nullptr;
  }
  if (pool_bytes < heap_block_size_min() || pool_bytes > block_size_max) {
    MMStdBase::mmPrint("heap_add_pool: Memory size must be between 0x%x and 0x%x00 bytes.\n",
                       static_cast<unsigned int>(pool_overhead + heap_block_size_min()),
                       static_cast<unsigned int>((pool_overhead + block_size_max) / 256));
    return nullptr;
  }
  block = offset_to_block(mem, -static_cast<ptrdiff_t>(block_header_overhead));
  block_set_size(block, pool_bytes);
  block_set_free(block);
  block_set_prev_used(block);
  block_insert(static_cast<control_t *>(heap), block);
  next = block_link_next(block);
  block_set_size(next, 0);
  block_set_used(next);
  block_set_prev_free(next);
  return mem;
}

void HeapAllocUtil::heap_remove_pool(void *heap, void *pool) {
  control_t *control = static_cast<control_t *>(heap);
  block_header_t *block = offset_to_block(pool, -static_cast<int>(block_header_overhead));
  int fl = 0, sl = 0;
// The assert lines of the game: they are the line arguments of the asserts.
#line 692
  MM_ASSERT(block_is_free(block) && "block should be free");
  MM_ASSERT(!block_is_free(block_next(block)) && "next block should not be free");
  MM_ASSERT(block_size(block_next(block)) == 0 && "next block size should be zero");
  mapping_insert(block_size(block), &fl, &sl);
  remove_free_block(control, block, fl, sl);
}

void *HeapAllocUtil::heap_create(void *mem) {
  if ((reinterpret_cast<ptrdiff_t>(mem) % ALIGN_SIZE) != 0) {
    MMStdBase::mmPrint("heap_create: Memory must be aligned to %u bytes.\n", static_cast<unsigned int>(ALIGN_SIZE));
    return nullptr;
  }
  control_construct(static_cast<control_t *>(mem));
  return mem;
}

void HeapAllocUtil::heap_destroy(void *heap) {}

void *HeapAllocUtil::heap_malloc(void *heap, size_t size) {
  control_t *control = static_cast<control_t *>(heap);
  const size_t adjust = adjust_request_size(size, ALIGN_SIZE);
  block_header_t *block = block_locate_free(control, adjust);
  return block_prepare_used(control, block, adjust);
}

void *HeapAllocUtil::heap_memalign(void *heap, size_t align, size_t size) {
  control_t *control = static_cast<control_t *>(heap);
  const size_t adjust = adjust_request_size(size, ALIGN_SIZE);
  const size_t gap_minimum = sizeof(block_header_t);
  const size_t size_with_gap = adjust_request_size(adjust + align + gap_minimum, align);
  const size_t aligned_size = (align <= ALIGN_SIZE) ? adjust : size_with_gap;
  block_header_t *block = block_locate_free(control, aligned_size);
  MM_ASSERT(sizeof(block_header_t) == heap_block_size_min() + block_header_overhead);
  if (block) {
    void *ptr = block_to_ptr(block);
    void *aligned = align_ptr(ptr, align);
    size_t gap = static_cast<size_t>(reinterpret_cast<ptrdiff_t>(aligned) - reinterpret_cast<ptrdiff_t>(ptr));
    if (gap && gap < gap_minimum) {
      const size_t gap_remain = gap_minimum - gap;
      const size_t offset = gap_remain > align ? gap_remain : align;
      const void *next_aligned = reinterpret_cast<void *>(reinterpret_cast<ptrdiff_t>(aligned) + offset);
      aligned = align_ptr(next_aligned, align);
      gap = static_cast<size_t>(reinterpret_cast<ptrdiff_t>(aligned) - reinterpret_cast<ptrdiff_t>(ptr));
    }
    if (gap) {
// The assert line of the game: it is the line argument of the assert.
#line 802
      MM_ASSERT(gap >= gap_minimum && "gap size too small");
      block = block_trim_free_leading(control, block, gap);
    }
  }
  return block_prepare_used(control, block, adjust);
}

void HeapAllocUtil::heap_free(void *heap, void *ptr) {
  if (ptr) {
    control_t *control = static_cast<control_t *>(heap);
    block_header_t *block = block_from_ptr(ptr);
// The assert line of the game: it is the line argument of the assert.
#line 817
    MM_ASSERT(!block_is_free(block) && "block already marked as free");
    block_mark_as_free(block);
    block = block_merge_prev(control, block);
    block = block_merge_next(control, block);
    block_insert(control, block);
  }
}

void *HeapAllocUtil::heap_realloc(void *heap, void *ptr, size_t size) {
  control_t *control = static_cast<control_t *>(heap);
  void *p = nullptr;
  if (ptr && size == 0) {
    heap_free(heap, ptr);
  } else if (!ptr) {
    p = heap_malloc(heap, size);
  } else {
    block_header_t *block = block_from_ptr(ptr);
    block_header_t *next = block_next(block);
    const size_t cursize = block_size(block);
    const size_t combined = cursize + block_size(next) + block_header_overhead;
    const size_t adjust = adjust_request_size(size, ALIGN_SIZE);
// The assert line of the game: it is the line argument of the assert.
#line 848
    MM_ASSERT(!block_is_free(block) && "block already marked as free");
    if (adjust > cursize && (!block_is_free(next) || adjust > combined)) {
      p = heap_malloc(heap, size);
      if (p) {
        const size_t minsize = cursize < size ? cursize : size;
        memcpy(p, ptr, minsize);
        heap_free(heap, ptr);
      }
    } else {
      if (adjust > cursize) {
        block_merge_next(control, block);
        block_mark_as_used(block);
      }
      block_trim_used(control, block, adjust);
      p = ptr;
    }
  }
  return p;
}

bool HeapAllocUtil::valid_ptr(void *pool, const void *ptr) {
  for (block_header_t *block = offset_to_block(pool, -static_cast<int>(block_header_overhead)); block && !block_is_last(block); block = block_next(block)) {
    if (block_to_ptr(block) == ptr) {
      return !block_is_free(block);
    }
  }
  return false;
}

} // namespace mtl
} // namespace mm
