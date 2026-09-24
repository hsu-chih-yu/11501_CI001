# Code Review Report: [UVa] [10035] - [Primary Arithmetic]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10035
- **Problem Title:** Primary Arithmetic
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=976
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva10035.cpp](./src/uva10035.cpp)
- **Review Date:** 2026-09-24

## 2. Problem Statement in My Own Words

- 每一行包含兩個整數 `a` 和 `b`。當兩者皆為 0 時結束輸入。
- 計算這兩個數字相加時產生了多少次「進位」(Carry operations)，並以特定句型輸出。
- 輸出文字有單複數之分 (`No carry operation.`, `1 carry operation.`, `%d carry operations.`)。
- 模擬直式加法的過程，逐位檢查數字加總是否超過 9，並累計進位次數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 這題考察的是對十進位加法的拆解。只要像國小算術一樣，由右到左逐位相加即可。
- 需要一個變數 `count` 記錄前一位是否進位，另一個變數 `ans` 記錄總進位次數。

### Final Strategy
- 只要 `a > 0` 或 `b > 0` 其中一個成立，就進入迴圈。
- 取出目前兩數的個位數 `i = a % 10` 和 `j = b % 10`。
- 將兩者相加，加上前一次的進位 `count`。如果和大於 9，則總計數 `ans++`，並把進位 `count` 設為 1；否則進位設為 0。
- 將 `a` 和 `b` 除以 10 捨去最後一位。
- 結束後依照 `ans` 的數量決定輸出的單複數句型。

### Complexity Analysis
- **Time Complexity:** $O(\max(\log_{10} a, \log_{10} b))$。迴圈執行的次數等同於最大數字的位數長度。
- **Space Complexity:** $O(1)$。只用了四個整數變數。
- **為何滿足限制：** 針對每個數字頂多執行 10 次左右的迴圈，效能極佳。

## 4. Pseudocode
```
START
1. WHILE read a and b AND (a != 0 OR b != 0):
2.     SET ans = 0, count = 0
3.     WHILE a > 0 OR b > 0:
4.         i = a % 10
5.         j = b % 10
6.         IF i + j + count > 9 THEN
7.             ans = ans + 1
8.             count = 1
9.         ELSE count = 0
10.        a = a / 10
11.        b = b / 10
12.    IF ans == 0 THEN PRINT "No carry operation."
13.    ELSE IF ans == 1 THEN PRINT "1 carry operation."
14.    ELSE PRINT ans + " carry operations."
END
```
## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int main()
{
    int a, b;
    while(cin >> a >> b && (a != 0 && b != 0)){
        int ans = 0;
        int count = 0;
        while(a > 0 || b > 0){
            int i = a % 10;
            int j = b % 10;
            if(i + j + count > 9){
                ans ++;
                count = 1;
            }else{
                count = 0;
            }
            a /= 10;
            b /= 10;
        }
        if(ans == 0){
            cout << "No carry operation.\n";
        }else if(ans == 1){
            printf("1 carry operation.\n");
        }else{
            printf("%d carry operations.\n", ans);
        }
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 透過 `while(a > 0 || b > 0)` 確保即使兩數字位數不同長，也能完整處理較長的數字。將進位計數完美融入判斷式中。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 無進位 | `123 456` | `No carry operation.` | `No carry operation.` | 測試沒有進位的情況 |
| 單次進位 | `555 555` | `3 carry operations.` | `3 carry operations.` | 測試連續進位 |
| 位數不同 | `123 9` | `1 carry operation.` | `1 carry operation.` | 測試長度不同且單數輸出的文法 |

## 7. Reflection
- **根本原因：** 忘記單複數格式或漏算前一位進位是本題最容易出錯的地方。
- **學到的教訓：** 仔細區分 `No carry`, `1 carry` (單數不加s) 與 `n carry operations` (複數) 是 AC 的細節關鍵。
- **下一步行動：** 可以善用 `string` 與大數運算模組來擴充此邏輯，使其能處理超過 `long long` 範圍的超大數字相加。

## 8. AI Usage Disclaimer
- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10035 / Primary Arithmetic | Gemini | 幫助整理 README.md | 獨立實作位數拆解與進位邏輯 |
