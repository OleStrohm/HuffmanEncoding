


#include <iostream>

#include "tree.h"
#include "bitarray.h"

int main() {
//	std::vector<Leaf*> originData = {
//			new Leaf("A", 1),
//			new Leaf("B", 5),
//			new Leaf("C", 4),
//			new Leaf("D", 13),
//			new Leaf("E", 5),
//			new Leaf("F", 5),
//			new Leaf("G", 5),
//			new Leaf("H", 4),
//	};
//
//	Tree tree(originData);
//
//	tree.print();
//	std::cout << "\n\n";
//	std::cout << "\n\n";
//
//	std::string comp = "111010001";
//	BitArray data(comp);
//	std::cout << comp << " -> " << tree.uncompress(data) << std::endl;
//	std::cout << "DAB" << " -> " << tree.compress("DAB");
	
	std::string symbols[] = {
			"A", "B", "C", "D", "E", "F", "G", "H"
	};
	
	unsigned int lengths[] {
			4, 3, 4, 2, 3, 3, 3, 3
	};
	
	BitArray intB;
	intB.pushBack((unsigned char) 17);
	std::cout << "\n" << intB;
//	BitArray intB2(2, 4);
//	std::cout << "\n" << intB2;
//	intB.add(intB2);
//	std::cout << "\n" << intB;
	
	//Tree treeS(symbols, lengths, 8);
	//tree.print();
	
	return 0;
}

std::map<std::string, int> analyseText() {

}