#ifndef TEST_SLIST_H
#define TEST_SLIST_H
#include "test_obj.h"
#include "test_base.h"
#include "stl_slist.h"
#include <forward_list>

inline void Print(STL::sList<std::shared_ptr<test_class_t_obj>>&listObj)
{
	for (auto iter = listObj.begin(); iter != listObj.end(); ++iter)
		std::cout << "list obj is: " << *iter << ", this obj use count:" << iter->use_count() << "\n";
}
class Test_sList :public TestBase
{
public:
	virtual void Run()
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

		stl_slist_fun();
		my_stl_slist_fun();
	}
private:
	inline void stl_slist_fun();
	inline void my_stl_slist_fun();
};

void Test_sList::stl_slist_fun(){}

void Test_sList::my_stl_slist_fun()
{
	std::cout << "test class object:\n";
	std::cout << "test push_front():\n";
	STL::sList<std::shared_ptr<test_class_t_obj>>listObj;
	std::cout << "listObj size :" << listObj.size() << std::endl;

	for (size_t i = 0; i < 6; i++)
	{
		auto sp_obj = std::make_shared<test_class_t_obj>(10);
		listObj.push_front(sp_obj);
		std::cout << "listObj size :" << listObj.size() << std::endl;
	}
	Print(listObj);
	std::cout << "test reverse():\n";
	listObj.reverse();
	Print(listObj);
	std::cout << "test pop_front():\n";
	listObj.pop_front();
	listObj.pop_front();
	Print(listObj);
	std::cout << "test remove():\n";
	listObj.remove(listObj[1]);
	Print(listObj);
	std::cout << "test insert_after():\n";
	auto spobj = std::make_shared<test_class_t_obj>();
	listObj.insert_after(listObj.begin()+2, spobj);
	spobj.reset();
	Print(listObj);
	std::cout << "test resize():\n";
	listObj.resize(10);
	Print(listObj);
	std::cout << "test erase():\n";
	listObj.erase_after(listObj.begin() + 2);
	Print(listObj);
	std::cout << "test erase():\n";
	listObj.erase_after(listObj.begin() + 2,listObj.begin()+5);
	Print(listObj);
	std::cout << "test resize():\n";
	listObj.resize(4);
	Print(listObj);
	std::cout << "test clear():\n";
	listObj.clear();

}

#endif