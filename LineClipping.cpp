#include <bits/stdc++.h>
using namespace std;

class LineClipping{
		int xmax,xmin,ymax,ymin,n;
		int r1,r2,r3,r4,r5,r6,r7,r8,r9;
		vector<vector<int>> lines;
		vector<vector<int>> clipped;
		vector<vector<int>>::iterator it;
		
	public:
		LineClipping(){
			r1=9; r2=8; r3=10;
			r4=1; r5=0; r6=2;
			r7=5; r8=4; r9=6;
		}
		void input();
		int find_region(int x,int y);
		void clipLine();
		void clipCurrLine(int x1,int y1,int x2,int y2);
		void display(vector<vector<int>> v);	
};

void LineClipping::input(){
	//window	
	cout<<"\nEnter Window info :";
	cout<<"\nxmax : "; cin>>xmax;
	cout<<"ymax : "; cin>>ymax;
	cout<<"xmin : "; cin>>xmin;
	cout<<"ymin : "; cin>>ymin;
	
	//lines	
	cout<<"\nEnter number of lines :";
	cin>>n;
	int x1,y1,x2,y2;
	for(int i=0;i<n;i++){
		cout<<"\nEnter end point of line "<<i+1<<" (x1 y1 x2 y2) : ";
		cin>>x1>>y1>>x2>>y2;
		lines.push_back({x1,y1,x2,y2});
	}
	
	cout<<"\n\nOriginal lines :";
	cout<<"\n==================\n";
	display(lines);
}

int LineClipping::find_region(int x,int y){
//	cout<<endl<<x<<" "<<y;
	if(x<xmin && y>ymax)
		return r1;
	else if(x>=xmin && x<=xmax && y>ymax)
		return r2;
	else if(x>xmax && y>ymax)
		return r3;
	else if(x<xmin && y>=ymin && y<=ymax)
		return r4;
	else if(x>=xmin && x<=xmax && y>=ymin && y<=ymax)
		return r5;
	else if(x>xmax && y>=ymin && y<=ymax)
		return r6;
	else if(x<xmin && y<ymin)
		return r7;
	else if(x>=xmin && x<=xmax && y<ymin)
		return r8;
	else if(x>xmax && y<ymin)
		return r9;
	else
		return -1;									
}

void LineClipping::clipCurrLine(int x1,int y1,int x2,int y2){
	vector<int> clip;
	int codeStart = find_region(x1,y1);
	int codeEnd = find_region(x2,y2);
	bool flag=false, reject = false;
	do{
		
		if(!(codeStart | codeEnd)){
			//trivially accepted		
			flag= true;
		}
		
		else if(codeStart & codeEnd){
			//trivially reject
			flag=true;	
			reject = true;		
		}
		
		else{
			// pick the point which lies outside the clipping window			
			int x,y;
			int pointOutside = codeStart ? codeStart:codeEnd;
	
			if(pointOutside & 1){
				//point lies left of xmin
				x = xmin;
				y = y1 + (y2-y1)*(xmin-x1)/(x2-x1);				
			}
			else if(pointOutside & 2){
				//point lies right of xmax
				x = xmax;
				y = y1 + (y2-y1)*(xmax-x1)/(x2-x1);
			}
			else if(pointOutside & 4){
				//point lies below ymin			
				y = ymin;
				x = x1 + (x2-x1)*(ymin-y1)/(y2-y1);	
			}
			else if(pointOutside & 8){
				//point lies above ymax	
				y = ymax;
				x = x1 + (x2-x1)*(ymax-y1)/(y2-y1);			
			}
			
			//update the new point
			if(pointOutside == codeStart){
				x1 = x; y1 = y;
				codeStart = find_region(x1,y1); 
			}			
			else{
				x2 = x; y2 = y;
				codeEnd = find_region(x2,y2);
			}
		}
	}while(flag==false);
	
	if(!reject)
		clipped.push_back({x1,y1,x2,y2});
}

void LineClipping::clipLine(){
	for(int i=0;i<n;i++){
		clipCurrLine(lines[i][0],lines[i][1],lines[i][2],lines[i][3]);
	}
	
	cout<<"\nClipped lines :";
	cout<<"\n==================\n";
	display(clipped);
}

void LineClipping::display(vector<vector<int>> v){
	int size = v.size();
	for(int i=0;i<size;i++){ 
		cout<<"("<<v[i][0]<<","<<v[i][1]<<") <--> ("<<v[i][2]<<","<<v[i][3]<<")"<<endl;
	}
}

int main(){
	LineClipping obj;
	obj.input();
	obj.clipLine();
	return 0;
}

/*

Enter Window info :
xmax : 10
ymax : 8
xmin : 4
ymin : 4

Enter number of lines :3

Enter end point of line 1 (x1 y1 x2 y2) : 5 5 7 7

Enter end point of line 2 (x1 y1 x2 y2) : 7 9 11 4

Enter end point of line 3 (x1 y1 x2 y2) : 1 5 4 1


Original lines :
==================
(5,5) <--> (7,7)
(7,9) <--> (11,4)
(1,5) <--> (4,1)

Clipped lines :
==================
(5,5) <--> (7,7)
(7,8) <--> (10,5)

--------------------------------
Process exited after 16.71 seconds with return value 0
Press any key to continue . . .
*/
