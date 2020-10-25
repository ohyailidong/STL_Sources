#ifndef STL_SLIST_H
#define STL_SLIST_H

#include "stl_common_define.h"

namespace STL {

	struct sListNodeBase {
		sListNodeBase* next;
	};
	template<typename T>
	struct sListNode :public sListNodeBase{
		T data;
	};
	//已知某一节点，插入新节点与其后
	inline sListNodeBase* slist_make_link(sListNodeBase* pre_node,sListNodeBase* new_node)
	{
		new_node->next = pre_node->next;
		pre_node->next = new_node;
		return new_node;
	}
	inline size_t slist_size(sListNodeBase* node)
	{
		int result(0);
		for (; node != 0; node = node->next)
			result++;
		return result;
	}
	struct sList_Iterator_Base {
		typedef size_t					size_type;
		//typedef ptrdiff_t				different_type;
		//typedef forward_iterator_tag    iterator_category;

		sListNodeBase* node;
		sList_Iterator_Base(){}
		sList_Iterator_Base(sListNodeBase* x):node(x){}

		void incr() { node = node->next; }
		bool operator== (const sList_Iterator_Base& x) { return node == x.node; }
		bool operator!= (const sList_Iterator_Base& x) { return node != x.node; }
	};

	template<typename T>
	struct sList_Iterator :public sList_Iterator_Base {
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference;
		typedef sListNode<T>		list_node;
		typedef sList_Iterator<T>   iterator;
		typedef sList_Iterator<T>   self;
		
		//slist_Iterator() {};
		sList_Iterator(list_node*x):sList_Iterator_Base(x){}
		sList_Iterator(const iterator &iter):sList_Iterator_Base(iter.node){}

		reference operator* ()const { return((list_node*)node)->data; }
		pointer operator->()const { &(operator*()); }
		self& operator++()
		{
			incr();
			return *this;
		}
		self operator++(int)
		{
			self temp = *this;
			incr();
			return temp;
		}
	};
	template <typename T,class Alloc = std::allocator<sListNode<T>>>
	class sList{
	public:
		typedef T					value_type;
		typedef value_type*			pointer;
		typedef const value_type	const_pointer;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef size_t				size_type;
		//typedef ptrdiff_t			difference_type;
		typedef sList_Iterator<T>	iterator;

	private:
		typedef sListNode<T>		list_node;
		typedef sListNodeBase		list_node_base;
		typedef sList_Iterator_Base iterator_base;
	private:
		list_node_base head;//头结点不存放数据
	private:
		list_node* create_node(const value_type& x)
		{
			Alloc alloc;
			list_node* p = alloc.allocate(1);//申请一个node的内存
			construct(&p->data, x);
			return p;
		}
		void destory_node(list_node* p)
		{
			destory(&p->data);
			Alloc().deallocate(p, 1);
		}
	public:
		sList() { head.next = nullptr; }
		~sList() { clear(); }//清除节点，并释放节点对象内存
		iterator begin() { return iterator((list_node*)head.next); }
		iterator end() { return iterator(nullptr); }
		bool empty() { return head.next == nullptr; }
		size_type size() { return slist_size(head.next);	}
		//两个slist交换，只需要将head 指针交换即可
		void swap(sList& L)
		{
			list_node_base tmp = head.next;
			head.next = L.head.next;
			L.head.next = tmp;
		}
		reference front()
		{
			return ((list_node*)head.next)->data;
		}
		void push_front(const_reference x)
		{
			slist_make_link(&head, create_node(x));
		}
		//从头部删除元素
		void pop_front()
		{
			list_node*node = (list_node*)head.next;
			head.next = node->next;
			destory_node(node);
		}
		void clear()
		{
			list_node* cur = (list_node*)head.next;
			while (cur != nullptr)
			{
				list_node* tmp = (list_node*)cur;
				cur = (list_node*)cur->next;
				destory_node(tmp);
			}
			head.next = nullptr;
		}
	};
}

#endif
