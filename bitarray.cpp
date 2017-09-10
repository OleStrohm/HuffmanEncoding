//
// Created by Ole on 10.09.2017.
//

#include "bitarray.h"

BitArray::BitArray()
: localSize(0)
{
	current = new std::bitset<BITSET_SIZE>();
	arrays.push_back(current);
}

BitArray::BitArray(std::string& bits)
:	localSize(0)
{
	current = new std::bitset<BITSET_SIZE>();
	arrays.push_back(current);
	
	pushBack(bits);
}

BitArray::BitArray(const bool* bits, const unsigned int& size)
		: localSize(0) {
	current = new std::bitset<BITSET_SIZE>();
	arrays.push_back(current);
	
	for(int i = 0; i < size; i++)
		pushBack(bits[i]);
}

BitArray::~BitArray() {
	for(auto bitset : arrays)
		delete bitset;
}

void BitArray::pushBack(const bool& one) {
	if(localSize == BITSET_SIZE) {
		current = new std::bitset<BITSET_SIZE>();
		localSize = 0;
	}
	(*current)[localSize] = one;
	localSize++;
}

void BitArray::pushBack(const std::string& bits) {
	for(char c : bits) {
		if(c == '0')
			pushBack(0);
		else if (c == '1')
			pushBack(1);
	}
}

bool BitArray::getBit(const unsigned int& pos) const {
	if(pos >= getSize())
		return false;
	return (*(arrays[pos / BITSET_SIZE]))[pos%BITSET_SIZE];
}

const unsigned int BitArray::getSize() const {
	return (unsigned int) (BITSET_SIZE * (arrays.size()-1) + localSize);
}

const std::string BitArray::toString() const {
	std::string out;
	for(int i = 0; i < getSize(); i++) {
		out += (getBit(i) ? "1" : "0");
	}
	return out;
}

std::ostream& operator<< (std::ostream& stream, const BitArray& array) {
	return stream << array.toString();
}
