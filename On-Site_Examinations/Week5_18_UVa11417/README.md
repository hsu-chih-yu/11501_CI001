# Code Review Report: [UVa] [11417] - [GCD]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11417
- **Problem Title:** GCD
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2412
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11417.cpp](./src/uva11417.cpp)
- **Review Date:** 2026-10-07

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 每行包含一個整數 $N$ ($1 < N < 501$)，當輸入 $N = 0$ 時終止程式。
- **預期的輸出是什麼？** 輸出所有滿足 $1 \le i < j \le N$ 的數對 $(i, j)$ 之最大公因數總和 $G$，並換行。
- **主要的規則與限制是什麼？** $N$ 最大僅為 $500$，需要加總所有可能組合的 GCD 值。
- **必須解決的核心任務是什麼？** 實作輾轉相除法計算 GCD，並透過雙層迴圈枚舉所有 $1 \le i < j \le N$ 的組合進行加總。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 題目的數值範圍很小（$N < 501$），直接按照題目給定的雙層迴圈邏輯進行雙重窮舉是直覺可行的。
- 需要實作一個有效率且穩健的 GCD 函式，避免使用窮舉因數導致超時。

### Final Strategy

- 實作經典的歐幾里得演算法（輾轉相除法）`getgcd(a, b)`：每次計算 `remainder = a % b`，並反覆迭代直到 `b == 0`，最後取 `abs(a)`。
- 外層迴圈 `i` 從 1 跑到 $n-1$，內層迴圈 `j` 從 $i+1$ 跑到 $n$。
- 累加每一對的 `getgcd(i, j)` 至總和 `g` 中，迴圈結束後輸出 `g`。
- 輸入為 0 時跳出迴圈。

### Complexity Analysis

- **Time Complexity:** $O(N^2 \log N)$ 每筆測資。雙層迴圈共執行約 $\frac{N(N-1)}{2}$ 次，每次呼叫 GCD 的時間複雜度為對數級別 $O(\log N)$。當 $N \le 500$ 時，總運算次數約為 $1.25 \times 10^5$ 次，耗時僅數毫秒。
- **Space Complexity:** $O(1)$。僅使用常數等級的變數存放累加值與迴圈計數。
- **解釋為何這些複雜度滿足問題限制：** 運算規模非常小，能在遠低於 1 秒的時間限制內輕鬆通過。

## 4. Pseudocode
```
START
FUNCTION getgcd(a, b):
    WHILE b != 0:
        remainder = a % b
        a = b
        b = remainder
    RETURN abs(a)

WHILE read n successfully AND n != 0:
    SET g = 0
    FOR i = 1 TO n - 1:
        FOR j = i + 1 TO n:
            g = g + getgcd(i, j)
    PRINT g
END
```
## 5. Correct Code
```cpp
#include <iostream>
#include <cmath>

using namespace std;


long long getgcd(long long a, long long b){
    while(b != 0){
        long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return abs(a);
}


int main()
{
    int n;
    while(cin >> n && n != 0){
        int g = 0;
        for(int i = 1; i < n; i++){
            for(int j = i + 1 ; j <= n; j++){
                g += getgcd(i, j);
            }
        }
        cout << g << endl;
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 雙層迴圈精確走訪了所有滿足 $i < j$ 的數對，無重複亦無遺漏；歐幾里得演算法保證了以極高的效率正確求得兩數的最大公因數。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 最小範圍 | `2` | `1` | `1` | 測試只有一對數 (1, 2) 的邊界情況 |
| 一般數值 | `10` | `67` | `67` | 驗證題目範例測資運算正確性 |
| 最大邊界 | `100` | `13015` | `13015` | 測試較大數值下的累加正確度與效能 |

## 7. Reflection

- **根本原因：** 此題為雙層枚舉與基本數論結合的經典題型。
- **解決辦法：** 使用輾轉相除法替代暴力列舉因數，保證單次 GCD 的執行速度。
- **改進：** 若 $N$ 的上限進一步提高（例如 $N \le 10^6$），暴力雙層枚舉會超時，屆時需要使用歐拉函數（Euler's totient function）進行預處理的最佳化。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11417 / GCD | Gemini | 幫助整理 README.md | 獨立實作歐幾里得輾轉相除法與雙層枚舉邏輯 |