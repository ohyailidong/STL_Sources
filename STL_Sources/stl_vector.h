#ifndef STL_VECTOR_H
#define STL_VECTOR_H

#include <iostream>
#include <xmemory>
#include <algorithm>
#include "stl_common_define.h"

namespace STL
{
	template <class T, class Alloc = std::allocator<T> >
	class Vector
	{
	public:
		typedef T            value_type;
		typedef value_type*  point;
		typedef value_type*  iterator;
		typedef value_type&  reference;
		typedef size_t       size_type;
		typedef ptrdiff_t    difference_type;

	public:
		Vector() :start(0), finish(0), end_of_storage(0) {}
		Vector(size_type n) { fill_initialize(n, 0); }
		Vector(size_type n, const T& value) { fill_initialize(n, value); }
		Vector(const Vector<T, Alloc>& x)
		{
			start = allocate_and_copy(x.end() - x.begin(), x.begin(), x.end());
			finish = start + (x.end() - x.begin());
			end_of_storage = finish;
		}
		Vector(const iterator first, const iterator last)
		{
			size_type n = last - first;
			//std::distance(first, last, n);
			start = allocate_and_copy(n, first, last);
			finish = start + n;
			end_of_storage = finish;
		}
		~Vector()
		{
			destory(start, finish);
			if (start)
			{
				deallocate();
			}
		}

		iterator begin()const { return start; }
		iterator end()const { return finish; }

		size_type size() { return size_type(end() - begin()); }
		size_type capacity() { return size_type(end_of_storage - begin()); }
		bool empty() { return (begin() == end()); }
		reference operator[](size_type n) { return *(begin() + n); }

		void push_back(const T& x)
		{
			if (finish != end_of_storage)
			{
				construct(finish, x);
				finish++;
			}
			else
			{
				insert_aux(end(), x);
			}
		}
		void pop_back()
		{
			--finish;
			destory(finish);
		}
		iterator erase(iterator first, iterator last)
		{
			iterator i = std::copy(last, finish, first);
			destory(i, finish);
			finish = finish - (last - first);
			return first;
		}
		iterator erase(iterator position)
		{
			if (position + 1 != end())
			{
				std::copy(position + 1, finish, position);
			}
			finish--;
			destory(finish);
			return position;
		}
		void insert(iterator position, size_type n, const T& x)
		{
			if (n < 1)return;
			//��n!=0ʱ���Ž����������в���
			if (size_type(end_of_storage - finish) >= n)//ʣ��Ŀռ���Բ�����ֵ
			{
				T x_copy = x;
				//���������Ԫ�صĸ���
				const size_type elems_after = finish - position;
				iterator old_finish = finish;
				if (elems_after > n)
				{
					//�������������Ԫ�صĸ��������ڡ���Ҫ����Ԫ�صĸ���
					std::uninitialized_copy(finish - n, finish, finish);
					finish += n;//β�˺���
					std::copy_backward(position, old_finish - n, old_finish);
					std::fill(position, position + n, x_copy);
				}
				else
				{
					//�������������Ԫ�صĸ�����С�ڵ��ڡ���Ҫ����Ԫ�صĸ���
					std::uninitialized_fill_n(finish, n - elems_after, x_copy);
					finish += (n - elems_after);
					std::uninitialized_copy(position, old_finish, finish);
					finish += elems_after;
					std::fill(position, old_finish, x_copy);
				}
			}
			else//���ÿռ�С�ڲ����������Ҫ���¿����¿ռ�
			{
				const size_type old_size = size();
				const size_type len = old_size + std::max(old_size, n);
				iterator new_start = std::allocator<T>().allocate(len);
				iterator new_finish = new_start;
				new_finish = std::uninitialized_copy(start, position, new_start);
				new_finish = std::uninitialized_fill_n(new_finish, n, x);
				new_finish = std::uninitialized_copy(position, finish, new_finish);
				//����ԭʼ����
				destory(start, finish);
				deallocate();
				//�������λ
				start = new_start;
				finish = new_finish;
				end_of_storage = start + len;
			}
		}
		void clear() { erase(start, finish); }

	protected:
		void fill_initialize(size_type n, const T& value)
		{
			start = allocate_and_fill(n, value);
			finish = start + n;
			end_of_storage = start + n;
		}
		iterator allocate_and_fill(size_type n, const T& value)
		{
			iterator result = std::allocator<T>().allocate(n);

			std::uninitialized_fill_n(result, n, value);
			return result;
		}
		iterator allocate_and_copy(size_type n, const iterator first, const iterator last)
		{
			iterator result = std::allocator<T>().allocate(n);;
			std::uninitialized_copy(first, last, result);
			return result;
		}
		void deallocate()
		{
			std::allocator<T>().deallocate(start, end_of_storage - start);
		}

		template<class valuetype>
		void insert_aux(iterator position, const valuetype & x)
		{
			if (finish != end_of_storage)//���б��ÿռ�
			{
				construct(finish, *(finish - 1));
				++finish;
				T x_copy = x;
				std::copy_backward(position, finish - 2, finish - 1);
				*position = x_copy;
			}
			else//���ޱ��ÿռ�
			{
				const size_type old_size = size();
				const size_type len = old_size != 0 ? 2 * old_size : 1;
				iterator new_start = std::allocator<T>().allocate(len);
				iterator new_finish = new_start;
				try
				{
					//��ԭvector���ݿ���
					new_finish = std::uninitialized_copy(start, position, new_start);
					construct(new_finish, x);
					++new_finish;
					new_finish = std::uninitialized_copy(position, finish, new_finish);
				}
				catch (const std::exception&)
				{

				}
				catch (...)
				{

				}

				deallocate();
				start = new_start;
				finish = new_finish;
				end_of_storage = new_start + len;
			}
		}
	private:
		iterator start;
		iterator finish;
		iterator end_of_storage;
	};
}

#endif
