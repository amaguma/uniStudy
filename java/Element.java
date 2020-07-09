public class Element<T> {
    private T element;
    private Element<T> next;
    private Element<T> past;
    private int s;
    private Element<T> head;

    Element(T x) {
        this.element = x;
        this.next = this;
        this.past = this;
        this.s = 0;
    }

    T x() {
        return this.element;
    }

    boolean equivalent(Element<T> elem) {
        boolean k = false;
        Element<T> a = this;
        while (a.head != null) {
            a = a.head;
            if (a == elem){
                k = true;
                return k;
            }
        }
        while (elem.head != null) {
            elem = elem.head;
            if (elem == a){
                k = true;
                return k;
            }
        }
        if (a == elem){
            k = true;
        }
        return k;
    }

    void union(Element<T> elem) {
        Element<T> a = this;
        while (a.head != null) {
            a = a.head;
        }
        while (elem.head != null) {
            elem = elem.head;
        }
        a.head = elem;
    }
}

