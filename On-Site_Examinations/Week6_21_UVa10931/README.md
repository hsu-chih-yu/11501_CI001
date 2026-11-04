# Code Review Report: [UVa] [10931] - [Parity]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10931
- **Problem Title:** Parity
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1872
- **Language / Version:** C++
- **Submission Result:** Wrong Answer / Need Revision
- **Source Code (Initial/Fail):** [src/uva10931_fail.cpp](./src/uva10931_fail.cpp)
- **Source Code (Final/Accepted):** [src/uva10931.cpp](./src/uva10931.cpp)
- **Review Date:** 2026-10-14

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 多行輸入，每行一個正整數 $I$ ($1 \le I \le 2147483647$)，讀到 `0` 時結束。
- **預期的輸出是什麼？** 輸出 `The parity of B is P (mod 2).`，其中 $B$ 是 $I$ 的二進位表示（無前導零），$P$ 是二進位中 `1` 的個數。
- **主要的規則與限制是什麼？** $I$ 最大為 $2^{31} - 1$，二進位最多有 31 位。
- **必須解決的核心任務是什麼？** 將整數轉為二進位字串輸出，同時計算其中 `1` 的個數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 用 `n % 2`、`n /= 2` 取得每一個二進位位元，從低位存進陣列 `b[]`，同時累計 `1` 的個數 `ans`。
- 原本想把陣列「倒過來」拼成一個十進位整數 `k`（例如 `1010`）再一次輸出。

### Final Strategy

- 位元的取得與 `1` 的計數邏輯是正確的。
- 問題出在 `int k`：二進位位元當作十進位數字拼接時，31 位的數字（約 $10^{30}$）遠超過 `int` 甚至 `long long` 的範圍，造成溢位。
- 改為從最高位到最低位「逐位輸出」`b[i]`，完全不需要把結果存成整數。

### Complexity Analysis

- **Time Complexity:** $O(\log I)$ 每筆測資，最多 31 次除法與輸出。
- **Space Complexity:** $O(\log I)$，陣列 `b[]` 最多使用 31 格。
- **解釋為何這些複雜度滿足問題限制：** 每筆測資只需數十次運算，執行時間可忽略。

## 4. Pseudocode
```
START
WHILE read n successfully AND n != 0:
    SET ans = 0, t = 0
    WHILE n > 0:
        IF n % 2 == 1 THEN
            ans = ans + 1
            b[t] = 1
        t = t + 1
        n = n / 2
    PRINT "The parity of "
    FOR i = t - 1 DOWNTO 0:
        PRINT b[i]
    PRINT " is " + ans + " (mod 2)."
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
    while(cin >> n && n != 0){
        int ans = 0;
        int  b[100] = {};
        long long t = 0;


        while(n > 0){
            if(n % 2 == 1){
                ans++;
                b[t] = 1;
            }
            t++;
            n /= 2;
        }
        cout << "The parity of " ;
        int k = 0;
        for(int i = t - 1; i >= 0; i--){
            k = k * 10 + b[i];
        }
        cout << k ;
        cout << " is " << ans << " (mod 2)." << endl;
    }
    return 0;
}
```
**Why it failed:**
- **技術原因：** 用 `int k = k * 10 + b[i]` 把二進位位元拼成十進位整數。`int` 最多只能表示約 10 位十進位數字，當 $I \ge 1024$（二進位 11 位以上）時 `k` 就會溢位，輸出錯誤的數字。
- **暴露問題的測資：** `2147483647` → 錯誤程式輸出 `The parity of 1193046471 is 31 (mod 2).`，正確應為 31 個 `1`。

### Correct Code
```cpp
#include <iostream>

using namespace std;

int main()
{
    long long n;
    while(cin >> n && n != 0){
        int ans = 0;
        int b[100] = {};
        int t = 0;

        while(n > 0){
            if(n % 2 == 1){
                ans++;
                b[t] = 1;
            }
            t++;
            n /= 2;
        }
        cout << "The parity of ";
        for(int i = t - 1; i >= 0; i--){
            cout << b[i];
        }
        cout << " is " << ans << " (mod 2)." << endl;
    }
    return 0;
}
```
**Why it works:**
- **關鍵條件：** 不再把二進位結果存成整數，而是從 `b[t-1]` 到 `b[0]` 逐位輸出，因此不論多少位元都不會溢位。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 最小值 | `1` | `The parity of 1 is 1 (mod 2).` | `The parity of 1 is 1 (mod 2).` | 測試只有一位的邊界 |
| 一般情況 | `10` | `The parity of 1010 is 2 (mod 2).` | `The parity of 1010 is 2 (mod 2).` | 驗證位元順序正確 |
| 一般情況 | `21` | `The parity of 10101 is 3 (mod 2).` | `The parity of 10101 is 3 (mod 2).` | 驗證 1 的計數正確 |
| 最大值 | `2147483647` | 31 個 `1`，`is 31` | 31 個 `1`，`is 31` | 驗證長位元不會溢位 |

## 7. Reflection

- **根本原因：** 把「數字的字串表示」當成整數儲存，忽略了二進位位數遠多於十進位、會快速超出整數型態範圍。
- **解決辦法：** 改為直接逐位輸出陣列內容。
- **改進：** 只要是「輸出某種進位的表示法」，優先考慮逐位輸出或使用 `string`；提交前務必用題目上限（例如 $2^{31}-1$）測試。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10931 / Parity | Claude | 幫助分析溢位原因與整理 README.md | 獨立以最大值測資驗證逐位輸出的正確性 |
