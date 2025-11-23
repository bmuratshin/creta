#pragma once

#include <stdlib.h>
#include "btcodes.h"
#include "mempool.h"

#define _RNDUP(SZ,AL)    ((((SZ) + AL - 1) / AL) * AL)
#define ALIGN_4(x)    _RNDUP((x), 4)
#define ALIGN_8(x)    _RNDUP((x), 8)
#define ALIGN_16(x)    _RNDUP((x), 16)

	typedef unsigned char tag_t;
	typedef void * box_t;

	struct s_node_t
	{
		void *        data;
		s_node_t *    next;
	};
	typedef s_node_t  *box_set_t;

	/* this is like car or first in lisp */
#define DO_SET_FIRST(set) \
    (*set ? (((box_set_t) *set)->data) : NULL)

#define DO_SET(type, var, set) \
    { \
      type var; \
      s_node_t *iter = *set; \
      s_node_t *nxt; \
      for ( ; (NULL != iter); iter = nxt) \
        { \
          var = (type) (iter->data); \
          nxt = iter->next;

#define END_DO_SET()   \
        } \
    }

	inline int
		box_length_inline(void *box)
	{
		return ((uint32_t)(0x00ffffff & ((const uint32_t *)(box))[-1]));
	}

#ifndef BOX_ELEMENTS
#undef BOX_ELEMENTS
#endif
#define BOX_ELEMENTS(b) \
    (box_mp_t::box_length ((char*) (b)) / sizeof (char*))

#ifdef _MSC_VER
#define _DO_BOX(tag, inx, arr) \
    for ((inx) = 0; (inx) < (long)((arr) ? BOX_ELEMENTS (arr) : 0); (inx) ++) \
      {
#else
#define _DO_BOX(tag, inx, arr) \
    for ((inx) = 0; (inx) < ((arr) ? BOX_ELEMENTS(arr) : 0); (inx) ++) \
      {
#endif

#define DO_BOX(tag, v, inx, arr) \
    _DO_BOX((tag), (inx), (arr)) \
        tag v = (tag) (arr) [inx];



#define END_DO_BOX \
      }

	inline tag_t box_tag(const void *box) {
		return (*((tag_t *) &(((const unsigned char *)(box))[-1])));
	}
	inline void set_box_tag(box_t box, tag_t tag) {
		*((tag_t *) &(((unsigned char *)(box))[-1])) = tag; 
	}

	/*
	 * We allow pointer arrays to contain small integers
	 * for the sake of convenience. Even is a segmented
	 * architecture this would be an invalid pointer.
	 */
#define SMALLEST_POSSIBLE_POINTER (1<<20)

       /*
	* IS_BOX_POINTER.  Test if the item is a non null pointer
	*/
#define IS_BOX_POINTER(n) \
    (((intptr_t) n) >= SMALLEST_POSSIBLE_POINTER || \
     ((intptr_t) n) <= -SMALLEST_POSSIBLE_POINTER)

#define IS_NONLEAF_TAG(tag) \
    (((tag) == BT_ARRAY_OF_POINTER) || \
     ((tag) == BT_LIST_OF_POINTER) )

#define BT_TYPE_OF(x) \
    (IS_BOX_POINTER (x) \
        ? box_tag(x) \
        : ((tag_t)(BT_INT)) )

#define BT_STRINGP(q) \
  (IS_BOX_POINTER (q) && (BT_STRING == box_tag (q)))


	class box_mp_t : public mem_pool_t {
	public:

		box_mp_t() : mem_pool_t() {};
		~box_mp_t() {};
		mem_pool_t& operator=(mem_pool_t&& that) { return mem_pool_t::operator=((mem_pool_t&&)that); };

		box_mp_t(const box_mp_t&) = delete; //запретить копирование
		void operator=(const box_mp_t&) = delete; //запретить присваивание

		wchar_t *box_string(const wchar_t *);
		wchar_t *box_string(const char *str, int len = -1);
		box_t box_int(intptr_t);
		box_t box_long(int64_t val);
		box_t box_double(double);

		box_t alloc_box(int n, tag_t tag);
		char **list_to_array(s_node_t * set);
		char **revlist_to_array(s_node_t * set);
		char **mk_node(long n, ...);
		char **mk_node(long n, va_list &ap);
		box_t box_num(intptr_t n);
		static uint32_t box_set_length(s_node_t *set);
		static void revert(box_set_t &set);
		static float unbox_float(const box_t f) { return (*((float *)f)); }
		static double unbox_double(const box_t f) { return (*((double *)f)); }
		static const wchar_t *unbox_string(const box_t s) { return ((wchar_t *)s); };
		static intptr_t unbox_int(const box_t box);
		static int64_t unbox_long(const box_t box) { return (*((int64_t *)box)); }
		static int box_length(const box_t box) { return (((int)((int *)(box))[-1]) & 0xffffff); }
		box_t box_copy(box_t box);
		box_t box_copy_tree(box_t box);
		box_set_t cons_set(void* car, box_set_t cdr);
		box_set_t cons_set_wo_nulls(void* car, box_set_t cdr) 
		{ 
			return car ? cons_set(car, cdr) : cdr; 
		};
		void set_push(box_set_t *set, void *elem);
		box_set_t box_set_conc(box_set_t s1, box_set_t s2);
		box_set_t box_set_last(box_set_t set);
	};

