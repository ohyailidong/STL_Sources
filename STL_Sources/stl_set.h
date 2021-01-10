#ifndef STL_SET_H
#define STL_SET_H
#include "stl_rbtree.h"
NAMESPACE_STL_BEGIN

//template <class Key, class Compare = std::less<Key> >
//class Set {
//public:
//	typedef Key key_type;
//	typedef Key value_type;
//	typedef Compare key_compare;
//	typedef Compare value_compare;
//private:
//	typedef rb_tree < key_type, value_type, std::identity<value_type>, key_compare> rep_type;
//	rep_type t;
//
//public:
//	typedef typename rep_type::const_pointer pointr;
//	typedef typename rep_type::const_pointer const_pointer;
//	typedef typename rep_type::const_reference const_reference;
//	typedef typename rep_type::const_reference reference;
//	typedef typename rep_type::const_iterator const_iterator;
//	typedef typename rep_type::const_iterator iterator;
//	typedef typename rep_type::size_type size_type;
//	typedef typename rep_type::difference_type difference_type;
//
//	Set():t(Compare()) {}
//	//explict Set (const Compare& comp):t(comp){}
//
//	template <class InputIterator>
//	Set(InputIterator first, InputIterator last) : t(Compare()) { t.insert_unique(first, last); }
//	template <class InputIterator>
//	Set(InputIterator first, InputIterator last, const Compare& comp) : t(comp) { t.insert_unique(first, last); }
//	Set(const Set<Key,Compare> &x):t(x.t){}
//	Set<Key, Compare>& operator =(const Set<Key, Compare> &x) {
//		t = x.t;
//		return *this;
//	}
//
//	key_compare key_comp() const { return t.key_comp; }
//	value_compare value_comp() const { return t.value_comp; }
//	iterator begin() const { return t.begin(); }
//	iterator end() const { return t.end(); }
//	bool empty() const { return t.empty(); }
//	size_type size()const { return t.size(); }
//	size_type max_size() const { return t.max_size(); }
//	void swap(Set<Key, Compare> &x) { t.swap(x); }
//
//	std::pair<iterator, bool> insert(const value_type& x)
//	{
//		std::pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
//		return std::pair<iterator, bool>(p.first, p.second);
//	}
//	//iterator insert(iterator position, const value_type& x)
//	//{
//	//	typedef typename rep_type::iterator rep_itertator;
//	//	return t.insert((rep_iteration&)position, x);
//	//}
//	template <class InputIterator>
//	void insert(InputIterator first, InputIterator last)
//	{
//		t.insert_unique(first, last);
//	}
//
//	void erase(iterator position)
//	{
//		typedef typename rep_type::iterator rep_iterator;
//		t.erase((rep_iterator&)position);
//	}
//	size_type erase(const key_type& key) { return t.erase(key); }
//	void erase(iterator first, iterator last)
//	{
//		typedef typename rep_type::iterator rep_iterator;
//		t.erase((rep_iterator&)first, (rep_iterator&)last);
//	}
//
//	void clear() { t.clear(); }
//
//	iterator find(const key_type& x)const { return t.find(x); }
//	size_type count(const key_type& x)const { return t.count(x); }
//	
//};

NAMESPACE_STL_END
#endif
