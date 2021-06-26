/*  
    　～～～ゲームの流れ～～～
    プレイヤーに難易度選択(カードの総数)を選択してもらう
    その後ゲームスタート
    プレイヤーにカードを２枚選択してもらう　１枚選択するごとにカードの中身を公開していく
    選択した２枚のカードの中身が一致した場合当たり
    全てのカードを当てるとゲーム終了し、スコア(選択した回数)を表示

    ～～～アルゴリズムの説明～～～
    ・プレイヤーに縦、横を入力してもらい神経衰弱のカード総量を決定しています。カードの総数が奇数の場合はゲームが成立しないのでエラーチェックを行います

    ・配列にカード総量分の数字を１から順番 かつ 同じ数字を２個セットする　(例、カードの総量が 12 枚なら、配列内の数字は 1 ～ 6 が各 2 個入ります)
    　
    ・配列内の数字(以後カード)は最初？？で表示する。
    　プレイヤーが選択したカードは中身(数字)を表示。
    　プレイヤーが当てたカードは何も表示しない。
    　なお、出力は関数outputで行っている。　

    ・プレイヤーが選択した２枚のパネルの中身(数字)が等しい場合は配列内の数字を 1000 にして当たりの状態にする

    ・プレイヤーが選択を行うたびにカウント増やし何回選択したかを計測し、最後にスコアとして表示

    ・プレイヤーがカードを当てた回数もカウントする　なお、当たりの回数は配列内の同じ数字のペア数に等しい
    　なので、当たりの回数が　（カード総量 / 2）　に達したらゲーム終了
*/

#include <stdio.h>
#include <stdlib.h>

void output(int *psentou, int tate, int yoko,int *phantei);



int main(void)
{
    int cade[100][100] = {{0},{0}};         //神経衰弱のカード
    int i;                                  //ループカウンタ
    int j;                                  //ループカウンタ
    int temp1;                              //作業領域
    int temp2;                              //作業領域
    int scan_tate[2];                       //カードの読み込み(縦)に使用　　要素 0 が 1 回目、要素 1 が 2 回目
    int scan_yoko[2];                       //カードの読み込み(横)に使用   　　　　　　　　↑同上
    int tate;                               //神経衰弱のカード総量の縦
    int yoko;                               //神経衰弱のカード総量の横
    int count;                              //プレイヤーが何回カードをめくったかのカウント
    int error_flag;                         //入力のエラーチェックに使用
    int hit_flag;                           //選択した２枚のパネルが等しい回数のカウント、終了条件に使用

    printf("神経衰弱プログラム\n");

    //難易度選択
    printf("神経衰弱の難易度選択\n");
    printf("縦と横のカードの数を入力してください。(多いほど難易度が上がります)　また縦、横のどちらかは偶数で入力してください。\n");
    do {
        printf("縦　==> ");
        scanf("%d", &tate);
        printf("横 ==> ");
        scanf("%d", &yoko);
        if ((tate * yoko) % 2 == 1 ) {
            printf("カードの合計枚数が奇数になり神経衰弱が成立しません。\n");
            printf("縦、横どちらかは偶数を入力してください。\n");
        }
    } while ((tate * yoko) % 2 == 1);

    
    //rand関数を用いて配列内のランダムな場所に数字を配置　配列内の要素の初期値が０であることを利用し数字の被りを回避
    for (i = 0; i < ((tate * yoko) / 2); i++) {
        for (j = 0; j < 2; j++) {
            do {
                temp1 = 0 + rand() % tate;
                temp2 = 0 + rand() % yoko;
            } while (cade[temp1][temp2] != 0);
            cade[temp1][temp2] = i + 1;
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4;j++) {
            printf(" %d",cade[i][j]);
        }
        printf("\n");
    }

    printf("めくりたいカードは縦、横の順で入力してください。\n");
    printf("そりではゲームスタートです！\n");
    printf("\n");                           //ここではプレイヤーの選択がなく、？？のみを表示したいので４つ目の引数を配列外のものにしている

    hit_flag = 0;
    count = 0;

    do {
        printf(" %d 巡目\n", count + 1);
        printf("\n");
        
        //カードの入力(２枚分)　エラーチェックも同時に行う    
        for (i = 0; i < 2; i++) {
            do {
                printf("現時点の残りパネル\n");
                output(&cade[0][0],tate,yoko,&i);                       //ここではプレイヤーの選択がなく、残りパネルのみを表示したいので４つ目の引数を配列外のものにしている


                error_flag = 0;
                printf("%d 枚目のカードを入力してください。\n", i + 1);
                printf("縦 ==> ");
                scanf("%d", &scan_tate[i]);
                printf("横 ==> ");
                scanf("%d", &scan_yoko[i]);

                scan_tate[i] = scan_tate[i] - 1;
                scan_yoko[i] = scan_yoko[i] - 1;
                
                if (cade[scan_tate[i]][scan_yoko[i]] == 1000) {
                    printf("エラー 入力した %d 枚目のパネルはすでに裏返っています。もう 1 度入力してください。", i + 1);
                    error_flag = 1;
                } else if (scan_tate[i] > tate || scan_yoko[i] > yoko) {
                    printf("エラー 入力した %d 枚目のパネルは存在しません。もう 1 度入力してください。", i + 1);
                    error_flag  = 1;
                } else if (scan_tate[0] == scan_tate[1] && scan_yoko[0] == scan_yoko[1] && i == 1) {
                    printf("エラー 入力したパネルが同じです。もう 1 度 2 枚目のパネルを入力してください");
                    error_flag = 1;
                }
            } while (error_flag == 1);
            output(&cade[0][0], tate, yoko , &cade[scan_tate[i]][scan_yoko[i]]);      //プレイヤーが選択したカードを表示
        }   

        if (cade[scan_tate[0]][scan_yoko[0]] == cade[scan_tate[1]][scan_yoko[1]]) {
            printf("当たり！　当たった数字は %d でした\n", cade[scan_tate[0]][scan_yoko[0]]);
            cade[scan_tate[0]][scan_yoko[0]] = 1000;
            cade[scan_tate[1]][scan_yoko[1]] = 1000;
            hit_flag++;
        } else {
            printf("残念、、、外れ～\n");
        }

        printf("\n");
        count++;

    } while (hit_flag != (tate * yoko) / 2);


    printf("スコア発表\n");
    printf("あなたは %d 枚のカードを %d 回目で全て当てました", tate * yoko, count);

    return 0;
}

//神経衰弱のカードを表示する関数
//*pseisuにはcade配列の先頭アドレスを渡す
//プレイヤーに選んでもらったカード総量によって出力する範囲が変わるのでtate,yokoを渡す
//*phyouji　に渡したアドレスの中身(数字)を表示　（プレイヤーが選択する）
void output(int *psentou, int tate, int yoko, int *phyouji)
{
    int i;
    int *pcade;

    for (i = 0; i < yoko; i++){
        printf("    %d", i + 1);
    }
    printf("\n");

    for (i = 0; i < tate; i++){
        printf("%d", i + 1);
        for (pcade = psentou + (i * 100); *pcade != 0; pcade++) {
            if (pcade == phyouji) {
                printf("  %2d", *phyouji);
            } else if(*pcade == 1000){
                printf("     ");
            } else {
                printf("   ??");
            }
        }
        printf("\n");
    }
    
   
        printf("\n");
}