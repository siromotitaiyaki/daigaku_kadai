/**
 * Human.java
 * @author KondoT
 */

import java.io.*; // for IOException

public class Human {

    public static void main(String[] args) throws IOException {

	MusicPlayer iPod = new MusicPlayer();

	while(true) {
	    int key = System.in.read(); // Wait an input from Standard Input
	    if(key==-1) break;          // Ctrl+C (Windows) or Ctrl+D (UNIX and MacOSX)
	    if(key==10) iPod.shuffle(); // Action when Enter key is pressed
	}
    }	
}