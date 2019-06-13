#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <queue>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"


using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
deque<pair<int,int> >edges;

void findcircuit(int x,int node_size,vector<vector<int>> &map,int walking_dis);
void dikjstra(int source,int node_size,vector<vector<int>> &map,int parent[],bool visit[],int d[]);
int main(int argc, char** argv){
    
    Vertex *node;
    vector<Vertex*> node_name;
    vector<Vertex*> odd_node;
    int *begin;
    int walking_dis=0;
    int *parent = new int[node_name.size()];
    int *d = new int[node_name.size()];
    bool *visit = new bool[node_name.size()];
   // build basic topo
    nm->interpret("topo3.txt");
    node = nm->get_all_nodes();
    while(node!=0){
        node_name.push_back(node);
        node=node->next;
        cout<<"node = "<<node_name[0]->name<<endl;
    }

    int *degree;
    degree= new int[node_name.size()];



    cout<<"node_name size= "<<node_name.size()<<endl;

//-----------------------count degree---------------------//
    for(int i=0;i<node_name.size();i++)
        degree[i]=0;
    for(int i=node_name.size()-1;i>0;i--){
        for(int j=0;j<i;j++){
            if(nm->connected(node_name[i]->name,node_name[j]->name)==0){
                degree[i]++;
                degree[j]++;
            }
        }
        if(degree[i]%2==1){
            odd_node.push_back(node_name[i]); 
            *begin=i;
 
        }
    }
    if(*begin>1000)
        *begin=0;

//cout degree and odd nodes

    for(int x=0;x<node_name.size();x++)
        cout<<"degree ["<<node_name[x]->name<<"] = "<<degree[x]<<endl; 
    cout<<"odd nodes = "<<odd_node.size()<<" : ";
    for(int x=0;x<odd_node.size();x++)
        cout<<odd_node[x]->name<<"  "; 
    cout<<endl;
//------------------------make a map--------------------//
    vector<vector<int>> map(node_name.size(),vector<int>(node_name.size(),0));
    for(int i=0;i<node_name.size();i++)     
        for(int j=0;j<node_name.size();j++) 
            map[i][j]=0;

    for(int i=node_name.size()-1;i>0;i--){
        for(int j=0;j<i;j++){
            if(nm->connected(node_name[i]->name,node_name[j]->name)==0){
                map[i][j]++;
                map[j][i]++;
            }
        }
    }

    for(int i=0;i<node_name.size();i++){     
        for(int j=0;j<node_name.size();j++) {
            cout<<"map ["<<i<<"] ["<<j<<"]= "<<map[i][j]<<"  ";
            if(j==node_name.size()-1) cout<<endl;
        }
    }
//-------------------------------------------------------------------------//
//check dikjstra

dikjstra(*begin,node_name.size(),map,parent,visit,d);
//------------------------findpath-----------------------------------------//
    cout<<"begin = "<<*begin<<endl;
    findcircuit(*begin,node_name.size(),map,walking_dis);
        cout<<" path ="<<endl;
    for(int i=0;i<edges.size();i++)
        cout<< edges[i].first<< "-----"<<edges[i].second<<endl;

    cout<<"walking distance=  "<<walking_dis<<endl;


    // using gplot to export a dot file, and then using graphviz to generate the figure
    Gplot *gp = new Gplot();
    gp->gp_add(nm->elist);
    gp->gp_dump(true);
    gp->gp_export("plot");

    return 0;
}
//---------------------------function-------------------------------//

void findcircuit(int x,int node_size,vector<vector<int>> &map,int walking_dis)
{
    for(int y=0;y<node_size;y++){
        if(map[x][y]>0)
        {
            map[x][y]--;
            if(x!=y) 
            {
                map[y][x]--;
                edges.push_back(make_pair(x,y));
            //    walking_dis++;
                findcircuit(y,node_size,map,walking_dis);

            }
           
            break;
        }

 //   cout<<"walking distance  2=  "<<walking_dis<<endl;
    }
}
/*
void addpath(vector<Vertex*> &odd_node,vector<vector<int>> &map)
{  
    for(int i=0;i<odd_node.size();i++)
    {
   

    }
    




}

*/

void dikjstra(int source, int node_size,vector<vector<int>> &map,int parent[],bool visit[],int d[])
{
    cout<<" in dikjstra"<<endl;
    for(int i=0;i<node_size;i++) {
        visit[i]=false;
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
              //  cout<<"d ["<<i<<"]  = "<<d[i]<<endl;
                a=i;
                min=d[i];
            }
        }
    if(a==-1)
        break;//finish connecting
    visit[a]=true;

    for(b=0;b<node_size;b++){
            //cout<<"in for "<<endl; 
            //cout<<"visit[ "<<b<<"]="<<visit[b]<<endl;
        //    cout<<"d ["<<b<<"]  = "<<d[b]<<endl;
       //     cout<<"map["<<a<<"]["<<b<<"] = "<<d[a]+map[a][b]<<endl; 
        if(visit[b]==false && d[a]+map[a][b]<d[b] /*&& map[a][b]!=0*/)
        {
            d[b]=d[a]+map[a][b];
            parent[b]=a;
            cout<<"parent ["<<b<<"] = "<<parent[b]<<endl; 
        }
    }
    }        
        
}





