/**
* Count.java
* @author 22266055 Shigemura Kazuma
*/

import java.util.ArrayList;
import java.util.Collections;
public class Count {
    public static void main(String[] args){
        ArrayList<String> List = new ArrayList<String>();
        for(String i : args){
            List.add(i);
        }
        Collections.sort(List);
        String s = "";
        for(String i : List){
            s = s + i + " ";
        }
        System.out.println(s);
        System.out.println("単語数:"+List.size());
    }
}
