# Code Review Report: [UVa] [579] - [Clock Hands]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 579
- **Problem Title:** Clock Hands
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=520
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva579.cpp](./src/uva579.cpp)
- **Review Date:** 2026-09-30

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 每行包含一個時鐘時間格式 `H:M`，代表時針與分針的當前位置。當讀取到 `0:00` 時終止輸入。
- **預期的輸出是什麼？** 輸出時針與分針夾角的最小角度（度數），格式固定保留至小數點後三位 (`%.3f`) 並換行。
- **主要的規則與限制是什麼？** 兩指針之間的夾角介於 0 到 180 度之間。分針走動時，時針會同步等比例移動（每分鐘時針移動 0.5 度）。
- **必須解決的核心任務是什麼？** 計算時針與分針各自相對於 12 點鐘方向的角度，求出差值後取兩者間的小於等於 180 度夾角。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 時針一整圈 360 度共有 12 小時，每小時為 30 度；且每走 1 分鐘，時針會額外移動 $30^\circ / 60 = 0.5^\circ$。
- 分針一整圈 360 度共有 60 分鐘，每分鐘走 $360^\circ / 60 = 6^\circ$。
- 求出兩針各自的角度後相減，若角度差為負數需補正為正角度，最後再取小於等於 180 度的最小夾角。

### Final Strategy

- 使用 `scanf("%d:%d", &a, &b)` 讀取輸入，直接過濾掉冒號分隔符。
- 計算時針角度：`da = 30 * a + 0.5 * b`。若達到 360 度則歸零（`da = 0`）。
- 計算分針角度：`db = 6 * b`。
- 計算角度差：`ans = da - db`。若 `ans < 0` 則 `ans += 360` 轉為正角度。
- 若 `ans >= 180`，代表大於半圓，最小夾角為其補角 `ans = 360 - ans`。
- 以 `printf("%.3f\n", ans)` 輸出結果。

### Complexity Analysis

- **Time Complexity:** $O(1)$ 每筆測資。只進行常數次的算術運算。
- **Space Complexity:** $O(1)$。僅使用少數浮點數變數儲存角度。
- **解釋為何這些複雜度滿足問題限制：** 運算不包含任何迴圈或遞迴，執行時間極短，能輕鬆應付大量測資。

## 4. Pseudocode
```
START
1. WHILE read a and b in format "H:M" successfully:
2.     IF a == 0 AND b == 0 THEN BREAK
3.     SET da = 30 * a + 0.5 * b
4.     IF da == 360 THEN da = 0
5.     SET db = 6 * b
6.     SET ans = da - db
7.     IF ans < 0 THEN ans = ans + 360
8.     IF ans >= 180 THEN ans = 360 - ans
9.     PRINT ans formatted to 3 decimal places
END
```
## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int main()
{
    int a, b;
    while(scanf("%d:%d", &a, &b)){
        if(a == 0 && b == 0)break;
        float da = 30 * a + 0.5 * b;
        if(da == 360){
            da = 0;
        }
        float db = 6 * b;
        float ans = da - db;
        if(ans < 0){
            ans += 360;
        }
        if(ans >= 180){
            ans = 360 - ans;
        }

        printf("%.3f\n", ans);
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 精確模擬了時針隨分鐘推進的位移量（`0.5 * b`）；並利用圓周性質（加上 360 度或取 360 度互補角），確保計算出來的夾角落在 $[0^\circ, 180^\circ]$ 的最小夾角範圍內。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `12:00` | `0.000` | `0.000` | 測試兩針完全重合 |
| 邊界互補 | `9:00` | `90.000` | `90.000` | 測試超過 180 度時正確轉成最小補角 |
| 包含分鐘位移 | `3:30` | `75.000` | `75.000` | 測試時針受分鐘影響的前進角度 (90+15-180 = -75 -> 75) |

## 7. Reflection

- **根本原因：** 時鐘指針計算若忘記時針會隨分鐘移動，算出來的角度就會有偏差。
- **解決辦法：** 將時針拆為「小時基準角」加上「分鐘微調角」（$30H + 0.5M$），分針為 $6M$。
- **改進：** 遇到具有循環對稱性的角度問題，統一先轉換至同一基準點（如 12 點鐘方向），相減後再做大於 180 度的補角調整。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 579 / Clock Hands | Gemini | 幫助整理 README.md | 獨立推導時針與分針幾何夾角公式 |