// Write a program to fill a polygon using Scan line fill algorithm.

#include <conio.h>
#include <iostream>
#include <graphics.h>
#include <stdlib.h>
using namespace std;

//Declaration of class point
class point
{
    public:
    int x,y;
};

class poly
{
    private:
        point p[20];
        int inter[20], x, y;
        int v, xmin, ymin, xmax, ymax;
        
    public:
        int c;
        void input();
        void calcs();
        void display();
        void ints(float);
        void sort(int);
};


void poly::input(){
    int i;
    cout<<"\nEnter the number of vertices of polygon: ";
    cin>>v;
    if(v>2){
        for(i=0; i<v; i++){ //ACCEPT THE VERTICES
            cout<<"\n  Coordinates of Vertex "<<i+1<<": ";
            cout<<"\n\tx"<<(i+1)<<"=";
            cin>>p[i].x;
            cout<<"\ty"<<(i+1)<<"=";
            cin>>p[i].y;
        }
        p[i].x = p[0].x;
        p[i].y = p[0].y;
        xmin = xmax = p[0].x;
        ymin = ymax = p[0].y;
    }
    else
        cout<<"\n Number of vertices is invalid.";
}

//function for finding min/max of the coordinates
void poly::calcs(){
    for(int i=0;i<v;i++){
        if(xmin>p[i].x)
        xmin=p[i].x;
        if(xmax<p[i].x)
        xmax=p[i].x;
        if(ymin>p[i].y)
        ymin=p[i].y;
        if(ymax<p[i].y)
        ymax=p[i].y;
    }
}

//DISPLAY FUNCTION
void poly::display(){

    float s;
    
    s = ymin + 0.01;
    delay(10);
    cleardevice();
    while(s <= ymax){
        ints(s);
        sort(s);
        s++;
    }
    cout<<"\nFILLED POLYGON DRAWN!";

}

void poly::ints(float z){
	
    int x1, x2, y1, y2, temp;
    c=0;
    for(int i=0; i<v; i++)
	{	
        x1=p[i].x;
        y1=p[i].y;
        x2=p[i+1].x;
        y2=p[i+1].y;
        
        if(y2<y1)
    	{
            temp=x1;
            x1=x2;
            x2=temp;
            temp=y1;
            y1=y2;
            y2=temp;
        }
        if(z<=y2 && z>=y1)
        {
            if((y1-y2)==0)
            x=x1;
            else // used to make changes in x. so that we can fill our polygon after cerain distance
            {
                x=((x2-x1)*(z-y1))/(y2-y1);
                x=x+x1;
            }
            if(x<=xmax && x>=xmin)
            inter[c++]=x;
        }
    }
}

void poly::sort(int z) //SORT FUNCTION
{
    int temp,j,i;

        for(i=0; i<v; i++)
        {
            line(p[i].x,p[i].y,p[i+1].x,p[i+1].y); // used to make hollow outlines of a polygon
        }
        delay(10);
        for(i=0; i<c; i+=2)
        {
            delay(10);
            line(inter[i],z,inter[i+1],z);  // Used to fill the polygon ....
        }
}

int main(){
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout<<"~~ POLYGON FILLING  USING SCAN LINE FILL ALGORITHM ~~\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	
    initwindow(500,600);
    cleardevice();

    poly x;
    x.input();
    x.calcs();
    cleardevice();

	x.display();
	
    getch();
    return 0;
}


/*
OUTPUT:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~ POLYGON FILLING  USING SCAN LINE FILL ALGORITHM ~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter the number of vertices of polygon: 3

  Coordinates of Vertex 1:
        x1=100
        y1=200

  Coordinates of Vertex 2:
        x2=200
        y2=300

  Coordinates of Vertex 3:
        x3=250
        y3=150

FILLED POLYGON DRAWN!

*/
