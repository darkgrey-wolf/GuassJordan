#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include <cmath>
#include "drawing.h"
#define XDEFSIZE 7
#define YDEFSIZE 7
#define XSPACE 2
#define YSPACE 11
#define XSPACE2 51
#define YSPACE2 11
#define XDIALOG 1
#define YDIALOG 9
#define XDIALOG2 1
#define YDIALOG2 24
#define XDIALOG3 120
using namespace std;
using namespace LimT_Drawing;
int cinInteger(int,int,int,int);
double input();
double calcDisp(double[][YDEFSIZE],int);
double fixMatrix(double[][YDEFSIZE],int,int);
double dispMatrix(double[][YDEFSIZE],int);
double dispMatrix2(double[][YDEFSIZE],int);//dispMatrix and dispMatrix2 differs only in cooridnates
void border();
void init();
int main()
{
	system("color f0");
	system("mode con: cols=150 lines=31");
	border();
	init();
	return 0;
}
void init()
{
	input();
	pnt(XDIALOG,YDIALOG); cout <<"Press ENTER to input another or ESC to exit.";
	switch(getch())
	{
		case 13: pnt(XDIALOG,YDIALOG); cout <<"                                             ";
		         EraseBoxMass(XSPACE-1,YSPACE-1,50,14);
						 init(); 
						 break;
		case 27: return;
	}
}
double input()
{
	double mat[XDEFSIZE][YDEFSIZE];
	int unknowns,a,b,k,l;
	pnt(XDIALOG,YDIALOG); cout <<"Input number of unknowns: ";
	                      unknowns= cinInteger(1,5,XDIALOG+26,YDIALOG);
	CreateBox(XSPACE-1,YSPACE-1,unknowns*10,unknowns*2+2);
	for(k=0,a=XSPACE,b=YSPACE;k<unknowns;k++)
	{
		for(l=0;l<unknowns+1;l++)
		{
			pnt(a,b); cin>>mat[k][l];
			a+=10;
		}
		a=XSPACE;
		b+=2;
	}
	pnt(XDIALOG2,YDIALOG2); cout <<"Press any key to continue...";
	getch(); 
	pnt(XDIALOG,YDIALOG); cout <<"                               ";
	pnt(XDIALOG,YDIALOG); cout <<"Matrix";
	dispMatrix2(mat,unknowns);
	getch();
	calcDisp(mat,unknowns);
	EraseBoxMass(XSPACE-1,YSPACE-2,148,16);
	CreateBox(XSPACE-1,YSPACE-1,unknowns*10,unknowns*2+2);
	pnt(XDIALOG,YDIALOG); cout <<"Final Answer: ";
	for(a=XSPACE,b=YSPACE,k=0;k<unknowns;k++)
	{
		pnt(a,b); cout <<"X" <<k+1 <<" = " <<mat[k][unknowns];
		b+=2;
	}
}
double calcDisp(double matrix[][YDEFSIZE],int equations)
{
	int k,l,m,n;
	double cache;//phew! took hours to notice that this must be double and not int
	int rows=equations;
	int columns=equations+1;
	start:
	pnt(XDIALOG,YDIALOG); cout <<"Previous Matrix";
	//lower triangle
		//Note: the actual dimensions of matrix is matrix[equation-1][equation]
	//                                        or matrix[row-1][column-1]
	for(k=0;k<equations;k++) //grand loop ensures equation k
	{	//here the diagonal element is matrix[k][k]
		for(l=k;l<rows;l++)//second loop to traverse the rows
		{
			if(l==k)
			{
				if(matrix[k][k]==0)
				{
					fixMatrix(matrix,k,equations); 
					//dispMatrix2(matrix,equations);
					//getch();
					goto start;
				}
				else 
				cache=1.0/matrix[k][k];
				//dispMatrix2(matrix,equations);
				//pnt(XDIALOG3,YDIALOG);cout <<"DIAGONAL IS: " <<matrix[k][k];
				//pnt(XDIALOG3,YDIALOG+1);cout <<"RECIPROCAL: " <<cache;
				//pnt(XDIALOG3,YDIALOG+2);cout <<" k= " <<k;
				//pnt(XDIALOG3,YDIALOG+3);cout <<" l= " <<l;
				for(m=k;m<columns;m++) 
					matrix[k][m]=matrix[k][m]*cache;	
				//dispMatrix(matrix,equations);
				//getch();
				//EraseBoxMass(XDIALOG3,YDIALOG,27,8);
			}
			else if(l>k)
			{  
					//pnt(XDIALOG3,YDIALOG);cout <<"DIAGONAL IS: " <<matrix[k][k];				
					//pnt(XDIALOG3,YDIALOG+3);cout <<" k= " <<k;
					//pnt(XDIALOG3,YDIALOG+4);cout <<" l= " <<l;
				for(m=0;m<columns;m++)
				{
					//dispMatrix2(matrix,equations);
					if(m==k)
					{		
						cache=matrix[l][k]/matrix[k][k];
						//pnt(XDIALOG3,YDIALOG+2);cout <<"CACHE IS: " <<cache;	
					}
					//pnt(XDIALOG3,YDIALOG+1); cout <<"Picked element:   ";
					//pnt(XDIALOG3+16,YDIALOG+1); cout <<matrix[l][m];
					matrix[l][m]=matrix[l][m]-cache*matrix[k][m];	
					//dispMatrix(matrix,equations);
					//getch();
				}
				//EraseBoxMass(XDIALOG3,YDIALOG,27,8);
			}
		}
	}
	//upper triangle                             
	for(k=1;k<equations;k++) //start with the second equation:k=1
	{
		//traverse the row from second to the last equation
		for(l=1;l<rows;l++) 
		{
			//travere the row from first to equation l
			for(m=0;m<l;m++) 
			{
				if(m!=l)
				{
					cache=matrix[m][l]/matrix[l][l];
					//EraseBoxMass(XDIALOG3,YDIALOG,27,8);
					//pnt(XDIALOG3,YDIALOG);cout <<"DIAGONAL IS: " <<matrix[l][l];
					//pnt(XDIALOG3,YDIALOG+2);cout <<"CACHE IS: " <<cache;
					for(n=k;n<columns;n++)
					{
						//dispMatrix2(matrix,equations);
						//pnt(XDIALOG3,YDIALOG+1); cout <<"Picked element:    ";
						//pnt(XDIALOG3+16,YDIALOG+1); cout <<matrix[m][n];	
						matrix[m][n]=matrix[m][n]-cache*matrix[l][n];
						//dispMatrix(matrix,equations);
						//getch();
					}
					//EraseBoxMass(XDIALOG3,YDIALOG,27,8);
				}
			}
		}
	}
	pnt(XDIALOG2,YDIALOG2); cout <<"Press any key to view final answer...";
	getch();
}
double fixMatrix(double matrix[][YDEFSIZE],int eq, int unknown)
{
	pnt(XDIALOG3-3,YDIALOG+1); cout <<"Fixing matrix..";
	int k,l;
	double cache; //and it happened again..
	for(k=eq;k<unknown;)
	{
		pnt(XDIALOG3-3,YDIALOG+2); cout <<"checing row number " <<k;
		if(matrix[k][eq]==0) 
		{
			++k;
			getch();
			continue;
		}
		else
		{
			pnt(XDIALOG3-3,YDIALOG+3); cout <<"Found equation " <<k;
			cache=1.0/matrix[k][eq];
			break;
		}
	}
	for(l=0;l<unknown+1;l++)
	{
		matrix[eq][l]=matrix[eq][l]+cache*matrix[k][l];
	}
	pnt(XDIALOG3-3,YDIALOG+1); cout <<"Matrix diagonal fixed.";
	getch();
	EraseBoxMass(XDIALOG3-4,YDIALOG,31,5);
}
double dispMatrix(double matrix[][YDEFSIZE],int equations)
{
	int x,y,k,l;
	x=XSPACE+equations*10+12;
	y=YSPACE2;
	CreateBox(XSPACE+equations*10+12-1,YSPACE2-1,equations*10,equations*2+2);
	for(k=0;k<equations;k++)
	{
		for(l=0;l<equations+1;l++)
		{
			pnt(x,y); cout <<"        ";
			pnt(x,y); cout <<noshowpoint <<matrix[k][l];
			x+=10;
		}
		x=XSPACE+equations*10+12;
		y+=2;
	}
}
double dispMatrix2(double matrix[][YDEFSIZE],int equations)
{
	int x,y,k,l;
	CreateBox(XSPACE-1,YSPACE-1,equations*10,equations*2+2);
	for(x=XSPACE,y=YSPACE,k=0;k<equations;k++)
	{
		for(l=0;l<equations+1;l++)
		{
			pnt(x,y); cout <<"        ";
			pnt(x,y); cout <<noshowpoint <<matrix[k][l];
			x+=10;
		}
		x=XSPACE;
		y+=2;
	}
}
int cinInteger(int lower, int upper, int x, int y)
{
	string input;
	int k,num;
	bool valid;
	while(1)
	{
		valid=true;
		cin.sync();
		pnt(x,y); cout <<"                                       ";
		pnt(x,y); cin >>input;
		for(k=0;k<input.length();k++)
		{
			if(!isdigit(input[k])) valid=false;
		}
		if(valid==true)
		{
			stringstream(input) >>num;
			if(num>=lower&&num<=upper) return num;
		}
		else continue;
	}
}
void border()
{
	CreateBox(0,0,150,30);
	hzline(0,3,150); hzline(0,8,150);
	hzline(0,25,150); vtline(75,25,4);
	pnt(0,3);  cout <<char(204);pnt(149,3); cout <<char(185);
	pnt(0,8);  cout <<char(204);pnt(149,8); cout <<char(185);
	pnt(0,25); cout <<char(204);pnt(149,25);cout <<char(185);
	pnt(75,25);cout <<char(203);pnt(75,29); cout <<char(202);
	pnt(63,1); cout <<"University of Mindanao";
	pnt(63,2); cout <<"College of Engineering";
	pnt(53,4); cout <<"First Term, First Semester, S.Y. 2015-2016";
	pnt(46,5); cout <<"EDP 5/L - Computer Fundamentals and Programming for CpE";
	pnt(67,6); cout <<"Plate Number: 5";
	pnt(58,7); cout <<"Title: Gauss Jordan Elimination";
	pnt(2,26); cout <<"Programmed by:";pnt(2,27);cout <<"Lim, Tito Jr. C.";
	pnt(76,26);cout <<"Submitted to:"; pnt(76,27);cout <<"Engr R.S. Pangantihon";
	pnt(2,28); cout <<"Note: 1 to 5 unknowns only.";
	pnt(1,1);
}
