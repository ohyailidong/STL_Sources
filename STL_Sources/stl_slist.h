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
		typedef ptrdiff_t				different_type;
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
		pointer operator->()const { return &(operator*()); }
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
		self& operator+ (int n)
		{
			for (int i = 0; i < n; i++)
				++(*this);
			return *this;
		}
	};
	template <typename T,class Alloc = std::allocator<sListNode<T>>>
	class sList{
	public:
		typedef T							value_type;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef sList_Iterator<T>			iterator;
		typedef const sList_Iterator<T>     const_iterator;

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
		iterator _Before_begin()
		{
			return iterator((list_node*)&head);
		}
		iterator _Before_end() 
		{	// get iterator just before end
			iterator _Next = _Before_begin();
			for (iterator _Nextp = _Next; ++_Nextp != end(); )
				_Next = _Nextp;
			return (_Next);
		}
		void _Splice_same_after(iterator _Where,
			sList& _Right, iterator _First, iterator _Last)
		{	// splice _Right (_First, _Last) just after _Where
			iterator _Next = _First;
			iterator _After = _Next;
			for (++_After; _After != _Last; ++_Next, (void)++_After)
			{
				if (_After == _Right.end())
				{	// find last element, and check for bad range
					std::cout<<("forward_list splice_after invalid range\n");
					return;
				}
			}

			_Next.node->next = _Where.node->next;	// link last to new home
			_Where.node->next = _First.node->next;	// link first to new home
			_First.node->next = _Last.node;	// drop range from old home
		}
		void _Insert_after(iterator _Where, value_type& _Val)
		{
			auto nextNode = create_node(_Val);
			auto preNode = _Where.node;
			slist_make_link(preNode, nextNode);
		}
	public:
		sList() { head.next = nullptr; }
		~sList() { clear(); }//清除节点，并释放节点对象内存
		iterator begin() { return iterator((list_node*)head.next); }
		iterator end() { return iterator(nullptr); }
		bool empty() { return head.next == nullptr; }
		size_type size() { return slist_size(head.next); }
		//两个slist交换，只需要将head指向的第一个node指针交换即可
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
		void reverse()
		{
			if (!empty())
			{	// worth doing, move to back in reverse order
				const_iterator _First = _Before_end();
				while (begin() != _First)
				{
					_Splice_same_after(_First, *this, _Before_begin(), ++begin());
				}
			}
		}
		void remove(const T& _Val)
		{	// erase each element matching _Val
			iterator _Firstb = _Before_begin();
			iterator _Val_it = end();

			for (iterator _First = begin(); _First != end(); )
				if (*_First == _Val)
					if (_STD addressof(*_First) == _STD addressof(_Val))
					{	// store iterator to _Val and advance iterators
						_Val_it = _Firstb;
						++_Firstb;
						++_First;
					}
					else
						_First = erase_after(_Firstb);
				else
				{	// advance iterators
					++_Firstb;
					++_First;
				}

			if (_Val_it != end())
				erase_after(_Val_it);
		}

		void resize( size_type _Newsize)
		{	// determine new length, padding with _Ty() elements as needed
			size_type _Cursize = size();
			if (_Cursize < _Newsize)
			{	// pad to make larger
				iterator _Next = _Before_end();
				for (; _Cursize < _Newsize; ++_Cursize)
					_Insert_after(_Next,((list_node*)_Next.node)->data);

			}
			else if (_Newsize < _Cursize)
			{	// erase all but _Newsize elements
				iterator _Next = _Before_begin();
				for (; 0 < _Newsize; --_Newsize)
					++_Next;
				erase_after(_Next, end());
			}
		}

		iterator erase_after(iterator _Where)
		{
			auto _Pnodeb = _Where.node;
			if (++_Where == end())
			{
				std::cout<<"forward_list erase_after iterator outside range\n";
				assert(false);
			}
			else
			{	// node exists, erase it
				auto _Pnode = _Where.node;	// subject node
				++_Where;	// point past subject node

				_Pnodeb->next = _Pnode->next;	// link past it

				this->destory_node((list_node*)_Pnode);
			}

			return (iterator(_Where));

		}
		iterator erase_after(iterator _First, iterator _Last)
		{
			if (_First == begin() && _Last == end())
			{	// erase all and return fresh iterator
				clear();
				return (end());
			}
			else
			{	// erase subrange
				if (_First == end() || _First == _Last)
				{
					std::cout<<("forward_list invalid erase_after range\n");
					assert(false);
				}
				else
				{	// range not awful, try it
					iterator _After = _First;
					++_After;
					_Adl_verify_range(_After, _Last);
					while (_After != _Last)
						_After = erase_after(_First);
				}
				return (iterator(_Last));
			}
		}

		iterator insert_after(iterator _Where, value_type& _Val)
		{
			_Insert_after(_Where, _Val);
			return iterator(++_Where);
		}
		iterator insert_after(iterator _Where, size_type _Count, const value_type& _Val)
		{
			for (; 0 < _Count; --_Count,++_Where)
				_Insert_after(_Where, _Val);
		}
		T& operator[](int index) { 
			auto iter = begin();
			for (int i = 0; i < index; ++i)
				iter++;
			return ((list_node*)(iter.node))->data; 
		}
	};
}

#endif
