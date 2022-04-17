#include<bits/stdc++.h>
using namespace std;

class threeD{
		vector<vector<float>> vertex;
		int num, dim=4;
	public:
		void get();
		vector<vector<float>> scale(vector<vector<float>> vertex);
		vector<vector<float>> translate(vector<vector<float>> vertex);
		vector<vector<float>> rotate(vector<vector<float>> vertex);
		vector<vector<float>> reflect(vector<vector<float>> vertex);
		vector<vector<float>> axonometricProjection();
		vector<vector<float>> obliqueProjection();
		vector<vector<float>> perspectiveProjection();
		vector<vector<float>> multiply(vector<vector<float>> a, vector<vector<float>> b);
		void display(vector<vector<float>> v);
		void menu();	
};

//input
void threeD::get(){
	float x, y, z;
	cout<<"\nEnter number of vertex : ";
	cin>>num;
	
	for(int i=0;i<num;i++){
		cout<<"\nCoordinate "<<i+1;
		cout<<"\nEnter value of x coordinate :";
		cin>>x;
		cout<<"Enter value of y coordinate :";
		cin>>y;
		cout<<"Enter value of z coordinate :";
		cin>>z;
		
		vertex.push_back({x,y,z,1});
	}
	
	display(vertex);
}

//multiply two matrix
vector<vector<float>> threeD::multiply(vector<vector<float>> a, vector<vector<float>> b){

	vector<vector<float>> res;
	
	//fix the size of resultant matrix before multiplication	
	for(int i=0;i<num;i++)
		res.push_back({0,0,0,0});
		
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


vector<vector<float>> threeD::scale(vector<vector<float>> vertex){
	float sx,sy,sz;
	cout<<"\nEnter scaling factor along x (sx) :";
	cin>>sx;
	cout<<"Enter scaling factor along y (sy) :";
	cin>>sy;
	cout<<"Enter scaling factor along z (sz) :";
	cin>>sz;
	vector<vector<float>> scaling = {{sx,0,0,0},{0,sy,0,0},{0,0,sz,0},{0,0,0,1}};
	
	vector<vector<float>> scaled = multiply(vertex,scaling);
	
	return scaled;
	
}

//rotate
vector<vector<float>> threeD::rotate(vector<vector<float>> vertex){
	int c;
	float angle;
	cout<<"\nEnter the value of theta (in degrees) : ";
	cin>>angle;
	angle = angle*(3.1415)/180;
	float sine = sin(angle), cosine = cos(angle);
	
	vector<vector<float>> rotating;
	cout<<"\nRotate about : \n1. X-axis \n2. Y-axis \n3. Z-axis";
	cout<<"\nEnter you choice : ";
	cin>>c;
	if (c==1)	
		rotating = {{1,0,0,0},{0,cosine,sine,0},{0,-sine,cosine,0},{0,0,0,1}};
	else if(c==2)
		rotating = {{cosine,0,-sine,0},{0,1,0,0},{sine,0,cosine,0},{0,0,0,1}};
	else if(c==3)	
		rotating = {{cosine,sine,0,0},{-sine,cosine,0,0},{0,0,1,0},{0,0,0,1}};
	
	vector<vector<float>> rotated = multiply(vertex,rotating); 
	
	return rotated;
}

//translate
vector<vector<float>> threeD::translate(vector<vector<float>> vertex){
	float tx,ty,tz;
	cout<<"\nEnter amount translated along x :";
	cin>>tx;
	cout<<"Enter amount translated along y :";
	cin>>ty;
	cout<<"Enter amount translated along y :";
	cin>>tz;
	
	vector<vector<float>> translating ;
	translating = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{tx,ty,tz,1}};
	
	vector<vector<float>> translated = multiply(vertex,translating);
	
	return translated;
}

//reflect
vector<vector<float>> threeD::reflect(vector<vector<float>> vertex){
	int c;
	vector<vector<float>> reflecting;
	cout<<"\nReflect about : \n1. XY-plane \n2. YZ-plane \n3. XZ-plane";
	
	cout<<"\nEnter you choice : ";
	cin>>c;
	if (c==1)	
		reflecting = {{1,0,0,0},{0,1,0,0},{0,0,-1,0},{0,0,0,1}};
	else if(c==2)
		reflecting = {{-1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
	else if(c==3)	
		reflecting = {{1,0,0,0},{0,-1,0,0},{0,0,1,0},{0,0,0,1}};

	vector<vector<float>> reflected = multiply(vertex,reflecting); 
	
	return reflected;
}

//axonometric projection
vector<vector<float>> threeD::axonometricProjection(){
	
	vector<vector<float>> projZ = {{1,0,0,0},{0,1,0,0},{0,0,0,0},{0,0,0,1}};
	vector<vector<float>> projected;
	
	//first rotate about y-axis and x-axis then project on z=0 plane
	projected = rotate(vertex);
	display(projected);
	projected = rotate(projected);
	display(projected);
	projected = multiply(projected,projZ);
	
	return projected;
}

//oblique projection
vector<vector<float>> threeD::obliqueProjection(){
	int ch;
	float f,angle;
	cout<<"\n1. Cavalier Projection \n2. Cabinet Projection";
	cout<<"\nEnter your choice : "; cin>>ch;
	
	if(ch==1)
		f=1;
	else if(ch==2)
		f=0.5;
		
	cout<<"\nEnter the angle alpha (in degrees) : ";
	cin>>angle;	
	angle = angle*(3.1415)/180;
	
	float sine = sin(angle), cosine = cos(angle);
	
	vector<vector<float>> proj = {{1,0,0,0},{0,1,0,0},{-f*cosine,-f*sine,0,0},{0,0,0,1}};
	cout<<endl; display(proj);
	vector<vector<float>> projected=  multiply(vertex,proj);
	return projected;	
}

//perspective projection
vector<vector<float>> threeD::perspectiveProjection(){
	int ch;
	float copx,copy,copz;
	cout<<"\n1. Single Point \n2. Two Point \n3. Three Point";
	cout<<"\nEnter your choice : "; cin>>ch;
	
	vector<vector<float>> projZ = {{1,0,0,0},{0,1,0,0},{0,0,0,0},{0,0,0,1}};
	vector<vector<float>> proj, projected;
	
	if (ch==1){
		cout<<"\nEnter position of center of projection on z-axis : "; cin>>copz;
 		//	assuming centre of projection is on z-axis
		proj = {{1,0,0,0},{0,1,0,0},{0,0,1,-1/copz},{0,0,0,1}};	
		projected = multiply(vertex,proj);	
		
		// project on z=0 plane
		projected = multiply(projected,projZ);  		
	}
	
	else if(ch==2){
		cout<<"\nEnter centre of projection on x-axis : "; cin>>copx;
		cout<<"Enter centre of projection on y-axis : "; cin>>copy;
		
		proj = {{1,0,0,-1/copx},{0,1,0,-1/copy},{0,0,1,0},{0,0,0,1}};	
		
		projected = multiply(vertex,proj);
		
		//project on z=0 plane
		projected = multiply(projected,projZ);
	}
	else if(ch==3){
		cout<<"\nEnter centre of projection on x-axis : "; cin>>copx;
		cout<<"Enter centre of projection on y-axis : "; cin>>copy;
		cout<<"Enter centre of projection on z-axis : "; cin>>copz;
		
		proj = {{1,0,0,-1/copx},{0,1,0,-1/copy},{0,0,1,-1/copz},{0,0,0,1}};	
		
		projected = multiply(vertex,proj);
		
		//project on z=0 plane
		projected = multiply(projected,projZ);
	
	}
	
	return projected;
}

//display
void threeD::display(vector<vector<float>> v){
	cout<<endl;
	int len = v.size();
	for(int i=0;i<len;i++){
		for(int j=0;j<dim;j++){
			cout<<setw(10)<<v[i][j]<<"     ";
		}
		cout<<endl;
	}
}

void threeD::menu(){
	cout<<"THREE DIMENSIONAL TRANSFORMATION";
	cout<<"\n================================\n";
	
	vector<vector<float>> res;
	char c; int ch;
	do{
		vertex.clear();
		
		cout<<"\n1. ROTATE A OBJECT";
		cout<<"\n2. TRANSLATE A OBJECT";
		cout<<"\n3. SCALE A OBJECT";
		cout<<"\n4. REFLECT A OBJECT";
		cout<<"\n5. AXONOMETRIC PROJECTION";
		cout<<"\n6. OBLIQUE PROJECTION";
		cout<<"\n7. PERSPECTIVE TRANSFORMATION";
		cout<<"\n\nEnter your choice : ";
		cin>>ch;
		
		get();
		
		switch(ch){
			case 1 : res = rotate(vertex);
					 break;
			case 2 : res = translate(vertex);
					 break;
			case 3 : res = scale(vertex);
					 break;
			case 4 : res = reflect(vertex);
					 break;		 
			case 5 : res = axonometricProjection();	
					 break;	 
			case 6 : res = obliqueProjection();	
					 break;	 
			case 7 : res=  perspectiveProjection();  		 
					 break;
			default : cout<<"\nWrong choice !!";		 		 		 
		}
		
		cout<<"\nUPDATES COORDINATES OF OBJECT ARE : \n";
		display(res);
		
		cout<<"\nDo you want to continue (y/n) : ";
		cin>>c;
	}while(c=='y');
	
}


int main(){
	threeD obj;
	obj.menu();
	return 0;
}

/*
		OUTPUT
		
THREE DIMENSIONAL TRANSFORMATION
================================

1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT
5. AXONOMETRIC PROJECTION
6. OBLIQUE PROJECTION
7. PERSPECTIVE TRANSFORMATION

Enter your choice : 1

Enter number of vertex : 3

Coordinate 1
Enter value of x coordinate :1
Enter value of y coordinate :2
Enter value of z coordinate :3

Coordinate 2
Enter value of x coordinate :4
Enter value of y coordinate :5
Enter value of z coordinate :6

Coordinate 3
Enter value of x coordinate :7
Enter value of y coordinate :8
Enter value of z coordinate :9

         1              2              3              1
         4              5              6              1
         7              8              9              1

Enter the value of theta (in degrees) : 45

Rotate about :
1. X-axis
2. Y-axis
3. Z-axis
Enter you choice : 3

UPDATES COORDINATES OF OBJECT ARE :

 -0.707058        2.12134              3              1
 -0.706959        6.36398              6              1
 -0.706861        10.6066              9              1

Do you want to continue (y/n) : y

1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT
5. AXONOMETRIC PROJECTION
6. OBLIQUE PROJECTION
7. PERSPECTIVE TRANSFORMATION

Enter your choice : 2

Enter number of vertex : 2

Coordinate 1
Enter value of x coordinate :1
Enter value of y coordinate :2
Enter value of z coordinate :3

Coordinate 2
Enter value of x coordinate :4
Enter value of y coordinate :5
Enter value of z coordinate :6

         1              2              3              1
         4              5              6              1

Enter amount translated along x :2
Enter amount translated along y :5
Enter amount translated along y :3

UPDATES COORDINATES OF OBJECT ARE :

         3              7              6              1
         6             10              9              1

Do you want to continue (y/n) : y

1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT
5. AXONOMETRIC PROJECTION
6. OBLIQUE PROJECTION
7. PERSPECTIVE TRANSFORMATION

Enter your choice : 3

Enter number of vertex : 1

Coordinate 1
Enter value of x coordinate :1
Enter value of y coordinate :2
Enter value of z coordinate :3

         1              2              3              1

Enter scaling factor along x (sx) :2
Enter scaling factor along y (sy) :2
Enter scaling factor along z (sz) :2

UPDATES COORDINATES OF OBJECT ARE :

         2              4              6              1

Do you want to continue (y/n) : y

1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT
5. AXONOMETRIC PROJECTION
6. OBLIQUE PROJECTION
7. PERSPECTIVE TRANSFORMATION

Enter your choice : 4

Enter number of vertex : 2

Coordinate 1
Enter value of x coordinate :1
Enter value of y coordinate :2
Enter value of z coordinate :3

Coordinate 2
Enter value of x coordinate :3
Enter value of y coordinate :2
Enter value of z coordinate :1

         1              2              3              1
         3              2              1              1

Reflect about :
1. XY-plane
2. YZ-plane
3. XZ-plane
Enter you choice : 1

UPDATES COORDINATES OF OBJECT ARE :

         1              2             -3              1
         3              2             -1              1

Do you want to continue (y/n) : y

1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT
5. AXONOMETRIC PROJECTION
6. OBLIQUE PROJECTION
7. PERSPECTIVE TRANSFORMATION

Enter your choice : 5

Enter number of vertex : 10

Coordinate 1
Enter value of x coordinate :0
Enter value of y coordinate :0
Enter value of z coordinate :1

Coordinate 2
Enter value of x coordinate :1
Enter value of y coordinate :0
Enter value of z coordinate :1

Coordinate 3
Enter value of x coordinate :1
Enter value of y coordinate :0.5
Enter value of z coordinate :1

Coordinate 4
Enter value of x coordinate :0.5
Enter value of y coordinate :1
Enter value of z coordinate :1

Coordinate 5
Enter value of x coordinate :0
Enter value of y coordinate :1
Enter value of z coordinate :1

Coordinate 6
Enter value of x coordinate :0
Enter value of y coordinate :0
Enter value of z coordinate :0

Coordinate 7
Enter value of x coordinate :1
Enter value of y coordinate :0
Enter value of z coordinate :0

Coordinate 8
Enter value of x coordinate :1
Enter value of y coordinate :1
Enter value of z coordinate :0

Coordinate 9
Enter value of x coordinate :0
Enter value of y coordinate :1
Enter value of z coordinate :0

Coordinate 10
Enter value of x coordinate :1
Enter value of y coordinate :1
Enter value of z coordinate :0.5

         0              0              1              1
         1              0              1              1
         1            0.5              1              1
       0.5              1              1              1
         0              1              1              1
         0              0              0              1
         1              0              0              1
         1              1              0              1
         0              1              0              1
         1              1            0.5              1

Enter the value of theta (in degrees) : 30

Rotate about :
1. X-axis
2. Y-axis
3. Z-axis
Enter you choice : 2

Enter the value of theta (in degrees) : 45

Rotate about :
1. X-axis
2. Y-axis
3. Z-axis
Enter you choice : 1

UPDATES COORDINATES OF OBJECT ARE :

  0.499987      -0.612364              0              1
   1.36602      -0.258828              0              1
   1.36602      0.0947336              0              1
  0.933003       0.271527              0              1
  0.499987      0.0947595              0              1
         0              0              0              1
  0.866033       0.353536              0              1
  0.866033        1.06066              0              1
         0       0.707123              0              1
   1.11603       0.754477              0              1

Do you want to continue (y/n) : y

1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT
5. AXONOMETRIC PROJECTION
6. OBLIQUE PROJECTION
7. PERSPECTIVE TRANSFORMATION

Enter your choice : 6

Enter number of vertex : 10

Coordinate 1
Enter value of x coordinate :0
Enter value of y coordinate :0
Enter value of z coordinate :1

Coordinate 2
Enter value of x coordinate :1
Enter value of y coordinate :0
Enter value of z coordinate :1

Coordinate 3
Enter value of x coordinate :1
Enter value of y coordinate :0.5
Enter value of z coordinate :1

Coordinate 4
Enter value of x coordinate :0.5
Enter value of y coordinate :1
Enter value of z coordinate :1

Coordinate 5
Enter value of x coordinate :0
Enter value of y coordinate :1
Enter value of z coordinate :1

Coordinate 6
Enter value of x coordinate :0
Enter value of y coordinate :0
Enter value of z coordinate :0

Coordinate 7
Enter value of x coordinate :1
Enter value of y coordinate :0
Enter value of z coordinate :0

Coordinate 8
Enter value of x coordinate :1
Enter value of y coordinate :1
Enter value of z coordinate :0

Coordinate 9
Enter value of x coordinate :0
Enter value of y coordinate :1
Enter value of z coordinate :0

Coordinate 10
Enter value of x coordinate :1
Enter value of y coordinate :1
Enter value of z coordinate :0.5

         0              0              1              1
         1              0              1              1
         1            0.5              1              1
       0.5              1              1              1
         0              1              1              1
         0              0              0              1
         1              0              0              1
         1              1              0              1
         0              1              0              1
         1              1            0.5              1

1. Cavalier Projection
2. Cabinet Projection
Enter your choice : 2

Enter the angle alpha (in degrees) : 30


         1              0              0              0
         0              1              0              0
 -0.433017      -0.249993              0              0
         0              0              0              1

UPDATES COORDINATES OF OBJECT ARE :

 -0.433017      -0.249993              0              1
  0.566983      -0.249993              0              1
  0.566983       0.250007              0              1
 0.0669834       0.750007              0              1
 -0.433017       0.750007              0              1
         0              0              0              1
         1              0              0              1
         1              1              0              1
         0              1              0              1
  0.783492       0.875003              0              1

Do you want to continue (y/n) : y

1. ROTATE A OBJECT
2. TRANSLATE A OBJECT
3. SCALE A OBJECT
4. REFLECT A OBJECT
5. AXONOMETRIC PROJECTION
6. OBLIQUE PROJECTION
7. PERSPECTIVE TRANSFORMATION

Enter your choice : 7

Enter number of vertex : 8

Coordinate 1
Enter value of x coordinate :0
Enter value of y coordinate :0
Enter value of z coordinate :1

Coordinate 2
Enter value of x coordinate :1
Enter value of y coordinate :0
Enter value of z coordinate :1

Coordinate 3
Enter value of x coordinate :1
Enter value of y coordinate :1
Enter value of z coordinate :1

Coordinate 4
Enter value of x coordinate :0
Enter value of y coordinate :1
Enter value of z coordinate :1

Coordinate 5
Enter value of x coordinate :0
Enter value of y coordinate :0
Enter value of z coordinate :0

Coordinate 6
Enter value of x coordinate :1
Enter value of y coordinate :0
Enter value of z coordinate :0

Coordinate 7
Enter value of x coordinate :1
Enter value of y coordinate :1
Enter value of z coordinate :0

Coordinate 8
Enter value of x coordinate :0
Enter value of y coordinate :1
Enter value of z coordinate :0

         0              0              1              1
         1              0              1              1
         1              1              1              1
         0              1              1              1
         0              0              0              1
         1              0              0              1
         1              1              0              1
         0              1              0              1

1. Single Point
2. Two Point
3. Three Point
Enter your choice : 3

Enter centre of projection on x-axis : -10
Enter centre of projection on y-axis : -10
Enter centre of projection on z-axis : 10

UPDATES COORDINATES OF OBJECT ARE :

         0              0              0            0.9
         1              0              0              1
         1              1              0            1.1
         0              1              0              1
         0              0              0              1
         1              0              0            1.1
         1              1              0            1.2
         0              1              0            1.1

Do you want to continue (y/n) : n

--------------------------------
Process exited after 400 seconds with return value 0
Press any key to continue . . .		
*/
