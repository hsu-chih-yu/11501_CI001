# Code Review Report: [UVa] [11455] - [Behold my quadrangle]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11455
- **Problem Title:** Behold my quadrangle
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2450
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11455.cpp](./src/uva11455.cpp)
- **Review Date:** 2026-09-24

## 2. Problem Statement in My Own Words

- *測資筆數，每筆給定四個整數代表四個邊長 `a, b, c, d`。
- 判斷這四邊能組成哪種圖形，輸出 `square`、`rectangle`、`quadrangle`或 `banana`。
- 四邊形的構成條件為「任意三邊和大於第四邊」。
- 有效過濾出正方形、矩形，並找出最大邊來驗證四邊形構成條件。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- 正方形和矩形可以直接透過比較四個邊是否相等或兩兩相等來判斷。
- 判斷是否為普通四邊形，需要先排序，把最大的邊獨立出來，檢查剩餘三邊總和是否大於它。

### Final Strategy
- 利用 `if` 先行攔截 `a == b && b == c && c == d` (正方形)，以及兩兩相等的組合 (矩形)。
- 將四個邊存入陣列 `len` 中，透過一次迴圈將最大的邊推至陣列尾端 `len[3]`。
- 檢查前三個較小邊的總和是否大於 `len[3]`。若大於，輸出 `quadrangle`，否則為 `banana`。

### Complexity Analysis
- **Time Complexity:** $O(1)$ 每筆測資。只進行常數次的比較與交換。
- **Space Complexity:** $O(1)$。使用常數大小的陣列 `len[4]`。
- **為何滿足限制：** 無論測資多大，常數級別的運算皆能輕鬆應付。

## 4. Pseudocode
```
START
1. READ cases
2. WHILE cases > 0:
3.     READ a, b, c, d
4.     IF all sides equal THEN PRINT "square"
5.     ELSE IF sides form two equal pairs THEN PRINT "rectangle"
6.     ELSE:
7.         Put a, b, c, d in array len
8.         Push max value to len[3] by comparing adjacent elements
9.         IF len[0] + len[1] + len[2] > len[3] THEN PRINT "quadrangle"
10.        ELSE PRINT "banana"
11.    cases = cases - 1
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
    while(cases--){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if(a == b && b == c && c == d){
            cout << "square" << endl;
            continue;
        }else if((a == b && c == d)||(a == c && b == d) || (a == d && b == c)){
            cout << "rectangle" << endl;
            continue;
        }
        int len[4]={a, b, c, d};
        for(int i = 0; i < 3; i++){
            if(len[i] > len[i+1]){
                int temp = len[i];
                    len[i] = len[i+1];
                    len[i+1] = temp;
            }
        }
        int sum = len[0]+len[1]+len[2];
        if(sum > len[3]){
            cout << "quadrangle" << endl;

        }else{
            cout << "banana" << endl;
        }
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 精確運用了多邊形的基本幾何性質。透過找出最大邊來測試 `sum > max_edge`，避免了寫出冗長的四次比較邏輯，確保了正確分類圖形。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `10 10 10 10` | `square` | `square` | 測試正方形 |
| 一般情況 | `10 20 10 20` | `rectangle` | `rectangle` | 測試矩形 |
| 邊界情況 | `1 2 3 5` | `quadrangle` | `quadrangle` | 測試普通四邊形 (和剛好大於最大邊) |
| 極端情況 | `1 1 1 10` | `banana` | `banana` | 測試無法構成四邊形的情況 |

## 7. Reflection
- **根本原因：** 四邊形條件判斷若不找出最大值，會因為需要窮舉各種組合而使程式碼雜亂。
- **學到的教訓：** 用一次走訪把最大值推到陣列最末端（類似氣泡排序的一回合）是非常取巧且有效率的寫法。
- **下一步行動：** 若數字範圍極大，記得計算 `sum` 時可考慮使用 `long long` 防範整數溢位。

## 8. AI Usage Disclaimer
- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11455 / Behold my quadrangle | Gemini | 幫助整理 README.md | 獨立完成幾何判斷與極值搜尋邏輯 |
