#include "stl_vector.h"
#include "test_obj.h"

int main_vec()
{
	// 使用分配器申请内存
	//std::vector<int>a;

	int *p = nullptr;
	std::allocator<int> alloca1;
	p = alloca1.allocate(1);
	*p = 4;
	alloca1.deallocate(p, 1);
	// test STL::Vector , test int
	std::cout << "Test vector:int:\n";
	std::cout << "test push_back():\n";
	STL::Vector<int>vecInt;
	std::cout <<"VecInt size and capacity:"<< vecInt.size() << "  "<<vecInt.capacity() << std::endl;
	for (size_t i = 1; i < 6; i++)
	{
		vecInt.push_back(i);
		std::cout << "VecInt size and capacity:" << vecInt.size() << "  " << vecInt.capacity() << std::endl;
	}
	//test int push_back
	for (auto iter = vecInt.begin(); iter != vecInt.end(); iter++)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	//test int insert
	std::cout << "test insert():\n";
	vecInt.insert(&vecInt[2], 3, 8);
	for (auto iter = vecInt.begin(); iter != vecInt.end(); iter++)
	{
		std::cout << *iter << " ";
	}
	std::cout<<std::endl;

	std::cout << "test clear():\n";
	vecInt.clear();
	std::cout << "VecInt size and capacity:" << vecInt.size() << "  " << vecInt.capacity() << std::endl;

	std::cout << "Test vector:class object:\n";
	std::cout << "test push_back():\n";
	STL::Vector<std::shared_ptr<test_class_t_obj>>vecObj;
	std::cout << "vecObj size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	for (size_t i = 1; i < 6; i++)
	{
		auto sp_obj = std::make_shared<test_class_t_obj>(10);
		vecObj.push_back(sp_obj);
		std::cout << "vecObj size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	}
	//test int push_back
	for (auto iter = vecObj.begin(); iter != vecObj.end(); iter++)
	{
		std::cout << *iter << ",  ";
	}
	std::cout << std::endl;

	//test obj class insert
	std::cout << "test insert():\n";
	auto sp_obj = std::make_shared<test_class_t_obj>(10);
	vecObj.insert(&vecObj[2], 1, sp_obj);
	sp_obj.reset();
	for (auto iter = vecObj.begin(); iter != vecObj.end(); iter++)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
	std::cout << "test clear():\n";
	vecObj.clear();
	std::cout << "vecObj size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;

	return 0;
}