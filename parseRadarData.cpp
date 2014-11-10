/*Program that parse the Radar Data file
  by Yiming Yuan (gwyuan@gwmail.gwu.edu; henryontheway@gmail.com)
*/
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;
#include "parse.h"

int main(int argc, char *arg[]){
        if(argc!=2){
                cout<<"wrong argument number"<<endl;
				cout<<"usage: "<<arg[1]<<" [filename]"<<endl;
                return 1;
        }
        vector<Data> set;

        ifstream inFile(arg[1], ifstream::in);
        string str;
        while(inFile){
                Data data;
                getline(inFile, str);
                stringstream ss;
                ss<<str;
                ss>>data.date>>data.time>>data.plot>>data.side>>data.hh>>data.hv>>data.vv>>data.vh>>data.filename>>data.cycle;
                if(data.cycle=='Y'){
                        ss>>data.phi1>>data.phi2>>data.samples;
                }

                stringstream x;
                x<<data.time;
                int h,mm;
                char mid,hypen,ap,m;
                x>>h>>mid>>mm>>hypen;
                if(hypen=='-'){
                        x>>ap>>m;
                        if(ap=='P' && h!=12){
                                h=h+12;
                        }
                }

                stringstream y;
                if(h<10){
                        y<<'0'<<h;
                }
                else{
                        y<<h;
                }
                y<<mid;
                if(mm<10){
                        y<<'0'<<mm;
                }
                else{
                        y<<mm;
                }
                y>>data.time;

                set.push_back(data);
        }
        inFile.close();

        ofstream dtout, tmout, ptout, sdout, hhout, hvout, vvout, vhout, fnout, cyout, p1out, p2out, spout;
        dtout.open("Data_date.txt"); tmout.open("Data_time.txt"); ptout.open("Data_plot.txt"); sdout.open("Data_side.txt"); hhout.open("Data_HH.txt"); hvout.open("Data_HV.txt"); vvout.open("Data_VV.txt"); vhout.open("Data_VH.txt"); fnout.open("Data_filename.txt"); cyout.open("Data_cycle.txt"); p1out.open("Data_phi1.txt"); p2out.open("Data_phi2.txt"); spout.open("Data_samples.txt");

		cout<<"Exporting data...\n\n";
        
        for(unsigned int i=0; i<set.size(); ++i){
                dtout<<set[i].date<<endl;
                tmout<<set[i].time<<endl;
                ptout<<set[i].plot<<endl;
                sdout<<set[i].side<<endl;
                hhout<<set[i].hh<<endl;
                hvout<<set[i].hv<<endl;
                vvout<<set[i].vv<<endl;
                vhout<<set[i].vh<<endl;
                fnout<<set[i].filename<<endl;
                cyout<<set[i].cycle<<endl;
                if(set[i].cycle=='Y'){
                        p1out<<set[i].phi1<<endl;
                        p2out<<set[i].phi2<<endl;
                        spout<<set[i].samples<<endl;
                }
                else{
                        p1out<<endl;
                        p2out<<endl;
                        spout<<endl;
                }
        }
        dtout.close(); tmout.close(); ptout.close(); sdout.close();hhout.close(); hvout.close(); vvout.close(); vhout.close(); fnout.close(); cyout.close(); p1out.close(); p2out.close(); spout.close();
		cout<<"Finished."<<endl;

        return 0;
}

