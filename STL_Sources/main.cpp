#include "test_vector.h"
#include "test_slist.h"

int main(int argc, char**argv)
{
	//std::shared_ptr<TestBase> spTestPtr= std::make_shared<Test_Vector>();
	std::shared_ptr<TestBase> spTestPtr= std::make_shared<Test_sList>();
	spTestPtr->Run();
	system("pause");
	return 0;
}