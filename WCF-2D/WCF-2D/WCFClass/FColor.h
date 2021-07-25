#pragma once
class FColor
{
public:
	FColor() :R(0), G(0), B(0) {};
	FColor(int r, int g, int b) :R(r), G(g), B(b) {};
	FColor(int val) :R(val), G(val), B(val) {};
	~FColor();
	int R, G, B;
};