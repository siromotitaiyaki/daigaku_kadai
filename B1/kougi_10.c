#include <time.h>
#include <stdio.h>
/*--- 日付・時刻を表示 ---*/
void put_date(struct tm *timer)
{
char *wday_name[] = {"日", "月", "火", "水", "木", "金", "土"};
/*変数 wday_name を定義する。*/
printf("%4d 年%02d 月%02d 日(%s)%02d 時%02d 分%02d 秒",
 timer->tm_year + 1900, /* 年 */
 timer->tm_mon + 1, /* 月 */
 timer->tm_mday, /* 日 */
 wday_name[ timer->tm_wday ], /* 曜日 */
 timer->tm_hour, /* 時*/
 timer->tm_min, /* 分*/
 timer->tm_sec /* 秒*/
 );
 }

 int main(void)
 {
 time_t current; /* 暦時刻(単一の算術型)*/
 struct tm *timer; /* 要素別の時刻(構造体)*/

 time(&current); /* 現在の時刻を取得 */
 timer = localtime(&current); /* 地方時に変換 */

 printf("現在の日付・時刻は");
 put_date(timer);
 printf("です。\n");
    
    return (0);
}