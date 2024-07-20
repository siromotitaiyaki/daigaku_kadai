class B{
    public String e;
    public B(String e){this.e=e;}
    public void r(){
        System.out.println(e);
    }
}

public class Class2 {
    public static void main(String[] args){
        B[] b=new B[3];
        b[0] = new B("D"); //修正箇所
        b[1] = new B("E"); //修正箇所
        b[2] = new B("F"); //修正箇所
        for(B t:b){
            t.r();
        }
    }
}