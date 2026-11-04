# Code Review Report: [UVa] [11799] - [Horror Dash]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11799
- **Problem Title:** Horror Dash
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2899
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11799.cpp](./src/uva11799.cpp)
- **Review Date:** 2026-10-21

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 第一行為測資筆數 $T$。每筆測資一行，第一個數字為學生人數 $N$，後面接著 $N$ 個整數代表每位學生的速度。
- **預期的輸出是什麼？** 輸出 `Case X: S`，其中 $S$ 是小丑（Clown）至少需要的速度，也就是所有學生速度中的最大值。
- **主要的規則與限制是什麼？** 小丑必須能追上每一位學生，因此速度不能低於任何一位學生；速度皆為正整數。
- **必須解決的核心任務是什麼？** 找出每一行數字中的最大值，並依格式輸出 Case 編號。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 小丑要追上所有人，只要速度等於最快的學生即可，所以答案就是該行的最大值。
- 由於每行開頭的 $N$ 本身也是正整數，且 $N$ 不會影響「是否需要讀完這一行」，因此可以選擇逐行讀到換行為止。

### Final Strategy

- 以 `cin >> n` 讀取數字，再用 `getchar()` 讀取緊接在後的字元：若是空白代表同一行還有數字，若是換行（或 EOF）則該行結束。
- 一路維護最大值 `maxi`（初始為 -1）。
- 注意：這個寫法會把每行開頭的 $N$ 也當成速度一起比較。若出現 $N$ 大於所有速度的測資（例如 `5 1 1 1 1 1`，正確答案為 `1`，程式卻會輸出 `5`），就會答錯；本次能 AC 是因為 UVa 測資沒有出現這種情況，屬於潛在錯誤。

### Complexity Analysis

- **Time Complexity:** $O(N)$ 每筆測資，每個數字只讀取並比較一次。
- **Space Complexity:** $O(1)$，只需保存目前最大值。
- **解釋為何這些複雜度滿足問題限制：** $N \le 100$，運算量極小。

## 4. Pseudocode
```
START
READ cases
SET caseNo = 1
WHILE cases > 0:
    SET c = ' ', maxi = -1
    WHILE c == ' ':
        READ n
        IF n > maxi THEN maxi = n
        c = next character
    PRINT "Case " + caseNo + ": " + maxi
    caseNo = caseNo + 1
    cases = cases - 1
END
```
## 5. Correct Code
```cpp
#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

int main()
{
    int cases;
    cin >> cases;
    int i = 1;
    while(cases--){

        char c = ' ';
        int maxi = -1;
        while(c == ' '){
            int n;
            cin >> n;
            if(n > maxi){
                maxi = n;
            }
            c = getchar();
        }
        printf("Case %d: %d\n", i, maxi);
        i++;
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** `getchar()` 能判斷數字後方是空白還是換行，藉此在同一行內持續讀取並維護最大值；答案即為最快學生的速度。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 題目範例 | `5 9 3 5 2 6` | `Case 1: 9` | `Case 1: 9` | 驗證取最大值 |
| 最少人數 | `1 2` | `Case 2: 2` | `Case 2: 2` | 驗證只有一位學生的情況 |

## 7. Reflection

- **根本原因：** 題目本質是求最大值，難點在於輸入格式的處理。
- **解決辦法：** 利用 `getchar()` 偵測行尾。
- **改進：** 目前的寫法會把 $N$ 誤當成速度比較，是潛在的錯誤。此外，依賴「數字後面緊接一個空白或換行」的讀法很脆弱（例如行尾有多餘空白或 Windows 的 `\r\n` 就會出錯，Week 5 的 UVa 11827 就踩過這個坑）。既然每行已經給了 $N$，更穩健的寫法是先 `cin >> n`，再用 `for` 迴圈讀 $N$ 個速度。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11799 / Horror Dash | Claude | 幫助整理 README.md | 獨立確認最大值邏輯與輸入讀取方式 |
