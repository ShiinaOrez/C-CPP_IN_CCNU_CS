#include<iostream>
#include<fstream>
#include<iostream>
#include<cstdio>

using namespace std ;

int cpy(char * filename,char * newfile){
    ifstream in ;
    ofstream out ;
    in.open(filename);
    if(in.fail()){
        cout << "open file failed" << endl ;
        in.close();
        out.close();
        return 0 ;
    }
    out.open(newfile);
    if(out.fail()){
        cout<<"create file failed"<<endl ;
        in.close();
        out.close();
        return 0 ;
    }
    else {
        out<<in.rdbuf();
        out.close();
        in.close();
        return 1 ;
    }
}

int main(int argc, char* argv[]){
    char * source_name = argv[1];
    char * result_name = argv[2];
    int response = cpy(source_name, result_name);
    return 0;
}
