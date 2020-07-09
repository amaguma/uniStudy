import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Calc {
    static public class Lexer {
        private String ss;
        private int index;
        public Lexer (String ss) {
            this.ss = ss;
            this.index = 0;
            skipSpace();
        }
        public boolean isNotEmpty (){
            return ss.length() > index;
        }
        public boolean isInteger (){
            return Character.isDigit(ss.charAt(index));
        }
        public boolean isVariable (){
            return Character.isLetter(ss.charAt(index));
        }
        public boolean isPlus () {
            return ss.charAt(index) == '+';
        }
        public boolean isMinus () {
            return ss.charAt(index) == '-';
        }
        public boolean isDelenie (){
            return ss.charAt(index) == '/';
        }
        public boolean isUmnoj (){
            return ss.charAt(index) == '*';
        }
        public boolean isLeft (){
            return ss.charAt(index) == '(';
        }
        public boolean isRight (){
            return ss.charAt(index) == ')';
        }
        private void skipSpace () {
           while (isNotEmpty() && Character.isWhitespace(ss.charAt(index)))
               index++;
        }
        public int scanInt () {
            int a = Character.digit(ss.charAt(index++), 10);
            while (isNotEmpty() && isInteger()) {
                a = a * 10 + Character.digit(ss.charAt(index++), 10);
            }
            skipSpace();
            return a;
        }
        public String scanVariable () {
            StringBuilder a = new StringBuilder();
            a.append(ss.charAt(index++));
            while (isNotEmpty() && Character.isLetterOrDigit(ss.charAt(index))){
                a.append(ss.charAt(index++));
            }
            skipSpace();
            return a.toString();
        }
        public void scanOther (){
            index++;
            skipSpace();
        }
    }

    public static class Parser {
        private Lexer lexer;
        private Map<String, Integer> map;
        private Scanner scanner;
        private Parser (String ss, Scanner scanner) {
            this.lexer = new Lexer (ss);
            this.map = new HashMap<>();
            this.scanner = scanner;
        }
        private int parseE() throws ParserException{
            int a = parseT();
            while (lexer.isNotEmpty() && (lexer.isPlus() || lexer.isMinus())){
                if (lexer.isPlus()) {
                    lexer.scanOther();
                    a += parseT();
                } else {
                    lexer.scanOther();
                    a -= parseT();
                }
            }
            return a;
        }

        private int parseT() throws ParserException {
            int a = parseF();
            while (lexer.isNotEmpty() && (lexer.isUmnoj() || lexer.isDelenie())){
                if (lexer.isUmnoj()) {
                    lexer.scanOther();
                    a *= parseF();
                } else {
                    lexer.scanOther();
                    a /= parseF();
                }
            }
            return a;
        }

        private int parseF() throws ParserException {
            if (lexer.isNotEmpty()) {
                if (lexer.isInteger()) {
                    return lexer.scanInt();
                } else {
                    if (lexer.isVariable()) {
                        String h = lexer.scanVariable();
                        if (map.containsKey(h)) {
                            return map.get(h);
                        } else {
                            map.put(h, scanner.nextInt());
                            return map.get(h);
                        }
                    } else {
                        if (lexer.isLeft()) {
                            lexer.scanOther();
                            int k = parseE();
                            if (!lexer.isNotEmpty() || !lexer.isRight()) {
                                throw new ParserException();
                            }
                            lexer.scanOther();
                            return k;
                        } else {
                            if (lexer.isMinus()) {
                                lexer.scanOther();
                                return -parseF();
                            } else {
                                throw new ParserException();
                            }
                        }
                    }
                }
            } else
                throw new ParserException();
        }
        public static int parse (String ss, Scanner scanner) throws ParserException{
            Parser parser = new Parser(ss, scanner);
            int b = parser.parseE();
            if (parser.lexer.isNotEmpty()) {
                throw new ParserException();
            }
            return b;
        }
    }

    public static class ParserException extends Exception {
        public ParserException(){
            super();
        }
    }
    public static void main (String[] args){
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.println(Parser.parse(scanner.nextLine(), scanner));
        } catch (ParserException e){
            System.out.println("error");
        }
    }
}
