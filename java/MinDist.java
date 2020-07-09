import java.util.Scanner;

public class MinDist {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String s = in.nextLine();
        char x = in.next().charAt(0), y = in.next().charAt(0);
        int min = Math.abs(s.indexOf(x) - s.indexOf(y)) - 1;
        int i,j, b = s.indexOf(x), c = s.indexOf(y);
        for (i = 0; i < s.length(); i++) {
            if ((s.charAt(i) == x) && (i != s.indexOf(x))) {
                b = i;
            }
            if ((s.charAt(i) == y) && (i !=s.indexOf(y))) {
                c = i;
            }
            if (min > Math.abs(c - b) - 1) min = Math.abs(c - b) - 1;
        }

        System.out.println(min);
    }
}