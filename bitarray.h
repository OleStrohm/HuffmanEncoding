//
// Created by Ole on 10.09.2017.
//

#pragma once

#include <bitset>
#include <vector>
#include <iostream>

#define BITSET_SIZE 128

class BitArray {
private:
	std::vector<std::bitset<BITSET_SIZE>*> arrays;
	std::bitset<BITSET_SIZE>* current;
	unsigned int localSize;
public:
	BitArray();
	BitArray(std::string& bits);
	BitArray(const bool* bits, const unsigned int& size);
	
	~BitArray();
	
	void pushBack(const bool& one);
	void pushBack(const std::string& one);
	bool getBit(const unsigned int& pos) const;
	
	const unsigned int getSize() const;
	const std::string toString() const;
};

std::ostream& operator<< (std::ostream& stream, const BitArray& array);
