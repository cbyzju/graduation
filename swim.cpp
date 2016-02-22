
#include <math.h>
#include "matrix.h"
#include "swim.h"

#define PI 3.1415926

using namespace std;

matrix swim(const matrix& binary, int& center_horizon, int& center_vertical)
{
	int degree=6; //swim outside every 6 degrees around the circle.
	matrix cood(360/degree, 2);
	int count=0;
	int r=6;
	int x_cood=0;//vertical direction.
	int y_cood=0;//horizontal direction.
	for(int angle=0; angle<360; angle=angle+degree)
	{
		x_cood=center_vertical-round(r*sin(angle*PI/180));
		y_cood=center_horizon+ round(r*cos(angle*PI/180));
		while(x_cood>0  && x_cood<binary.width() && y_cood>0 && y_cood<binary.height() && binary.getvalue(x_cood, y_cood)<1)
		{
			r++;
			x_cood=center_vertical-round(r*sin(angle*PI/180));
		    y_cood=center_horizon+ round(r*cos(angle*PI/180));
		}
        cood.setvalue(count, 0, x_cood);
        cood.setvalue(count, 1, y_cood);
		count++;
	}

	return cood;
}