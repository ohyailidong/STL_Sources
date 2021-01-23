#ifndef STL_COMMON_DEFINE_H
#define STL_COMMON_DEFINE_H

#include <iostream>
#include <xmemory>
#include <assert.h>
#include <algorithm>

#define NAMESPACE_STL_BEGIN namespace STL{
#define NAMESPACE_STL_END }

template<class T1, class T2>
inline void construct(T1*p, const T2& value)
{
	new (p) T1(value);
}
template <class T>
inline void destory(T* pointer)
{
	// µ÷ÓÃ dtor ~T()  
	pointer->~T();
}
template<class Itetrator>
inline void destory(Itetrator first, Itetrator last)
{
	std::_Destroy_range(first, last);
}

#endif
