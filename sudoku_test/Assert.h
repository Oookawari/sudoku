#ifndef MY_ASSERT
#define MY_ASSERT

#include<iostream>
#include<string>
void Assert(bool cond, std::string mess = "") {
	if (!cond) {
		std::cout << mess << std::endl;
		exit(EXIT_FAILURE);
	}
}

#endif // !MY_ASSERT