#include "stl_rbtree.h"

int main()
{
	STL::rb_tree<int, int, std::identity<int>, std::less<int>> intRb_tree;
	//****************************test int******************************************
	std::cout << "test int: \n";
	std::cout << "size is:" << intRb_tree.size() << std::endl;
	auto iterbegin = intRb_tree.begin();
	auto iterend = intRb_tree.end();
	intRb_tree.insert_equal(10);
	intRb_tree.insert_equal(7);
	intRb_tree.insert_equal(8);
	intRb_tree.insert_equal(15);
	intRb_tree.insert_equal(5);
	intRb_tree.insert_equal(6);
	intRb_tree.insert_equal(11);
	intRb_tree.insert_equal(13);
	intRb_tree.insert_equal(12);
	iterbegin = intRb_tree.begin();
	iterend = intRb_tree.end();
	std::cout << "test operator++\n";
	for (; iterbegin != iterend; iterbegin++)
	{
		std::cout << *iterbegin << "(" << iterbegin.node->color << ")" << std::endl;
	}
	std::cout << "size is:"<<intRb_tree.size() <<std::endl;
	std::cout << "test operator--\n";
	for (iterbegin--; iterbegin != intRb_tree.begin(); iterbegin--)
	{
		std::cout << *iterbegin << "(" << iterbegin.node->color << ")" << std::endl;
	}
	return 0;
}