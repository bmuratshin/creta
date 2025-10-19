#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <algorithm>
#include "mempool.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifdef __ALLOC
#undef __ALLOC
#endif
#ifdef __FREE
#undef __FREE
#endif

#define _RNDUP(SZ,AL)    ((((SZ) + AL - 1) / AL) * AL)
#define ALIGN_4(x)    _RNDUP((x), 4)
#define ALIGN_8(x)    _RNDUP((x), 8)

static void *test_calloc(size_t count, size_t sz)
{
	static int cnt = 1;
	if (0 == (cnt++ % 10000))
		return NULL;
	return calloc(count, sz);
}

#define __ALLOC(a) (/*test_*/calloc(a,1))
#define __FREE(a, b) (free (a))


	int max_sz = 0;
	mem_pool_t::mem_pool_t()
	{
		mp_first = NULL;
		total_bytes_ = 0;
		lastLen = 0;
		usdef_ = 0;
	}

	mem_pool_t::~mem_pool_t()
	{
		reset();
	}

	mem_pool_t::mem_pool_t(mem_pool_t&& that) {
		mp_first = that.mp_first;
		that.mp_first = nullptr;

		total_bytes_ = that.total_bytes_;
		that.total_bytes_ = 0;

		lastLen = that.lastLen;
		that.lastLen = 0;

		usdef_ = that.usdef_;
		that.usdef_ = 0;
	}

	mem_pool_t& mem_pool_t::operator=(mem_pool_t&& that) {
		std::swap(mp_first, that.mp_first);
		std::swap(total_bytes_, that.total_bytes_);
		std::swap(lastLen, that.lastLen);
		std::swap(usdef_, that.usdef_);
		return *this;
	}

	int
		mem_pool_t::reset()
	{
		mem_block_t * mb = mp_first, *next;
		while (mb)
		{
			next = mb->mb_next;
			__FREE((char*)mb, mb->mb_size);
			mb = next;
		}
		mp_first = NULL;
		total_bytes_ = 0;
		usdef_ = 0;
		return 0;
	}


	void *
		mem_pool_t::alloc__(size_t len1, unsigned char type)
	{
		unsigned char  *ptr;
		size_t len = ALIGN_8(len1 + 8);
		mem_block_t * mb = NULL;
		mem_block_t * f = mp_first;
		size_t hlen = ALIGN_8((sizeof(mem_block_t))); /* we can have a doubles so structure also must be aligned */
		if (!f || (f->mb_size - f->mb_fill) < (len + 4))
		{
			if (len > mp_block_size - hlen)
			{
				mb = (mem_block_t *)__ALLOC(hlen + len);//-V641
				if (NULL == mb)
				{
					throw ("NO MEM");
					return NULL;
				}
				mb->mb_size = (uint32_t)(len + hlen);
				mb->mb_fill = (uint32_t)hlen;
				if (f)
				{
					mb->mb_next = f->mb_next;
					f->mb_next = mb;
				}
				else
				{
					mb->mb_next = NULL;
					mp_first = mb;
				}
			}
			else
			{
				mb = (mem_block_t *)__ALLOC(mp_block_size);
				if (NULL == mb)
				{
					throw ("NO MEM");
					return NULL;
				}
				mb->mb_size = (uint32_t)mp_block_size;
				mb->mb_fill = (uint32_t)hlen;
				mb->mb_next = mp_first;
				mp_first = mb;
			}
		}
		else
			mb = f;
		ptr = ((unsigned char*)mb) + mb->mb_fill + 4;
		mb->mb_fill += (uint32_t)len;
		(ptr++)[0] = (unsigned char)(len1 & 0xff);
		(ptr++)[0] = (unsigned char)((len1 >> 8) & 0xff);
		(ptr++)[0] = (unsigned char)((len1 >> 16) & 0xff);
		(ptr++)[0] = type;
		memset(ptr, 0, len1);
		total_bytes_ += len1;
		return ((char*)ptr);
	}

	void *
		mem_pool_t::alloc(size_t len1)
	{
		unsigned char  *ptr;
		size_t len = ALIGN_8(len1);
		mem_block_t * mb = NULL;
		mem_block_t * f = mp_first;
		size_t hlen = ALIGN_8((sizeof(mem_block_t))); /* we can have a doubles so structure also must be aligned */
		if (!f || (f->mb_size - f->mb_fill) < len)
		{
			if (len > mp_block_size - hlen)
			{
				mb = (mem_block_t *)__ALLOC(hlen + len);//-V641
				if (NULL == mb)
				{
					throw ("NO MEM");
					return NULL;
				}
				mb->mb_size = (uint32_t)(len + hlen);
				mb->mb_fill = (uint32_t)hlen;
				if (f)
				{
					mb->mb_next = f->mb_next;
					f->mb_next = mb;
				}
				else
				{
					mb->mb_next = NULL;
					mp_first = mb;
				}
			}
			else
			{
				mb = (mem_block_t *)__ALLOC(mp_block_size);
				if (NULL == mb)
				{
					throw ("pmOutOfMem");
					return NULL;
				}
				mb->mb_size = (uint32_t)mp_block_size;
				mb->mb_fill = (uint32_t)hlen;
				mb->mb_next = mp_first;
				mp_first = mb;
			}
		}
		else
			mb = f;
		ptr = ((unsigned char*)mb) + mb->mb_fill;
		mb->mb_fill += (uint32_t)len;
		lastLen = len;
		memset(ptr, 0, len1);
		total_bytes_ += len;
		return ((char*)ptr);
	}

	void
		mem_pool_t::undoLastAlloc() {
		assert(mp_first);
		mp_first->mb_fill -= (uint32_t)lastLen;
		total_bytes_ -= lastLen;
		lastLen = 0;
	}

	void
		mem_pool_t::swap(mem_pool_t &other)
	{
		char *buf = (char*)alloca(ALIGN_8(sizeof(mem_pool_t)));
		memcpy(buf, this, sizeof(mem_pool_t));
		memcpy(this, &other, sizeof(mem_pool_t));
		memcpy(&other, buf, sizeof(mem_pool_t));
	}

	char *mem_pool_t::strdup_(char *s)
	{
		size_t len = strlen(s);
		char *ret = (char*)alloc(len + 1);
		memcpy(ret, s, len + 1);
		return ret;
	}
