#ifndef STL_RBTREE_H
#define STL_RBTREE_H
#include "stl_common_define.h"

typedef bool rb_tree_color_type;
const rb_tree_color_type rb_tree_red = false;//红为0
const rb_tree_color_type rb_tree_black = true;//黑为1

struct rb_tree_node_base
{
	typedef rb_tree_color_type color_type;
	typedef rb_tree_node_base* nodebase_ptr;

	color_type color;//红色为0，黑色为1
	nodebase_ptr parent;
	nodebase_ptr left;
	nodebase_ptr right;

	//define max and min fun
	static nodebase_ptr min(nodebase_ptr x)
	{
		while (x->left != nullptr)
			x = x->left;
		return x;
	}
	static nodebase_ptr max(nodebase_ptr x)
	{
		while (x->right != nullptr)
			x = x->right;
		return x;
	}
};

template<typename Value>
struct rb_tree_node: public rb_tree_node_base
{
	typedef rb_tree_node<Value>* node_ptr;
	Value value;
};
//define rb_tree iterator
struct rb_tree_base_iterator
{
	typedef rb_tree_node_base::nodebase_ptr node_base_ptr;
	//typedef bidirectional_iterator_tag iterator_category;
	//typedef ptrdiff_t defferent_type;

	node_base_ptr node;

	void increment()
	{
		//如果iter指向的节点有右节点，则寻找右节点分支最左边的节点
		if (node->right != nullptr)
		{
			node = node->right;
			while (node->left != nullptr)
				node = node->left;
		}
		//如果iter指向的节点没有右节点，需判断当前节点在其父节点的左边还是右边
		else
		{
			//如果当前节点在父节点的右边，一直寻找其父节点，直到节点在父节点的左边位置，
			//其父节点就是iter++需要指向的节点
			node_base_ptr y = node->parent;
			while (y->right == node)
			{
				node = y;
				y = node->parent;
			}
			//该节点位于父节点的左边，父节点即是iter++指向的节点
			if (y->left == node)//原书中是node->right!=y
			{
				node = y;
			}
		}
	}
	void decrement()
	{
		//当node指向end()时，即rb_tree的header时
		if (node->color == rb_tree_red &&
			node->parent->parent == node)
			node = node->right;
		//当node指向的节点有左分支时，则寻找左分支最右边的值
		else if (node->left != nullptr)
		{
			node_base_ptr y = node->left;
			while (y->right != nullptr)
			{
				y = y->right;
			}
			node = y;
		}
		//如果当前节点只有右分支，向父节点寻找；
		//当父节点的左节点！=当前节点时，父节点即iter--指向的节点
		else
		{
			node_base_ptr y = node->parent;
			while (y->left==node)
			{
				node = y;
				y = y->parent;
			}
			node = y;
		}
	}
};

template<typename Value>
struct rb_tree_iterator :public rb_tree_base_iterator
{
	typedef Value							value_type;
	typedef value_type&						reference;
	typedef value_type*						pointer;
	typedef rb_tree_iterator<Value>			iterator;
	typedef rb_tree_iterator<const Value>	const_iterator;
	typedef rb_tree_iterator<Value>			self;
	typedef rb_tree_node<Value>*			tree_node;

	rb_tree_iterator(){}
	rb_tree_iterator(tree_node x) :{node = x; }
	rb_tree_iterator(const iterator& iter) { node = iter.node; }

	self& operator++()
	{
		increment();
		return *this;
	}
	self operator++(int) 
	{
		self tmp = *this;
		increment();
		return tmp;
	}
	self&operator--()
	{
		decrement();
		return *this;
	}
	self operator--(int)
	{
		self tmp = *this;
		decrement();
		return tmp;
	}
	reference operator*() 
	{
		return tree_node(node)->value;
	}
	pointer operator->()
	{
		return &(operator*());
	}
};

//define rb_tree
template <class Key, class Value, class KeyOfValue, class Compare, 
	class Alloc = std::allocator<rb_tree_node<Value>>>
	class rb_tree {
	protected:
		typedef void* void_pointer;
		typedef rb_tree_node_base* base_ptr;
		typedef rb_tree_node<Value> rb_tree_node;
		typedef rb_tree_color_type color_type;

	public:
		typedef Key key_type;
		typedef Value value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef rb_tree_node* link_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	protected:
		link_type get_node()
		{
			Alloc alloc;
			return (link_type)alloc.allocate(1);
		}
		void put_node(link_type x)
		{
			Alloc().deallocate(x, 1);
		}
		link_type create_node(const value_type &x)
		{
			link_type tmp = get_node();
			construct(&tmp->value, x);
			return tmp;
		}
		link_type clone_node(link_type x)
		{
			link_type p = creat_node(x->value);
			p->color = x->color;
			p->left = nullptr;
			p->right = nullptr;
			return p;
		}
		void destory_node(link_type p)
		{
			destory(&p->value);
			put_node(p);
		}
	protected:
		link_type& root()const { return (link_type&)header->parent; }
		link_type& leftmost()const { return (link_type&)header->left; }
		link_type& rightmost()const { return (link_type&)header->right; }

		static link_type& left(link_type x) { return (link_type&)x->left; }
		static link_type& right(link_type x) { return (link_type&)x->right; }
		static link_type& parent(link_type x) { return (link_type&)x->parent; }
		static reference value(link_type x) { return x->value; }
		static const Key& key(link_type x) { return KeyOfValue()(value(x)); }
		static color_type &color(link_type x) { return (colot_type&)(x->color); }
		static link_type& left(base_ptr x) { return (link_type&)x->left; }
		static link_type& right(base_ptr x) { return (link_type&)x->right; }
		static link_type& parent(base_ptr x) { return (link_type&)x->parent; }
		static reference value(base_ptr x) { return ((link_type)x)->value; }
		static const Key& key(base_ptr x) { return KeyOfValue()(value(x)); }
		static color_type &color(base_ptr x) { return (colot_type&)(link_type(x)->color); }

		static link_type minimun(link_type x) {
			return (link_type)rb_tree_node_base::min(x);
		}
		static link_type maximun(link_type x) {
			return (link_type)rb_tree_node_base::max(x);
		}
	public:
		typedef rb_tree_iterator<value_type> iterator;
	private:
		iterator _insert(base_ptr x, base_ptr y, const value_type &v);
		link_type _copy(link_type x, link_type p);
		void _erase(link_type x);
		void init();
	public:
		rb_tree(const Compare& comp= Compare()):
			node_count(0),
			key_compare(comp) 
		{
			init();
		}
		~rb_tree()
		{
			clear();
			put_node();
		}
		rb_tree & operator= (const rb_tree & x);
		Comppare key_comp() const { return key_compare; }
		iterator begin() { return leftmost(); }
		iterator end() { return header; }
		bool empty()const { return node_count == 0; }
		size_type size()const { return node_count; }
		size_type max_size()const { return size_type(-1); }
		std::pair<iterator, bool> insert_unique(const value_type& x);
		iterator insert_equal(const value_type& x);
		//成员变量
	protected:
		size_type node_count;
		link_type header;
		Compare key_compare;

};
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::init()
{
	header = get_node();
	color(header) = rb_tree_red;
	root() = nullptr;
	leftmost() = header;
	rightmost() = header;
}

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
std::pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value & x)
{
	return pair<iterator, bool>();
}

template<class Key,class Value,class KeyOfValue ,class Compare,class Alloc>
typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const Value& v)
{

}
#endif 
