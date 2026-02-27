#include<iostream>
#include<cstdlib>
using namespace std;

int main(int arg, char* argv[]){
    float sum = 0;
    
    for(int i = 1; i < arg; i++){
        sum += atof(argv[i]);
    }
    float avg = sum/(arg-1);
    if(arg < 2){
        cout<<"Please input numbers to find average."<<endl;
    }else{
    cout<<"---------------------------------"<<endl;
    cout<<"Average of "<<arg-1<<" numbers = "<<avg<<endl;
    cout<<"---------------------------------"<<endl;
    }

}