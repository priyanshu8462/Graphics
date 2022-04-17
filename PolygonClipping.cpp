#include<iostream>
#include<conio.h>
#include<graphics.h>
#define round(a) ((int)(a+0.5))

using namespace std;
class polygon
{
	int k,n,poly[20];
	float xmin,ymin,xmax,ymax,arr[20],polyy[20],m;
	int **p1,**p2;
	public:
		void getPolygon();
		void clipl(float,float,float,float);
		void clipr(float,float,float,float);
		void clipt(float,float,float,float);
		void clipb(float,float,float,float);
		void polygon_cliping();
};

void polygon::getPolygon()
{
	
	
	cout<<"Coordinates of rectangular clip window :\n";
	cout<<"\nMinimum value of X-coordinate:-";
    cin>>xmin;
    cout<<"\nMinimum value of Y-coordinate:-";
	cin>>ymin;
    cout<<"\nMaximum value of X-coordinate:-";
    cin>>xmax;
	cout<<"\nMaximum value of Y-coordinate:-";
	cin>>ymax;
    cout<<"\n\nPolygon to be clipped :\nNumber of sides       :";
    cin>>n;
    p1=new int*[n];
	for(int i=0;i<n;++i)
		p1[i]=new int[2];
		
    cout<<"\nEnter the coordinate of the Polygon:-";
    int i;
    for(i=0;i < 2*n;i++)
		cin>>polyy[i];
	polyy[i]=polyy[0];
    polyy[i+1]=polyy[1];
    
    for(i=0;i < 2*n+2;i++)
		poly[i]=round(polyy[i]);
    
    //Save the original points of polygon
    int a=0;
    for(i=0;i<n;++i)
    	for(int j=0;j<2;++j)
    		p1[i][j]=poly[a++];
    		
    
    setcolor(RED);
    rectangle(xmin,ymax,xmax,ymin);
    cout<<"\n\nUNCLIPPED POLYGON\n";
    for(i=0;i<n;++i)
    {
    	for(int j=0;j<2;++j)
    		cout<<p1[i][j]<<"  ";
    	cout<<"\n";
	}
    setcolor(WHITE);
    fillpoly(n,poly);
	
    
}

void polygon::clipl(float x1,float y1,float x2,float y2)
{
	if(x2-x1)
		m=(y2-y1)/(x2-x1);
	else
		m=100000;
	
	if(x1 >= xmin && x2 >= xmin)
    {
        arr[k]=x2;
        arr[k+1]=y2;
        k+=2;
    }
    if(x1 < xmin && x2 >= xmin)
    {
        arr[k]=xmin;
        arr[k+1]=y1+m*(xmin-x1);
        arr[k+2]=x2;
        arr[k+3]=y2;
        k+=4;
    }
    if(x1 >= xmin  && x2 < xmin)
    {
        arr[k]=xmin;
        arr[k+1]=y1+m*(xmin-x1);
        k+=2;
    }
}

void polygon::clipr(float x1,float y1,float x2,float y2)
{
	if(x2-x1)
        m=(y2-y1)/(x2-x1);
    else
        m=100000;
    if(x1 <= xmax && x2 <= xmax)
    {
        arr[k]=x2;
        arr[k+1]=y2;
        k+=2;
    }
    if(x1 > xmax && x2 <= xmax)
    {
        arr[k]=xmax;
        arr[k+1]=y1+m*(xmax-x1);
        arr[k+2]=x2;
        arr[k+3]=y2;
        k+=4;
    }
    if(x1 <= xmax  && x2 > xmax)
    {
        arr[k]=xmax;
        arr[k+1]=y1+m*(xmax-x1);
        k+=2;
    }
}

void polygon::clipt(float x1,float y1,float x2,float y2)
{
	if(y2-y1)
        m=(x2-x1)/(y2-y1);
    else
        m=100000;
    if(y1 <= ymax && y2 <= ymax)
    {
        arr[k]=x2;
        arr[k+1]=y2;
        k+=2;
    }
    if(y1 > ymax && y2 <= ymax)
    {
        arr[k]=x1+m*(ymax-y1);
        arr[k+1]=ymax;
        arr[k+2]=x2;
        arr[k+3]=y2;
        k+=4;
    }
    if(y1 <= ymax  && y2 > ymax)
    {
        arr[k]=x1+m*(ymax-y1);
        arr[k+1]=ymax;
        k+=2;
    }	
}

void polygon::clipb(float x1,float y1,float x2,float y2)
{
	if(y2-y1)
        m=(x2-x1)/(y2-y1);
    else
        m=100000;
    if(y1 >= ymin && y2 >= ymin)
    {
        arr[k]=x2;
        arr[k+1]=y2;
        k+=2;
    }
    if(y1 < ymin && y2 >= ymin)
    {
        arr[k]=x1+m*(ymin-y1);
        arr[k+1]=ymin;
        arr[k+2]=x2;
        arr[k+3]=y2;
        k+=4;
    }
    if(y1 >= ymin  && y2 < ymin)
    {
        arr[k]=x1+m*(ymin-y1);
        arr[k+1]=ymin;
        k+=2;
    }                  
}


void polygon::polygon_cliping()
{
	//cleardevice();
    k=0;
    int i;
    for(i=0;i < 2*n;i+=2)
		clipl(polyy[i],polyy[i+1],polyy[i+2],polyy[i+3]);
		
		
    n=k/2;
    for(i=0;i < k;i++)
		polyy[i]=arr[i];
    polyy[i]=polyy[0];
    polyy[i+1]=polyy[1];
    
    
    k=0;
    for(i=0;i < 2*n;i+=2)
		clipt(polyy[i],polyy[i+1],polyy[i+2],polyy[i+3]);
    n=k/2;
    for(i=0;i < k;i++)
		polyy[i]=arr[i];
    polyy[i]=polyy[0];
    polyy[i+1]=polyy[1];
    
	k=0;
    for(i=0;i < 2*n;i+=2)
		clipr(polyy[i],polyy[i+1],polyy[i+2],polyy[i+3]);
    n=k/2;
    for(i=0;i < k;i++)
		polyy[i]=arr[i];
    polyy[i]=polyy[0];
    polyy[i+1]=polyy[1];
    
	k=0;
    
	for(i=0;i < 2*n;i+=2)
		clipb(polyy[i],polyy[i+1],polyy[i+2],polyy[i+3]);
    for(i=0;i <k;i++)
		poly[i]=round(arr[i]);
 
    setcolor(RED);
    rectangle(xmin,ymax,xmax,ymin);
    if(k)
		fillpoly(k/2,poly);
    
	cout<<"\n\nCLIPPED POLYGON\n";
    //cout<<k;
    int size=(k)/2;
    p2=new int*[size];
	for(int i=0;i<size;++i)
		p2[i]=new int[2];
		
	//Save the Clipped points of polygon
    int a=0;
    for(i=0;i<size;++i)
    	for(int j=0;j<2;++j)
    		p2[i][j]=poly[a++];
    		
    for(i=0;i<size;++i)
    {
    	for(int j=0;j<2;++j)
    		cout<<p2[i][j]<<"  ";
    	cout<<"\n";
	}	
    
    getch();
    closegraph();
}
int main()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");
	polygon p1;
	p1.getPolygon();
	getch();
	cleardevice();
	p1.polygon_cliping();
	getch();
	return 0;
}


/* OUTPUT

Coordinates of rectangular clip window :

Minimum value of X-coordinate:-200

Minimum value of Y-coordinate:-200

Maximum value of X-coordinate:-400

Maximum value of Y-coordinate:-400


Polygon to be clipped :
Number of sides       :3

Enter the coordinate of the Polygon:-150
300
300
150
300
300


UNCLIPPED POLYGON
150  300
300  150
300  300


CLIPPED POLYGON
200  300
200  250
250  200
300  200
300  300

*/
