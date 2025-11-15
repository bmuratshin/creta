#ifndef __MEMDEBUG_H
#define __MEMDEBUG_H


extern void *new_smth (size_t size);
extern void *new_smth (size_t size);
extern void free_smth (void *ptr);
inline wchar_t *wcsdup_smth (const wchar_t *str)
{
	size_t size = wcslen (str) + 1;
	wchar_t *ret = (wchar_t*)new_smth (sizeof (wchar_t) * size);
	wcscpy (ret, str);
	return ret;
}

template<typename T>
inline T* 
new_arr_smth (int n)
{
  char *retptr = (char*)new_smth(sizeof(T)*n+8);
  *(int*)retptr = n;
  for (int i = 0; i < n; i++)
    new (retptr + 8) T();
  return (T*)(retptr+8);
}

template<typename T>
inline void
del_arr_smth (T*ptr)
{
  if (NULL == ptr)
    return;
  char *retptr = ((char*)ptr)-8;
  int n = *(int*)retptr;
  for (int i = 0; i < n; i++)
    ptr[i].~T();
  free_smth (retptr);
}

template<typename T>
inline void
del_smth (T *ptr)
{
  if (NULL == ptr)
    return;
  ptr->~T();
  free_smth (ptr);
}

#define NEW_SMTH(T) (new (new_smth(sizeof(T))) T())
#define NEW_SMTH_P(T,b) (new (new_smth(sizeof(T))) T b)
#define NEW_ARR_SMTH(T,n) new_arr_smth<T>(n);
#define DEL_ARR_SMTH(T,p) del_arr_smth<T>(p);
#define DEL_SMTH(T,p) del_smth<T>(p);


#if !defined(OMIT_MEMDEBUG) && !defined(_WIN32_WCE)

#ifdef WIN32
#ifdef _DEBUG
#ifdef new
    #undef new
#endif
#ifdef calloc
    #undef calloc
#endif
#ifdef malloc
    #undef malloc
#endif
#ifdef free
    #undef free
#endif

#ifndef _WIN32_WCE
#include <crtdbg.h>
#endif

inline void * __malloc_dbg (size_t size, int type, const char *fileName, int lineNum)
{
//printf ("%d ", size);
  return _malloc_dbg (size, type, fileName, lineNum);
}

inline char * __strdup_dbg (const char *val, int type, const char *fileName, int lineNum)
{
  size_t size = strlen (val) + 1;
  char *ret = (char*)_malloc_dbg (sizeof (char) * size, type, fileName, lineNum);
  strcpy (ret, val);
  return ret;
}

inline wchar_t * __wcsdup_dbg (const wchar_t *val, int type, const char *fileName, int lineNum)
{
  size_t size = wcslen (val) + 1;
  wchar_t *ret = (wchar_t*)_malloc_dbg (sizeof (wchar_t) * size, type, fileName, lineNum);
  wcscpy (ret, val);
  return ret;
}

inline void * __calloc_dbg (size_t size, size_t nel, int type, const char *fileName, int lineNum)
{
//printf ("%d ", size*nel);
  return _calloc_dbg (size, nel, type, fileName, lineNum);
}


inline void __free_dbg( void *userData, int blockType )
{
  _free_dbg (userData, blockType);
}

inline void * operator new (size_t size, const char * fileName, int lineNum)
{
  return __malloc_dbg (size, _NORMAL_BLOCK, fileName, lineNum);
}

//inline void * operator new (size_t size)
//{
//  return __malloc_dbg (size, _NORMAL_BLOCK, "", 0);
//}

//inline void * operator new[] (size_t size)
//{
//  return __malloc_dbg (size, _NORMAL_BLOCK, "", 0);
//}

inline void * operator new[] (size_t size, const char * fileName, int lineNum)
{
  return __malloc_dbg (size, _NORMAL_BLOCK, fileName, lineNum);
}

//inline void operator delete[] (void * buf)
//{
//  __free_dbg (buf, _NORMAL_BLOCK);
//}

inline void operator delete(void* pData, const char * /* fileName */, int /* lineNum */)
{
  __free_dbg (pData, _NORMAL_BLOCK);
}

inline void operator delete[](void* pData, const char * /* fileName */, int /* lineNum */)
{
  __free_dbg (pData, _NORMAL_BLOCK);
}

#define DEBUG_NEW new(THIS_FILE, __LINE__)
#define malloc(a) __malloc_dbg (a, _NORMAL_BLOCK, THIS_FILE, __LINE__)
#define calloc(a,b) __calloc_dbg (a, b, _NORMAL_BLOCK, THIS_FILE, __LINE__)
#define free(a) __free_dbg (a, _NORMAL_BLOCK)
#define strdup(a) __strdup_dbg (a, _NORMAL_BLOCK, THIS_FILE, __LINE__)
#define wcsdup(a) __wcsdup_dbg (a, _NORMAL_BLOCK, THIS_FILE, __LINE__)

#endif
#endif

#else  //OMIT_MEMDEBUG
#define DEBUG_NEW new
#endif //OMIT_MEMDEBUG


#endif
