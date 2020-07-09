package main

import "fmt"

type state struct {
	depth, ind int
	pi, parent *state
	used       bool
	d          []*state
}

type graph struct {
	v []state
	c int
	f [][]string
}

func find(v *state) *state {
	if v.parent == v {
		return v
	}
	v.parent = find(v.parent)
	return v.parent

}

func union(s1 *state, s2 *state) {
	roots1 := find(s1)
	roots2 := find(s2)
	if roots1.depth < roots2.depth {
		roots1.parent = roots2
	} else {
		roots2.parent = roots1
		if roots1.depth == roots2.depth && roots2 != roots1 {
			roots1.depth++
		}
	}
	return
}

func (g *graph) split1(n int, m int) int {
	q := n
	for i := 0; i < n; i++ {
		g.v[i].parent = &g.v[i]
		g.v[i].depth = 0
	}
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			if find(&g.v[i]) != find(&g.v[j]) {
				eq := true
				for k := 0; k < m; k++ {
					if g.f[i][k] != g.f[j][k] {
						eq = false
						break
					}
				}
				if eq {
					union(&g.v[i], &g.v[j])
					q--
				}
			}
		}
	}
	for i := range g.v {
		g.v[i].pi = find(&g.v[i])
	}
	return q
}

func (g *graph) split(n int, m int) int {
	q := n
	for i := 0; i < n; i++ {
		g.v[i].parent = &g.v[i]
		g.v[i].depth = 0
	}
	for i := range g.v {
		for j := i + 1; j < n; j++ {
			if g.v[i].pi == g.v[j].pi && find(&g.v[i]) != find(&g.v[j]) {
				eq := true
				for k := 0; k < m; k++ {
					w1 := g.v[i].d[k]
					w2 := g.v[j].d[k]
					if w1.pi != w2.pi {
						eq = false
						break
					}
				}
				if eq {
					union(&g.v[i], &g.v[j])
					q--
				}
			}
		}
	}
	for i := range g.v {
		g.v[i].pi = find(&g.v[i])
	}
	return q
}

func aufenkampHohn(a, n, m int, g graph, delta [][]int) {
	h := g.split1(n, m)
	for h1 := g.split(n, m); h != h1; h1 = g.split(n, m) {
		h = h1
	}
	g.DFS(a, delta, g.v[a].pi)
	g.print()
}

func (g *graph) DFS(b int, delta [][]int, s *state) {
	s.ind = g.c
	g.c++
	s.used = true
	for i := range delta[b] {
		next := delta[b][i]
		if !s.d[i].pi.used {
			g.DFS(next, delta, s.d[i].pi)
		}
	}
}

func (g *graph) print() {
	fmt.Print("digraph {\n rankdir=LR\n dummy [label = \"\", shape = none]\n")
	for i := 0; i < g.c; i++ {
		fmt.Print(" ", i, "[shape=circle]\n")
	}
	fmt.Print(" dummy->0\n")
	for i := range g.v {
		if g.v[i].used {
			for j := range g.v[i].d {
				if g.v[i].d[j].pi.used {
					fmt.Print(" ", g.v[i].ind, "->", g.v[i].d[j].pi.ind, "[label=\"", string('a'+j), "(", g.f[i][j], ")\"]\n")
				}
			}
		}
	}
	fmt.Print("}")
}

func main() {
	var g graph
	g.c = 0
	var a, n, m int

	fmt.Scan(&n, &m, &a)

	g1 := make([][]int, n)
	for i := range g1 {
		g1[i] = make([]int, m)
	}

	g.v = make([]state, n)
	for i := range g.v {
		g.v[i].d = make([]*state, m)
		for j := range g.v[i].d {
			fmt.Scan(&g1[i][j])
			g.v[i].d[j] = &g.v[g1[i][j]]
		}
	}

	g.f = make([][]string, n)
	for i := range g.f {
		g.f[i] = make([]string, m)
		for j := range g.f[i] {
			fmt.Scan(&g.f[i][j])
		}
	}

	aufenkampHohn(a, n, m, g, g1)
}
