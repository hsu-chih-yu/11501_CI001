# Code Review Report: [UVa] [10474] - [Where is the Marble?]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10474
- **Problem Title:** Where is the Marble?
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1415
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva10474.cpp](./src/uva10474.cpp)
- **Review Date:** 2026-10-21

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 每筆測資第一行為 $N$（彈珠數）與 $Q$（詢問數），接著 $N$ 個彈珠上的數字，再接 $Q$ 個詢問數字。當 $N = 0$ 且 $Q = 0$ 時結束。
- **預期的輸出是什麼？** 先輸出 `CASE# X:`，接著對每個詢問輸出 `x found at p`（$p$ 為排序後第一次出現的位置，從 1 開始）或 `x not found`。
- **主要的規則與限制是什麼？** 彈珠數字可能重複，必須回報「排序後第一次出現」的位置。
- **必須解決的核心任務是什麼？** 將彈珠排序，並在排序後的陣列中找出每個詢問值第一次出現的索引。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 先用 `sort` 將彈珠由小到大排列。
- 對每個詢問，從頭線性掃描，遇到第一個相等的值就輸出位置並停止，自然就會得到「第一次出現」的位置。

### Final Strategy

- 讀入 $N$ 個數字存到 `vector<int> a` 後排序。
- 每個詢問 `t` 用迴圈從 `j = 0` 開始尋找，找到即輸出 `j + 1` 並 `break`；若掃完都沒找到則輸出 `not found`。

### Complexity Analysis

- **Time Complexity:** $O(N \log N + Q \cdot N)$ 每筆測資。排序為 $O(N \log N)$，每個詢問最壞需線性掃描 $O(N)$。
- **Space Complexity:** $O(N)$，儲存所有彈珠。
- **解釋為何這些複雜度滿足問題限制：** 本題 UVa 測資的 $N$、$Q$ 規模不大，線性搜尋即可在時限內通過。

## 4. Pseudocode
```
START
SET caseNo = 1
WHILE read n, m AND n != 0 AND m != 0:
    READ n numbers into array a
    SORT a
    PRINT "CASE# " + caseNo + ":"
    FOR each of m queries t:
        SET found = false
        FOR j = 0 TO n - 1:
            IF a[j] == t THEN
                PRINT t + " found at " + (j + 1)
                found = true
                BREAK
        IF NOT found THEN PRINT t + " not found"
    caseNo = caseNo + 1
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
    int n, m;
    int c = 1;
    while(cin >> n >> m && n != 0 && m != 0){
        vector<int> a;
        vector<int> b;
        
        for(int i = 0; i < n; i++){
            int t;
            cin >> t;
            a.push_back(t);
        }
        sort(a.begin(), a.end());
        cout << "CASE# " << c << ":" << endl;
        for(int i = 0; i < m; i++){
            bool f = false;
            int t;
            cin >> t;
            for(int j = 0; j < n; j++){
                if(a[j] == t){
                    cout << t << " found at " << j+1 << endl;
                    
                    f = true;
                    break;
                }
            }
            if(!f){
                cout << t << " not found\n";
            }
        }


        c++;
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 陣列已排序，從前往後掃描遇到的第一個相等元素就是最小索引，因此重複值也能正確回報第一次出現的位置。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 題目範例 1 | 彈珠 `2 3 5 1`，詢問 `5` | `5 found at 4` | `5 found at 4` | 驗證排序後位置 |
| 找不到 | 彈珠 `1 3 3 3 1`，詢問 `2` | `2 not found` | `2 not found` | 驗證查無資料的輸出 |
| 重複值 | 彈珠 `1 3 3 3 1`，詢問 `3` | `3 found at 3` | `3 found at 3` | 驗證回報第一次出現的位置 |

## 7. Reflection

- **根本原因：** 題目核心是「排序 + 搜尋」，需要注意重複值要回報第一個位置。
- **解決辦法：** 排序後線性搜尋，找到第一個即停止。
- **改進：** 若資料量變大，可改用 `lower_bound(a.begin(), a.end(), t)` 進行二分搜尋，將每次詢問降到 $O(\log N)$，且 `lower_bound` 本身就會回傳第一個不小於 `t` 的位置；另外宣告了但未使用的 `vector<int> b` 可以移除。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10474 / Where is the Marble? | Claude | 幫助整理 README.md | 獨立確認排序後線性搜尋與重複值處理 |
