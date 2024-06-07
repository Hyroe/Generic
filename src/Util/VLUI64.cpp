#include "Generic/Util/VLUI64.h"
#include <cmath>

void Generic::VLUI64::set(std::uint64_t bitIndex){
	std::uint64_t bitValue = pow(2, bitIndex % 64);
	int wordToSet = bitIndex / 64;
	words[wordToSet] = words[wordToSet] | bitValue;
}

void Generic::VLUI64::clear(std::uint64_t bitIndex){
	int wordToClear = bitIndex / 64;
	words[wordToClear] = words[wordToClear] & ~(int)pow(2, bitIndex % 64);
	if (words[wordToClear] == 0)
		words.erase(wordToClear);
}