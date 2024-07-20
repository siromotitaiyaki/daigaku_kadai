/**
  * MusicPlayer.java
  * @author 22266055 Kazuma Shigemura
  */

import java.util.Random; // パッケージのインポート
public class MusicPlayer {
    // フィールド
    private Song[] song;
    private int current;

    //コンストラクタ
    public MusicPlayer(){
        song = new Song[10];
        song[0] = new Song("Song A");
        song[1] = new Song("Song B");
        song[2] = new Song("Song C");
        song[3] = new Song("Song D");
        song[4] = new Song("Song E");
        song[5] = new Song("Song F");
        song[6] = new Song("Song G");
        song[7] = new Song("Song H");
        song[8] = new Song("Song I");
        song[9] = new Song("Song J");
        current = 0;
    }

    private void play(){
        System.out.println(song[current].getName() + "を再生中♪");
    }

    // publicメソッド：早送り
    public void ff(){
        current %= song.length;
        play(); // privateメソッドの呼び出し
        current++;
    }

    // publicメソッド：シャッフル再生
    public void shuffle(){
        Random random = new Random();
        int index = random.nextInt(song.length);
        while(index == current){
            index = random.nextInt(song.length);
        }
        current = index;
        play();
    }
}