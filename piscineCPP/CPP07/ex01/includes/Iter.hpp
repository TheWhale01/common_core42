#pragma once
#include <iostream>

template<typename T>
void add_one(T &item)
{
	item++;
}

template<typename T1, typename T2, typename T3>
void iter(T1 &addr, T2 const &length, T3 const &func)
{
	for (T2 i = 0; i < length; i++)
		func(addr[i]);
}