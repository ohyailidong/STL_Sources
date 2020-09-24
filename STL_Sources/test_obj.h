#ifndef STL_CLASS_OBJECT_H
#define STL_CLASS_OBJECT_H
#include <iostream>

class test_class_t_obj
{
public:
	test_class_t_obj(int len) :m_MallocLen(len)
	{
		m_ptr = (void*)new int[len];
		for (size_t i = 0; i < len; i++)
		{
			((int*)m_ptr)[i] = i;
		}
		std::cout << "construct this obj address is:" << this << "\n";
	}
	~test_class_t_obj()
	{
		if (m_ptr)
		{
			std::cout << "ÊÍ·ÅÄÚ´æ\n";
			delete[]m_ptr;
		}
		std::cout << "deconstruct this obj address is:" << this << "\n";
	}
private:
	int m_MallocLen;
	void* m_ptr;
};

#endif
