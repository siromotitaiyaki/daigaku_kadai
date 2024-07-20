public class Human3 {
    
    public static void main(String[] args) {

	SmartPhone iphone = new SmartPhone();

	iphone.call("012-3456-7890"); // 縲�012-3456-7890縺ｸ逋ｺ菫｡荳ｭ縲阪→讓呎ｺ門�蜉帙☆繧九％縺ｨ��

	iphone.emergencyCall();  // 縲�110縺ｸ逋ｺ菫｡荳ｭ縲阪→讓呎ｺ門�蜉帙☆繧九％縺ｨ��
	
	iphone.rec("Test, Test, One, Two, Three."); // VoiceRecorder縺ｨ縺励※繧ょ虚菴懊☆繧具ｼ�
	iphone.play();
	
	iphone.shuffle(); // MusicPlayer縺ｨ縺励※繧ょ虚菴懊☆繧具ｼ�
    }
    
}