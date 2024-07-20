/**
* WhatTime.java
* @author 22266055 Shigemura Kazuma
*/

import java.text.SimpleDateFormat;
import java.util.Calendar;

public class WhatTime implements Runnable{
    public void run(){
        SimpleDateFormat n = new SimpleDateFormat("HH:mm:ss");
        while(true){
            Calendar time = Calendar.getInstance();
            System.out.println(n.format(time.getTime()));
            try{
                Thread.sleep(1000);
            }
            catch(InterruptedException e){
                System.out.println(e);
            }
        }
    }
    public static void main(String[] args){
        WhatTime time = new WhatTime();
        new Thread(time).start();
    }
}