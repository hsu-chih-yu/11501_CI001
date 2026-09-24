# Code Review Report: [UVa] [1225] - [Digit Counting]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 1225
- **Problem Title:** Digit Counting
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3666
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva1225.cpp](./src/uva1225.cpp)
- **Review Date:** 2026-09-24

## 2. Problem Statement in My Own Words

- 測資數量 `cases`，接著每一筆給定一個整數 `n`。
- 輸出在 1 到 `n` 的所有整數中，數字 0 到 9 各出現了多少次，以空白分隔。
- 必須將多個數字拆解，分別統計每個位數的出現次數。
- 建立計數陣列，並透過迴圈與除法運算分解每一位數字。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 可以將 1 到 `n` 轉成字串，再統計字元個數，但數字與字串轉換比較耗時。
- 直接對數字做數學運算（取餘數、除以 10）是更有效率且標準的解法。

### Final Strategy
- 建立一個大小為 10 的陣列 `a[10]` 並初始化為 0，代表數字 0~9 的計數器。
- 用 `for` 迴圈從 1 走到 `n`，對每個數字 `temp` 使用 `temp % 10` 取得個位數，並將對應的 `a[t]` 加一。
- 將 `temp` 除以 10 進入下一位，直到數字變為 0。
- 最後輸出陣列 0 到 9 的結果。

### Complexity Analysis
- **Time Complexity:** $O(N \log_{10} N)$。迴圈跑 $N$ 次，每次需要分解數字位數，時間對應數字長度。
- **Space Complexity:** $O(1)$。僅使用長度固定為 10 的陣列 `a`。
- **為何滿足限制：** $N$ 範圍通常不大（UVa 原題 $N \le 10000$），這套直接硬上的算法完全足夠。

## 4. Pseudocode
```
START
1. READ cases
2. WHILE cases > 0:
3.     READ n
4.     INIT array a[10] = {0}
5.     FOR i = 1 TO n:
6.         temp = i
7.         WHILE temp > 0:
8.             t = temp % 10
9.             a[t] = a[t] + 1
10.            temp = temp / 10
11.    PRINT array a from 0 to 9 separated by space
12.    cases = cases - 1
END
```
## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    while(cases--){
        int n;
        cin >> n;
        int a[10] = {};
        for(int i = 1; i <= n; i++){
                int temp = i;
            while(temp > 0){
                int t = temp % 10;
                a[t] ++;
                temp /= 10;
            }
        }
        for(int i = 0; i < 9; i++){
            cout << a[i] << " ";
        }
        cout << a[9] << endl;
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 利用 `% 10` 取出最後一位，然後用 `/ 10` 截斷該位數，這是剝離十進位數字最可靠的方法。陣列歸零 `int a[10] = {}` 保證了每筆測資獨立運作。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `3` | `0 1 1 1 0 0 0 0 0 0` | `0 1 1 1 0 0 0 0 0 0` | 測試 1, 2, 3 的組成 |
| 進位情況 | `13` | 統計 1~13 | 正確對應 | 測試兩位數 10~13 中 1 和 0 的計數 |
| 邊界情況 | `1` | `0 1 0...` | `0 1 0...` | 測試極小值 |

## 7. Reflection
- **根本原因：** 分解位數並統計頻率是基本的陣列應用。
- **學到的教訓：** `int a[10] = {};` 這種寫法是將陣列全域初始化為 0 的乾淨作法，避免迴圈 `memset`。
- **下一步行動：** 若數字非常大，可能需要推導排列組合公式來計算出現次數（$O(\log N)$ 解法），而非暴力計算。

## 8. AI Usage Disclaimer
- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 1225 / Digit Counting | Gemini | 幫助整理 README.md | 獨立實作數字位元分解邏輯 |
