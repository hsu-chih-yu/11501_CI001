# Code Review Report: [UVa] [10019] - [Funny Encryption Method]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10019
- **Problem Title:** Funny Encryption Method
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=960
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva10019.cpp](./src/uva10019.cpp)
- **Review Date:** 2026-10-14

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 第一行為測資筆數 $N$，接下來每行一個整數 $M$ ($0 < M \le 9999$)。
- **預期的輸出是什麼？** 輸出兩個數字 $b_1$ 與 $b_2$：$b_1$ 是把 $M$ 當十進位轉成二進位後 `1` 的個數；$b_2$ 是把 $M$ 的每一位數字當成十六進位的一位（即每位 0~9 各自轉成 4 位二進位）後 `1` 的個數。
- **主要的規則與限制是什麼？** $M$ 最多 4 位數，因此二進位不會超過 14 位。
- **必須解決的核心任務是什麼？** 計算整數的二進位中 `1` 的個數，並對每一位十進位數字分別計算後加總。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- $b_1$：直接計算 $M$ 的二進位中有幾個 `1`。
- $b_2$：把 $M$ 視為十六進位，等同於把每一位十進位數字（0~9）分別轉成二進位後數 `1`，最後加總。

### Final Strategy

- 計算 `1` 的個數：從 $2^{14} = 16384$ 開始往下除以 2，若 `n >= t` 就減掉 `t` 並計數，最後若剩下 `n == 1` 再加一，即為二進位 `1` 的個數。
- 把這段邏輯包成函式 `binary(n)`。
- $b_1$ 直接在 `main` 中對 $M$ 計算；$b_2$ 則用 `n % 10` 逐位取出數字並呼叫 `binary(k)` 累加。

### Complexity Analysis

- **Time Complexity:** $O(\log M)$ 每筆測資。$b_1$ 固定約 14 次比較，$b_2$ 對最多 4 位數字各做 14 次比較。
- **Space Complexity:** $O(1)$。只使用固定數量的整數變數。
- **解釋為何這些複雜度滿足問題限制：** 每筆測資只需不到百次運算，效能完全足夠。

## 4. Pseudocode
```
START
FUNCTION binary(n):
    SET count = 0, t = 16384
    WHILE t != 1:
        IF n >= t THEN
            n = n - t
            count = count + 1
        t = t / 2
    IF n == 1 THEN count = count + 1
    RETURN count

READ c
WHILE c > 0:
    READ n
    SET b1 = binary(n)
    SET b2 = 0
    WHILE n > 0:
        b2 = b2 + binary(n % 10)
        n = n / 10
    PRINT b1, b2
    c = c - 1
END
```
## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int binary(int n){
        int ans1 = 0;
        int t = 1024*16;
        int N = n;

        while(t != 1 ){
            if(n >= t){
                n -= t;
                ans1++;
            }
            t /= 2;
        }
        if(n == 1)ans1++;
        return ans1;
        }

int main()
{
    int c;
    cin >> c;
    while(c--){
        int n;
        cin >> n;
        int ans1 = 0;
        int t = 1024*16;
        int N = n;

        while(t != 1 ){
            if(n >= t){
                n -= t;
                ans1++;
            }
            t /= 2;
        }
        if(n == 1)ans1++;
        n = N;
        int ans2 = 0;
        while(n > 0){
            int k = n % 10;
            ans2 += binary(k);
            n /= 10;
        }
        cout << ans1 << " " << ans2 << endl;
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 從 $2^{14}$ 往下逐一扣除的方式等同於找出所有為 `1` 的位元，因 $M \le 9999 < 16384$，範圍完全涵蓋；十六進位每一位對應 4 個二進位位元，因此 $b_2$ 等於各十進位數字的 `1` 個數總和。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 題目範例 | `265` | `3 5` | `3 5` | 驗證範例運算正確 |
| 題目範例 | `111` | `6 3` | `6 3` | 驗證 $b_2$ 逐位加總 |
| 題目範例 | `1234` | `5 5` | `5 5` | 驗證四位數字的情況 |

## 7. Reflection

- **根本原因：** 此題的關鍵是理解「把十進位數字當十六進位解讀」等同於逐位分別轉二進位。
- **解決辦法：** 將「計算二進位 1 的個數」抽成函式重複使用。
- **改進：** `main` 中計算 $b_1$ 的程式碼與 `binary()` 完全相同，可以直接寫成 `ans1 = binary(n)` 減少重複；也可以使用 `n & 1` 搭配 `n >>= 1` 或 `__builtin_popcount(n)` 讓程式更簡潔。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10019 / Funny Encryption Method | Claude | 幫助整理 README.md | 獨立實作二進位計數函式與逐位加總邏輯 |
