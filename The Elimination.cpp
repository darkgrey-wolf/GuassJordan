/*
	Name: Lim, Tito Jr. C.
	Subject: EDP5/L
*/
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cmath>
#include <windows.h>
using namespace std;
void gotoxy(int,int);
void border();
void vertical(int);
void horizontal();
int k,l,m;
int main()
{
	system("cls"); system("color f0");border();
	
	int n,a,b,c,key;
  long double x[6],mat[10][10],cache,cache2;
	gotoxy(31,9);cout <<"G A U S S I A N   E L I M I N A T I O N";
	gotoxy(33,10); cout <<"How many variables do you have?:"; cin>>n;
	//Input data in a two dimensional matrix
	for(k=0,a=32,b=12;k<n;k++) //loop for row
		{ //if there are n variables, there are n rows
			for(l=0;l<n+1;l++)//loop for columns
			{ // if there are n variables, there are n+1 columns
			
			  // this part is just for display stuff
				if(l==n) {	gotoxy(a-5,b);cout <<char(186);
				gotoxy(a-5,b+1);cout <<char(186);gotoxy(a,b);}
				gotoxy(a,b);
				//input data
				cin >>mat[k][l]; a+=10;
			}b+=2; a=32;	
		}
	fixed:
	//loop for the lower triangle
	for(m=0;m<n;m++) //Grand step (repeats n times)
	{
		//this loop will ensure equation 'm' as basis
		//of the grand step
		for(k=m;k<n;k++)//row-by-row step (repeats n times)
		{
			//this loop will traverse different equations (equation k)
			// equation k can be m itself or other equation
			// the index [m][m] is the diagonal element of m
			if(mat[m][m]!=0) // if the diagonal of m is not zero, do this
			{
				//store the reciprocal of the diagonal
				cache = 1/mat[m][m]; 
				for(l=m;l<n+1;l++) //this will traverse 1 row up to the last column
					mat[m][l] = cache*mat[m][l]; //multiply the element with the reciprocal
					if(k>m) //if its in other equation
					{
						for(l=0;l<n+1;l++)
						{
							if(l==m) //if its in the diagonal, store the 'factor'
							// the factor is the diagonal of k divided by diagonal of m
							cache = mat[k][l] / mat[m][m]; //this is the factor
						 /*
						    get equation m and multiply each element by the 'factor'
						    subract equation k with equation m;
						    do this column-by-column	 
						 */
							mat[k][l] = mat[k][l] - (cache*mat[m][l]);
							// the first element of equation k will be zero.
							// the rest will follow with different value
						}
						/*
						   NOTE: at m=2 or any number, the processes will no longer include
						   the first elements since they are already zero.
						*/
				}
			}
			else 
			{
				for(a=1;a<n;a++)
				{
					if(mat[m+a][m]==0) continue;
					else cache = 1/mat[m+a][m];
					for(l=m;l<n+1;l++) mat[m][l] += mat[m+a][l]*cache;
					goto fixed;
				}
			}
		}
	}
	//loop for the upper triangle
	for(m=1;m<n;m++) //Grand step
	{
		for(k=1;k<=m;k++)
		{
			for(a=1;a<=k;a++)
			{
				for(l=k;l<=n;l++)
				{
					if(l==k)
						cache2 = mat[k-a][l] / mat[k][l];
					mat[k-a][l] = mat[k-a][l] - (mat[k][l]*cache2);
				}
			}
		}
	}
	gotoxy(40,b+2);cout <<"Reduced Echelon Form: ";
	for(k=0,a=32,b+=4;k<n;k++)
	{
		for(l=0;l<n+1;l++)
		{
			if(l==n) {gotoxy(a-5,b);cout <<char(186);
					gotoxy(a-5,b+1);cout <<char(186);gotoxy(a,b);}
			gotoxy(a,b);cout <<mat[k][l]; a+=10;
		} b+=2;a=32;
	}
	view:
	gotoxy(28,31); cout <<"Press <ENTER> to view the answers..."; key=getch();
	if(key!=13) goto view;
	system("cls"); border(); b=14;
	gotoxy(47,b); cout <<"Answers: ";
	for(l=0,a=44,b+=4;l<n;l++)
	{gotoxy(a,b); cout <<"X" <<l+1<<"    =    " <<mat[l][n]; b+=1;}
	ask: gotoxy(28,31);cout <<"Press <ENTER> to input another <ESC> to exit."; key=getch();
	if(key==13) main(); else if(key==27) return 0; else goto ask;	
}
void border()
{
	for(k=0;k<=35;k++)vertical(k); gotoxy(0,0);
	cout <<(char)201; horizontal();horizontal();cout <<(char)187;gotoxy(0,3);
	cout <<(char)204; horizontal();horizontal();cout <<(char)185; gotoxy(0,8);
	cout <<(char)204; horizontal();horizontal();cout <<(char)185; gotoxy(0,32);
	cout <<(char)204; horizontal();cout <<'\b' <<(char)203;horizontal(); cout <<(char)185;
	for(m=33;m<=34;m++)
	{for(l=0;l<=99;l++)if(l==0||l==49||l==99){ gotoxy(l,m); cout <<(char)186;}} gotoxy(0,35);
	cout <<(char)200; horizontal();cout <<'\b' <<(char)202;horizontal(); cout <<(char)188;
	gotoxy(39,1); cout <<"University of Mindanao";gotoxy(39,2); cout <<"College of Engineering";
	gotoxy(29,4); cout <<"First Term, First Semester, S.Y. 2015-2016";
	gotoxy(23,5); cout <<"EDP 5/L - Computer Fundamentals and Programming for CpE";
	gotoxy(42,6); cout <<"Plate Number: 1";
	gotoxy(31,7); cout <<"Title: Addition of Two or More Matrices";
	gotoxy(2,33); cout <<"Programmed by:";gotoxy(2,34);cout <<"Lim, Tito Jr. C.";
	gotoxy(52,33);cout <<"Submitted to:";gotoxy(52,34);cout <<"Engr R.S. Pangantihon"; gotoxy(1,9);
}
void horizontal() {for(l=1;l<=49;l++) cout <<(char)205;}
void vertical(int y){  for(l=0;l<=99;l++){ if(l==0||l==99) {gotoxy(l,y);cout <<(char)186;} }  }
void gotoxy(int x,int y)
{COORD point = {x,y}; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),point);}
