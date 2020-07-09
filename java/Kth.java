import java.util.Scanner;

public class Kth {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long k = in.nextLong();
        long b = 0;
        long n1 = 10;
        long n2 = 100;
        long a = 2;
        if (k >= 9) {
            k -= 9;
            while (k >= (n2 - n1) * a) {
                k -= (n2 - n1) * a;
                a++;
                n1 *= 10;
                n2 *= 10;
            }
            b = k / a + n1;
            long c = a - (k % a);
            while (c != a + 1) {
                n2 /= 10;
                c++;
            }
            b = b / n2 % 10;
        } else {
            b = k + 1;
        }
        System.out.println(b);
    }
}

