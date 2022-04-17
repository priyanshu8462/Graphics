#include<bits/stdc++.h>
using namespace std;

class twoD{
		vector<vector<float>> vertex;
		int num, dim=3;
	public:
		void get();
		void scale();
		void translate();
		void rotate();
		void reflect();
		vector<vector<float>> multiply(vector<vector<float>> a, vector<vector<float>> b);
		void display(vector<vector<float>> v);
		void menu();	
};

//input
void twoD::get(){
	float x; float y;
	cout<<"\nEnter number of vertex : ";
	cin>>num;
	
	for(int i=0;i<num;i++){
		cout<<"\nCoordinate "<<i+1;
		cout<<"\nEnter value of x coordinate :";
		cin>>x;
		cout<<"Enter value of y coordinate :";
		cin>>y;
		
		vertex.push_back({x,y,1});
	}
	
	display(vertex);
}

//multiply two matrix
vector<vector<float>> twoD::multiply(vector<vector<float>> a, vector<vector<float>> b){

	vector<vector<float>> res;
	
	//fix the size of resultant matrix before multiplication	
	for(int i=0;i<num;i++)
		res.push_back({0,0,0});
		
	for(int i=0; i<num; i++){
            for(int j=0; j<dim; j++){
            	res[i][j]=0;
                for(int k=0; k<dim; k++){
                    res[i][j] += a[i][k] * b[k][j];
                }
            }
    }
    
    return res;
}


void twoD::scale(){
	float sx,sy;
	cout<<"\nEnter scaling factor along x (sx) :";
	cin>>sx;
	cout<<"\nEnter scaling factor along y (sy) :";
	cin>>sy;
	vector<vector<float>> scaling = {{sx,0,0},{0,sy,0},{0,0,1}};
	
	vector<vector<float>> scaled = multiply(vertex,scaling);
	
	cout<<"\nUPDATED COORDINATES AFTER SCALING :";
	display(scaled);
	
}

//rotate
void twoD::rotate(){
	int c;
	float angle;
	cout<<"\nEnter the value of theta (in degrees) : ";
	cin>>angle;
	angle = angle*(3.1415)/180;
	float sine = sin(angle), cosine = cos(angle);
	
	vector<vector<float>> rotating;
	cout<<"\nRotate in : \n1. Clockwise Direction \n2. Anticlockwise Direction ";
	cout<<"\nEnter you choice : ";
	cin>>c;
	if (c==1)	
		rotating = {{cosine,-sine,0},{sine,cosine,0},{0,0,1}};
	else if(c==2)
		rotating = {{cosine,sine,0},{-sine,cosine,0},{0,0,1}};
	vector<vector<float>> rotated = multiply(vertex,rotating); 
	
	cout<<"\nUPDATED COORDINATES AFTER ROTATING :";
	display(rotated);
}

//translate
void twoD::translate(){
	float tx,ty;
	cout<<"\nEnter amount translated along x :";
	cin>>tx;
	cout<<"Enter amount translated along y :";
	cin>>ty;
	
	vector<vector<float>> translating ;
	translating = {{1,0,0},{0,1,0},{tx,ty,1}};
	
	vector<vector<float>> translated = multiply(vertex,translating);
	
	cout<<"\nUPDATED COORDINATES AFTER TRANSLATING :";
	display(translated);
}

//reflect
void twoD::reflect(){
	int c;
	vector<vector<float>> reflecting;
	cout<<"\nReflect about : \n1. X-axis \n2. Y-axis ";
	cout<<"\nEnter you choice : ";
	cin>>c;
	if (c==1)	
		reflecting = {{1,0,0},{0,-1,0},{0,0,1}};
	else if(c==2)
		reflecting = {{-1,0,0},{0,1,0},{0,0,1}};
	vector<vector<float>> reflected = multiply(vertex,reflecting); 
	
	cout<<"\nUPDATED COORDINATES AFTER ROTATING :";
	display(reflected);
}

//display
void twoD::display(vector<vector<float>> v){
	cout<<endl;
	int len = v.size();
	for(int i=0;i<len;i++){
		for(int j=0;j<dim;j++){
			cout<<v[i][j]<<"     ";
		}
		cout<<endl;
	}
}

void twoD::menu(){
	cout<<"TWO DIMENSIONAL TRANSFORMATION";
	cout<<"\n================================";
	
	char c; int ch;
	do{
		vertex.clear();
		
		cout<<"\n1. ROTATE A OBJECT";
		cout<<"\n2. TRANSLATE A OBJECT";
		cout<<"\n3. SCALE A OBJECT";
		cout<<"\n4. REFLECT A OBJECT";
		cout<<"\n\nEnter your choice : ";
		cin>>ch;
		
		get();
		
		switch(ch){
			case 1 : rotate();
					 break;
			case 2 : translate();
					 break;
			case 3 : scale();
					 break;
			case 4 : reflect();
					 break;		 
			default : cout<<"\nWrong choice !!";		 		 		 
		}
		
		cout<<"\nDo you want to continue (y/n) : ";
		cin>>c;
	}while(c=='y');
	
}


int main(){
	twoD obj;
	obj.menu();
	return 0;
}

/*
TWO DIMENSIONAL TRANSFORMATION
================================
1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT

Enter your choice : 1

Enter number of vertex : 2

Coordinate 1
Enter value of x coordinate :1
Enter value of y coordinate :2

Coordinate 2
Enter value of x coordinate :5
Enter value of y coordinate :6

1     2     1
5     6     1

Enter the value of theta (in degrees) : 180

Rotate in :
1. Clockwise Direction
2. Anticlockwise Direction
Enter you choice : 1

UPDATED COORDINATES AFTER ROTATING :
-0.999815     -2.00009     1
-4.99944     -6.00046     1

Do you want to continue (y/n) : y

1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT

Enter your choice : 2

Enter number of vertex : 2

Coordinate 1
Enter value of x coordinate :1
Enter value of y coordinate :2

Coordinate 2
Enter value of x coordinate :3
Enter value of y coordinate :4

1     2     1
3     4     1

Enter amount translated along x :4
Enter amount translated along y :10

UPDATED COORDINATES AFTER TRANSLATING :
5     12     1
7     14     1

Do you want to continue (y/n) : y

1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT

Enter your choice : 3

Enter number of vertex : 2

Coordinate 1
Enter value of x coordinate :1
Enter value of y coordinate :2

Coordinate 2
Enter value of x coordinate :4
Enter value of y coordinate :5

1     2     1
4     5     1

Enter scaling factor along x (sx) :3

Enter scaling factor along y (sy) :0.5

UPDATED COORDINATES AFTER SCALING :
3     1     1
12     2.5     1

Do you want to continue (y/n) : y

1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT

Enter your choice : 4

Enter number of vertex : 2

Coordinate 1
Enter value of x coordinate :1
Enter value of y coordinate :2

Coordinate 2
Enter value of x coordinate :3
Enter value of y coordinate :4

1     2     1
3     4     1

Reflect about :
1. X-axis
2. Y-axis
Enter you choice : 2

UPDATED COORDINATES AFTER ROTATING :
-1     2     1
-3     4     1

Do you want to continue (y/n) : n

--------------------------------
Process exited after 60.94 seconds with return value 0
Press any key to continue . . .
*/
