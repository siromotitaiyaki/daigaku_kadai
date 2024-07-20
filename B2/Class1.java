public class Class1 {
    static int c; //修正箇所
    static int d; //修正箇所
    String e;

    Class1(String e){
        this.e=e;
        u();
    }
    static void u(){d=++c;}
    void m(){System.out.println(d+e);}
    public static void main(String[] args){
        Class1 a=new Class1("A");
        a.m();
        Class1 b=new Class1("B");
        b.m();
    }
}