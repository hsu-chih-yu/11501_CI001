# Code Review Report: [UVa] [11332] - [Summing Digits]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11332
- **Problem Title:** Summing Digits
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2307
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11332.cpp](./src/uva11332.cpp)
- **Review Date:** 2026-09-24

## 2. Problem Statement in My Own Words

- 一系列的正整數 `n`，當遇到 0 時代表結束。
- 對應每個數字，印出其化簡後的「個位數」。
- 將數字的每一位相加，若加總結果還是多位數（$\ge 10$），則繼續相加，直到數字變成單一位數為止。
- 使用雙重迴圈結構：外層確保數字降至個位數，內層負責分解位數相加。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 可以使用遞迴，也可以直接用迴圈。考慮到這題邏輯單純，迴圈包迴圈是最直接的解法。
- 也可以利用數學解（同餘理論中，數字位數和相當於該數 `% 9`），但直觀模擬法更不容易出錯。

### Final Strategy
- 第一層 `while` 迴圈負責讀取測資，遇到 `n == 0` 時跳出。
- 第二層 `while(n >= 10)` 迴圈用來檢查當前數字是否超過一位數。
- 第三層 `while(t > 0)` 迴圈把數字 `t` 的每一位分離出來（`t % 10`）並累加到 `ans`，最後再把 `ans` 賦值回給 `n` 進行下一輪檢查。

### Complexity Analysis
- **Time Complexity:** 極低。第一次相加花費 $O(\log_{10} n)$ 時間，得到的數不會超過 90（因 $N \le 2\times10^9$，最多十位數 $9 \times 10=90$），後續相加步數極少，總體接近 $O(1)$。
- **Space Complexity:** $O(1)$。僅使用 `t` 和 `ans` 變數。
- **為何滿足限制：** 運算量小到可以忽略不計。

## 4. Pseudocode
```
START
1. WHILE read n AND n != 0:
2.     WHILE n >= 10:
3.         t = n
4.         ans = 0
5.         WHILE t > 0:
6.             ans = ans + (t % 10)
7.             t = t / 10
8.         n = ans
9.     PRINT n
END
```
## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int main()
{
    int n;
    while(cin >> n && n != 0){
        while(n >= 10){
            int t = n;
            int ans = 0;
            while(t > 0){
                ans += t % 10;
                t /= 10;
            }
            n = ans;
        }
        cout << n << endl;
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 透過 `while(n >= 10)` 持續壓縮數字，並搭配內層 `while(t > 0)` 精確執行每一位的抽離相加，能穩穩處理所有過程。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 個位數輸入 | `2` | `2` | `2` | 測試不需相加的情況 |
| 雙位數輸入 | `11` | `2` | `2` | 測試一次相加 |
| 需多次相加 | `47` | `2` | `2` | 測試 4+7=11 -> 1+1=2 的多重折疊 |

## 7. Reflection
- **根本原因：** 此題純粹測驗對數字 `% 10` 與 `/ 10` 運算的熟練度。
- **學到的教訓：** 雖然可以用模擬法實作，但其實這就是數學中的「數位根」(Digital Root) 問題，如果 `n % 9 == 0` 答案是 9，否則答案是 `n % 9`。
- **下一步行動：** 嘗試使用數學解法 (`n % 9`) 改寫，可以將整個迴圈簡化為一行程式碼，作為精進的挑戰。

## 8. AI Usage Disclaimer
- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11332 / Summing Digits | Gemini | 幫助整理 README.md | 獨立實作數字壓縮模擬迴圈 |