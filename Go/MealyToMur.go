package main

import s "strings"
import "fmt"

type graph struct {
	d        [][]int
	z1, w, v []string
	f        [][]string
	o        []int
}

func main() {
	var g graph
	var n, m, h int

	fmt.Scan(&m)
	g.z1 = make([]string, m)
	for i := range g.z1 {
		fmt.Scan(&g.z1[i])
	}

	fmt.Scan(&h)
	g.w = make([]string, h)
	for i := range g.w {
		fmt.Scan(&g.w[i])
	}

	fmt.Scan(&n)
	g.f = make([][]string, n)
	g.d = make([][]int, n)
	for i := range g.d {
		g.d[i] = make([]int, m)
		g.f[i] = make([]string, m)
		for j := range g.d[i] {
			fmt.Scan(&g.d[i][j])
		}
	}

	for i := range g.f {
		for j := range g.f[i] {
			fmt.Scan(&g.f[i][j])
		}
	}

	g.v = make([]string, 0, n*m)
	g.o = make([]int, n*m)
	g.o[0] = g.d[0][0]
	a := fmt.Sprint(g.d[0][0], ",", g.f[0][0])
	g.v = append(g.v, a)

	z := 1
	for i := range g.f {
		for j := range g.f[i] {
			a = fmt.Sprint(g.d[i][j], ",", g.f[i][j])
			k := 0
			for l := range g.v {
				if s.Index(g.v[l], a) != -1 {
					k++

				}
			}
			if k == 0 {
				g.v = append(g.v, a)
				g.o[z] = g.d[i][j]
				z++
			}
		}
	}

	var b, j int
	k := g.o[0]
	fmt.Print("digraph {\n rankdir = LR\n")
	for i := range g.v {
		fmt.Print(" ", i, " [label = \"(", g.v[i], ")\"]\n")
		for j = range g.f[0] {
			if k == n {
				k = 0
			}
			a = fmt.Sprint(g.d[k][j], ",", g.f[k][j])
			for l := range g.v {
				if g.v[l] == a {
					b = l
					break
				}
			}
			fmt.Print(" ", i, " -> ", b, " [label = \"", g.z1[j], "\"]\n")
		}
		V := i + 1
		if V < len(g.o) {
			if g.o[i] != g.o[V] {
				k++
			}
		}
	}
	fmt.Print("}")
}
