# Code Review Report: [UVa] [299] - [Train Swapping]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 299
- **Problem Title:** Train Swapping
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=235
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva299.cpp](./src/uva299.cpp)
- **Review Date:** 2026-10-21

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 第一行為測資筆數。每筆測資先給車廂數 $L$ ($0 \le L \le 50$)，接著 $L$ 個整數代表目前車廂的排列順序。
- **預期的輸出是什麼？** 輸出 `Optimal train swapping takes S swaps.`，$S$ 為把車廂排成遞增順序所需的最少相鄰交換次數。
- **主要的規則與限制是什麼？** 每次只能交換「相鄰」的兩節車廂。
- **必須解決的核心任務是什麼？** 計算排序所需的最少相鄰交換次數（即逆序數對的數量）。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 只允許交換相鄰元素，這正是泡沫排序（Bubble Sort）的操作方式。
- 泡沫排序每次交換恰好消除一個逆序對，因此其交換次數就是最少交換次數。

### Final Strategy

- 實作泡沫排序：外層 `i` 跑 $L$ 次，內層比較 `a[j]` 與 `a[j+1]`，若前者較大就交換並將 `ans` 加一。
- 排序完成後輸出 `ans`。

### Complexity Analysis

- **Time Complexity:** $O(L^2)$ 每筆測資。$L \le 50$ 時最多約 1225 次比較。
- **Space Complexity:** $O(L)$，陣列大小 51。
- **解釋為何這些複雜度滿足問題限制：** 車廂數最多 50，平方級演算法完全足夠。

## 4. Pseudocode
```
START
READ c
WHILE c > 0:
    READ n and array a[0..n-1]
    SET ans = 0
    FOR i = 0 TO n - 1:
        FOR j = 0 TO n - i - 2:
            IF a[j] > a[j + 1] THEN
                SWAP a[j], a[j + 1]
                ans = ans + 1
    PRINT "Optimal train swapping takes " + ans + " swaps."
    c = c - 1
END
```
## 5. Correct Code
```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int c;
    cin >> c;
    while(c--){
        int n;
        cin >> n;
        int a[51];
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n - i - 1; j++){
                if(a[j] > a[j+1]){
                    ans++;
                    int temp = a[j];
                    a[j] = a[j+1];
                    a[j + 1] = temp;
                }
            }
        }
        printf("Optimal train swapping takes %d swaps.\n", ans);
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 每次相鄰交換最多只能減少一個逆序對，而泡沫排序的每次交換恰好減少一個，因此泡沫排序的交換次數 = 逆序對數 = 最少相鄰交換次數。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 題目範例 | `1 3 2` | `1 swaps` | `1 swaps` | 驗證單一逆序對 |
| 完全反序 | `4 3 2 1` | `6 swaps` | `6 swaps` | 驗證最壞情況 $\frac{L(L-1)}{2}$ |
| 題目範例 | `2 1` | `1 swaps` | `1 swaps` | 驗證最小交換情況 |

## 7. Reflection

- **根本原因：** 「只能交換相鄰元素的最少次數」等價於計算逆序對數量。
- **解決辦法：** 直接以泡沫排序模擬並計數。
- **改進：** 輸出格式固定為 `swaps.`（即使只有 1 次也不改成單數），要嚴格照題目輸出；若 $L$ 很大，需要改用合併排序計算逆序數（見 UVa 10810）。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 299 / Train Swapping | Claude | 幫助整理 README.md | 獨立確認泡沫排序交換次數等於逆序數 |
