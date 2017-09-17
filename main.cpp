


#include <iostream>

#include "tree.h"
#include "bitarray.h"

int main() {
//	std::string symbols[] = {
//			"A", "B", "C", "D", "E", "F", "G", "H"
//	};
//
//	unsigned int lengths[8];
//	lengths[0] = 2;
//	lengths[1] = 4;
//	lengths[2] = 4;
//	lengths[3] = 4;
//	lengths[4] = 4;
//	lengths[5] = 3;
//	lengths[6] = 3;
//	lengths[7] = 2;
//
//	Tree fromLengths(symbols, lengths, 8);
//	std::cout << std::endl;
//	fromLengths.print();
//
//	std::cout << std::endl;
//	std::cout << fromLengths.uncompress("1110001100") << std::endl;
	
	std::string pngSymbols[288];
	unsigned int pngLengths[288];
	for(unsigned int i = 0; i < 288; i++) {
		pngSymbols[i] = std::to_string(i);
		if(i <= 143) {
			pngLengths[i] = 8;
		} else if(i <= 255) {
			pngLengths[i] = 9;
		} else if(i <= 279) {
			pngLengths[i] = 7;
		} else {
			pngLengths[i] = 8;
		}
	}
	
	Tree pngTree(pngSymbols, pngLengths, 288);
	pngTree.print();
	
	unsigned int end; // 1111100001100 11001111 1111100001100
	std::cout << pngTree.uncompressOneCode("0011000011111111100110000001111001111", 0, end) << std::endl;
	std::cout << pngTree.uncompressOneCode("0011000011111111100110000001111001111", end, end) << std::endl;
	std::cout << pngTree.uncompressOneCode("0011000011111111100110000001111001111", end, end) << std::endl;
	std::cout << pngTree.uncompressOneCode("0011000011111111100110000001111001111", end, end) << std::endl;
	std::cout << pngTree.uncompressOneCode("0011000011111111100110000001111001111", end, end) << std::endl;
	std::cout << "Ended at: " << end << std::endl;
	
	return 0;
}