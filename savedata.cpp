#include <iostream>
#include <fstream>
#include "matrix.h"
using namespace std;

int main()
{
	matrix store(50,50);
	for(unsigned i=0; i<50; i++)
		for(unsigned j=0; j<50; j++)
			store.setvalue(i,j,i+j);
	ofstream myfile;
	myfile.open("data.txt");
	if(myfile.is_open())
	{
		for(unsigned i=0; i<50; i++)
		{
		    for(unsigned j=0; j<50; j++)
		    {
		    	if(j==49)
		          myfile<<store.getvalue(i,j);
		    	else
			      myfile<<store.getvalue(i,j)<<",";
		    }
		    myfile<<";\n";
	    }
		myfile.close();
	}
	else cout<<"Unable to open file";
	return 0;
}