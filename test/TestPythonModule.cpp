#include "PythonModule/PyAgent.h"
using namespace std;

int main()
{
	auto agent = Py::PythonAgent::getInstance();
	agent->initialize(nullptr);
	agent->submit("1+1");
	// std::cout << "执行Python： " << result << std::endl;

	return 0;
}