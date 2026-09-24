# Code Review Report: [UVa] [11172] - [Relational Operator]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11172
- **Problem Title:** Relational Operator
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2113
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11172.cpp](./src/uva11172.cpp)
- **Review Date:** 2026-09-24

## 2. Problem Statement in My Own Words

- 第一行為測資筆數，接下來每一行包含兩個整數 `a` 和 `b`。
- 輸出兩者大小關係對應的符號：`>`、`<` 或 `=`。
- 需處理多筆測資，判斷簡單的大小關係。
- 使用條件判斷式比較兩個數字並輸出正確的關係符號。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直覺的想法是直接使用`if-else`來區分三種可能的情況。
- 這個問題非常單純，沒有複雜的邊界條件需要特別考慮。

### Final Strategy
- 利用 `if (a > b)`、`else if (a == b)` 與 `else if (a < b)` 進行邏輯分流。
- 因為只有三種互斥結果，這個方法精準且不會有遺漏。

### Complexity Analysis
- **Time Complexity:** $O(1)$ 每筆測資。只需執行兩次比較運算。
- **Space Complexity:** $O(1)$。僅使用兩個變數 `a` 與 `b`。
- **解釋為何滿足限制：** 基本比較運算極其輕量，完全能在時間限制內完成。

## 4. Pseudocode
```
START
1. READ number of cases
2. WHILE cases > 0:
3.     READ a, b
4.     IF a > b THEN PRINT ">"
5.     ELSE IF a == b THEN PRINT "="
6.     ELSE IF a < b THEN PRINT "<"
7.     cases = cases - 1
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
        int a, b;
        cin >> a >> b;
        if(a > b){
            cout << ">";
        }else if(a == b){
            cout << "=";
        }else if(a < b){
            cout << "<";
        }
        cout << endl;
    }
    return 0;
}
```

**Why it works：**
- **關鍵條件：** 數字之間的關係必然屬於大於、等於或小於其中之一，透過 `if-else if` 的結構可以完美覆蓋所有情況，達到正確輸出。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `10 20` | `<` | `<` | 測試小於 |
| 一般情況 | `20 10` | `>` | `>` | 測試大於 |
| 邊界情況 | `10 10` | `=` | `=` | 測試等於 |

## 7. Reflection
- **根本原因：** 這是基本語法練習題，直接實作即可。
- **學到的教訓：** 保持程式碼簡潔，善用 `if-else` 結構。
- **下一步行動：** 確認變數型態是否能容納題目可能給的數值（例如是否需要用到 `long long`）。

## 8. AI Usage Disclaimer
- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11172 / Relational Operator | Gemini | 幫助整理 README.md | 獨立完成條件判斷實作 |
