#include <iostream>
#include <string>
using namespace std;

class Point {
private:
	int x;
	int y;

public:
	
	void Pointe(int x1, int y1) {
		x = x1;
		y = y1;
	}

	void distance(class Point p){
		int xy = sqrt(pow((p.x - x), 2) + pow((p.y - y), 2));
		printf("%d\n", xy);
	}
	void compare(class Point p) {
		if (x == p.x && y == p.y) {
			printf("Meme coordonnee\n");
		}
		else {
			printf("pas la meme coordonnee\n");
		}
	}
};

int main() {
	Point point1, point2;
	point1.Pointe(5, 10);
	point2.Pointe(8, 3);
	point1.distance(point2);
	point1.compare(point2);

	return 0;
}