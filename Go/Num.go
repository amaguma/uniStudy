package main

import "fmt"

func d(a [][]int, b int, used []bool, c []int, h *int) {
	used[b] = true
	c[b] = *h
	*h++
	for _, g := range a[b] {
		if !used[g] {
			d(a, g, used, c, h)
		}
	}
}

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
	used := make([]bool, n)
	c := make([]int, n)
	h := 0
	d(a, b, used, c, &h)

	v := make([][]string, n)
	k := make([][]int, n)
	for i, x := range c {
		k[x] = a[i]
		v[x] = e[i]
		for j := range a[i] {
			a[i][j] = c[a[i][j]]
		}
	}

	fmt.Println(h)
	fmt.Println(m)
	fmt.Println(0)
	for i := range k[:h] {
		for j := range k[i] {
			fmt.Printf("%d ", k[i][j])
		}
		fmt.Printf("\n")
	}

	for i := range v[:h] {
		for j := range k[i] {
			fmt.Printf("%s ", v[i][j])
		}
		fmt.Printf("\n")
	}
}
