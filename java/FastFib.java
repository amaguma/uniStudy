import java.math.BigInteger;
import java.util.Scanner;

public class FastFib {
    private static Matrix getDegree(int n) {
        Matrix matrix1 = new Matrix(BigInteger.valueOf(1), BigInteger.valueOf(1), BigInteger.valueOf(1), BigInteger.valueOf(0));
        Matrix e = new Matrix(BigInteger.valueOf(1), BigInteger.valueOf(1), BigInteger.valueOf(1), BigInteger.valueOf(0));
        if (n % 2 == 0) {
            matrix1 = new Matrix(BigInteger.valueOf(1), BigInteger.valueOf(0), BigInteger.valueOf(0), BigInteger.valueOf(1));
        }
        n /= 2;
        while (n != 0) {
            e = e.getComposition(e);
            if (n % 2 == 1) {
                matrix1 = matrix1.getComposition(e);
            }
            n /= 2;
        }
        return matrix1;
    }

    private static class Matrix {
        private BigInteger a1, a2, a3, a4;

        Matrix(BigInteger a1, BigInteger a2, BigInteger a3, BigInteger a4) {
            this.a1 = a1;
            this.a2 = a2;
            this.a3 = a3;
            this.a4 = a4;
        }

        private Matrix getComposition(Matrix a) {
            Matrix squaredMatrix = new Matrix(a1.multiply(a.a1).add(a2.multiply(a.a3)), a1.multiply(a.a2).add(a2.multiply(a.a4)), a3.multiply(a.a1).add(a4.multiply(a.a3)), a3.multiply(a.a2).add(a4.multiply(a.a4)));
            return squaredMatrix;
        }
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        BigInteger res;
        if (n == 1) {
            res = BigInteger.valueOf(1);
        } else {
            Matrix fibMatrix = getDegree(n - 1);
            res = fibMatrix.a3.add(fibMatrix.a4);
        }
        System.out.println(res);
    }
}
