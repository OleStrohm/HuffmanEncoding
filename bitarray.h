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
	std::vector<std::bitset<BITSET_SIZE>*> bitsets;
	std::bitset<BITSET_SIZE>* current;
	unsigned short localSize;
	unsigned int totalSize;
public:
	BitArray();
	BitArray(const int& value, unsigned int length);
	explicit BitArray(std::string& bits);
	BitArray(const bool* bits, const unsigned int& size);
	
	~BitArray();
	
	void pushBack(const bool& one);
	void pushBack(const unsigned char& byte);
	void pushBack(const std::string& one);
	void setBit(const unsigned int& pos, bool one);
	bool getBit(const unsigned int& pos) const;
	
	void addBit(const unsigned int& position);
	void add(unsigned int value);
	void add(const BitArray& value);
	
	char readByte(const unsigned int& position);
	
	inline const unsigned int& getSize() const {
		return totalSize;
	}
	const std::string toString() const;
private:
	void updateSize();
};

std::ostream& operator<< (std::ostream& stream, const BitArray& array);
