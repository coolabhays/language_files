#include <iostream>
#include "pair.hpp"

namespace chlng{
	Pair::Pair(int a, int b) {
		pa = new int(a);
		pb = new int(b);
		std::cout << "constructor with two args" << std::endl;
	}

	Pair::Pair(const Pair& obj) {
		this->pa = new int(*(obj.pa));
		this->pb = new int(*(obj.pb));
		std::cout << "copy constructor" << std::endl;
	}

	Pair::~Pair() {
		std::cout << "deleting current object" << std::endl;
		//delete this;
	}
	void Pair::print() {
		std::cout << "pa -> " << *pa << std::endl;
		std::cout << "pb -> " << *pb << std::endl;
	}
	/* static can only be defined at class definition, so static is mentioned in header file */
	void Pair::print(const Pair& obj) {
		std::cout << "pa -> " << *(obj.pa) << std::endl;
		std::cout << "pb -> " << *(obj.pb) << std::endl;
	}
	void Pair::print(const Pair* obj) {
		std::cout << "pa -> " << *(obj->pa) << std::endl;
		std::cout << "pb -> " << *(obj->pb) << std::endl;
	}
	bool Pair::compare(const Pair& obj) {
		return ((*pa == *(obj.pa)) && (*pb == *(obj.pb)));
	}
	bool Pair::compare(const Pair* obj) {
		return (*pa == *(obj->pa) && (*pb == *(obj->pb)));
	}
};
