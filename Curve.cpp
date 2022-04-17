#include <bits/stdc++.h>
#include <cmath>
using namespace std;

class Curve{
		vector<float> P1,P4,R1,R4;
		vector<vector<float>> res;
	public:
		void get(int ch);
		void hermite();
		void bezier();
		void print(vector<vector<float>> res);
		void menu();
};

// get value
void Curve::get(int ch){
	float x,y,z;
	
	cout<<"Enter Starting Point (format :x y z) :";
	cin>>x>>y>>z;
	P1 = {x,y,z};
	
	cout<<"Enter Ending Point (format :x y z) :";
	cin>>x>>y>>z;
	P4 = {x,y,z};
	
	if(ch==1)
		cout<<"Enter Tangent Vector at Starting Point (format :x y z) :";
	else
		cout<<"Enter First Intermediate Point (format :x y z) :";
	
	cin>>x>>y>>z;
	R1 = {x,y,z};
	
	if(ch==1)
		cout<<"Enter Tangent Vector at Ending Point (format :x y z) :";
	else
		cout<<"Enter Second Intermediate Point (format :x y z) :";
	
	cin>>x>>y>>z;
	R4 = {x,y,z};
}

void Curve::hermite(){
	vector<float> temp;
	float Xc,Yc,Zc;
	float t=0;
	while(t<=1.01){
		Xc = (2*pow(t,3) - 3*pow(t,2) +1 )*P1[0] + (-2*pow(t,3) + 3*pow(t,2))*P4[0] + (pow(t,3)-2*pow(t,2)+t)*R1[0] + (pow(t,3) - pow(t,2))*R4[0];
		Yc = (2*pow(t,3) - 3*pow(t,2) +1 )*P1[1] + (-2*pow(t,3) + 3*pow(t,2))*P4[1] + (pow(t,3)-2*pow(t,2)+t)*R1[1] + (pow(t,3) - pow(t,2))*R4[1];
		Zc = (2*pow(t,3) - 3*pow(t,2) +1 )*P1[2] + (-2*pow(t,3) + 3*pow(t,2))*P4[2] + (pow(t,3)-2*pow(t,2)+t)*R1[2] + (pow(t,3) - pow(t,2))*R4[2];	
		res.push_back({Xc,Yc,Zc});	
		t=t+0.1;
	}
	print(res);	
}


void Curve::bezier(){
	vector<float> temp;
	float Xc,Yc,Zc;
	float t=0;
	while(t<=1.01){
		Xc = pow((1-t),3)*P1[0] + 3*t*pow((1-t),2)*R1[0] + 3*pow(t,2)*(1-t)*R4[0] + pow(t,3)*P4[0];
		Yc = pow((1-t),3)*P1[1] + 3*t*pow((1-t),2)*R1[1] + 3*pow(t,2)*(1-t)*R4[1] + pow(t,3)*P4[1];
		Zc = pow((1-t),3)*P1[2] + 3*t*pow((1-t),2)*R1[2] + 3*pow(t,2)*(1-t)*R4[2] + pow(t,3)*P4[2];
		res.push_back({Xc,Yc,Zc});	
		t=t+0.1;
	}
	print(res);	
}

void Curve::print(vector<vector<float>> res){
	cout<<endl;
	int len = res.size();
	for(int i=0;i<len;i++){
		for(int j=0;j<3;j++){
			cout<<setw(5)<<setprecision(3)<<res[i][j]<<"     ";
		}
		cout<<endl;
	}
}

void Curve::menu(){
	int ch; char c;
	
	cout<<"\nCURVE SKETCHING";
	cout<<"==================";
	do{
		cout<<"\n1. Hermite Curve \n2. Bezier Curve";
		cout<<"\nEnter your choice : ";
		cin>>ch;
		get(ch);
		
		if (ch==1)
			hermite();
		else
			bezier();
			
		cout<<"\nDo you want to continue ? [y/n]  ";
		cin>>c;
		
		//clear res vector for next iteration			
		res.clear();		
	
	}while(c=='y');
	
}

int main(){
	Curve obj;
	obj.menu();
	return 0;
}

