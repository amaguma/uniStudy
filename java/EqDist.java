import static java.lang.StrictMath.min;
import static java.util.Arrays.fill;

import java.util.*;

class Vertex {
    public int number;
    public int[] dist;
    public ArrayList<Integer> edge = new ArrayList<Integer>();

    Vertex(int n) {
        this.number = n;
    }

    public void addEdge(int a) {
        edge.add(a);
    }

    public int getEdge(int a) {
        return edge.get(a);
    }

    public int getNumber() {
        return number;
    }
}


public class EqDist {
    public  static int INF = Integer.MAX_VALUE / 2;

    static void dijkstra(Vertex[] graph, Vertex s) {
        boolean[] used = new boolean[graph.length]; 
        s.dist = new int[graph.length]; 
        fill(s.dist, INF); 
        s.dist[s.number] = 0; 
        for (; ; ) {
            int v = -1;
            for (int nv = 0; nv < graph.length; nv++) { 
                if (!used[nv] && s.dist[nv] < INF && (v == -1 || s.dist[v] > s.dist[nv])) { 
                    v = nv;
                }
            }
            if (v == -1) { 
                break;
            }
            used[v] = true; 
            for (int nv: graph[v].edge){ 
                if (!used[nv]){ 
                    s.dist[nv] = min(s.dist[nv], s.dist[v] + 1); 
                }
            }
        }
    }

    public static void main (String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        Vertex[] graph = new Vertex[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new Vertex(i);
        }
        int a, b;
        for (int i = 0; i < m; i++) {
            a = in.nextInt();
            b = in.nextInt();
            graph[a].addEdge(b);
            graph[b].addEdge(a);
        }
        int k = in.nextInt();
        a = in.nextInt();
        Vertex c = new Vertex(a);
        dijkstra(graph, c);
        int[] h = c.dist;
        for (int i = 1; i < k; i++) {
            a = in.nextInt();
            c = new Vertex(a);
            dijkstra(graph, c);
            for (int j = 0; j < graph.length; j++) {
                if (h[j] != c.dist[j]) {
                    h[j] = -1;
                }
            }
        }
        k = 0;
        for (int i = 0; i < graph.length; i++) {
            if (h[i] != -1 && h[i] != INF) {
                System.out.println(i);
                k++;
            }
        }
        if (k == 0) {
            System.out.println("-");
        }
    }
}


