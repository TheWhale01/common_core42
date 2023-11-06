#include "serial.hpp"

int main(void)
{
	Data data = {42};

	std::cout << deserialize(serialize(&data))->raw << std::endl;
	return (0);
}