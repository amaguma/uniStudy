package main

import (
	"fmt"
)

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

func aufenkampHohn(a, n, m int, g graph, delta [][]int) []string {
	h := g.split1(n, m)
	for h1 := g.split(n, m); h != h1; h1 = g.split(n, m) {
		h = h1
	}
	g.DFS(a, delta, g.v[a].pi)
	s := g.print(m)
	return s
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

func (g *graph) print(m int) []string {
	output := make([]string, g.c+g.c*m)
	k := 0
	for i := 0; i < g.c; i++ {
		output[k] += fmt.Sprint(i, "[shape=circle]\n")
		k++
	}
	for i := range g.v {
		if g.v[i].used {
			for j := range g.v[i].d {
				if g.v[i].d[j].pi.used {
					output[k] += fmt.Sprint(g.v[i].ind, "->", g.v[i].d[j].pi.ind, "[label=\"", string('a'+j), "(", g.f[i][j], ")\"]\n")
					k++
				}
			}
		}
	}
	return output
}

func main() {
	var g1 graph
	g1.c = 0
	var a1, n1, m1 int

	fmt.Scan(&n1, &m1, &a1)

	g11 := make([][]int, n1)
	for i := range g11 {
		g11[i] = make([]int, m1)
	}

	g1.v = make([]state, n1)
	for i := range g1.v {
		g1.v[i].d = make([]*state, m1)
		for j := range g1.v[i].d {
			fmt.Scan(&g11[i][j])
			g1.v[i].d[j] = &g1.v[g11[i][j]]
		}
	}

	g1.f = make([][]string, n1)
	for i := range g1.f {
		g1.f[i] = make([]string, m1)
		for j := range g1.f[i] {
			fmt.Scan(&g1.f[i][j])
		}
	}

	var g2 graph
	g2.c = 0
	var a2, n2, m2 int

	fmt.Scan(&n2, &m2, &a2)

	g22 := make([][]int, n2)
	for i := range g22 {
		g22[i] = make([]int, m2)
	}

	g2.v = make([]state, n2)
	for i := range g2.v {
		g2.v[i].d = make([]*state, m2)
		for j := range g2.v[i].d {
			fmt.Scan(&g22[i][j])
			g2.v[i].d[j] = &g2.v[g22[i][j]]
		}
	}

	g2.f = make([][]string, n2)
	for i := range g2.f {
		g2.f[i] = make([]string, m2)
		for j := range g2.f[i] {
			fmt.Scan(&g2.f[i][j])
		}
	}
	s1 := aufenkampHohn(a1, n1, m1, g1, g11)
	s2 := aufenkampHohn(a2, n2, m2, g2, g22)
	if len(s1) == len(s2) {
		for i := range s1 {
			h := 0
			for j := range s1 {
				if s1[i] == s2[j] {
					h++
				}
			}
			if h != 1 {
				fmt.Print("NOT EQUAL")
				return
			}
		}
		fmt.Print("EQUAL")
	} else {
		fmt.Print("NOT EQUAL")
	}
}
