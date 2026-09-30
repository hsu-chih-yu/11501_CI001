# Code Review Report: [UVa] [12468] - [Zapping]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 12468
- **Problem Title:** Zapping
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3912
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva12468.cpp](./src/uva12468.cpp)
- **Review Date:** 2026-09-30

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 每行包含兩個整數 `a` 和 `b`，代表電視遙控器的目前頻道與目標頻道（頻道範圍為 0 到 99）。輸入直到 `a = -1` 且 `b = -1` 時結束。
- **預期的輸出是什麼？** 從目前頻道切換到目標頻道所需按按鈕的最少次數，並換行輸出。
- **主要的規則與限制是什麼？** 遙控器只有「上一個頻道」與「下一個頻道」兩個按鈕。頻道為循環設計（0 的前一個是 99，99 的下一個是 0），共有 100 個頻道。
- **必須解決的核心任務是什麼？** 計算環狀結構中兩個數字之間的最短距離（順時針與逆時針兩種走法取最小值）。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 直覺的想法是先計算兩頻道的直接絕對差值 `abs(b - a)`。
- 但因為頻道首尾相連（環狀），往另一個方向切換的步數就是 `100 - abs(b - a)`。

### Final Strategy

- 讀取 `a` 與 `b`，終止條件為 `a != -1 && b != -1`。
- 計算直接差值：`a = abs(b - a)`。
- 計算跨越邊界（99 與 0）的反向步數：`n = 100 - a`。
- 比較兩者大小，輸出較小的值（`a < n ? a : n`）。

### Complexity Analysis

- **Time Complexity:** $O(1)$ 每筆測資。只進行一次絕對值與一次減法比較。
- **Space Complexity:** $O(1)$。僅使用兩個輸入變數與一個暫存差值的變數。
- **解釋為何這些複雜度滿足問題限制：** 運算量為極小的常數時間，能瞬間處理大量輸入資料。

## 4. Pseudocode
```
START
1. WHILE read a and b successfully AND a != -1 AND b != -1:
2.     SET diff = abs(b - a)
3.     SET reverse_diff = 100 - diff
4.     IF diff < reverse_diff THEN
5.         PRINT diff
6.     ELSE
7.         PRINT reverse_diff
8. END WHILE
END
```
## 5. Correct Code
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a, b;
    while(cin >> a >> b && a != -1 && b != -1){
         a = abs(b - a);
        int n = 100 - a;
        if(a < n){
            cout << a << endl;

        }else{
            cout << n << endl;
        }
    }
    return 0;
}
```

**Why it works：**
- **關鍵條件：** 電視頻道總數固定為 100 個並構成一個圓環。兩點在圓環上的最短距離必然是「直接相減的絕對值」與「補數（100 - 絕對值）」兩者中的最小值。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般相鄰 | `10 15` | `5` | `5` | 測試同向直接切換 |
| 跨越邊界 | `2 98` | `4` | `4` | 測試反向跨越 0 與 99 更短的情形 |
| 相同頻道 | `50 50` | `0` | `0` | 測試原地不需按按鈕的情形 |

## 7. Reflection

- **根本原因：** 環狀陣列/循環問題若只考慮單向差值，會忽略跨越首尾的更短路徑。
- **解決辦法：** 計算兩點直接距離後，用總長度減去直接距離得到反向距離，兩者取最小值。
- **改進：** 遇到環狀或模數（Modulo）循環問題時，直接利用「正向差」與「總長度減正向差」取極小值是標準且不易出錯的做法。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 12468 / Zapping | Gemini | 幫助整理 README.md | 獨立完成環狀最短距離推導與邏輯實作 |