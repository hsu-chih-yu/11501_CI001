# Code Review Report: [UVa] [11364] - [Parking]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11364
- **Problem Title:** Parking
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2349
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11364.cpp](./src/uva11364.cpp)
- **Review Date:** 2026-10-21

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 第一行為測資筆數 $t$。每筆測資先給商店數量 $n$ ($1 \le n \le 20$)，接著 $n$ 個整數代表商店在一直線街道上的位置 ($0 \le x \le 99$)。
- **預期的輸出是什麼？** 輸出把車停在最佳位置後，走訪所有商店並回到停車處的最短步行距離。
- **主要的規則與限制是什麼？** 所有商店位於同一條直線上，必須從停車處出發並回到停車處。
- **必須解決的核心任務是什麼？** 找出最小與最大位置，計算來回距離。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 不論車停在最左與最右商店之間的哪個位置，都必須走到最左端與最右端各一次再回來。
- 因此總距離固定是 $(\max - \min) \times 2$，停車位置不影響答案（只要停在區間內）。

### Final Strategy

- 讀入所有位置時同時維護 `maxi` 與 `mini`（`mini` 初始為 9999，`maxi` 初始為 0）。
- 輸出 `(maxi - mini) * 2`。

### Complexity Analysis

- **Time Complexity:** $O(n)$ 每筆測資，每個位置只比較一次。
- **Space Complexity:** $O(1)$，不需要儲存所有位置。
- **解釋為何這些複雜度滿足問題限制：** $n \le 20$，運算量極小。

## 4. Pseudocode
```
START
READ cases
WHILE cases > 0:
    READ n
    SET maxi = 0, mini = 9999
    FOR i = 1 TO n:
        READ k
        maxi = max(maxi, k)
        mini = min(mini, k)
    PRINT (maxi - mini) * 2
    cases = cases - 1
END
```
## 5. Correct Code
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    while(cases--){
        int n;
        cin >> n;
        int maxi = 0;
        int mini = 9999;
        int k;
        for(int i = 0; i < n; i++){
            cin >> k;
            maxi = max(maxi, k);
            mini = min(mini, k);
        }
        int ans = maxi - mini;
        ans *= 2;
        cout << ans << endl;
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 在一直線上走訪所有點並回到起點，最短路徑就是覆蓋 $[\min, \max]$ 區間兩次，因此答案為 $2(\max - \min)$。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 題目範例 | `24 13 89 37` | `152` | `152` | 驗證 $2 \times (89 - 13)$ |
| 題目範例 | `7 30 41 14 39 42` | `70` | `70` | 驗證 $2 \times (42 - 7)$ |
| 單一商店 | `n = 1` | `0` | `0` | 驗證最大最小相同時距離為 0 |

## 7. Reflection

- **根本原因：** 這是一題需要先觀察幾何性質的題目，一旦看出「答案只跟最遠兩端有關」就能直接計算。
- **解決辦法：** 讀入時同步維護最大值與最小值，不需要排序。
- **改進：** `mini` 初始值可以用 `INT_MAX` 或第一筆輸入取代魔術數字 9999，讓程式更通用。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11364 / Parking | Claude | 幫助整理 README.md | 獨立推導 $2(\max - \min)$ 的公式 |
