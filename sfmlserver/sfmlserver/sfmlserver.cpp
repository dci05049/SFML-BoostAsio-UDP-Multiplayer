#include <ctime>
#include <iostream>
#include <string>
#include "server.h"

int main()
{
	try
	{
		std::cout << "starting a server" << std::endl;
		server server("s", "s");
		server.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}