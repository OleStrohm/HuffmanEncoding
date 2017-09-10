


#include <iostream>

#include "tree.h"
#include "bitarray.h"

int main() {
	std::vector<Leaf*> originData = {
			new Leaf("A", 1),
			new Leaf("E", 5),
			new Leaf("B", 5),
			new Leaf("F", 5),
			new Leaf("G", 5),
			new Leaf("C", 4),
			new Leaf("M", 4),
			new Leaf("D", 13)
	};
	
	Tree tree(originData);
	
	tree.print();
	
	std::string comp = "111010010";
	BitArray data(comp);
	std::cout << comp << " -> " << tree.uncompress(data) << std::endl;
	std::cout << "DAB" << " -> " << tree.compress("DAB");
	return 0;
}

std::map<std::string, int> analyseText() {

}