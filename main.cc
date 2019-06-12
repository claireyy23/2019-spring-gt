#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();

int main(int argc, char** argv){
    // build basic topo
    Vertex *node;
    vector<Vertex*> node_name;
    vector<Vertex*> odd_node;

    nm->interpret("topo.txt");
    node = nm->get_all_nodes();
    while(node!=0){
        node_name.push_back(node);
        node=node->next;
        cout<<"node = "<<node_name[0]->name<<endl;
    }

    int *degree;
    degree= new int[node_name.size()];
    cout<<"node_name size= "<<node_name.size()<<endl;

    for(int i=0;i<node_name.size();i++)
        degree[i]=0;

    for(int i=node_name.size()-1;i>0;i--){
   cout<<" i= "<<i<<endl;
        for(int j=0;j<i;j++){
   cout<<" j= "<<j<<endl;
   //cout<<" node_name[i]= "<<node_name[i]->node_name<<endl;
            if(nm->connected(node_name[i]->name,node_name[j]->name)==0){
                degree[i]++;
                degree[j]++;

            }
        }
        if(degree[i]%2==1)
            odd_node.push_back(node_name[i]); 

    }

//cout degree and odd nodes

    for(int x=0;x<node_name.size();x++)
        cout<<"degree ["<<node_name[x]->name<<"] = "<<degree[x]<<endl; 
   
      
    






    // using gplot to export a dot file, and then using graphviz to generate the figure
    Gplot *gp = new Gplot();
    gp->gp_add(nm->elist);
    gp->gp_dump(true);
    gp->gp_export("plot");

    return 0;
}
