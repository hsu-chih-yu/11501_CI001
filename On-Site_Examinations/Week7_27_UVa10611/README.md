# Code Review Report: [UVa] [10611] - [The Playboy Chimp]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10611
- **Problem Title:** The Playboy Chimp
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1552
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva10611.cpp](./src/uva10611.cpp)
- **Review Date:** 2026-10-21

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 第一行為母猩猩數量 $N$，接著 $N$ 個身高（題目保證非遞減排列）。之後給詢問數 $Q$，接著 $Q$ 個 Luchu 的身高。
- **預期的輸出是什麼？** 對每個詢問輸出兩個數：「嚴格比 Luchu 矮的最高者」與「嚴格比 Luchu 高的最矮者」，若不存在則輸出 `X`。
- **主要的規則與限制是什麼？** 必須是嚴格小於與嚴格大於，身高相等的不能選。
- **必須解決的核心任務是什麼？** 在已排序的數列中找出某值的嚴格前驅（predecessor）與嚴格後繼（successor）。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 先將身高排序（保險起見即使題目已排序也再排一次）。
- 從小到大掃描：所有小於 `h` 的值中最後一個即為最高的矮者；第一個大於 `h` 的值即為最矮的高者。

### Final Strategy

- 每個詢問以 `ans = -1`、`ans2 = -1` 初始化。
- 線性掃描 `mt[i]`：若 `mt[i] < h` 就更新 `ans`；若 `mt[i] > h` 就記錄 `ans2` 並立即 `break`。
- 等於 `h` 的值兩個條件都不成立，自然被跳過。
- 若值仍為 -1 則輸出 `X`。

### Complexity Analysis

- **Time Complexity:** $O(N \log N + Q \cdot N)$。排序 $O(N \log N)$，每個詢問最壞線性掃描。
- **Space Complexity:** $O(N)$，儲存所有身高。
- **解釋為何這些複雜度滿足問題限制：** 線性掃描在找到第一個較高者時就會停止，在本題測資下可於時限內通過。

## 4. Pseudocode
```
START
READ m and heights into mt
SORT mt
READ n
WHILE n > 0:
    READ h
    SET lower = -1, upper = -1
    FOR i = 0 TO m - 1:
        IF mt[i] < h THEN lower = mt[i]
        IF mt[i] > h THEN
            upper = mt[i]
            BREAK
    PRINT (lower == -1 ? "X" : lower) + " " + (upper == -1 ? "X" : upper)
    n = n - 1
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
**Why it works：**
- **關鍵條件：** 陣列排序後，最後一個 `< h` 的元素就是嚴格前驅，第一個 `> h` 的元素就是嚴格後繼；相等的元素被兩個嚴格不等式排除。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 題目範例 | 身高 `1 4 5 7`，詢問 `4` | `1 5` | `1 5` | 驗證相等身高被排除 |
| 一般情況 | 詢問 `6` | `5 7` | `5 7` | 驗證介於兩值之間 |
| 無較高者 | 詢問 `8` | `7 X` | `7 X` | 驗證後繼不存在時輸出 X |
| 無較矮者 | 詢問 `1` | `X 4` | `X 4` | 驗證前驅不存在時輸出 X |

## 7. Reflection

- **根本原因：** 題目考的是在有序數列中查找嚴格前驅與後繼。
- **解決辦法：** 排序後線性掃描並利用嚴格不等式排除相等值。
- **改進：** $N$ 最多 50000、$Q$ 最多 25000，最壞情況線性掃描約 $1.25 \times 10^9$ 次比較，有超時風險；應改用 `lower_bound`（第一個 `>= h` 的前一個即前驅）與 `upper_bound`（第一個 `> h` 即後繼）讓每次詢問降為 $O(\log N)$。另外使用 -1 作為「不存在」的標記，要確認身高不會是 -1（本題身高為正整數，因此安全）。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10611 / The Playboy Chimp | Claude | 幫助整理 README.md | 獨立驗證嚴格前驅與後繼的邊界情況 |
