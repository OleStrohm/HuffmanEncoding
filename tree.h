//
// Created by Ole on 10.09.2017.
//

#pragma once

#include "node.h"
#include "bitarray.h"
#include <vector>
#include <map>

std::string addOne(const std::string& string);

class Tree {
private:
	Node* root;
	std::map<std::string, std::string> codes; // (symbol, code)
public:
	explicit Tree(std::vector<Leaf*>& data);
	Tree(const std::string* symbols, const unsigned int* lengths, const unsigned int& size);
	~Tree();
	
	std::string uncompress(std::string compressed);
	std::string uncompress(const BitArray& compressed);
	
	BitArray compress(const std::string& uncompressed);
	
	void print();
private:
	void saveCodes();
};


