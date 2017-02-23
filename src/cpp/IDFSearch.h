#ifndef IDFSEARCH_H
#define IDFSEARCH_H

#include <algorithm>
#include <iostream>


using std::find;
using std::cout;

#include <vector>
using std::vector;


template <class T> class IDFSearch {

public:
  IDFSearch(){};

  bool start(T start,bool (*isGoal)(T &state), vector<T> &path, int maxDepth){
    return start(start, isGoal, path, maxDepth, 0);
}

  bool start(T start,bool (*isGoal)(T &state), vector<T> &path, int maxDepth, int startDepth){

    int visitedSize = 0;
    for (int i=startDepth; i<maxDepth; i++){
        vector<T> visited;
        cout << "search depth:" << i << "\n";
        if (search(start, isGoal, visited, path, i)){
            cout << "visited " << visited.size() << " nodes.\n";
            path.push_back(start);
            return true;
        }

        if (visitedSize == visited.size()){
            cout << "no more states \n";
            return false;
        }
        visitedSize = visited.size();
    };

    return false;
}

private:
  bool search(T node, bool (*isGoal)(T &state), vector<T> &visited, vector<T> &path, int depth){

    if (isGoal(node)){
        return true;
    }

    if (depth == 0){
        return false;
    }

    vector<T> childrens = node.childrens();

    for (typename vector<T>::iterator it = childrens.begin(); it != childrens.end(); it++){
        T state = (*it);
        typename vector<T>::const_iterator result = find(visited.begin(), visited.end(), state);
        if (result == visited.end()){
            visited.push_back(state);
            if (search(state, isGoal, visited, path, depth-1)){
                path.push_back(state);
                return true;
            }
        }
    }

    return false;
}

};

#endif
