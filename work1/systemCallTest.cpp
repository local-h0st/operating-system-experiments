#include <iostream>
#include <fstream>
using namespace std;

int main(){
    char sf[20];
    char df[20];
    char data[5];
    cout<<"input source file name here: ";
    cin>>sf;
    cout<<"input destiny file name here: ";
    cin>>df;
    ifstream sourcefile(sf,ios::in);
    if(!sourcefile.is_open()){
        cout<<"source file not found."<<endl;
        return 0;
    }
    ifstream dfexist(df,ios::in);
    if(dfexist.is_open()){
        cout<<"destiny file already exists."<<endl;
        dfexist.close();
        sourcefile.close();
        return 0;
    }
    ofstream destinyfile(df);
    char c;
    while((c=sourcefile.get())!=EOF){
        destinyfile<<c;
    }
    destinyfile.close();
    sourcefile.close();
    cout<<"file copied from "<<sf<<" to "<<df<<" successfully."<<endl;
    return 0;
}

// 这个就是我的作业写的代码