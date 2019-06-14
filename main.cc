#include <iostream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <queue>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

#define INPUT "topo3" //define input file
#define OUTPUT "postman_path3" //define input file
using namespace std;
  
// create NetworkManager first
NetworkManager *nm = new NetworkManager();

deque<pair<int,int> >edges;//for euler

void findcircuit(int x,int node_size,vector<vector<int>> &map,int edge_num);
void dikjstra(int source,int node_size,vector<vector<int>> &map,int parent[],bool visit[],int d[]);
void addpath(int source2,vector<Vertex*>&node_name,int parent[],vector<vector<int>> &map,int &edge_num); 

int main(int argc, char** argv){

    Vertex* node=NULL;
    vector<Vertex*> node_name;
    vector<int> record_odd;
    int *begin=new int;
    int edge_num=0;

   // build topo
    nm->interpret(INPUT".txt");
    node = nm->get_all_nodes();

    while(node!=0){
        node_name.push_back(node);
        node=node->next;
    }
    delete node;

    int *degree;
    degree= new int[node_name.size()];
//-----------dikjstra------------//
    int *parent = new int[node_name.size()];
    int *d = new int[node_name.size()];
    bool *visit = new bool[node_name.size()];
//-------------------------------//

    cout<<"node_name size= "<<node_name.size()<<endl;

//----------------------1. count degree-----------------------//
    for(int i=0;i<node_name.size();i++)
        degree[i]=0;
    for(int i=node_name.size()-1;i>0;i--){
        for(int j=0;j<i;j++){
            if(nm->connected(node_name[i]->name,node_name[j]->name)==0){
                degree[i]++;
                degree[j]++;
            }
        }
    }
//---------------------2. find odd degree---------------------//
    *begin=1001;
    for(int i=0;i<node_name.size();i++){
        if(degree[i]%2==1){
           // odd_node.push_back(node_name[i]); 
            record_odd.push_back(i);
            *begin=i;
        }
    }
    if(*begin>1000)
        *begin=0;

    for(int x=0;x<node_name.size();x++)
        cout<<"degree ["<<node_name[x]->name<<"] = "<<degree[x]<<endl; 
        cout<<"record odds = "<<record_odd.size()<<" : ";
    for(int x=0;x<record_odd.size();x++)
        cout<<node_name[record_odd[x]]->name<<"  "; 
    cout<<endl;
//----------------------3. make an adjacent matrix(map)--------------------//
    vector<vector<int>> map(node_name.size(),vector<int>(node_name.size(),0));
    for(int i=0;i<node_name.size();i++)     
        for(int j=0;j<node_name.size();j++) 
            map[i][j]=0;

    for(int i=node_name.size()-1;i>0;i--){
        for(int j=0;j<i;j++){
            if(nm->connected(node_name[i]->name,node_name[j]->name)==0){
                map[i][j]++;
                map[j][i]++;
                edge_num++;
            }
        }
    }
    cout<<"--------------------------------- INITIAL MAP --------------------------------"<<endl;
    for(int i=0;i<node_name.size();i++){     
        for(int j=0;j<node_name.size();j++) {
            cout<<"map ["<<i<<"] ["<<j<<"]= "<<map[i][j]<<"  ";
            if(j==node_name.size()-1) cout<<endl;
        }
    }
//--------------------- 4. if odd node >=2, add path-----------------------//
//check dikjstra
    for(int x=0;x<record_odd.size();x=x+2){
        cout<<endl<<"-----------"<<endl;
        cout<<" add new path of two odds : " <<node_name[record_odd[x]]->name<<"   "<<node_name[record_odd[x+1]]->name <<endl;
        dikjstra(record_odd[x],node_name.size(),map,parent,visit,d);
        addpath(record_odd[x+1],node_name,parent,map,edge_num);
    }
//---------------------------print new map------------------------------------//
    cout<<"------------------------------- I AM NEW MAP ---------------------------------"<<endl;
    for(int i=0;i<node_name.size();i++){     
        for(int j=0;j<node_name.size();j++) {
            cout<<"map ["<<i<<"] ["<<j<<"]= "<<map[i][j]<<"  ";
            if(j==node_name.size()-1) cout<<endl;
        }
    }
//-----------------------  5. find euler path-------------------------------//
    ofstream file;
    file.open(OUTPUT".txt");
    cout<<endl<<"begin = "<<node_name[*begin]->name<<endl;
    findcircuit(*begin,node_name.size(),map,edge_num);
        cout<<"###################################### "<<endl;
        cout<<" < CHINESE POST MAN WALKING PATH > "<<endl;
        cout<<"###################################### "<<endl;
    for(int i=0;i<edges.size();i++){
        cout<< "              "<<node_name[edges[i].first]->name<< "-----"<<node_name[edges[i].second]->name<<endl;
        file<< node_name[edges[i].first]->name;
        file<< "---";
        file<< node_name[edges[i].second]->name;
        file<< "\n";
    }
        
    cout<<"            walking distance=  "<<edges.size()<<endl;
   // cout<<"edge num=  "<<edge_num<<endl;
    cout<<"------------------------------- FINAL CLEAR MAP --------------------------------"<<endl;
    for(int i=0;i<node_name.size();i++){     
        for(int j=0;j<node_name.size();j++) {
            cout<<"map ["<<i<<"] ["<<j<<"]= "<<map[i][j]<<"  ";
            if(j==node_name.size()-1) cout<<endl;
        }
    }   
    file.close();
    // using gplot to export a dot file, and then using graphviz to generate the figure
    Gplot *gp = new Gplot();
    gp->gp_add(nm->elist);
    gp->gp_dump(true);
    gp->gp_export("plot");

    return 0;
}
//---------------------------other functions-------------------------------//

void findcircuit(int x,int node_size,vector<vector<int>> &map,int edge_num)
{
    for(int y=0;y<node_size;y++){
        if(map[x][y]>0)
        {
            map[x][y]--;
            if(x!=y) 
            {
                map[y][x]--;
                edges.push_back(make_pair(x,y));
              //  cout<<"make -------"<<x<<" and  "<<y<<endl;
                findcircuit(y,node_size,map,edge_num);
            }
           // cout<<"find distance = "<<edges.size()<<endl;

            if(edges.size()!=edge_num)
            {
              //  cout<<"deal -------"<<x<<" and  "<<y<<endl;
                map[y][x]++;
                map[x][y]++;
                edges.pop_back();                    
            }             
            else
                break;
        }
    }
}

void addpath(int source2,vector<Vertex*>&node_name,int parent[],vector<vector<int>> &map,int &edge_num)
{
    if(source2!=parent[source2])
    {
        addpath(parent[source2],node_name,parent,map,edge_num);
        nm->connect(node_name[source2]->name,node_name[parent[source2]]->name);
        cout<<" add path "<< node_name[source2]->name<<"-----"<<node_name[parent[source2]]->name<<endl;
        map[source2][parent[source2]]++;
        map[parent[source2]][source2]++;
        edge_num++;

  
    }
}

void dikjstra(int source, int node_size,vector<vector<int>> &map,int parent[],bool visit[],int d[])
{
  //  cout<<" in dikjstra"<<endl;
    for(int i=0;i<node_size;i++) {
        visit[i]=false;
        parent[i]=0;
        d[i]=1000;
    }
    d[source]=0;
    parent[source]=source;
    for(int i=0;i<node_size;i++) {
        int a=-1;
        int b=-1;
        int min=1000;

        for(int i=0;i<node_size;i++){
            if(visit[i]==false&&d[i]<min)
            {
                a=i;
              //  cout<<"a= "<<a<<endl;
                min=d[i];
            }
        }
        if(a==-1)
          break;//finish connecting
        visit[a]=true;

        for(b=0;b<node_size;b++){
            //cout<<"in for "<<endl; 
            //cout<<"visit[ "<<b<<"]="<<visit[b]<<endl;
          //  cout<<"d ["<<b<<"]  = "<<d[b]<<endl;
         //   cout<<"d[a]+map["<<a<<"]["<<b<<"] = "<<d[a]+map[a][b]<<endl; 
            if(visit[b]==false && d[a]+map[a][b]<d[b] && map[a][b]!=0)
            {
                d[b]=d[a]+map[a][b];
                parent[b]=a;
             
                //cout<<"parent ["<<b<<"] = "<<parent[b]<<endl; 
            }
        }
    }               
}



