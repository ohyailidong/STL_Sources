#include "test_vector.h"

int main(int argc, char**argv)
{
	std::shared_ptr<TestBase> spTestPtr= std::make_shared<Test_Vector>();
	spTestPtr->Run();
	system("pause");
	return 0;
}