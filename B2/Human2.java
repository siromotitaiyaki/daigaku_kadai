/**
 * Human2.java
 * @author KondoT
 */

public class Human2 {

    public static void main(String[] args) {

	VoiceRecorder iPodTouch = new VoiceRecorder();

	// Usage of voice recording function
	iPodTouch.rec("Test, Test, One, Two, Three."); // iPodTouch can store a String text message by the rec() method.
	iPodTouch.play(); // iPodTouch plays the stored text message by the play() method.

	// It still works as MusicPlayer.
	iPodTouch.shuffle();
    } 
}