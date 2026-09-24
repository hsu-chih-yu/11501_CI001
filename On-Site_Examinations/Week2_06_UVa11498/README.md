# Code Review Report: [UVa] [11498] - [Division of Nlogonia]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11498
- **Problem Title:** Division of Nlogonia
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2493
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11498.cpp](./src/uva11498.cpp)
- **Review Date:** 2026-09-24

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 查詢次數 `k`，接著是中心劃分點座標 `(a, b)`。接下來有 `k` 個查詢點座標 `(x, y)`。輸入直到 `k = 0` 結束。
- **預期的輸出是什麼？** 判斷點落在哪個方位，輸出 `NE`, `SE`, `SO`, `NO`，若落在劃分線上則輸出 `divisa`。
- **主要的規則與限制是什麼？** 這是一個單純的直角坐標系四象限判斷問題。
- **必須解決的核心任務是什麼？** 比較查詢座標 `(x, y)` 與中心點 `(a, b)` 的相對位置。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 判斷點在平面上的位置只需要對 X 軸和 Y 軸分別進行比較即可。
- 需要特別處理點與中心線重疊的情況。

### Final Strategy
- 在讀取 `k` 時設置迴圈，當 `k == 0` 時終止。
- 先判斷 `x == a` 或 `y == b` 處理邊界情況 (`divisa`)。
- 接著使用 `if-else if` 針對 `x > a` 或 `x < a` 與 `y > b` 或 `y < b` 的四種組合輸出對應的方位象限。

### Complexity Analysis
- **Time Complexity:** $O(K)$。每組測試資料有 $K$ 次查詢，每次查詢皆為 $O(1)$ 的條件判斷。
- **Space Complexity:** $O(1)$。只使用固定的幾個變數儲存座標。
- **解釋為何滿足限制：** 運算不包含任何迴圈巢狀結構或複雜計算。

## 4. Pseudocode
```
START
1. WHILE read k successfully AND k is not 0:
2.     READ center coordinates a, b
3.     WHILE k > 0:
4.         READ query coordinates x, y
5.         IF x == a OR y == b THEN PRINT "divisa"
6.         ELSE IF x > a AND y > b THEN PRINT "NE"
7.         ELSE IF x > a AND y < b THEN PRINT "SE"
8.         ELSE IF x < a AND y < b THEN PRINT "SO"
9.         ELSE PRINT "NO"
10.        k = k - 1
END
```
## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int main()
{
    int k;
    while(cin >> k && k != 0){
        int a, b;
        cin >> a >> b;
        while(k--){
            int x, y;
            cin >> x >> y;
            if(x == a || y == b){
                cout << "divisa" << endl;
            }else if(x > a && y > b){
                cout << "NE" << endl;
            }else if(x > a && y < b){
                cout << "SE" << endl;
            }else if(x < a && y < b){
                cout << "SO" << endl;
            }else{
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}
```
**Why it works：**
- **關鍵條件：** 第一時間把落於軸線上（`divisa`）的情況過濾掉，後續的四個 `else if` 就能乾淨俐落地對應四個象限，不需擔心等於的問題。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | 中心 (0,0)，點 (1,1) | `NE` | `NE` | 測試第一象限 |
| 一般情況 | 中心 (0,0)，點 (-1,-1) | `SO` | `SO` | 測試第三象限 |
| 邊界情況 | 中心 (2,2)，點 (2,5) | `divisa` | `divisa` | 測試落在垂直分隔線上 |

## 7. Reflection
- **根本原因：** 只要清楚直角座標系的概念，這是純邏輯分支的問題。
- **學到的教訓：** 處理多重條件判斷時，先過濾特殊或邊界條件（本題中的 `divisa`），可以讓剩下的邏輯更簡潔。
- **下一步行動：** 維持在迴圈讀取中利用 `while (cin >> k && k != 0)` 這種乾淨的輸入處理方式。

## 8. AI Usage Disclaimer
- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11498 / Division of Nlogonia | Gemini | 幫助整理 README.md | 獨立設計象限分流邏輯 |