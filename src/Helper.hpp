#ifndef HELPER_H
#define HELPER_H
#define WIDTH 10
#define HEIGHT 20
class Color{
public:
	Color(int red, int blue, int green):red(red), blue(blue), green(green){}
	Color():Color(0,0,0){}

	int red;
	int blue;
	int green;
};

class Position{
public:
	Position():Position(0,0){}
	Position(int x, int y): x(x), y(y){}
	int x, y;
};
#endif
