import java.util.*;
 
public class MaxComponent {
        public static void main(String[] args) {
        Graph g = new Graph();
        g.componentFinder();
    }
}
 
class Graph {
    int N;
    int[] vertexList;
    private Map<Integer, ArrayList<Integer>> incidentList;
    private boolean[] isVisited;
    int edges = 0;
    int vertexes = 0;
 
    public Graph() {
        incidentList = new HashMap<>();
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        int M = in.nextInt();
        this.N = N;
        vertexList = new int[N];
        isVisited = new boolean[N];
 
        for(int i = 0; i < M; i++) {
            int u = in.nextInt();
            int v = in.nextInt();
            if(u != v) {
                if(incidentList.containsKey(u))
                    incidentList.get(u).add(v);
                else {
                    ArrayList<Integer> valuesOfKey = new ArrayList<>();
                    valuesOfKey.add(v);
                    incidentList.put(u, valuesOfKey);
                }
            }
            if(incidentList.containsKey(v))
                incidentList.get(v).add(u);
            else {
                ArrayList<Integer> valuesOfKey = new ArrayList<>();
                valuesOfKey.add(u);
                incidentList.put(v, valuesOfKey);
            }
        }
    }
 
    public void BFS(int v, int u) {
        LinkedList queue = new LinkedList();
        vertexList[v] = u;
        isVisited[v] = true;
        vertexes++;
        queue.add(v);
        int vertex;
 
        while(!queue.isEmpty()) {
            int current = (int)queue.pop();
            if(incidentList.containsKey(current)) {
                edges += incidentList.get(current).size();
                for(int i = 0; i < incidentList.get(current).size(); i++)
                    if(!isVisited[incidentList.get(current).get(i)]) {
                        isVisited[incidentList.get(current).get(i)] = true;
                        vertexList[incidentList.get(current).get(i)] = u;
                        vertexes++;
                        queue.add(incidentList.get(current).get(i));
                    }
            } else break;
        }
    }
 
    public void componentFinder() {
        int maxVertexes = 0;
        int maxEdges = 0;
        int numOfAttrib = 0;
 
        for(int i = 0; i < N; i++)
            if(!isVisited[i]) {
                vertexes = 0;
                edges = 0;
                BFS(i, i);
                if((edges > maxEdges && vertexes == maxVertexes) || vertexes > maxVertexes) {
                    maxVertexes = vertexes;
                    maxEdges = edges;
                    numOfAttrib = i;
                }
            }
 
        StringBuilder gr = new StringBuilder();
        gr.append("graph {" + "\n");
        for(int v = 0; v < N; v++) {
            if(vertexList[v] == numOfAttrib) gr.append(v + " [color = red]" + "\n");
            else gr.append(v + "\n");
            if(incidentList.containsKey(v))
                for(int u = 0; u < incidentList.get(v).size(); u++) {
                    if(v < incidentList.get(v).get(u)) continue;
                    if(vertexList[incidentList.get(v).get(u)] == numOfAttrib)
                        gr.append(incidentList.get(v).get(u) + " -- " + v + " [color = red]" + "\n");
                    else gr.append(incidentList.get(v).get(u) + " -- " + v + "\n");
                }
        }
        gr.append("}");
 
        System.out.println(gr);
    }
}