class SmartPhone extends VoiceRecorder implements Phone {
    public void call(String number) {
        System.out.println(number + "へ発信中");
    }
    public void emergencyCall() {
        call(Phone.emergencyNumber);
    }
}