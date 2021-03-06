//Class for generating test case graphs
//Daanyaal du Toit
//Created: 22 August 2013
//Last Modified: 22 August 2013

#ifndef GRAPHGEN_H_INCLUDED
#define GRAPHGEN_H_INCLUDED

#include "Pathfinder.h"
#include "NodeManager.h"
#include <fstream>
#include "time.h"

namespace ADStar{

    class GraphGen{

        public:
            void read(std::string inFile){

                using namespace std;

                ifstream fileIn(inFile.c_str());

                int num_verts;
                fileIn >> num_verts;

                for(int i = 0; i < num_verts; ++i){

                    float x, y ,z;
                    fileIn >> x >> y >> z;
                    vertex_props vp;
                    vp.x = x;
                    vp.y = y;
                    vp.z = z;
                    add_vertex(vp, g);

                    }

                while(!fileIn.eof()){

                    int ind_One, ind_Two;
                    float weight;
                    fileIn >> ind_One >> ind_Two >> weight;
                    add_edge(ind_One, ind_Two, weight, g);

                }

            }

            void readPLY(std::string inFile){



            }


            void convert(std::string inFile, std::string outFile){

                using namespace boost;
                using namespace std;

                ifstream fileIn(inFile.c_str());

                string scrap;
                int num_verts, num_edges;

                fileIn >> scrap >> scrap >> num_verts;
                fileIn >> scrap >> scrap >> num_edges;

                for(int i = 0; i < num_verts; ++i){

                    float x, y ,z;
                    fileIn >> x >> y >> z;
                    vertex_props vp;
                    vp.x = x;
                    vp.y = y;
                    vp.z = z;
                    add_vertex(vp, g);
                    fileIn >> z >> z;

                    }

                srand(time(NULL));

                for(int i = 0; i < num_edges; ++i){

                    int ind_One, ind_Two, ind_Three;
                    fileIn >> ind_One >> ind_One >> ind_Two >> ind_Three;
                    if(!edge(ind_Two, ind_One, g).second)
                    add_edge(ind_One, ind_Two, rand() % 51 + 20, g);
                    if(!edge(ind_Three, ind_One, g).second)
                    add_edge(ind_One, ind_Three, rand() % 51 + 20, g);
                    if(!edge(ind_Two, ind_Three, g).second)
                    add_edge(ind_Three, ind_Two, rand() % 51 + 20, g);

                }

                std::ofstream fileOut(outFile.c_str());

                fileOut << num_verts << endl;

                for(int i = 0; i < num_verts; ++i)
                fileOut << g[i].x << " " << g[i].y << " " << g[i].z << endl;

                std::pair<graph_traits<WeightedGraph>::edge_iterator
                                        , graph_traits<WeightedGraph>::edge_iterator> er = edges(g);

                for(graph_traits<WeightedGraph>::edge_iterator it = er.first; it != er.second; ++it)
                    fileOut << source(*it, g) << " " << target(*it, g) << " " << get(edge_weight, g, *it) << endl;

            }
            WeightedGraph g;
            PathPoly_3 p;


    };

}

#endif // GRAPHGEN_H_INCLUDED
