#ifndef TEST_LIST_H
#define TEST_LIST_H

#include "test_base.h"
#include "stl_list.h"
#include <list>

inline void Print(STL::List<std::shared_ptr<test_class_t_obj>>&listObj)
{
	for (auto iter = listObj.begin(); iter != listObj.end(); ++iter)
		std::cout << "list obj is: " << *iter << ", this obj use count:" << iter->use_count() << "\n";
}
class Test_List :public TestBase
{
public:
	virtual void Run()
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

		for (size_t i = 0; i < 6; i++)
		{
			auto sp_obj = std::make_shared<test_class_t_obj>();
			listObj.push_back(sp_obj);
			std::cout << "listObj size :" << listObj.size() << std::endl;
		}
		Print(listObj);
		std::cout << "test reverse():\n";
		listObj.reverse();
		Print(listObj);
		std::cout << "test erase():\n";
		listObj.erase(listObj.begin());
		Print(listObj);
		std::cout << "test insert():\n";
		auto sp = std::make_shared<test_class_t_obj>();
		listObj.insert(listObj.begin()+2,sp);
		sp.reset();
		Print(listObj);
		std::cout << "test remove():\n";
		listObj.remove(listObj[2]);
		Print(listObj);
		std::cout << "test pop_back():\n";
		listObj.pop_back();
		Print(listObj);
		std::cout << "test pop_front():\n";
		listObj.pop_front();
		Print(listObj);
		std::cout << "test insert():\n";
		listObj.insert(listObj.end(), listObj[2]);
		Print(listObj);
		std::cout << "test unique():\n";
		listObj.unique();
		Print(listObj);
		std::cout << "test clear():\n";
		listObj.clear();
		Print(listObj);
	}
private:

};

#endif