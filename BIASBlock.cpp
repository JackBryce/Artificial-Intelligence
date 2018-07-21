#include "BIASBlock.h";

BIASBlock::BIASBlock(int nextLayerSize) {
	if (nextLayerSize == 0) {
		for (int i = 0; i < nextLayerSize; i++) {
			weightsFoward.push_back(Connection());
			weightsFoward.back().weight = rand() / RAND_MAX;
		}
	} else {
		weightsFoward.push_back(Connection());
		weightsFoward.back().weight = 1.0;
	}
}