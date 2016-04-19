#ifndef HELPER_H
#define HELPER_H
#define WIDTH 8
#define HEIGHT 20
enum Direction {Left, Right, Rotate_CC, Rotate_CW, Descend};
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
