/**
* Janken.java
* @author 22266055 Kazuma Shigemura
*/

import java.util.Random; // パッケージのインポート
public class Janken{
    public static void main(String[] args){
        Random janken = new Random();
        int num = janken.nextInt(3); // 乱数範囲の指定
        if(num == 0){
            System.out.println("グー");
        }
        if(num == 1){
            System.out.println("チョキ");
        }
        if(num == 2){
            System.out.println("パー");
        }
    }
}
