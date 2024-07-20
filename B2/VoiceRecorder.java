public class VoiceRecorder extends MusicPlayer{
    private String memory; // Recordingした文字列を記録するためのフィールド

    // コンストラクタ
    public VoiceRecorder(){
        super(); // 明示しなくても暗黙的にスーパークラスのコンストラクタ（引数なし）が呼び出される
    }

    // 文字列を記録するメソッド
    public void rec(String sentence){
        memory = sentence;
    }

    // rec()メソッドで記録した文字列を標準出力に表示するメソッド
    // オーバーライド
    public void play(){
        System.out.println(memory);
    }

}