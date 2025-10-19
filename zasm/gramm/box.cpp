#define _CRT_SECURE_NO_WARNINGS
#include <stdarg.h>
#include <string.h>
#include <wchar.h>
#include <assert.h>
#include "multibyte.h"
#include "box.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


	box_t
		box_mp_t::box_copy(box_t box)
	{
		dtp_t tag;
		uint32_t len;
		box_t copy;

		if (!IS_BOX_POINTER(box))
			return box;

		tag = box_tag(box);
		len = box_length(box);
		copy = alloc_box(len, tag);
		memcpy(copy, box, (uint32_t)len);
		return copy;
	}


	box_t
		box_mp_t::box_copy_tree(box_t box)
	{
		box_t *copy;
		dtp_t tag;

		if (!IS_BOX_POINTER(box))
			return box;

		tag = box_tag(box);
		copy = (box_t *)box_copy(box);
		if (IS_NONLEAF_DTP(tag))
		{
			uint32_t inx, len = BOX_ELEMENTS(box);
			for (inx = 0; inx < len; inx++)
				copy[inx] = box_copy_tree(((box_t *)box)[inx]);
		}
		return (box_t)copy;
	}


	box_t
		box_mp_t::box_int(intptr_t val)
	{
		if (!IS_BOX_POINTER(val))
			return (box_t)val;
		intptr_t *ret = (intptr_t*)alloc_box(sizeof(intptr_t), BT_INT);
		*ret = val;
		return ret;
	}

	box_t
		box_mp_t::box_double(double val)
	{
		double *ret = (double*)alloc_box(sizeof(double), BT_DOUBLE);
		*ret = val;
		return ret;
	}

	box_t
		box_mp_t::box_long(int64_t val)
	{
		int64_t *ret = (int64_t*)alloc_box(sizeof(int64_t), BT_LONG_INT);
		*ret = val;
		return ret;
	}

	wchar_t *
		box_mp_t::box_string(const wchar_t *str)
	{
		if (NULL == str)
			return NULL;
		wchar_t *ret = (wchar_t*)alloc_box(int((wcslen(str) + 1) * sizeof(wchar_t)), BT_STRING);
		wcscpy(ret, str);
		return ret;
	}

	wchar_t *
		box_mp_t::box_string(const char *str, int extlen)
	{
		if (NULL == str)
			return NULL;
		if (extlen <= 0)
			extlen = (int)strlen(str);
		int maxlen = 16385;
		wchar_t wstr[16385];
		wchar_t* pwstr = wstr;
		if (extlen > maxlen)
		{
			maxlen = extlen;
			pwstr = (wchar_t*)calloc(extlen + 1, sizeof(wchar_t));
		}
		unsigned char** src = (unsigned char**)&str;
		int len = dest_mbsnrtowcs(pwstr, src, extlen, maxlen * sizeof(wchar_t)) / sizeof(wchar_t);
		if (len >= 0 && len < maxlen)
		{
			pwstr[len] = L'\0';
			wchar_t* ret = (wchar_t*)alloc_box((len + 1) * sizeof(wchar_t), BT_STRING);
			wcscpy(ret, pwstr);
			if (pwstr != wstr)
				free(pwstr);
			return ret;
		}
		if (pwstr != wstr)
			free(pwstr);
		throw ("error in utf-8 literal parse");
		return NULL;
	}

	void *
		box_mp_t::alloc_box(int n, dtp_t tag)
	{
		unsigned char *ret;
		assert(n >= 0 && n < 10000000);
		ret = (unsigned char *)alloc(n + sizeof(int32_t));
		*(int32_t*)ret = (n & 0xffffff) | ((tag & 0xff) << 24);
		return ret + sizeof(int32_t);
	}

#if 1
	char **
		box_mp_t::list(long n, va_list& ap)
	{
		char ** box;
		int inx;
		box = (char **)alloc_box(sizeof(char*) * n, BT_ARRAY_OF_POINTER);
		for (inx = 0; inx < n; inx++)
		{
			char *child = va_arg(ap, char*);
			box[inx] = child;
		}
		return ((char **)box);
	}

	char **
		box_mp_t::list(long n, ...)
	{
		char ** box;
		va_list ap;
		va_start(ap, n);
		box = list(n, ap);
		va_end(ap);
		return ((char **)box);
	}
#else
	caddr_t *
		box_mp_t::list(long n, ...)
	{
		caddr_t *box;
		va_list ap;
		int inx;
		va_start(ap, n);
		box = (caddr_t *)alloc_box(sizeof(caddr_t) * n, BT_ARRAY_OF_POINTER);
		for (inx = 0; inx < n; inx++)
		{
			caddr_t child = va_arg(ap, caddr_t);
			box[inx] = child;
		}
		va_end(ap);
		return ((caddr_t *)box);
	}
#endif

	uint32_t
		box_mp_t::box_set_length(s_node_t * set)
	{
		uint32_t count;

		for (count = 0; set; set = set->next)
			count++;

		return count;
	}


	char **
		box_mp_t::list_to_array(s_node_t * set)
	{
		char **array;
		uint32_t len;
		uint32_t inx;

		len = box_set_length(set);
		if (0 == len)
			return 0;
		array = (char **)alloc_box(len * sizeof(void *), BT_ARRAY_OF_POINTER);
		inx = 0;

		DO_SET(char*, elt, &set)
		{
			array[inx++] = elt;
		}
		END_DO_SET();

		return array;
	}

	char **
		box_mp_t::revlist_to_array(s_node_t * set)
	{
		char **array;
		uint32_t len;
		uint32_t inx;

		inx = len = box_set_length(set);
		array = (char **)alloc_box(len * sizeof(void *), BT_ARRAY_OF_POINTER);

		DO_SET(char *, elt, &set)
		{
			array[--inx] = elt;
		}
		END_DO_SET();

		return array;
	}

	void
		box_mp_t::revert(box_set_t &set)
	{
		box_set_t next;
		box_set_t next2;

		if (!set)
			return;

		next = set->next;
		set->next = NULL;

		for (;;)
		{
			if (!next)
				return;

			next2 = next->next;
			next->next = set;
			set = next;
			next = next2;
		}
	}

	box_set_t
		box_mp_t::cons_set(void* car, box_set_t cdr)
	{
		s_node_t *s = (s_node_t *)alloc_box(sizeof(s_node_t), BT_LIST_OF_POINTER);
		s->data = car;
		s->next = cdr;
		return s;
	}

	void
		box_mp_t::set_push(box_set_t *set, void *elt)
	{
		*set = cons_set(elt, *set);
	}


	box_t
		box_mp_t::box_num(intptr_t n)
	{
		box_t *box;
		if (!IS_BOX_POINTER(n))
			return (box_t)n;
		box = (box_t *)alloc_box(sizeof(intptr_t), BT_INT);
		*box = (box_t)n;
		return box;
	}

	intptr_t
		box_mp_t::unbox_int(const box_t box)
	{
		if (!IS_BOX_POINTER(box))
			return (intptr_t)box;

		return *(intptr_t *)box;
	}


	box_set_t
		box_mp_t::box_set_last(box_set_t set)
	{
		box_set_t s;
		if (!set)
			return set;
		else
		{
			for (s = set; s->next; s = s->next)
				;
			return s;
		}
	}


	box_set_t
		box_mp_t::box_set_conc(box_set_t s1, box_set_t s2)
	{
		box_set_t last = box_set_last(s1);
		if (last)
		{
			last->next = s2;
			return s1;
		}
		else
		{
			return s2;
		}
	}

