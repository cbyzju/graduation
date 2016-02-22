

#include <iostream>
#include "matrix.h"
#include "binary.h"


// time comlexity: O(N^2).
matrix& binary(matrix& image, int& pointNum, int& center_horizon, int& center_vertical)
{
	pointNum=0;
	center_horizon=0;
	center_vertical=0;
    int colmnSum=0;
    int min=image.height();

	for(unsigned j=0; j< image.width(); j++)
	{
	    for(unsigned i=0; i< image.height(); i++)
	    {		
			if(image.getvalue(i,j)<50)  //  this threshold should be modified to be optimal.
			{ 
				image.setvalue(i,j,0);				
				if(i>30 && i<image.height()-30 && j>30 && j<image.width()-30)
				{
					pointNum++; // the sum of black point in the image, and tell wether the pupil exists according to this value.
					colmnSum++;
				}
			}
			else
			{
				image.setvalue(i,j,1);
			}
		}

		if(colmnSum<min)  // find the horizon coodinate of rough center.
		{
				min=colmnSum;
				center_horizon=j;
		}
	}

	for(int i=image.height()-30; i>30; i--)
	{
		//  this threshold should be modified to be optimal.
		if(image.getvalue(i,center_horizon)==0 &&  image.getvalue(i+30,center_horizon)==0 && image.getvalue(i-30,center_horizon)==0)
			center_vertical=i;
	}

	return image;
}