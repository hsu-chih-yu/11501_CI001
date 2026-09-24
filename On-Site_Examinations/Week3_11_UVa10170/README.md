# Code Review Report: [UVa] [10170] - [The Hotel with Infinite Rooms]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10170
- **Problem Title:** The Hotel with Infinite Rooms
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1111
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva10170.cpp](./src/uva10170.cpp)
- **Review Date:** 2026-09-24

## 2. Problem Statement in My Own Words

- `S` 和 `D`。`S` 是第一組旅行團的人數，`D` 是我們想查詢的天數。輸入直到 EOF。
- 在第 `D` 天時，住在旅館裡的旅行團人數。
- `S` 人的旅行團會住 `S` 天，接著 `S+1` 人的旅行團會住 `S+1` 天，依此類推。數字 `D` 可能非常大（高達 $10^{15}$）。
- **必須解決的核心任務是什麼？** 找出一個最小的整數 `k`，使得 $S + (S+1) + (S+2) + \dots + k \ge D$。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 直覺是用迴圈從 `S` 開始慢慢把天數加起來，直到總天數超過或等於 `D` 為止。
- 唯一要注意的是變數型態，`D` 可以到 $10^{15}$，所以必須使用 `long long`。

### Final Strategy
- 宣告 `long long` 型態的 `s` 和 `d`。
- 設定一個累計天數的變數 `current_day = 0`。
- 使用 `while(current_day < d)` 迴圈，每次將 `current_day` 加上目前的 `s`，然後 `s` 遞增（代表下一組人數）。
- 當迴圈結束時，因為 `s` 已經多加了 1，所以輸出 `s - 1` 就是答案。

### Complexity Analysis
- **Time Complexity:** $O(\sqrt{D})$。因為 $1 + 2 + \dots + k \approx \frac{k^2}{2}$，所需迴圈次數約為 $\sqrt{D}$。這在時間限制內是可接受的。
- **Space Complexity:** $O(1)$。只使用了幾個變數。
- **解釋為何滿足限制：** 即使 $D = 10^{15}$，$\sqrt{D}$ 大約是 $3 \times 10^7$，在 C++ 中只需不到 0.1 秒即可跑完。

## 4. Pseudocode
```START
1. WHILE read s and d successfully:
2.     SET current_day = 0
3.     WHILE current_day < d:
4.         current_day = current_day + s
5.         s = s + 1
6.     PRINT s - 1
END
```
## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int main()
{
    long long s, d;
    while(cin >> s >> d){
        long long current_day = 0;
        while(current_day < d){
            current_day += s;
            s++;
        }
        cout << s - 1 << "\n";
    }
    return 0;
}
```

**Why it works：**
- **關鍵條件：** 使用 `long long` 避免大數溢位。利用迴圈不斷累加天數，當累積的天數大於或等於 `D` 時，當下的人數即為所求。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `1 6` | `3` | `3` | 測試基本累加 (1+2+3=6) |
| 一般情況 | `3 10` | `5` | `5` | 測試不從 1 開始的累加 (3+4+5=12 >= 10) |
| 極端情況 | `1 100000000000000` | 大數 | 正確計算 | 測試 `long long` 範圍與效能 |

## 7. Reflection
- **根本原因：** 大數累加如果使用 32-bit `int` 會造成無限迴圈或溢位。
- **學到的教訓：** 看到題目有 $10^{15}$ 的極限值，必須毫不猶豫地使用 64 位元的 `long long`。
- **下一步行動：** 若遇到更大的 $D$，可以考慮使用一元二次方程式的公式解 (二分搜或數學推導) 來將時間複雜度降到 $O(\log D)$ 或 $O(1)$。

## 8. AI Usage Disclaimer
- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10170 / The Hotel with Infinite Rooms | Gemini | 幫助整理 README.md | 獨立完成邏輯推導與複雜度分析 |

