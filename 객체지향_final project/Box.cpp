#include "Box.h"
#include "View.h"

void Box::paintBox(char color) {
	View::fillBox(x, y, x + width, y + height, color);
}
