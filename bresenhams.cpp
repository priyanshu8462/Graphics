#include <bits/stdc++.h>
using namespace std;

class midPointLine{
		float sx,sy,tx,ty,dy,dx, p;
		vector<vector<float>> points;
	public:
		void get();
		void bresenham();
		void print();		
};

void midPointLine::get(){
	cout<<"\nEnter starting coordinate (x,y) : "; cin>>sx>>sy;
	cout<<"Enter ending coordinate (x,y) : "; cin>>tx>>ty;
	dy = ty-sy; dx = tx-sx;
	p = 2*dy-dx;	
}

void midPointLine::bresenham(){
	float x=sx,y=sy;
	points.push_back({x,y});
	do{
		if(p<0){
			x = x + 1;
			p += 2*dy ;
		}
		else{
			x = x + 1;
			y = y + 1;
			p += 2*dy - 2*dx;
		}
		points.push_back({x,y});
	}while(x!=tx && y!=ty);
}

void midPointLine::print(){
	int len  = points.size();
	cout<<endl;
	for(int i=0;i<len;i++){
		cout<<"("<<round(points[i][0])<<","<<round(points[i][1])<<")--->";
	}
}

int main(){
	midPointLine obj;
	obj.get();
	obj.bresenham();
	obj.print();
}

/*
OUTPUT

Enter starting coordinate (x,y) : 9 18
Enter ending coordinate (x,y) : 14 22

(9,18)--->(10,19)--->(11,20)--->(12,20)--->(13,21)--->(14,22)--->
--------------------------------
Process exited after 7.495 seconds with return value 0
Press any key to continue . . .
*/
