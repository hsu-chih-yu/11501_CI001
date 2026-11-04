# Code Review Report: [UVa] [10327] - [Flip Sort]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10327
- **Problem Title:** Flip Sort
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1268
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva10327.cpp](./src/uva10327.cpp)
- **Review Date:** 2026-10-21

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 多筆測資直到 EOF。每筆先給 $N$ ($N \le 1000$)，接著 $N$ 個整數。
- **預期的輸出是什麼？** 輸出 `Minimum exchange operations : X`，$X$ 為使用 Flip（交換相鄰兩元素）將數列排成遞增所需的最少次數。
- **主要的規則與限制是什麼？** 每次操作只能交換相鄰的兩個元素；輸入以 EOF 結束，沒有終止數字。
- **必須解決的核心任務是什麼？** 計算數列中的逆序對數量。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 這題與 UVa 299 Train Swapping 完全相同的概念：只能交換相鄰元素的最少次數 = 逆序對數。
- 差別在於本題以 EOF 結束，且 $N$ 上限變為 1000。

### Final Strategy

- 使用 `while (cin >> n)` 讀到 EOF 為止。
- 以泡沫排序模擬，每次交換將 `ans` 加一。
- 依指定格式輸出（注意冒號前後都有空白）。

### Complexity Analysis

- **Time Complexity:** $O(N^2)$ 每筆測資。$N = 1000$ 時約 $5 \times 10^5$ 次比較。
- **Space Complexity:** $O(N)$，陣列大小 1002。
- **解釋為何這些複雜度滿足問題限制：** 平方級演算法在 $N \le 1000$ 時仍非常快速。

## 4. Pseudocode
```
START
WHILE read n successfully:
    READ array a[0..n-1]
    SET ans = 0
    FOR i = 0 TO n - 1:
        FOR j = 0 TO n - i - 2:
            IF a[j] > a[j + 1] THEN
                SWAP a[j], a[j + 1]
                ans = ans + 1
    PRINT "Minimum exchange operations : " + ans
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
    
    int n;
    while(cin >> n){
        int a[1002];
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
        printf("Minimum exchange operations : %d\n", ans);
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 泡沫排序的每次相鄰交換恰好消除一個逆序對，因此交換總數即為最少操作次數；$N \le 1000$ 時逆序數最多約 $5 \times 10^5$，`int` 足以儲存。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 已排序 | `1 2 3` | `Minimum exchange operations : 0` | `Minimum exchange operations : 0` | 驗證不需交換的情況 |
| 一般情況 | `2 3 1` | `Minimum exchange operations : 2` | `Minimum exchange operations : 2` | 驗證逆序對計數 |

## 7. Reflection

- **根本原因：** 與 UVa 299 同樣是逆序對問題，只是輸入格式與資料量不同。
- **解決辦法：** 沿用泡沫排序計數，並改用 EOF 判斷結束。
- **改進：** 留意輸出字串 `operations : ` 冒號前的空白，格式錯一個字元就會 WA；資料量再大時（如 UVa 10810）需要改成 $O(N \log N)$ 的合併排序。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10327 / Flip Sort | Claude | 幫助整理 README.md | 獨立確認 EOF 讀取與泡沫排序計數 |
