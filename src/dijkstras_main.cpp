#include "dijkstras.cpp"


void testDijkstras() {
    Graph G;
    file_to_graph("small.txt", G);

    int source = 0;
    int destination = 4;

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    vector<int> path = extract_shortest_path(distances, previous, destination);

    if (distances[destination] == INF) {
        cout << "No path from " << source << " to " << destination << "." << endl;
    } else {
        print_path(path, distances[destination]);
    }

}

int main() {
    testDijkstras();

}