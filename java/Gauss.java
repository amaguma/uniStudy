
import java.util.Scanner;

class Fraction {
    public int a1, b1;
    public int zero = 0;

    Fraction(int a1, int b1) {
        this.a1 = a1;
        this.b1 = b1;
    }

    private static int getNod(int a, int b) {
        if (a < 0 && b > 0) {
            a = -a;
        }
        return b == 0 ? a : getNod(b, a % b);
    }

    private static Fraction getFraction(Fraction a) {
        a = new Fraction(a.a1 / getNod(a.a1, a.b1), a.b1 / getNod(a.a1, a.b1));
        if (a.a1 > 0 && a.b1 < 0) {
            a = new Fraction(-a.a1, -a.b1);
        }
        return a;
    }

    public static Fraction getComposition(Fraction a, Fraction b) {
        Fraction zero = new Fraction(0, 1);
        if ((Gauss.compare(a,zero) != 1) && (Gauss.compare(b,zero) != 1)) {
            Fraction v = new Fraction(a.a1 * b.a1, a.b1 * b.b1);
            return getFraction(v);
        } else {
            return  zero;
        }
    }
    public static Fraction ABS (Fraction a) {
        if (a.a1 < 0 && a.b1 > 0) {
            a = new Fraction(-a.a1, a.b1);
        } else if (a.b1 < 0 && a.a1 > 0) {
            a = new Fraction(a.a1, -a.b1);
        }
        return a;
    }

    private static int getNok(int a, int b) {
        return a / getNod(a, b) * b;
    }

    public static Fraction getDivision(Fraction a, Fraction b) {
        Fraction zero = new Fraction(0, 1);
        if ((Gauss.compare(a,zero) != -1) && (Gauss.compare(b,zero) != -1)) {
            Fraction v = new Fraction(a.a1 * b.b1, a.b1 * b.a1);
            return getFraction(v);
        } else {
            return zero;
        }
    }
    public static Fraction getAdd(Fraction a, Fraction b) {
        Fraction v = new Fraction(0, 1);
        if (Gauss.compare(a, v) == 1) {
            return b;
        }
        if (Gauss.compare(b, v) == 1) {
            return a;
        }
        int c = getNok(a.b1, b.b1) / a.b1;
        a = new Fraction(a.a1 * c, a.b1 * c);
        c = getNok(a.b1, b.b1) / b.b1;
        b = new Fraction(b.a1 * c, b.b1 * c);
        v = new Fraction(a.a1 + b.a1, a.b1);
        return getFraction(v);
    }

    public static Fraction getSubtraction(Fraction a, Fraction b) {
        Fraction v = new Fraction(0,1);
        if (Gauss.compare(a, v) == 1) {
             if (b.a1 > 0 && b.b1 > 0) {
                b = new Fraction(-b.a1, b.b1);
                 return b;
            }
            if ((b.a1 < 0 && b.b1 > 0) || (b.a1 > 0 && b.b1 < 0)) {
                b = Fraction.ABS(b);
                return b;
            }
        }
        if (Gauss.compare(b, v) == 1) {
            return a;
        }
        int c = getNok(a.b1, b.b1) / a.b1;
        a = new Fraction(a.a1 * c, a.b1 * c);
        c = getNok(a.b1, b.b1) / b.b1;
        b = new Fraction(b.a1 * c, b.b1 * c);
        if (a.a1 - b.a1 != 0 ) {
            v = new Fraction(a.a1 - b.a1, a.b1);
            return getFraction(v);
        } else {
            return v;
        }
    }
}

public class Gauss {

    private static int getLine(Fraction[][] a, int j, int i) {
        int k = -1;
        Fraction zero = new Fraction(0, 1);
        for (; i < a[0].length - 1; i++) {
            if (compare(a[i][j], zero) != 1) {
                k = i;
                break;
            }
        }
        return k;
    }

    private static void swapLine(Fraction[][] a, int i, int k) {
        if ((k != -1) && (k != i)) {
            for (int j = 0; j < a[0].length; j++) {
                Fraction tmp = a[i][j];
                a[i][j] = a[k][j];
                a[k][j] = tmp;
            }
        }
    }

    private static void division(Fraction[][] a, int i, int j, Fraction m) {
        Fraction f = new Fraction(0, 1);
        if (compare(m, f) != 1) {
            for (; j < a[0].length; j++) {
                if (compare(a[i][j], f) != 1) {
                    a[i][j] = Fraction.getDivision(a[i][j], m);
                }
            }
        }
    }

    public static int compare(Fraction a, Fraction b) {
        int k = 0;
        if ((a.a1 == b.a1) && (a.b1 == b.b1)) {
            k = 1;
        }
        return k;
    }


    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int b;
        Fraction[][] a = new Fraction[n][n + 1];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n + 1; j++) {
                b = in.nextInt();
                Fraction c = new Fraction(b, 1);
                a[i][j] = c;
            }
        }
        int l = 0;
        Fraction f;
        Fraction v = new Fraction(0, 1);
        while (l != n) {
            for (int i = 0; i < n; i++) {
                swapLine(a, i, getLine(a, l, i));
                f = a[i][l];
                if (compare(a[i][l], v) == 1){
                    l++;
                    f = a[i][l];
                }
                division(a, i, l, f);
                for (int j = i + 1; j < n; j++) {
                    if (compare(a[j][l], v) != 1) {
                        f = a[j][l];
                        for (int m = l; m < n + 1; m++) {
                            a[j][m] = Fraction.getSubtraction(a[j][m], Fraction.getComposition(a[i][m], f));
                        }
                    }
                }
                if (i != l){
                    break;
                }
                l++;
            }
            break;
        }
        f = new Fraction(0, 1);
        int s = 0;
        Fraction p = a[n - 1][0];
        for (int i = 0; i < n ; i++) {
            p = Fraction.getAdd(p, a[n - 1][i]);
        }
        if (compare(p, f) == 1) {
            System.out.println("No solution");
            return;
        }
        for (int i = 0; i < n; i++) {
            s = 0;
            for (int j = 0; j < n; j++) {
                if (compare(a[j][i], f) == 1){
                    s++;
                }
            }
            if (s == n) {
                System.out.println("No solution");
                return;
            }
        }
        for (int i = n - 1; i >= 0; i--){
            for (int j = n - 1; j >= 0; j--){
                if (i == j){
                    break;
                } else {
                    a[i][n] = Fraction.getSubtraction(a[i][n],a[i][j]);
                }
            }
            a[i][i] = a[i][n];
            l = i - 1;
            while(l >= 0){
                if (compare(a[l][i], f) != 1) {
                    a[l][i] = Fraction.getComposition(a[i][i], a[l][i]);
                }
                l--;
            }
        }
        for (int i = 0; i < n; i++){
            System.out.println(a[i][i].a1 + "/" + a[i][i].b1);
        }
    }
}



