#ifndef OI_CODES_GRAPH_H
#define OI_CODES_GRAPH_H

#include <vector>

class Graph {
public:
    Graph(bool _directed,int _weightType):directed(_directed),weightType(_weightType){};
private:
    //Base Information - Begin
    bool directed;
    int weightType;// 0:unweighted  1:edge weighted 2: node weighted

    //Base Information - End

    //Base Structure - Begin
    struct EDGE {
        int next;
        int destination;
        int weight;
    };
    struct NODE {
        int weight;
        int head;
    };

    std::vector<EDGE> edge;
    std::vector<NODE> node;
    //Base Structure - End
};

#endif //OI_CODES_GRAPH_H
