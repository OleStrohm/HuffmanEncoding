//
// Created by Ole on 10.09.2017.
//

#include "tree.h"

#include <iostream>

std::string addOne(const std::string& string) {
	std::string out;
	bool carry = true;
	for (int i = (int) string.size() - 1; i >= 0; i--) {
		char c = string.at(i);
		if (c == '1') {
			if (carry) {
				out.insert(0, 1, '0');
				carry = true;
			} else {
				out.insert(0, 1, '1');
				carry = false;
			}
		} else {
			if (carry) {
				out.insert(0, 1, '1');
				carry = false;
			} else {
				out.insert(0, 1, '0');
				carry = false;
			}
		}
	}
	return out;
}

Tree::Tree(std::vector<Leaf*>& data) {
	if (data.empty())
		return;
	std::vector<Leaf*> leaves;
	leaves.reserve(data.size());
	
	for (auto current : data) {
		auto pos = leaves.begin();
		auto end = leaves.end();
		while (pos != end) {
			if (current->getFrequency() >= (*pos)->getFrequency()) {
				break;
			}
			pos++;
		}
		leaves.insert(pos, current);
	}
	
	std::vector<InternalNode*> internalNodes;
	
	while (leaves.size() + internalNodes.size() > 1) {
		Node* node0;
		Node* node1;
		
		if (!leaves.empty()) {
			if (!internalNodes.empty()) {
				if (leaves.back()->getFrequency() <= internalNodes.back()->getFrequency()) {
					node0 = leaves.back();
					leaves.pop_back();
				} else {
					node0 = internalNodes.back();
					internalNodes.pop_back();
				}
			} else {
				node0 = leaves.back();
				leaves.pop_back();
			}
		} else {
			node0 = internalNodes.back();
			internalNodes.pop_back();
		}
		
		if (!leaves.empty()) {
			if (!internalNodes.empty()) {
				if (leaves.back()->getFrequency() <= internalNodes.back()->getFrequency()) {
					node1 = leaves.back();
					leaves.pop_back();
				} else {
					node1 = internalNodes.back();
					internalNodes.pop_back();
				}
			} else {
				node1 = leaves.back();
				leaves.pop_back();
			}
		} else {
			node1 = internalNodes.back();
			internalNodes.pop_back();
		}
		
		internalNodes.insert(internalNodes.begin(), new InternalNode(node0, node1));
	}
	
	root = internalNodes.back();
	saveCodes();
}

Tree::Tree(const std::string* symbols, const unsigned int* lengths, const unsigned int& size) {
	unsigned int longestCode = 0;
	for (unsigned int i = 0; i < size; i++) {
		if (longestCode < lengths[i])
			longestCode = lengths[i];
	}
//	std::cout << "longest: " << longestCode << std::endl;
	
	std::vector<unsigned int> numCodesOfLength;
	numCodesOfLength.reserve(longestCode + 1);
	for (unsigned int i = 0; i < longestCode + 1; i++) {
		numCodesOfLength.push_back(0);
	}
	
	for (unsigned int i = 0; i < size; i++) {
		numCodesOfLength[lengths[i]]++;
	}

//	for (unsigned int i = 1; i <= longestCode; i++) {
//		std::cout << "codes of length " << i << ": " << numCodesOfLength[i] << std::endl;
//	}
	
	std::vector<BitArray*> firstCode;
	firstCode.reserve(longestCode + 1);
	firstCode.push_back(new BitArray(0, 0));
	for (unsigned int i = 1; i < longestCode + 1; i++) {
		unsigned int code = 0;
		code += firstCode[i - 1]->read(0, i - 1);
		code += numCodesOfLength[i - 1];
		code <<= 1;
		firstCode.push_back(new BitArray(code, i));
	}

//	for (int c = 1; c <= longestCode; c++) {
//		std::cout << firstCode[c] << std::endl;
//	}
	
	std::vector<BitArray*> actualCodes;
	actualCodes.reserve(size);
	for (unsigned int s = 0; s < size; s++) {
		unsigned int length = lengths[s];
		BitArray* code = new BitArray(firstCode[length]->read(0, length), length);
		firstCode[length]->addBit(0);
		actualCodes.push_back(code);
	}
	
//	for (unsigned int s = 0; s < size; s++) {
//		std::cout << symbols[s] << ": " << actualCodes[s] << std::endl;
//	}
	
	root = new InternalNode(nullptr, nullptr);
	BitArray start;
	createTree(actualCodes, symbols, root, start);
//	std::cout << "Finished!";
}

void Tree::createTree(const std::vector<BitArray*>& codes, const std::string* symbols, Node* parent, const BitArray& curCode) {
	BitArray next0(curCode);
	next0.pushFront((bool) 0);
	bool leaf = false;
	unsigned int i = 0;
	for (; i < codes.size(); i++) {
		if ((*codes[i]) == next0) {
			leaf = true;
			break;
		}
	}
	if (leaf)
		((InternalNode*) parent)->setChild0(new Leaf(symbols[i], 0));
	else {
		InternalNode* internal0 = new InternalNode(nullptr, nullptr);
		((InternalNode*) parent)->setChild0(internal0);
		createTree(codes, symbols, internal0, next0);
	}
	
	BitArray next1(curCode);
	next1.pushFront((bool) 1);
	leaf = false;
	i = 0;
	for (; i < codes.size(); i++) {
		if ((*codes[i]) == next1) {
			leaf = true;
			break;
		}
	}
	if (leaf)
		((InternalNode*) parent)->setChild1(new Leaf(symbols[i], 0));
	else {
		InternalNode* internal1 = new InternalNode(nullptr, nullptr);
		((InternalNode*) parent)->setChild1(internal1);
		createTree(codes, symbols, internal1, next1);
	}
}

Tree::~Tree() {
	if (root)
		delete root;
}

std::string Tree::uncompress(const std::string& compressed) {
	if (!root->internal)
		return "";
	
	Node* current = root;
	std::string uncompressed;
	
	for (char c : compressed) {
		if (c == '0')
			current = ((InternalNode*) current)->getChild0();
		else if (c == '1')
			current = ((InternalNode*) current)->getChild1();
		
		if (!current->internal) {
			uncompressed += ((Leaf*) current)->getSymbol();
			current = root;
		}
	}
	
	return uncompressed;
}

std::string Tree::uncompress(const BitArray& compressed) {
	Node* current = root;
	std::string uncompressed;
	
	for (unsigned int index = 0; index < compressed.getSize(); index++) {
		if (compressed.getBit(index))
			current = ((InternalNode*) current)->getChild1();
		else
			current = ((InternalNode*) current)->getChild0();
		
		if (!current->internal) {
			uncompressed += ((Leaf*) current)->getSymbol();
			current = root;
		}
	}
	
	return uncompressed;
}

std::string Tree::uncompressOneCode(const std::string& compressed, const unsigned int& start, unsigned int& end) {
	Node* current = root;
	std::string code;
	
	for (unsigned int i = 0; true; i++) {
		const char c = compressed.at(start + i);
		if (c == '0')
			current = ((InternalNode*) current)->getChild0();
		else if (c == '1')
			current = ((InternalNode*) current)->getChild1();
		
		if (!current->internal) {
			end = start + i;
			return ((Leaf*) current)->getSymbol();
		}
	}
}

BitArray* Tree::compress(const std::string& uncompressed) {
	BitArray* a = new BitArray();
	for (char c : uncompressed) {
		std::string s = "";
		s += c;
		a->pushBack(codes[s]);
	}
	return a;
}

void Tree::print() {
	root->print("");
}

void Tree::saveCodes() {
	root->saveCode(codes, "");
}