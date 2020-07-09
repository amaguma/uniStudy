
import java.util.Scanner;

public class MaxNum {

    private static int getNumber(int a, int b) {
        if (a == 0) {
            return b * 10;
        } else {
            int c = a;
            int k = 0;
            while (c != 0) {
                c /= 10;
                k++;
            }
            double d = b * Math.pow(10, k);
            return (int) d + a;
        }
    }

    private static int compare(int a, int b) {
        return Integer.compare(getNumber(a, b), getNumber(b, a));
    }

    private static int[] sort(int[] a) {
        int k = 0;
        for (int i = 0; i < a.length; i++) {
            for (int j = i + 1; j < a.length; j++) {
                if (compare(a[i], a[j]) == 1) {
                    int tmp = a[i];
                    a[i] = a[j];
                    a[j] = tmp;
                }
            }
        }
        return a;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = in.nextInt();
        }
        int[] b = sort(array);
        for (int i = 0; i < n; i++) {
            System.out.print(b[i]);
        }
    }
}



