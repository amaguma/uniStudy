import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Econom {
    public static void main(String[] args) {
        Map<String, Integer> expression = new HashMap<>();
        Scanner in = new Scanner(System.in);
        String s = in.nextLine();
        String a = s;
        int k = 0, i = 0, m = 0;
        if (s.charAt(0) == '(') {
            i = 2;
        }
        while ((s.charAt(0) == '(') || (a.charAt(0) == '(')) {
            i = 2;
            k = 0;
            if (s.charAt(0)== '(') {
                if (s.charAt(i) == '(') {
                    k--;
                } else {
                    if (s.charAt(i) == ')') {
                        k++;
                    }
                }
                for (i++; k < 0; i++) {
                    if (s.charAt(i) == '(') {
                        k--;
                    } else {
                        if (s.charAt(i) == ')') {
                            k++;
                        }
                    }
                }

                if (expression.get(s) == null) {
                    expression.put(s, 1);
                    k--;
                }
                s = s.substring(2, i);
            }
            m += k;
            int c = 0;
            i = 2;
            if (a.charAt(0) == '(') {
                do {
                    if (a.charAt(i) == '(') {
                        c--;
                    } else {
                        if (a.charAt(i) == ')') {
                            c++;
                        }
                    }
                    i++;
                } while (c < 0);
                if (expression.get(a) == null) {
                    expression.put(a, 1);
                    c--;
                }
                a = a.substring(i, a.length() - 1);
            }
            m += c;
        }
        System.out.println(Math.abs(m));
    }
}