#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <cmath>
/*
///how ini file should look like
[ section ]
name-of-variable = value-of-variable

nameOfProduct = bus info sign //string
numberOfPixels = 21 //integer ranges from x to y
height = //double in meters //we can't produce bigger signs than x,y,z
width = //double in meters
depth = //double in meters
isLed = true/false //if this sign is made of led diodes/lamps //is it glowing with their own light?
*/

using namespace std;
//defining maximum values, could be implemented differently
#define MAX_HEIGHT 0.6
#define MAX_WIDTH 1.1
#define MAX_DEPTH 0.3
#define MAX_NUMBEROFPIXELS 32*256

//global variables, could be replaced with some nifty table/vector/list
string nameOfProduct="";
int numberOfPixels;
double height;
double width;
double depth;
bool isLed;


bool validate(char* name,char* arg){//check is value of certain variable is in correct range, but doesn't save them anywhere
    if(strcmp(name,"isLed")==0){
        if(strcmp(arg,"true")==0){
            return true;
        }else if(strcmp(arg,"false")==0){
            return true;
        }else{
            cout<<arg<<" wrong value of isLed parameter! (true/false)"<<endl;
            return false;
        }
    }else if(strcmp(name,"nameOfProduct")==0){
        string temp(arg);
        if(temp==""){
            cout<<temp<<" wrong value for nameOfProduct param! string cannot be empty!"<<endl;
            return false;
        }
        else{
            return true;
        }
    }else if(strcmp(name,"height")==0){
        double temp=(atof(arg));
        //cout<<"double height is "<<temp<<endl;
        if(temp > 0 && temp <= MAX_HEIGHT){
            return true;
        }
        else {
            cout<<temp<<" wrong height value, must be in range from 0 to "<<MAX_HEIGHT<<" and remember to use [.] dot instead of [,] comma"<<endl;
            return false;
        }
    }else if(strcmp(name,"width")==0){
        double temp=(atof(arg));
        //cout<<"double width is "<<temp<<endl;
        if(temp >0 && temp <= (MAX_WIDTH)){
            return true;
        }
        else{
            cout<<temp<<" wrong width value, must be in range from 0 to "<<MAX_WIDTH<<" and remember to use [.] dot instead of [,] comma"<<endl;
            return false;
        }
    }else if(strcmp(name,"depth")==0){
        double temp=(atof(arg));
        //cout<<"double depth is "<<temp<<endl;
        if(temp >0 && temp <= MAX_DEPTH){
            return true;
        }
        else {
            cout<<temp<<" wrong depth value, must be in range from 0 to "<<MAX_DEPTH<<" and remember to use [.] dot instead of [,] comma"<<endl;
            return false;
        }
    }else if(strcmp(name,"numberOfPixels")==0){
        int temp=atoi(arg);
        //cout<<"int numberOfPixels is "<<temp<<endl;
        if(temp >0 && temp <= MAX_NUMBEROFPIXELS){
            //numberOfPixels=temp;
            return true;
        }else {
            cout<<"number of pixels should range from 0 to "<<MAX_NUMBEROFPIXELS<<endl;
            return false;
        }
    }else cout<<"value not implemented!"<<endl;
    //cout<<arg<<endl;

    return false;
}

void update(char* name,char* arg){//sets global variables based on raw main function argument and name of variable
    //kinda dangerous, because it doesn't check value, you are forced to use validate() function beforehand
    if(strcmp(name,"isLed")==0){
        if(strcmp(name,"true") || strcmp(name,"True")==0){
            isLed=true;
        }else if(strcmp(name,"false") || strcmp(name,"False")==0){
            isLed=false;
        }
    }else if(strcmp(name,"nameOfProduct")==0){
        nameOfProduct=arg;
    }else if(strcmp(name,"height")==0){
        height=atof(arg);
    }else if(strcmp(name,"width")==0){
        width=atof(arg);
    }else if(strcmp(name,"depth")==0){
        depth=atof(arg);
    }else if(strcmp(name,"numberOfPixels")==0){
        numberOfPixels=atoi(arg);
    }
}

bool saveConfiguration(){//wipes config file and saves global variables as files
    fstream config("example.ini",ios::out | ios::trunc);
    config<<"[ Bus information sign ]\n";
    config<<"nameOfProduct = "<<nameOfProduct<<endl;
    config<<"numberOfPixels = "<<numberOfPixels<<endl;
    config<<"height = "<<height<<endl;
    config<<"width = "<<width<<endl;
    config<<"depth = "<<depth<<endl;
    config<<"isLed = "<<((isLed==0)?"false":"true")<<endl;
    config.close();
    return true;
}

void scrape(string line,string &valname,string &arg){//scrapes variable name and it's value from the line of ini file, supports spaces in it's values
    int spaceCounter=2;
    for(int i=0;i<line.length();i++){
        if(line[i]==' ')spaceCounter--;
        if(spaceCounter==2){
            if(line[i]!=' ')valname+=line[i];
        }else if(spaceCounter<2 && spaceCounter>0){
            ;
        }else{
            if(line[i]!=' ')arg+=line[i];
        }
    }
    //cout<<line<<"|"<<valname<<"|"<<arg<<endl;
}

void loadConfiguration(int argc){//loads config file, scrapes it's contents and loads values into correct global variables, it doesn't check it's correctness, please don't judge me, I know I could done it better
    fstream config("example.ini");

    int i=0;
    string line="";
    string valname="";
    string arg="";
    while (getline(config,line))
    {
        i++;
        scrape(line,valname,arg);
        //cout<<line<<" | "<<valname<<" | "<<arg<<endl;

        char* cvalname=new char[valname.length() + 1];
        char* carg=new char[arg.length() + 1];

        strcpy(cvalname, valname.c_str());
        strcpy(carg, arg.c_str());
        if(argc==1 && i>1)validate(cvalname,carg);
        update(cvalname,carg);
        if(argc==1 && i>1)cout<<cvalname<<" is loaded value is:"<<carg<<endl;

        line="";
        valname="";
        arg="";

        delete[] cvalname;
        delete[] carg;
    }

    config.close();
}

int main(int argc, char *argv[]){//that's a main function!
    cout<<"Loading variables from configuration file"<<endl;
    loadConfiguration(argc);//loads values of global variables from file example.ini

    for(int i=1;i+1<argc;i+=2){//overall handling of main function arguments, to much redundancy, potential for code refactoring
            //while getting variables from the user, values are checked and are changed ONLY when correct
        if(strcmp(argv[i],"-isLed")==0){
            if(validate("isLed",argv[i+1])){
                update("isLed",argv[i+1]);
                cout<<"isLed updated to:"<<argv[i+1]<<endl;
            }
        }else if(strcmp(argv[i],"-nameOfProduct")==0){
            if(validate("nameOfProduct",argv[i+1])){
                update("nameOfProduct",argv[i+1]);
                cout<<"nameOfProduct updated to:"<<argv[i+1]<<endl;
            }
        }else if(strcmp(argv[i],"-height")==0){
            if(validate("height",argv[i+1])){
                update("height",argv[i+1]);
                cout<<"height updated to:"<<argv[i+1]<<endl;
            }
        }else if(strcmp(argv[i],"-width")==0){
            if(validate("width",argv[i+1])){
                update("width",argv[i+1]);
                cout<<"width updated to:"<<argv[i+1]<<endl;
            }
        }else if(strcmp(argv[i],"-depth")==0){
            if(validate("depth",argv[i+1])){
                update("depth",argv[i+1]);
                cout<<"depth updated to:"<<argv[i+1]<<endl;
            }
        }else if(strcmp(argv[i],"-numberOfPixels")==0){
            if(validate("numberOfPixels",argv[i+1])){
                update("numberOfPixels",argv[i+1]);
                cout<<"numberOfPixels updated to:"<<argv[i+1]<<endl;
            }
        }else cout<<"parameter "<<argv[i]<<" was not implemented!"<<endl;
    }
    cout<<endl;

    saveConfiguration();//saves configuration to file

}
