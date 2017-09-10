//
// Created by Ole on 10.09.2017.
//

#include "tree.h"

#include <iostream>

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

Tree::~Tree() {
	delete root;
}

std::string Tree::uncompress(std::string compressed) {
	if(!root->internal)
		return "";
	
	Node* current = root;
	std::string uncompressed;
	
	for (char c : compressed) {
		if (c == '0')
			current = ((InternalNode*)current)->getChild0();
		else if (c == '1')
			current = ((InternalNode*)current)->getChild1();
		
		if(!current->internal) {
			uncompressed += ((Leaf*)current)->getSymbol();
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
			current = ((InternalNode*)current)->getChild1();
		else
			current = ((InternalNode*)current)->getChild0();
		
		if(!current->internal) {
			uncompressed += ((Leaf*)current)->getSymbol();
			current = root;
		}
	}
	
	return uncompressed;
}

BitArray Tree::compress(const std::string& uncompressed) {
	BitArray a;
	for(char c : uncompressed) {
		std::string s = "";
		s += c;
		a.pushBack(codes[s]);
	}
	return a;
}

void Tree::print() {
	root->print("");
}

void Tree::saveCodes() {
	root->saveCode(codes, "");
}