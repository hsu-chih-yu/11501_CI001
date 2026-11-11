# Code Review Report: [UVa] [10611] - [The Playboy Chimp]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10611
- **Problem Title:** The Playboy Chimp
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1552
- **Language / Version:** C++
- **Submission Result:** Accepted (original) → Improved
- **Source Code (Original/Accepted):** [src/uva10611_original.cpp](./src/uva10611_original.cpp)
- **Source Code (Final/Improved):** [src/uva10611.cpp](./src/uva10611.cpp)
- **Review Date:** 2026-10-21

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 第一行為母猩猩數量 $N$，接著 $N$ 個身高（題目保證非遞減排列）。之後給詢問數 $Q$，接著 $Q$ 個 Luchu 的身高。
- **預期的輸出是什麼？** 對每個詢問輸出兩個數：「嚴格比 Luchu 矮的最高者」與「嚴格比 Luchu 高的最矮者」，若不存在則輸出 `X`。
- **主要的規則與限制是什麼？** 必須是嚴格小於與嚴格大於，身高相等的不能選。
- **必須解決的核心任務是什麼？** 在已排序的數列中找出某值的嚴格前驅（predecessor）與嚴格後繼（successor）。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 先將身高排序（保險起見即使題目已排序也再排一次）。
- 原始版本對每個詢問從小到大線性掃描：所有小於 `h` 的值中最後一個即為最高的矮者；第一個大於 `h` 的值即為最矮的高者。
- 但 $N$ 最多 50000、$Q$ 最多 25000，最壞情況（例如每次詢問都比所有身高高）需要約 $1.25 \times 10^9$ 次比較，有超時風險。原始版本能 AC 是因為測資沒有觸發最壞情況。

### Final Strategy

- 陣列已排序，因此改用二分搜尋：
  - `lower_bound(h)`：第一個 `>= h` 的位置，它的**前一個**就是嚴格比 `h` 矮的最高者；若它就是開頭，代表不存在，輸出 `X`。
  - `upper_bound(h)`：第一個 `> h` 的位置，就是嚴格比 `h` 高的最矮者；若它是結尾，代表不存在，輸出 `X`。
- 等於 `h` 的值會落在 `[lower_bound, upper_bound)` 之間，自然被排除。
- 不再需要用 `-1` 當作「不存在」的標記。

### Complexity Analysis

- **Time Complexity:** $O(N \log N + Q \log N)$。排序 $O(N \log N)$，每個詢問兩次二分搜尋 $O(\log N)$。
- **Space Complexity:** $O(N)$，儲存所有身高。
- **解釋為何這些複雜度滿足問題限制：** $N = 50000$、$Q = 25000$ 時約 $10^6$ 次運算；實測最壞情況資料約 0.08 秒。

## 4. Pseudocode
```
START
READ m and heights into mt
SORT mt
READ n
WHILE n > 0:
    READ h
    lo = first position with mt[pos] >= h
    hi = first position with mt[pos] > h
    IF lo == begin THEN PRINT "X" ELSE PRINT mt[lo - 1]
    IF hi == end   THEN PRINT "X" ELSE PRINT mt[hi]
    n = n - 1
END
```
## 5. Original Code vs Improved Code

### Original Code (Accepted)
```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int m;
    cin >> m;
    vector<int> mt;
    for(int i = 0; i < m ;i++){
        int t;
        cin >> t;
        mt.push_back(t);
    }
    sort(mt.begin(), mt.end());
    
    int n;
    cin >> n;
    while(n--){
        int h;
        int ans = -1;
        cin >> h;
        int i;
        int ans2 = -1;
        for(i = 0; i < m; i++){
            if(mt[i] < h){
                ans = mt[i];
            }
            if(mt[i] > h){
                ans2 = mt[i];
                break;
            }
        }
        
        
        if(ans == -1){
            cout << "X ";
        }else{
            cout << ans << " ";
        }

        if(ans2 == -1){
            cout << "X\n";
        }else{
            cout << ans2 << endl;
        }
    }
    return 0;
}
```
**Potential problem:**
- **技術原因：** 每個詢問最壞需要掃描整個陣列，總時間 $O(Q \cdot N)$，最大約 $1.25 \times 10^9$ 次比較，有 TLE 風險。
- **暴露問題的測資：** $N = 50000$、$Q = 25000$，且每個詢問都大於大部分身高。

### Improved Code
```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int m;
    cin >> m;
    vector<int> mt(m);
    for(int i = 0; i < m; i++){
        cin >> mt[i];
    }
    sort(mt.begin(), mt.end());

    int n;
    cin >> n;
    while(n--){
        int h;
        cin >> h;

        // 第一個 >= h 的位置，它的前一個就是嚴格比 h 矮的最高者
        auto lo = lower_bound(mt.begin(), mt.end(), h);
        // 第一個 > h 的位置，就是嚴格比 h 高的最矮者
        auto hi = upper_bound(mt.begin(), mt.end(), h);

        if(lo == mt.begin()){
            cout << "X ";
        }else{
            cout << *(lo - 1) << " ";
        }

        if(hi == mt.end()){
            cout << "X\n";
        }else{
            cout << *hi << "\n";
        }
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 在排序後的陣列中，`lower_bound` 的前一個元素是嚴格前驅，`upper_bound` 指向的元素是嚴格後繼；相等的元素位於兩者之間而被排除，每次詢問只需 $O(\log N)$。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 題目範例 | 身高 `1 4 5 7`，詢問 `4` | `1 5` | `1 5` | 驗證相等身高被排除 |
| 一般情況 | 詢問 `6` | `5 7` | `5 7` | 驗證介於兩值之間 |
| 無較高者 | 詢問 `8` | `7 X` | `7 X` | 驗證後繼不存在時輸出 X |
| 無較矮者 | 詢問 `1` | `X 4` | `X 4` | 驗證前驅不存在時輸出 X |
| 大量資料 | $N = 50000$、$Q = 25000$ | 正確結果 | 約 0.08 秒完成 | 驗證二分搜尋的效能 |

## 7. Reflection

- **根本原因：** 題目考的是在有序數列中查找嚴格前驅與後繼；原始版本雖然正確，但沒有利用「已排序」的性質，時間複雜度偏高。
- **解決辦法：** 改用 `lower_bound` / `upper_bound` 二分搜尋。
- **改進：** 寫程式前先用資料範圍估算最壞情況的運算量（$Q \cdot N$ 超過 $10^8$ 就要小心）；看到「已排序 + 多次查詢」就要想到二分搜尋。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10611 / The Playboy Chimp | Claude | 幫助整理 README.md | 獨立驗證嚴格前驅與後繼的邊界情況 |
