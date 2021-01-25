#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H
#include <vector>
#include "stl_vector.h"
#include "test_base.h"

class Test_Vector:public TestBase
{
public:
	virtual void Run()
	{
		int sizevec = sizeof(std::vector<int>);
		sizevec = sizeof(std::vector<std::shared_ptr<test_class_t_obj>>);
		sizevec = sizeof(STL::Vector<int>);
		sizevec = sizeof(STL::Vector<std::shared_ptr<test_class_t_obj>>);

		//stl_vector_fun();
		my_stl_vector_fun();
		// 使用分配器申请内存
		int *p = nullptr;
		std::allocator<int> alloca1;
		p = alloca1.allocate(1);
		*p = 4;
		alloca1.deallocate(p, 1);
	}
private:
	void stl_vector_fun();
	void my_stl_vector_fun();
};

void Test_Vector::stl_vector_fun()
{
	//test int
	std::vector<int>a1;//{}
	std::vector<int>a2(5, 1); //{1，1，1，1，1}
	int b[6] = { 3,2,5,6,7,4 };
	std::vector<int>a3(b,b+6);//{3，2，5，6，7，4}
	std::vector<int>a4(a3);//{3，2，5，6，7，4}
	a1.assign(a4.begin(), a4.begin() + 4);//{3，2，5，6}
	a2.assign(4, 3);//{3，3，3，3}
	int i = a4.back();//4
	i = a4.front();//3
	i = a4[2]; //5
	a3.clear(); 
	a4.empty();
	a4.pop_back(); //{3，2，5,6,7}
	auto iter=a4.erase(a4.begin() + 1, a4.begin() + 3); //{3,6,7}
	i= *iter;
	a4.push_back(5);//{3，6, 7, 5}
	iter=a4.insert(a4.begin() + 1, 5); 
	i= *iter;
	iter=a4.insert(a4.begin() + 1, 3, 5); 
	i= *iter;
	iter=a4.insert(a4.begin() + 1, b + 3, b + 6);      
	i= *iter;
	i= a4.capacity(); 
	i= a4.size();
	a4.resize(15, 2); 
	a4.reserve(100);      
	a4.swap(a2); 
//	sort(a.begin(), a.end()); 
//	reverse(a.begin(), a.end()); 
//	copy(a.begin(), a.end(), b.begin() + 1);
//	find(a.begin(), a.end(), 10); 

	std::vector<std::shared_ptr<test_class_t_obj>>vecObj;
	std::cout << "std::vector size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	for (size_t i = 1; i < 6; i++)
	{
		auto sp_obj = std::make_shared<test_class_t_obj>();
		vecObj.push_back(sp_obj);
		std::cout << "std::vector size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	}

	vecObj.erase(vecObj.begin() + 1, vecObj.begin() + 3);
}
void Test_Vector::my_stl_vector_fun()
{
	STL::Vector<std::shared_ptr<test_class_t_obj>>vecObj;
	std::cout << "std::vector size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	for (size_t i = 0; i < 6; i++)
	{
		auto sp_obj = std::make_shared<test_class_t_obj>();
		vecObj.push_back(sp_obj);
		std::cout << "std::vector size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	}
	for (auto iter = vecObj.begin(); iter != vecObj.end(); iter++)
		std::cout<<*iter<<", this obj use count:"<<iter->use_count()<<"\n";

	vecObj.erase(vecObj.begin() + 1);
	std::cout << "std::vector size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	vecObj.erase(vecObj.begin() + 1, vecObj.begin() + 3);
	std::cout << "std::vector size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	vecObj.pop_back();
	std::cout << "std::vector size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	auto sp1 = std::make_shared<test_class_t_obj>();
	vecObj.insert(vecObj.begin() + 1, sp1);
	std::cout << "std::vector size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	sp1.reset();
	sp1 = std::make_shared<test_class_t_obj>();
	vecObj.insert(vecObj.begin() + 1, 3, sp1);
	std::cout << "std::vector size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;
	sp1.reset();
	for (auto iter = vecObj.begin(); iter != vecObj.end(); iter++)
		std::cout << *iter << ", this obj use count:" << iter->use_count() << "\n";
	sp1 = vecObj[2];
	sp1 = vecObj.front();
	sp1 = vecObj.back();
	sp1.reset();
	vecObj.clear();
	std::cout << "std::vector size and capacity:" << vecObj.size() << "  " << vecObj.capacity() << std::endl;

}
#endif