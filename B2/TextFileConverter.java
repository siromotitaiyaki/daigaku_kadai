/**
* TextFileConverter.java
* @author 22266055 Shigemura Kazuma
*/

import java.util.ArrayList;
import java.io.*;

public class TextFileConverter{
    public static void main(String[] args){
        try{
            BufferedReader Read = new BufferedReader(new FileReader("sample.txt"));
            String line;
            ArrayList<String> List = new ArrayList<String>();
            while((line = Read.readLine()) != null){
                List.add(line);
            }
            for(int i=0; i<List.size(); i++){
                String replaced = List.get(i)
                    .replace("、",",")
                    .replace("。",".");
                List.set(i, replaced);
            }
            BufferedWriter Write = new BufferedWriter(new FileWriter("22266055.txt"));
            for(String l : List){
                Write.write(l);
                Write.newLine();
            }
            Write.close();
        }
        catch(FileNotFoundException k){
            System.out.println("そんなファイルはありません");
            return;
        }
        catch(IOException k){
            System.out.println(k);
            return;
        }
    }
}