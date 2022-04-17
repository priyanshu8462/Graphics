#include <bits/stdc++.h>
using namespace std;

class Circle{
		float r,dFactor;
		vector<vector<float>> points;
	public:
		void get();
		void circle();
		void print();		
};

void Circle::get(){
	cout<<"Enter radius : "; cin>>r;
	
	dFactor = 1.25 - r;
	
}

void Circle::circle(){
	float x=0,y=r;
	points.push_back({x,y});
	
	while(y>x){
		if(dFactor<0){
			dFactor += 2*x+3;
			x++;
		}
		else{
			dFactor += 2*(x-y)+5;
			y--; x++;
		}
		points.push_back({x,y});
		points.push_back({x,-y});
		points.push_back({-x,y});
		points.push_back({-x,-y});
		points.push_back({y,x});
		points.push_back({y,-x});
		points.push_back({-y,x});
		points.push_back({-y,-x});
	}
}

void Circle::print(){
	int len  = points.size();
	cout<<"["<<endl;
	for(int i=0;i<len;i++){
		cout<<"("<<round(points[i][0])<<","<<round(points[i][1])<<"), ";
	}
	cout<<"]";
}

int main(){
	Circle obj;
	obj.get();
	obj.circle();
	obj.print();
}

/*
Enter radius : 6
[
(0,6), (1,6), (1,-6), (-1,6), (-1,-6), (6,1), (6,-1), (-6,1), (-6,-1), (2,6), (2,-6), (-2,6), (-2,-6), (6,2), (6,-2), (-6,2), (-6,-2), (3,5), (3,-5), (-3,5), (-3,-5), (5,3), (5,-3), (-5,3), (-5,-3), (4,4), (4,-4), (-4,4), (-4,-4), (4,4), (4,-4), (-4,4), (-4,-4), ]
--------------------------------
Process exited after 1.374 seconds with return value 0
Press any key to continue . . .
*/
