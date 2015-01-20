/*
 * This is a fast and ghetto method for a length-2
 * circular buffer of blocks.
 *
 * This can be used in a situation where one block is being output
 * (transmitted, displayed, etc...) and the other is being prepared,
 * where only one block can be output at a time
 *
 * It works by getting a chunk of memory (reserved by linker in this case)
 * that is 2*block_size and aligned to 2*block_size. Then getting the "next
 * block" is simply a matter of xor-ing the current block with a mask!
 */

#include <stdint.h>

/*
 * XXX lol u thought u could change this and affect anything?
 * Until this is dynamically allocated, don't forget to
 * ---also change the alignment in linker script to 2*BUDDY_SIZE ---
 */
#define BUDDY_BITS 10	/* 1K */
#define BUDDY_SIZE (1<<(BUDDY_BITS))

/*
 * This is wrapped in a struct to keep you from fucking with it
 * without the API
 */
struct bbuf {
	char *addr;
};

static inline char *curr_block(struct bbuf *b)
{
	return b->addr;
}

/* This is why this is clever, the address of the next buffer is just 1 xor away */
static inline char *next_block(struct bbuf *b)
{
	return (char *)( ((uintptr_t)b->addr) ^ BUDDY_SIZE);
}

static inline char *swap_bbuf(struct bbuf *b)
{
	b->addr = next_block(b);
	return b->addr;
}

/*
 * If we had posix_memalign, we could dynamically allocate the blocks here,
 * but instead we just carve out some memory for each buffer in the linker.
 *
 * XXX TODO FIXME HACK ALERT! Can't make more than 2 bbufs!
 */
extern const char *i_block;
extern const char *q_block;

static inline void init_iq_bbuf(struct bbuf *b1, struct bbuf *b2)
{
	b1->addr = (char *)i_block;
	b2->addr = (char *)q_block;
	return;
}
