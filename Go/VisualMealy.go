package main

import "fmt"

func main() {
	var n, m, b int
	fmt.Scan(&n)
	fmt.Scan(&m)
	fmt.Scan(&b)

	a := make([][]int, n)
	for i := range a {
		a[i] = make([]int, m)
		for j := range a[i] {
			fmt.Scan(&a[i][j])
		}
	}

	e := make([][]string, n)
	for i := range e {
		e[i] = make([]string, m)
		for j := range e[i] {
			fmt.Scan(&e[i][j])
		}
	}

	fmt.Print("digraph {\n rankdir = LR\n dummy [label = \"\", shape = none]\n")
	for i := range a {
		fmt.Print(" ", i, "[shape = circle]\n")
	}
	fmt.Print(" dummy -> ", b, "\n")
	for i := range a {
		for j := range a[i] {
			fmt.Print(" ", i, " -> ", a[i][j], " [label = \"", string('a'+j), "(", e[i][j], ")\"]\n")
		}
	}
	fmt.Print("}")
}
