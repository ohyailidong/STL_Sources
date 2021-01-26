#ifndef STL_LIST_H
#define STL_LIST_H

#include "stl_common_define.h"

template <typename InputIterator>
inline int distance(InputIterator first, InputIterator last)
{
	int n(0);
	while (first != last)
	{
		first++;
		n++;
	}
	return n;
}

namespace STL
{
	template <class T>
	struct ListNode
	{
		typedef ListNode* listnodepoint;
		listnodepoint _m_prev;
		listnodepoint _m_next;
		T data;
	};
	template <class Ty>
	struct ListIterator
	{
	public:
		typedef ListIterator<Ty> self;
		//typedef bidirectional_iteraror_tag iterator_category;
		typedef Ty			 value_type;
		typedef value_type*  point;
		typedef value_type&  reference;

		typedef ListNode<Ty>* linktype;

	public:
		ListIterator() {}
		ListIterator(linktype x) :node(x) {}
		ListIterator(const ListIterator& x) :node(x.node) {}

		bool operator==(const self& x)const { return node == x.node; }
		bool operator!=(const self& x)const { return node != x.node; }
		reference operator*()const { return (*node).data; }
		point operator->()const { return &(operator*()); }
		//prefixform ++
		self& operator++() { node = (*node)._m_next; return *this; }
		//postfixform ++
		self operator++(int) { self tmp = *this; ++*this; return tmp; }
		//prefixform --
		self& operator--() { node = (*node)._m_prev; return *this; }
		//postfixform --
		self operator--(int) { self tmp = *this; --*this; return tmp; }
		self& operator+ (int n)
		{
			for (int i = 0; i < n; i++)
				++(*this);
			return *this;
		}
	public:
		linktype node;
	};

	template<class Ty, class Alloc = std::allocator<ListNode<Ty>>>
	class List
	{
	protected:
		typedef ListNode<Ty>			listnode;
	public:
		typedef listnode*				linktype;
		typedef size_t					size_type;
		typedef ListIterator<Ty>		iterator;
		typedef Ty&                     reference;
	public:
		List() { empty_initialize(); }
		List(size_type n) {}
		List(size_type n, Ty value) {}
		List(iterator first, iterator last) {}
		~List() { put_node(node); }

		iterator begin()const { return (*node)._m_next; }
		iterator end()const { return node; }
		bool empty()const { return node->_m_next == node; }
		size_type size()const { return distance(begin(), end()); }
		reference front() { return *begin(); }
		reference back() { return *(--end()); }

		void push_front(const Ty& x) { insert(begin(), x); }
		void push_back(const Ty& x) { insert(end(), x); }
		//在position前面insert
		iterator insert(iterator position, const Ty& x)
		{
			linktype tmp = create_node(x);
			//调整双向指针，使tmp插入进去
			tmp->_m_next = position.node;
			tmp->_m_prev = position.node->_m_prev;
			position.node->_m_prev->_m_next = tmp;
			position.node->_m_prev = tmp;
			return tmp;
		}
		void pop_front() { erase(begin()); }
		void pop_back() { iterator tmp = end(); erase(--tmp); }
		iterator erase(iterator position)
		{
			linktype next_node = position.node->_m_next;
			linktype pre_node = position.node->_m_prev;
			pre_node->_m_next = next_node;
			next_node->_m_prev = pre_node;
			destory_node(position.node);//释放节点内存和节点对象内存
			return iterator(next_node);
		}
		void clear()
		{
			linktype cur = node->_m_next;
			while (cur != node)
			{
				linktype tmp = cur;
				cur = cur->_m_next;
				destory_node(tmp);
			}
			node->_m_next = node;
			node->_m_prev = node;
		}
		void remove(const Ty&x)
		{
			iterator first = begin();
			iterator last = end();
			while (first != last)
			{
				iterator next = first;
				++next;
				if (*first == x)
					erase(first);
				first = next;
			}
		}
		void unique()
		{
			iterator first = begin();
			iterator last = end();
			if (last == first)
				return;
			iterator next = first;

			while (++next != last)
			{
				if (*next == *first)
				{
					erase(next);
				}
				else
				{
					first = next;//调整指针
				}
				next = first;//修正区段范围
			}
		}
		//merge   后期需要实现**********************
		//void sort(){}*****************************
		void reverse()
		{
			//如果是空链表或者只有一个元素，不进行任何操作
			if (node->_m_next == node || node->_m_next->_m_next == node)
				return;
			iterator first = begin();
			++first;
			while (first != end())
			{
				iterator old = first;
				++first;
				transfer(begin(), old, first);
			}
		}
		Ty& operator[](int index) {
			auto iter = begin();
			for (int i = 0; i < index; ++i)
				iter++;
			return (iter.node)->data;
		}
	protected:
		linktype get_node()
		{
			Alloc alloc;
			return (linktype)alloc.allocate(1);
		}
		void put_node(linktype x)
		{
			Alloc().deallocate(x, 1);
		}
		void empty_initialize()
		{
			node = get_node();
			node->_m_prev = node;
			node->_m_next = node;
		}
		linktype create_node(const Ty& x)
		{
			linktype p = get_node();
			construct(&p->data, x);
			return p;
		}
		void destory_node(linktype p)
		{
			destory(&p->data);
			put_node(p);
		}
		void transfer(iterator position, iterator first, iterator last)
		{
			if (position != last)
			{
				last.node->_m_prev->_m_next = position.node;
				first.node->_m_prev->_m_next = last.node;
				position.node->_m_prev->_m_next = first.node;
				linktype tmp = position.node->_m_prev;
				position.node->_m_prev = last.node->_m_prev;
				last.node->_m_prev = first.node->_m_prev;
				first.node->_m_prev = tmp;
			}
		}
	private:
		linktype node;//只要一个指针，就可以表示环状双向列表
	};
}

#endif
