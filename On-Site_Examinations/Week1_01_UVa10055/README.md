# Code Review Report: [UVa] [10055] - [Hashmat the Brave Warrior]


## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10055
- **Problem Title:** Hashmat the Brave Warrior
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=996
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva10055.cpp](./src/uva10055.cpp)
- **Review Date:** 2026-09-23

## 2. Problem Statement in My Own Words

- 多筆包含兩個整數的測資，直到 EOF。
- 每一對數字的絕對差值，並換行。
- 數字最大可能到 $2^{32}$，且兩數的輸入順序不固定。
- 在不發生整數溢位的情況下，計算兩數的絕對差。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 用 `int` 宣告變數，直接相減。
- 數字會大於 $2^{31}-1$，且直接相減可能會有負數。
- 使用 `int` 會造成整數溢位，且答案不符合絕對值的要求。

### Final Strategy

- 將變數型態改為 `long long`，並使用 `abs()` 函數計算絕對值。
- `long long` 可以儲存到 $2^{63}-1$，不會溢位；`abs()` 則能確保差值恆為正數。
- 兩數相等、第一數大於第二數、數字達到 $2^{32}$ 的極端情況。

### Complexity Analysis

- **Time Complexity:** $O(1)$。單純進行減法與絕對值運算。
- **Space Complexity:** $O(1)$。只使用了兩個變數存放輸入。
- **解釋為何這些複雜度滿足問題限制：** 運算成本極低，能輕鬆通過時間限制。

## 4. Pseudocode
```
START
1. WHILE read a and b successfully (until EOF):
2.     PRINT abs(a - b)
3. END WHILE
END
```
## 5. Correct Code
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    long long a, b;
    while (cin >> a >> b) {
        cout << abs(a - b) << "\n";
    }
    return 0;
}
```

**Why it works：**
- **關鍵條件：** 使用 64 位元的 `long long` 避免數值溢位，`abs()` 保證輸出為非負數。解決了記憶體與運算元順序的問題。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `10 12` | `2` | `2` | 測試正常相減 |
| 順序反轉 | `14 10` | `4` | `4` | 測試 `abs()` 處理負數 |
| 極端情況 | `4294967296 0` | `4294967296` | `4294967296` | 測試 `long long` 是否正常運作不溢位 |

## 7. Reflection

- **根本原因：** 忽略了題目所給的最大數值範圍限制。
- **解決辦法：** 看到超過 $2 \times 10^9$ 的數字，就要立刻想到使用 `long long`。
- **改進：** 寫程式前先確認測資的邊界與最大值。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10055 / Hashmat the Brave Warrior | Gemini | 幫助整理README.md| 自行驗證資料型態限制 |
