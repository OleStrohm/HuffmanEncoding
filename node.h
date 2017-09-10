//
// Created by Ole on 10.09.2017.
//

#pragma once

#include <string>
#include <utility>
#include <iostream>
#include <map>

class Node {
public:
	bool internal;
private:
	unsigned int frequency;
public:
	Node(unsigned int frequency, bool internal = true)
			: frequency(frequency), internal(internal) {}
	
	virtual ~Node() = default;
	
	virtual void print(const std::string&) {}
	virtual void saveCode(std::map<std::string, std::string>& codes, std::string code) {}
	
	inline const unsigned int& getFrequency() const {
		return frequency;
	}
};

class InternalNode : public Node {
private:
	Node* child0;
	Node* child1;
public:
	InternalNode(Node* child0, Node* child1)
			: Node(child0->getFrequency() + child1->getFrequency()), child0(child0), child1(child1) {}
	
	~InternalNode() override {
		delete child0;
		delete child1;
	}
	
	void print(const std::string& msg) override {
		child0->print(msg + "0");
		child1->print(msg + "1");
	}
	
	void saveCode(std::map<std::string, std::string>& codes, std::string code) override {
		child0->saveCode(codes, code + "0");
		child1->saveCode(codes, code + "1");
	}
	
	inline Node* getChild0() const { return child0; }
	inline Node* getChild1() const { return child1; }
};

class Leaf : public Node {
	std::string symbol;
public:
	Leaf(std::string symbol, unsigned int frequency)
			: Node(frequency, false), symbol(std::move(symbol)) {}
	
	void print(const std::string& msg) override {
		std::cout << symbol << ": " << msg << std::endl;
	}
	
	void saveCode(std::map<std::string, std::string>& codes, std::string code) override {
		codes[symbol] = code;
	}
	
	inline const std::string& getSymbol() const {
		return symbol;
	}
};

