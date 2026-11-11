# Code Review Report: [UVa] [11799] - [Horror Dash]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11799
- **Problem Title:** Horror Dash
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2899
- **Language / Version:** C++
- **Submission Result:** Accepted (original) → Improved
- **Source Code (Original/Accepted):** [src/uva11799_original.cpp](./src/uva11799_original.cpp)
- **Source Code (Final/Improved):** [src/uva11799.cpp](./src/uva11799.cpp)
- **Review Date:** 2026-10-21

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 第一行為測資筆數 $T$。每筆測資一行，第一個數字為學生人數 $N$，後面接著 $N$ 個整數代表每位學生的速度。
- **預期的輸出是什麼？** 輸出 `Case X: S`，其中 $S$ 是小丑（Clown）至少需要的速度，也就是所有學生速度中的最大值。
- **主要的規則與限制是什麼？** 小丑必須能追上每一位學生，因此速度不能低於任何一位學生；速度皆為正整數。
- **必須解決的核心任務是什麼？** 找出每一行數字中的最大值，並依格式輸出 Case 編號。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 小丑要追上所有人，只要速度等於最快的學生即可，所以答案就是該行速度的最大值。
- 原始版本以 `cin >> n` 讀數字、再用 `getchar()` 判斷後面是空白還是換行，逐行讀到行尾並維護最大值。
- 但這樣會把每行開頭的人數 $N$ 也當成速度一起比較：若 $N$ 大於所有速度（例如 `5 1 1 1 1 1`，正確答案為 `1`），原始程式會輸出 `5`。原始版本能 AC 只是因為 UVa 測資沒有出現這種情況，屬於潛在錯誤。

### Final Strategy

- 每行已經給了人數 $N$，因此改成先 `cin >> n`，再用 `for` 迴圈讀入恰好 $N$ 個速度。
- 只對速度維護最大值 `maxi`，$N$ 不再參與比較。
- 不需要判斷空白或換行，行尾多餘空白或 `\r\n` 都不會影響讀取。

### Complexity Analysis

- **Time Complexity:** $O(N)$ 每筆測資，每個速度只讀取並比較一次。
- **Space Complexity:** $O(1)$，只需保存目前最大值。
- **解釋為何這些複雜度滿足問題限制：** $N \le 100$，運算量極小。

## 4. Pseudocode
```
START
READ cases
FOR c = 1 TO cases:
    READ n
    SET maxi = 0
    FOR i = 1 TO n:
        READ speed
        maxi = max(maxi, speed)
    PRINT "Case " + c + ": " + maxi
END
```
## 5. Original Code vs Improved Code

### Original Code (Accepted)
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
**Potential problem:**
- **技術原因：** 每行開頭的人數 $N$ 被當成速度一起比較；且依賴「數字後面緊接一個空白或換行」判斷行尾，遇到行尾多餘空白或 `\r\n` 就會讀錯（與 Week 5 的 UVa 11827 同類問題）。
- **暴露問題的測資：** `5 1 1 1 1 1` → 原始程式輸出 `5`，正確答案為 `1`。

### Improved Code
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    for(int c = 1; c <= cases; c++){
        int n;
        cin >> n;
        int maxi = 0;
        for(int i = 0; i < n; i++){
            int speed;
            cin >> speed;
            maxi = max(maxi, speed);
        }
        printf("Case %d: %d\n", c, maxi);
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 先讀人數 $N$，再讀恰好 $N$ 個速度，因此 $N$ 不會被誤當成速度，也不受空白與換行格式影響；答案即為最快學生的速度。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 題目範例 | `5 9 3 5 2 6` | `Case 1: 9` | `Case 1: 9` | 驗證取最大值 |
| 最少人數 | `1 2` | `Case 2: 2` | `Case 2: 2` | 驗證只有一位學生的情況 |
| $N$ 大於所有速度 | `5 1 1 1 1 1` | `Case 3: 1` | `Case 3: 1` | 驗證 $N$ 不會被當成速度（原始版本會輸出 `5`） |

## 7. Reflection

- **根本原因：** 題目本質是求最大值，難點在於輸入格式；原始寫法忽略了每行開頭的 $N$ 本身不是速度。
- **解決辦法：** 利用題目給的 $N$ 控制讀取次數，取代以 `getchar()` 偵測行尾。
- **改進：** 題目有給「個數」時，優先用個數控制迴圈；只有在沒有給個數時，才改用 `getline` + `stringstream` 讀整行。AC 不代表程式完全正確，要自己設計邊界測資檢查。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11799 / Horror Dash | Claude | 幫助整理 README.md | 獨立確認最大值邏輯與輸入讀取方式 |
