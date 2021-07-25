#pragma once
#include "FColor.h"
#include <string>
#include <vector>
using namespace std;
struct FSprite4X4
{
	FSprite4X4(
		const FColor& p0,
		const FColor& p1,
		const FColor& p2,
		const FColor& p3,
		const FColor& p4,
		const FColor& p5,
		const FColor& p6,
		const FColor& p7,
		const FColor& p8,
		const FColor& p9,
		const FColor& p10,
		const FColor& p11,
		const FColor& p12,
		const FColor& p13,
		const FColor& p14,
		const FColor& p15
	)
	{
		ImageData = new vector<FColor>();
		ImageData->push_back(p0); ImageData->push_back(p1); ImageData->push_back(p2); ImageData->push_back(p3);
		ImageData->push_back(p4); ImageData->push_back(p5); ImageData->push_back(p6); ImageData->push_back(p7);
		ImageData->push_back(p8); ImageData->push_back(p9); ImageData->push_back(p10); ImageData->push_back(p11);
		ImageData->push_back(p12); ImageData->push_back(p13); ImageData->push_back(p14); ImageData->push_back(p15);
	}
	vector<FColor>* ImageData;
};