import java.util.ArrayList;
import java.util.Scanner;

import static java.util.Arrays.fill;

class Vertex {
    public int number;
    public int[] w;
    public ArrayList<Integer> edge = new ArrayList<Integer>();

    Vertex(int n) {
        this.number = n;
    }

    public void addEdge(int a) {
        edge.add(a);
    }
}


public class Prim {

    public static int min (int a, int b){
        return (a > b) ? b : a;
    }

    public static int INF = Integer.MAX_VALUE / 2;

    static int mstPrim(Vertex[] graph) {
        boolean[] used = new boolean[graph.length];
        int[] dist = new int[graph.length];
        fill(used, false);
        fill(dist, INF);
        dist[0] = 0;
        for (; ;){
            int v = -1;
            for (int i = 0; i < graph.length; i++){
                if (!used[i] && (v == -1 || dist[i] < dist[v])){
                    v = i;
                }
            }
            if (v == -1 || dist[v] == INF) break;
            used[v] = true;
            for (int i = 0; i < graph.length; i++){
                if (!used[i] && (graph[v].w[i] < INF || graph[v].w[i] < dist[i])){
                    dist[i] = min(dist[i], graph[v].w[i]);
                }
            }
        }
        int res = 0;
        for (int v = 0; v < graph.length; v++){
            res += dist[v];
        }
        return res;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        Vertex[] graph = new Vertex[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new Vertex(i);
            graph[i].w = new int [n];
            fill(graph[i].w, INF);
        }
        int a, b, c;
        for (int i = 0; i < m; i++) {
            a = in.nextInt();
            b = in.nextInt();
            c = in.nextInt();
            graph[a].addEdge(b);
            graph[a].w[b] = c;
            graph[b].addEdge(a);
            graph[b].w[a] = c;
        }
        int res = mstPrim(graph);
        System.out.println(res);
    }
}
