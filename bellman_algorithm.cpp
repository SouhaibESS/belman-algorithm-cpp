
/**
 *  Hello guys this is your frien souhaib if there's any bug try to contact me at
 *   email:<souhaibue@gmail.com>
*/


#include<iostream>
#define INF 10000000 // infinity
#define NINF -10000000 // negative infinity

using namespace std;

// a directed edge
class Arc
{
public:
    int to, from, cost;
    Arc(int from, int to, int cost):from(from),to(to),cost(cost) {}
    ~Arc();
};

// a directed path
typedef struct {
    int to, from, dist;
}path; // path structure Path is defines by the source node : from , destination : to , distance :dist

/**
 * an implementation of the Bellman algorithm to finds the shortest path between a starting node and all other nodes in the graph
 * if a node is part of a negative cycle then the minimum cost for that node is set to -10000000
 *
 * params :
 *  arcs an array of directed arcs
 *  numArcs number of arcs in the graph
 *  numNodes number of nodes in the graph
 *  start the id of the starting node
 */

path* bellmaAlgo(Arc **arcs, int numArcs, const int numNodes, int start)
{
    path *pathes = new path [numNodes]; // an array of type path
    for(int i = 0; i < numNodes ; i++)
    {                           // initialize the array values
        pathes[i].dist = INF;   // distane = infinity
        pathes[i].from = -1;    // from =  -1 no source node
        pathes[i].to = i;       // to itself
    }

    // initialize the values of the starting node
    pathes[start].dist = 0; // distance to it = 0
    pathes[start].from = start; // from itself
    pathes[start].to = start; // to itself

    for(int iteration = 0 ; iteration < numNodes - 1; iteration++ ) // iterate throught the nodes and modifying the path if its possible
    {
        for(int arcIndex = 0 ; arcIndex < numArcs ; arcIndex++ ) // iterates throught the arcs
            if(arcs[arcIndex]->cost + pathes[arcs[arcIndex]->from].dist < pathes[arcs[arcIndex]->to].dist) // if d(u)+C(u,v) < d(v)
            {
                pathes[arcs[arcIndex]->to].dist = arcs[arcIndex]->cost + pathes[arcs[arcIndex]->from].dist; // d(v) = d(u)+C(u,v)
                pathes[arcs[arcIndex]->to].from = arcs[arcIndex]->from; // modifying the source to the node
            }

        // displays the changes at each iteration
        cout<<"=========== iteration  ("<<iteration + 1<<")   ===========\n";
        cout<<" source ("<<start + 1<<")\n";
        cout<<"    |\n";
        for(int i = 0 ; i < numNodes ; i++)
        {
            cout<<"    |-> node ("<<i + 1<<") ";
            cout<<"| from node: ("<<pathes[i].from + 1<<")";
            cout<<" | cost : "<<pathes[i].dist;
            if(pathes[i].dist == INF)
                cout<<" no path";
            else if(pathes[i].dist == NINF)
                cout<<" infinite loop";

            cout<<" \n";
        }
        cout<<"\n\n=============================================\n\n";
    }

    // run algorithm a second time to detect which nodes are part
    // of a negative cycle. A negative cycle has occurred if we
    // can find a better path beyond the optimal solution.
    for(int iteration = 0 ; iteration < numNodes; iteration++ )
    {
        for(int arcIndex = 0 ; arcIndex < numArcs ; arcIndex++ )
            if(arcs[arcIndex]->cost + pathes[arcs[arcIndex]->from].dist < pathes[arcs[arcIndex]->to].dist)
            {
                pathes[arcs[arcIndex]->to].dist = NINF;
                pathes[arcs[arcIndex]->to].from = arcs[arcIndex]->from;
            }
    }

    return pathes;
}


int main(int argc, char const *argv[])
{
    int numNodes = 9, numArcs = 10, start = 1, from ,to ,cost, choix = 1;
    Arc **Arcs;

    // try this it will output

    /** OUTPUT :
     * source (1)
     *   |
     *   |-> node (1) | from node: (1) | cost : 0
     *   |-> node (2) | from node: (1) | cost : 1
     *   |-> node (3) | from node: (4) | cost : -10000000 infinite loop
     *   |-> node (4) | from node: (5) | cost : -10000000 infinite loop
     *   |-> node (5) | from node: (3) | cost : -10000000 infinite loop
     *   |-> node (6) | from node: (2) | cost : 5
     *   |-> node (7) | from node: (2) | cost : 5
     *   |-> node (8) | from node: (6) | cost : 8
     *   |-> node (9) | from node: (0) | cost : 10000000 no path
    */
    Arcs = new Arc*[numArcs];
    Arcs[0] = new Arc(0, 1, 1);
    Arcs[1] = new Arc(1, 2, 1);
    Arcs[2] = new Arc(2, 4, 1);
    Arcs[3] = new Arc(4, 3, -3);
    Arcs[4] = new Arc(3, 2, 1);
    Arcs[5] = new Arc(1, 5, 4);
    Arcs[6] = new Arc(1, 6, 4);
    Arcs[7] = new Arc(5, 6, 5);
    Arcs[8] = new Arc(6, 7, 4);
    Arcs[9] = new Arc(5, 7, 3);

    path *pathes = bellmaAlgo(Arcs, numArcs, numNodes, start - 1);

    cout<<"=========== final iteration  ===========\n";
    cout<<" source ("<<start<<")\n";
    cout<<"    |\n";
    for(int i = 0 ; i < numNodes ; i++)
    {
        cout<<"    |-> node ("<<i + 1<<") ";
        cout<<"| from node: ("<<pathes[i].from + 1<<")";
        cout<<" | cost : "<<pathes[i].dist;
        if(pathes[i].dist == INF)
            cout<<" no path";
        else if(pathes[i].dist == NINF)
            cout<<" infinite loop";

        cout<<" \n";
    }

    cout<<"\n==================================================================================\n";
    cout<<"\n\n\t\tthis was just a test to show you how the program works \n";
    cout<<"\t\t\t\t try it yourself now\n";
    cout<<"\n==================================================================================\n";

    while (choix)
    {
        cout<<"\n\n=============================================\n\n";

        cout<<"          saisir le nombre des cellules (nombre positive)\n";
        cin>>numNodes;
        cout<<"          saisir le nombre des arcs\n";
        cin>>numArcs;
        Arcs = new Arc*[numArcs];
        for(int i = 0 ; i < numArcs ; i++)
        {
            cout<<"          ARC ("<<i + 1<<")          //(les valeurs doivent etre strictement positive)//\n";
            cout<<"numero la cellule de depart de l'arc ("<<i + 1<<") = ";
            cin>>from;
            cout<<"numero la cellule d'arriver de l'arc ("<<i + 1<<") = ";
            cin>>to;
            cout<<"poids de l'arc ("<<i + 1<<") = ";
            cin>>cost;
            cout<<"\n";

            Arcs[i] = new Arc(from - 1, to - 1, cost);

        }

        cout<<"le numero de cellule de depart\n";
        cin>>start;

        cout<<"          saisie bien effectué\n";

        pathes = bellmaAlgo(Arcs, numArcs, numNodes, start - 1);

        cout<<"=========== final iteration  ===========\n";
        cout<<" source ("<<start<<")\n";
        cout<<"    |\n";
        for(int i = 0 ; i < numNodes ; i++)
        {
            cout<<"    |-> node ("<<i + 1<<") ";
            cout<<"| from node: ("<<pathes[i].from + 1<<")";
            cout<<" | cost : "<<pathes[i].dist;
            if(pathes[i].dist == INF)
                cout<<" no path";
            else if(pathes[i].dist == NINF)
                cout<<" infinite loop";

            cout<<" \n";
        }

        cout<<"\n\n=============================================\n\n";
        cout<<"do you want to test another graph?\n(YES=1 , NO=0) : ";
        cin>>choix;
    }
    

    return 0;
}
