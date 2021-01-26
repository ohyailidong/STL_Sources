#include "test_vector.h"
#include "test_slist.h"
#include "test_list.h"

int main(int argc, char**argv)
{
	//std::shared_ptr<TestBase> spTestPtr= std::make_shared<Test_Vector>();
	//std::shared_ptr<TestBase> spTestPtr= std::make_shared<Test_sList>();
	std::shared_ptr<TestBase> spTestPtr= std::make_shared<Test_List>();
	spTestPtr->Run();
	system("pause");
	return 0;
}