# Code Review Report: [UVa] [11185] - [Ternary]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11185
- **Problem Title:** Ternary
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2126
- **Language / Version:** C++
- **Submission Result:** Wrong Answer / Need Revision
- **Source Code (Initial/Fail):** [src/uva11185_fail.cpp](./src/uva11185_fail.cpp)
- **Source Code (Final/Accepted):** [src/uva11185.cpp](./src/uva11185.cpp)
- **Review Date:** 2026-10-14

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 多行輸入，每行一個十進位非負整數 $N$ ($0 \le N < 10^9$)。當讀到「負數」時結束輸入。
- **預期的輸出是什麼？** 將 $N$ 轉換為三進位（ternary）表示法後輸出，每筆一行。
- **主要的規則與限制是什麼？** 結束條件是「任意負數」，並不一定是 `-1`；$N = 0$ 時必須輸出 `0`。
- **必須解決的核心任務是什麼？** 正確實作十進位轉三進位，並正確判斷輸入的終止條件。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 先找出大於 $N$ 的最小 $3^k$（變數 `t`），再從最高位往下，每一位計算可以減掉幾次 `t`，該次數即為該位的三進位數字。
- 用 `long long b` 把每一位數字「當作十進位數字」拼接起來（`b = b * 10 + digit`）直接輸出。
- 一開始把結束條件寫成 `n != -1`，以為題目只會用 `-1` 結束。

### Final Strategy

- 演算法本身正確：$10^9$ 的三進位最多 19 位，且每位不超過 2，拼成的十進位數最大約 $2.2 \times 10^{18}$，仍在 `long long`（約 $9.2 \times 10^{18}$）範圍內，不會溢位。
- 真正的錯誤在結束條件：題目說輸入以「負數」結束，因此將 `n != -1` 改為 `n >= 0`。
- 當 $N = 0$ 時，`t = 1` 不進入任何迴圈，`b` 保持 0，正確輸出 `0`。

### Complexity Analysis

- **Time Complexity:** $O(\log_3 N)$ 每筆測資。最多 19 位，每位最多減兩次。
- **Space Complexity:** $O(1)$。只使用 `n`、`b`、`t` 三個變數。
- **解釋為何這些複雜度滿足問題限制：** 每筆測資只需幾十次運算，遠低於時間限制。

## 4. Pseudocode
```
START
WHILE read n successfully AND n >= 0:
    SET b = 0
    SET t = 1
    WHILE t <= n:
        t = t * 3
    WHILE t != 1:
        t = t / 3
        b = b * 10
        WHILE t <= n:
            n = n - t
            b = b + 1
    PRINT b
END
```
## 5. Fail Code vs Correct Code

### Fail Code
```cpp
#include <iostream>

using namespace std;

int main()
{
    long long n;
    while(cin >> n && n != -1){
        long long b = 0;
        long long t = 1;
        while(t <= n) t*= 3;
        while(t != 1){
            t/=3;
            b *= 10;
            while(t <= n){
                n -= t;
                b++;
            }
        }
        printf("%lld\n", b);
    }
    return 0;
}
```
**Why it failed:**
- **技術原因：** 迴圈結束條件寫成 `n != -1`。題目只保證以「負數」結束，若最後一筆是 `-2`、`-100` 等其他負數，程式不會停止，而是把該負數當成一般輸入處理（`t <= n` 永不成立，輸出多餘的 `0`），造成輸出多一行而判定 Wrong Answer。
- **暴露問題的測資：** `1 0 3 -5` → 錯誤程式輸出 `1`、`0`、`10` 之後還會多輸出一行 `0`。

### Correct Code
```cpp
#include <iostream>

using namespace std;

int main()
{
    long long n;
    while(cin >> n && n >= 0){
        long long b = 0;
        long long t = 1;
        while(t <= n) t *= 3;
        while(t != 1){
            t /= 3;
            b *= 10;
            while(t <= n){
                n -= t;
                b++;
            }
        }
        printf("%lld\n", b);
    }
    return 0;
}
```
**Why it works:**
- **關鍵條件：** 將結束條件改為 `n >= 0`，任何負數都會立即結束輸入；轉換演算法保持不變，並已確認 `long long` 足以容納最大 19 位的三進位結果。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `1`, `3`, `10` | `1`, `10`, `101` | `1`, `10`, `101` | 驗證基本進位轉換 |
| 邊界值 0 | `0` | `0` | `0` | 確認 $N = 0$ 不會輸出空行 |
| 最大值 | `1000000000` | `2120200200021010001` | `2120200200021010001` | 確認 19 位結果不會溢位 |
| 非 -1 的負數結尾 | `1 0 3 -5` | `1`, `0`, `10`（共三行） | `1`, `0`, `10`（共三行） | 驗證任何負數都會終止輸入 |

## 7. Reflection

- **根本原因：** 沒有仔細閱讀題目的輸入結束條件，憑直覺假設是 `-1`。
- **解決辦法：** 將終止條件改為涵蓋所有負數的 `n >= 0`。
- **改進：** 撰寫輸入迴圈前先確認題目的終止描述（「negative number」與「-1」意義不同）；遇到「數字當字串拼接」的寫法時，也要先估算位數確認型態不會溢位，或改用 `string` 儲存結果。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11185 / Ternary | Claude | 幫助分析 Wrong Answer 原因與整理 README.md | 獨立確認終止條件修正與 `long long` 位數範圍 |
