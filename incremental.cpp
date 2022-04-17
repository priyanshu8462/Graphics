#include <bits/stdc++.h>
using namespace std;

class IncrementalAlgo{
		float sx,sy,tx,ty, slope;
		vector<vector<float>> points;
	public:
		void get();
		void incremental();
		void print();		
};

void IncrementalAlgo::get(){
	cout<<"\nEnter starting coordinate (x,y) : "; cin>>sx>>sy;
	cout<<"Enter ending coordinate (x,y) : "; cin>>tx>>ty;
	slope = (ty-sy)/(tx-sx);
	
}

void IncrementalAlgo::incremental(){
	float x=sx,y=sy;
	points.push_back({x,y});
	do{
		if(slope<1){
			x = x + 1;
			y = y + slope;
		}
		else{
			x = x + 1/slope;
			y = y + 1;
		}
		points.push_back({x,y});
	}while(x!=tx && y!=ty);
}

void IncrementalAlgo::print(){
	int len  = points.size();
	for(int i=0;i<len;i++){
		cout<<"("<<round(points[i][0])<<","<<round(points[i][1])<<")--->";
	}
}

int main(){
	IncrementalAlgo obj;
	obj.get();
	obj.incremental();
	obj.print();
}

/*	OUTPUT
Enter starting coordinate (x,y) : 5 6
Enter ending coordinate (x,y) : 9 12
(5,6)--->(6,7)--->(6,8)--->(7,9)--->(8,10)--->(8,11)--->(9,12)--->
--------------------------------
Process exited after 8.383 seconds with return value 0
Press any key to continue . . .
*/
