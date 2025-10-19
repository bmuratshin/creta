#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


class mem_pool_t
{
 public:
  mem_pool_t ();
  mem_pool_t(mem_pool_t&& that);
  mem_pool_t& operator=(mem_pool_t&& that);
  ~mem_pool_t();

  mem_pool_t(const mem_pool_t&) = delete; //запретить копирование
  void operator=(const mem_pool_t&) = delete; //запретить присваивание

  int reset ();
  size_t size () {return total_bytes_;}
  void *alloc (size_t len1);
  void *alloc_ (size_t len1) {return alloc (len1);};
  void *alloc__ (size_t len1, unsigned char type = 0);
  void undoLastAlloc();
  void free_ (void *, size_t ) {};
  char *strdup_(char *);
  void swap(mem_pool_t &other);

  static const int mp_block_size = (8192);
private:
	struct mem_block_t
	{
		mem_block_t *     mb_next;
		uint32_t          mb_fill;
		uint32_t          mb_size;
	};

	mem_block_t  *mp_first;
	size_t        total_bytes_;
	size_t        lastLen;
	int           usdef_;
};

