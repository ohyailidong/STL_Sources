#include "stl_slist.h"
#include "test_obj.h"
//int main_slist()
int main()
{
	//ÉêÇë½ÚµãÄÚ´æ²âÊÔ
	//STL::sListNode<int>pnode;
	//STL::sListNode<int>*p = nullptr;

	//std::allocator<STL::sListNode<int>>allo;
	//int a = sizeof(STL::sListNode<int>);
	//int b = sizeof(STL::sListNode<double>);
	//p = allo.allocate(1);
	//p->data = 4;
	//allo.deallocate(p, 1);

	//****************************test int******************************************
	std::cout << "test int: \n";
	STL::sList<int> intList;
	auto iterbegin = intList.begin();
	auto iterend = intList.end();
	intList.push_front(2);
	intList.push_front(4);
	intList.push_front(6);
	intList.push_front(8);

	iterbegin = intList.begin();
	iterend = intList.end();
	for (auto iter = intList.begin(); iter != intList.end(); ++iter)
	{
		std::cout << (*iter) << "  ";
	}
	std::cout << std::endl;
	intList.pop_front();
	intList.pop_front();
	for (auto iter = intList.begin(); iter != intList.end(); ++iter)
	{
		std::cout << (*iter) << "  ";
	}
	intList.clear();
	for (auto iter = intList.begin(); iter != intList.end(); ++iter)
	{
		std::cout << (*iter) << "  ";
	}
	//intList.reverse();
	//for (auto iter = intList.begin(); iter != intList.end(); ++iter)
	//{
	//	std::cout << (*iter) << "  ";
	//}
	//std::cout << std::endl;
	std::cout << std::endl;

	//***************************************test shared ptr obj*********************************
	std::cout << "test class object:\n";
	std::cout << "test push_front():\n";
	STL::sList<std::shared_ptr<test_class_t_obj>>listObj;
	std::cout << "listObj size :" << listObj.size() << std::endl;

	for (size_t i = 1; i < 6; i++)
	{
		auto sp_obj = std::make_shared<test_class_t_obj>(10);
		listObj.push_front(sp_obj);
		std::cout << "listObj size :" << listObj.size() << std::endl;
	}
	for (auto iter = listObj.begin(); iter != listObj.end(); ++iter)
	{
		std::cout << "list obj is: " << *iter << std::endl;
	}
	//std::cout << "test reverse():\n";
	//listObj.reverse();
	//for (auto iter = listObj.begin(); iter != listObj.end(); ++iter)
	//{
	//	std::cout << "list obj is: " << *iter << std::endl;
	//}

	std::cout << "test pop_front():\n";
	listObj.pop_front();
	listObj.pop_front();

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