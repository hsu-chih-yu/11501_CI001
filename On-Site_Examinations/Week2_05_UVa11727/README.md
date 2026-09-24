# Code Review Report: [UVa] [11727] - [Cost Cutting]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11727
- **Problem Title:** Cost Cutting
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2827
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11727.cpp](./src/uva11727.cpp)
- **Review Date:** 2026-09-24

## 2. Problem Statement in My Own Words

- 測資筆數 `cases`，接著每一筆給定三個員工的薪水。
- 依照 `Case x: y` 的格式，輸出被留下的員工薪水 (亦即三者中的中位數)。
- 除最高薪資與最低薪資，留下中間值。
- 對三個數字進行排序以找出中位數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 可以使用一連串的 `if-else` 來判斷哪個數字位在中間，但這會讓邏輯過於冗長且容易出錯。

### Final Strategy
- 將三個數字讀入陣列 `a[3]` 中。
- 使用標準的氣泡排序 (Bubble Sort) 將陣列元素由小到大排序。利用兩層迴圈即可完成。
- 排序完成後，陣列中間的元素 `a[1]` 即為所求的中位數。

### Complexity Analysis
- **Time Complexity:** $O(1)$ 每筆測資。雖然使用雙層迴圈，但陣列大小僅為 3，運算次數極少。
- **Space Complexity:** $O(1)$。僅配置長度為 3 的陣列。
- **為何滿足限制：** $3 \times 3$ 的排序操作在硬體上幾乎不消耗任何時間，完全符合效能要求。

## 4. Pseudocode
```
START
1. READ cases
2. FOR n = 1 TO cases:
3.     READ array a[3]
4.     FOR j = 0 TO 2:
5.         FOR i = 0 TO 1:
6.             IF a[i] > a[i+1] THEN
7.                 Swap a[i] and a[i+1]
8.     PRINT "Case " + n + ": " + a[1]
END
```
## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    for(int n = 1; n <= cases; n++){
        int a[3];
        cin >> a[0] >> a[1] >> a[2];
        for(int j = 0; j < 3; j++){
            for(int i = 0; i < 2; i++){
                if(a[i] > a[i+1]){
                    int temp = a[i];
                    a[i] = a[i+1];
                    a[i+1] = temp;
                }
            }
        }
        printf("Case %d: %d\n", n, a[1]);
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 雙層迴圈確保相鄰的元素正確交換（大的往後排）。排序後直接取 `a[1]`，避開了繁瑣的條件比較分支。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `1000 2000 3000` | `2000` | `2000` | 測試已排序的輸入 |
| 一般情況 | `3000 1000 2000` | `2000` | `2000` | 測試未排序的輸入 |
| 極端情況 | `1500 1500 2000` | `1500` | `1500` | 測試包含重複值的輸入 |

## 7. Reflection
- **根本原因：** 三個數取中位數若不善用陣列與排序，會增加撰寫與維護難度。
- **學到的教訓：** 當遇到尋找極值或特定位階數字時，將資料放入陣列並執行輕量級排序是兼具可讀性與正確性的好策略。
- **下一步行動：** 若陣列較大，可以考慮直接調用 C++ 內建的 `std::sort` 讓程式碼更簡潔。

## 8. AI Usage Disclaimer
- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11727 / Cost Cutting | Gemini | 幫助整理 README.md | 獨立設計排序演算法與輸出格式 |
