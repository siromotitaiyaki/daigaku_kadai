class Factorial{
    public static void main(String[] args){
        int i=0, result; // ループ用の変数
        int[] a = {0,1,2,3,4,5,6,7,8,9}; /* 配列a[10]の宣言と初期化 */
        while(i<a.length){ // a[0]からa[9]まで配列の要素数分ループさせる
            result = 1;
            for(int j=a[i]; j>=1; j--)result *= j; /* 階乗の計算 */
            /* 結果を標準出力 */
            System.out.println(a[i]+"の階乗は"+result+"です。");
            i++;
        }
    }
}