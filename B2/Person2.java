/**
* Person2.java
* @author 22266055 Shigemura Kazuma
*/

public class Person2 {
    // フィールドの定義
    int age; // 年齢を記憶するフィールド
    String name; // 名前の文字列を記憶するフィールド

    // コンストラクタ(初期化のためのメソッド)
    Person2(int age, String name){
        this.age = age;
        this.name = name;
    }

    // メソッドの定義
    void myAgels(){
        // 年齢を画面に表示する手続き
        System.out.println("I'm " + age + " years old.");
    }

    void myNamels(){
        // 名前を画面に表示する手続き
        System.out.println("I'm sometimes called " + name + ".");
    }

    public static void main(String[] args){
        Person2 shigemura = new Person2(19, "Shigemura Kazuma");
        shigemura.myAgels();
        shigemura.myNamels();
    }
}
