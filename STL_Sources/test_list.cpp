#include <iostream>
#include<xmemory>
#include"stl_list.h"
#include"test_obj.h"

int main_list()
{
	//ListNode<int>*p = nullptr;
	//std::allocator<ListNode<int>>allocal;
	//int a=sizeof(ListNode<int>);
	//int b = sizeof(ListNode<double>);
	//p = allocal.allocate(1);
	//p->data = 4;
	//allocal.deallocate(p, 1);

	//****************************test int******************************************
	std::cout << "test int: \n";
	STL::List<int> intList;
	auto iterbegin = intList.begin();
	auto iterend = intList.end();

	intList.push_back(2);
	intList.push_back(4);
	intList.push_back(6);
	intList.push_back(8);

	iterbegin = intList.begin();
	iterend = intList.end();
	for (auto iter = intList.begin(); iter != intList.end(); ++iter)
	{
		std::cout << (*iter) << "  ";
	}
	std::cout << std::endl;
	intList.reverse();
	for (auto iter = intList.begin(); iter != intList.end(); ++iter)
	{
		std::cout << (*iter) << "  ";
	}
	std::cout << std::endl;

	intList.erase(iterbegin);
	iterbegin = intList.begin();

	for (auto iter = intList.begin(); iter != intList.end(); ++iter)
	{
		std::cout << (*iter) << "  ";
	}
	intList.clear();
	for (auto iter = intList.begin(); iter != intList.end(); ++iter)
	{
		std::cout << (*iter) << "  ";
	}
	std::cout << std::endl;

	//***************************************test shared ptr obj*********************************
	std::cout << "test class object:\n";
	std::cout << "test push_back():\n";

	STL::List<std::shared_ptr<test_class_t_obj>>listObj;
	std::cout << "listObj size :" << listObj.size() << std::endl;

	for (size_t i = 1; i < 6; i++)
	{
		auto sp_obj = std::make_shared<test_class_t_obj>(10);
		listObj.push_back(sp_obj);
		std::cout << "listObj size :" << listObj.size() << std::endl;
	}
	for (auto iter = listObj.begin(); iter != listObj.end(); ++iter)
	{
		std::cout << "list obj is: " << *iter << std::endl;
	}
	std::cout << "test reverse():\n";
	listObj.reverse();
	for (auto iter = listObj.begin(); iter != listObj.end(); ++iter)
	{
		std::cout << "list obj is: " << *iter << std::endl;
	}

	std::cout << "test erase():\n";
	auto iterbegin1 = listObj.begin();
	listObj.erase(iterbegin1);

	for (auto iter = listObj.begin(); iter != listObj.end(); ++iter)
	{
		std::cout << "list obj is: " << *iter << std::endl;
	}
	std::cout << "test clear():\n";
	listObj.clear();
	for (auto iter = listObj.begin(); iter != listObj.end(); ++iter)
	{
		std::cout << (*iter) << "  ";
	}
	std::cout << std::endl;

	return 0;
}