#ifndef STL_MAP_H
#define STL_MAP_H

#include "stl_rbtree.h"
NAMESPACE_STL_BEGIN
//template<class Key, class T, class Compare = std::less<Key>>
//class Map {
//public:
//	typedef Key key_type;
//	typedef T data_type;
//	typedef T mapped_type;
//	typedef std::pair<key_type, data_type> value_type;
//	typedef Compare key_compare;
//
//	class value_compare :public std::binary_function<value_type, value_type, bool>
//	{
//	public:
//		friend class Map<key_type, data_type, key_compare>;
//	protected:
//		key_compare comp;
//		value_compare(key_compare c) { comp = c; }
//	public:
//		bool operator(const value_type& x, const value_type& y)const
//		{
//			return comp(x.first, y.first);
//		}
//	};
//	template<typename value_type>
//	struct select1st {
//	public:
//		key_type operator(const value_type& x)const
//		{
//			return x.first;
//		}
//	};
//private:
//	typedef rb_tree<key_type, value_type, select1st<value_type>, key_compare>rep_type;
//	rep_type t;
//
//public:
//	typedef typename rep_type::pointer pointer;
//	typedef typename rep_type::const_pointer pointer;
//	typedef typename rep_type::reference reference;
//	typedef typename rep_type::const_reference const_reference;
//	typedef typename rep_type::iterator iterator;
//	typedef typename rep_type::const_iterator const_iterator;
//	typedef typename rep_type::size_type size_type;
//	typedef typename rep_type::difference_type difference_type;
//
//	Map():t(Compare()){}
//
//	template<typename InputIterator>
//	Map(InputIterator first, InputIterator last) : t(Compare()) 
//	{ t.insert_unique(first, last); }
//
//	template<typename InputIterator>
//	Map(InputIterator first, InputIterator last, const Compare& comp) : t(comp)
//	{
//		t.insert_unique(first, last);
//	}
//
//	Map(const Map<Key, T, Compare> & x) { t = x.t; }
//	Map<Key, T, Compare> &operator= (const Map<Key, T, Compare>x)
//	{
//		t = x.t;
//		return *this;
//	}
//
//	key_compare key_comp()const { return t.key_comp(); }
//	value_compare value_comp()const { return value_compare(t.key_comp()); }
//	iterator begin() { return t.begin(); }
//	const_iterator begin()const { return t.begin(); }
//	iterator end() { return t.end(); }
//	const_iterator end()const { return t.end(); }
//	bool empty()const { return t.empty(); }
//	size_type size() const { return t.size(); }
//	size_type max_size() const { return t.max_size(); }
//
//
//
//};

NAMESPACE_STL_END
#endif
