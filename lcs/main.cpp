/*
 * File:   main.cpp
 * Author: zhangf30
 *
 * Created on December 8, 2014, 5:07 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <vector>


using namespace std;
using std::string;
/*
 *
 */
struct lines{
    string line;
    vector<string> comstr;
    lines *next;
};

void lcsubstring(string a, string b,lines* rt){

       lines *substr=rt;
       while(substr!=NULL){
            if(substr->line==b){
                break;
            }
            substr=substr->next;
       }
       stringstream ssa(a);
       int acount=distance(std::istream_iterator<std::string>(ssa),std::istream_iterator<std::string>());
       stringstream ssb(b);
       int bcount=distance(std::istream_iterator<std::string>(ssb),std::istream_iterator<std::string>());
     //  cout<<acount<<endl;
       //cout<<bcount<<endl;
       if(acount<1250 && bcount<1250){
                string array[acount][bcount];
                stringstream first(a);

                for(int i=0;i<acount;i++){
                        string word_a;
                        first>>word_a;
                        stringstream second(b);
                        for(int j=0;j<bcount;j++){
                                    string word_b;
                                    second>>word_b;
                                        if(word_a==word_b){
                                                array[i][j]=word_a;
                                        }
                                        else{
                                                    array[i][j]=" ";
                                            }

                        }
                }

                for(int i=0;i<acount;i++){
                        for(int j=0; j<bcount; j++){
                                    if(array[i][j]!=" "){
                                            string buffer=array[i][j]+" ";
                                            array[i][j]=" ";
                                            int k=i+1;
                                            int l=j+1;
                                            while(k<acount && l<bcount && array[k][l]!=" "){
                                                            buffer+=array[k][l]+" ";
                                                                array[k][l]=" ";
                                                                k++;
                                                                    l++;
                                                }
                 //  cout<<buffer<<endl;
                                    substr->comstr.push_back(buffer);
                                    }
                            }
                }
       }
       else{

            string Arr[acount];
            stringstream first(a);

            for (int i=0; i<acount;i++){
                    first>>Arr[i];
                   // cout<<Arr[i]<<endl;
            }

            string Brr[bcount];
            stringstream second(b);

            for (int j=0; j<acount;j++){
                    second>>Brr[j];
            }

            for(int i=0;i<acount;i++){
                    for(int j=0; j<bcount;j++){
                            if(Arr[i]==Brr[j]){
                                    string common;

                                    common = Arr[i];

                                        int k=i+1;
                                        int l=j+1;

                                        while(k<acount && l<bcount )
                                        {
                                            if(Arr[k]==Brr[l]){
                                                common += " "+Arr[k];
                                                Brr[l]=" ";
                                                k++;
                                                l++;
                                            }
                                            else{
                                                i=k-1;
                                                break;
                                            }
                                        }

                                    if(substr->comstr.empty()){
                                                substr->comstr.push_back(common);
                                    }
                                    else if(std::find(substr->comstr.begin(),  substr->comstr.end(), common) ==  substr->comstr.end()){
                                            substr->comstr.push_back(common);
                                    }
                            }

                    }
            }

        }
}




int main(int argc, char** argv) {
        if(argv[1]!=NULL){

        const char* filename=argv[1];
       // const char* filename="input5.txt";
        lines *root=new lines;
        root->line="dummy";
        root->next=NULL;
        ifstream stream1(filename);
            while(!stream1.eof())
            {
                if(!stream1.fail()){
                        string checkline;
                        getline(stream1,checkline);
                        if(!checkline.empty()){
                                 lines *newline=new lines;
                                 newline->line=checkline;
                                 newline->next=NULL;
                                if(root->next==NULL){
                                         root->next=newline;
                                }else{
                                         lines *curr=root->next;
                                         root->next=newline;
                                         newline->next=curr;
                                }
                        }
                }
            }
        lines *ordercommon=root->next;

    //    cout<<"here\n";
        while(ordercommon->next!=NULL){
                lcsubstring(root->next->line, ordercommon->next->line,root);
                ordercommon=ordercommon->next;
        }




        vector<string> finalcommons;
        lines *sortcom=root->next;


        if(sortcom->next->next==NULL){//two input lines

                int j=0;
            for(int i=0;i<sortcom->next->comstr.size();i++){
                if(sortcom->next->comstr[i].size()>sortcom->next->comstr[j].size()){
                    j=i;
                }
            }
            cout<<sortcom->next->comstr[j]<<endl;
        }
        else{//more than two



            lines *addv=sortcom->next;
            lines *vnext=addv->next;


            for(int i=0;i<addv->comstr.size();i++){
                for(int j=0;j<vnext->comstr.size();j++){
                        if(addv->comstr[i]==vnext->comstr[j]){
                            if(finalcommons.empty()){
                                finalcommons.push_back(addv->comstr[i]);
                            }
                            else{

                                if(std::find(finalcommons.begin(),  finalcommons.end(), addv->comstr[i]) == finalcommons.end()){
                                            finalcommons.push_back(addv->comstr[i]);
                                }
                            }
                        }
                }
            }
            if(finalcommons.empty()){//still empty
                for(int i=0; i<addv->comstr.size();i++){
                        finalcommons.push_back(addv->comstr[i]);
                }

                for(int j=0;j<vnext->comstr.size();j++){
                        finalcommons.push_back(vnext->comstr[j]);
                }

            }

            if(vnext->next==NULL){//ONLY 3
                int j=0;

                for(int i=0;i<finalcommons.size();i++){
                    if(finalcommons[i]>finalcommons[j]){
                            j=i;}
                    }
            cout<<finalcommons[j]<<endl;
            }
            else{


                  lines* others=vnext->next;
                  while(others!=NULL){
                      //  cout<<finalcommons.size()<<" commons size"<<endl;
                       for(int i=0; i<finalcommons.size();i++){
                            string isthere=finalcommons[i];
                            int found=0;
                            for(int j=0;j<others->comstr.size();j++){
                                 //cout<<"others "<<others->comstr[j]<<endl;
                                 if(finalcommons[i]==others->comstr[j] || others->comstr[j].find(finalcommons[i]) != string::npos/* || finalcommons[i].find(others->comstr[j]) != string::npos */){
                                    // cout<<"found "<<finalcommons[i]<<endl;
                                        found=1;
                                      break;
                                 }
                                 else if(finalcommons[i].find(others->comstr[j]) != string::npos){
                                      found=2;
                                      break;

                                 }
                            }
                            if(found==0){


                                finalcommons.erase(std::remove(finalcommons.begin(), finalcommons.end(), isthere), finalcommons.end());
                            }
                            if(found==2)
                            {
                               for(int r=0;r<finalcommons.size();r++){
                                        if(finalcommons[i].find(finalcommons[r]) != string::npos &&r!=i ){
                                                    finalcommons.erase(std::remove(finalcommons.begin(), finalcommons.end(), finalcommons[i]), finalcommons.end());
                                        }

                               }

                            }

                       }
                      others=others->next;
                  }

                  int j=0;

                  for(int i=0;i<finalcommons.size();i++){
                    if(finalcommons[i].length()>finalcommons[j].length()){
                            j=i;
                            }
                    }
                  cout<<finalcommons[j]<<endl;
            }
        }
    }
    return 0;
}

