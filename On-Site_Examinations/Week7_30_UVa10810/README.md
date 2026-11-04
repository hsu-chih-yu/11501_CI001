# Code Review Report: [UVa] [10810] - [Ultra-QuickSort]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10810
- **Problem Title:** Ultra-QuickSort
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1751
- **Language / Version:** C++
- **Submission Result:** Time Limit Exceeded / Need Revision
- **Source Code (Initial/Fail):** [src/uva10810_fail.cpp](./src/uva10810_fail.cpp)
- **Source Code (Final/Accepted):** [src/uva10810.cpp](./src/uva10810.cpp)
- **Review Date:** 2026-10-21

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 多筆測資，每筆第一行為 $n$ ($n < 500000$)，接著 $n$ 行各一個整數 ($0 \le a[i] \le 999999999$)。當 $n = 0$ 時結束。
- **預期的輸出是什麼？** 輸出把數列排成遞增所需的最少「相鄰交換」次數。
- **主要的規則與限制是什麼？** $n$ 最大接近 50 萬，答案最大約 $\frac{n(n-1)}{2} \approx 1.25 \times 10^{11}$，超過 `int` 範圍。
- **必須解決的核心任務是什麼？** 在 $O(n \log n)$ 時間內計算逆序對數量。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 與 UVa 299、UVa 10327 相同，答案就是逆序對數，所以直接沿用泡沫排序計數。
- 但泡沫排序是 $O(n^2)$，$n = 500000$ 時約需 $1.25 \times 10^{11}$ 次比較，必定超時（TLE）。

### Final Strategy

- 改用**合併排序（Merge Sort）**計算逆序數：
  - 遞迴將區間 `[l, r)` 分成左右兩半，分別排序並計算各自內部的逆序數。
  - 合併時，若右半的 `a[j]` 小於左半的 `a[i]`，代表左半從 `i` 到 `mid - 1` 的所有元素都比 `a[j]` 大，一次加上 `mid - i` 個逆序對。
- 計數器與回傳值使用 `long long` 避免溢位。
- 改用 `vector` 動態配置，避免在迴圈內宣告 `int a[500001]` 這種約 2MB 的大型區域陣列（有 stack overflow 風險）。
- 加上 `ios::sync_with_stdio(false)` 與 `cin.tie(nullptr)` 加速大量輸入。

### Complexity Analysis

- **Time Complexity:** $O(n \log n)$ 每筆測資。$n = 5 \times 10^5$ 時約 $10^7$ 次運算。
- **Space Complexity:** $O(n)$，需要原陣列與合併用的暫存陣列。
- **解釋為何這些複雜度滿足問題限制：** $O(n \log n)$ 在 50 萬筆資料下只需數十毫秒，遠低於時間限制；而 $O(n^2)$ 需要上千億次運算，必定 TLE。

## 4. Pseudocode
```
START
FUNCTION mergeCount(a, tmp, l, r):
    IF r - l <= 1 THEN RETURN 0
    mid = (l + r) / 2
    cnt = mergeCount(a, tmp, l, mid) + mergeCount(a, tmp, mid, r)
    i = l, j = mid, k = l
    WHILE i < mid AND j < r:
        IF a[i] <= a[j] THEN
            tmp[k++] = a[i++]
        ELSE
            cnt = cnt + (mid - i)
            tmp[k++] = a[j++]
    COPY remaining a[i..mid-1] and a[j..r-1] into tmp
    COPY tmp[l..r-1] back to a
    RETURN cnt

WHILE read n successfully AND n != 0:
    READ array a[0..n-1]
    PRINT mergeCount(a, tmp, 0, n)
END
```
## 5. Fail Code vs Correct Code

### Fail Code
```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    
    int n;
    while(cin >> n && n != 0){
        int a[500001];
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
        printf("%d\n", ans);
    }
    return 0;
}
```
**Why it failed:**
- **技術原因：**
  1. 泡沫排序為 $O(n^2)$，$n$ 接近 50 萬時需要約 $1.25 \times 10^{11}$ 次比較，造成 **Time Limit Exceeded**。
  2. 計數器 `int ans` 最大只能到約 $2.1 \times 10^9$，但答案可達 $1.25 \times 10^{11}$，即使不超時也會溢位而 Wrong Answer。
  3. 在迴圈內宣告 `int a[500001]`（約 2MB）的區域陣列，在部分環境下可能造成 stack overflow。
- **暴露問題的測資：** $n = 100000$ 的完全反序數列：錯誤程式執行超過 10 秒仍未結束；正確答案 `4999950000` 也超過 `int` 範圍。

### Correct Code
```cpp
#include <iostream>
#include <vector>

using namespace std;

long long mergeCount(vector<long long>& a, vector<long long>& tmp, int l, int r){
    if(r - l <= 1) return 0;
    int mid = (l + r) / 2;
    long long cnt = mergeCount(a, tmp, l, mid) + mergeCount(a, tmp, mid, r);

    int i = l, j = mid, k = l;
    while(i < mid && j < r){
        if(a[i] <= a[j]){
            tmp[k++] = a[i++];
        }else{
            cnt += mid - i;
            tmp[k++] = a[j++];
        }
    }
    while(i < mid) tmp[k++] = a[i++];
    while(j < r) tmp[k++] = a[j++];
    for(int t = l; t < r; t++) a[t] = tmp[t];
    return cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while(cin >> n && n != 0){
        vector<long long> a(n), tmp(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        cout << mergeCount(a, tmp, 0, n) << "\n";
    }
    return 0;
}
```
**Why it works:**
- **關鍵條件：** 合併時右半元素 `a[j]` 先於左半剩餘的 `mid - i` 個元素被放入，代表這些元素都與 `a[j]` 構成逆序對，一次即可全部計入，使總時間降為 $O(n \log n)$；使用 `long long` 確保大答案不溢位。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 題目範例 | `9 1 0 5 4` | `6` | `6` | 驗證逆序對計數正確 |
| 已排序 | `1 2 3` | `0` | `0` | 驗證無逆序的情況 |
| 大量資料 | $n = 100000$ 完全反序 | `4999950000` | `4999950000`（約 0.01 秒） | 驗證效能與 `long long` 不溢位 |

## 7. Reflection

- **根本原因：** 沿用小資料量題目（UVa 299、10327）的 $O(n^2)$ 泡沫排序，沒有先根據 $n$ 的上限估算時間複雜度與答案範圍。
- **解決辦法：** 改用合併排序在合併過程中計算逆序對，並以 `long long` 儲存答案。
- **改進：** 寫程式前先看資料範圍：$n \le 10^3$ 可用 $O(n^2)$，$n \ge 10^5$ 就必須使用 $O(n \log n)$ 的演算法；同時估算答案最大值，決定是否需要 `long long`。另一種作法是使用樹狀陣列（Fenwick Tree / BIT）配合離散化計算逆序數。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10810 / Ultra-QuickSort | Claude | 幫助分析 TLE 原因、說明合併排序求逆序數並整理 README.md | 獨立以大量反序測資驗證效能與 `long long` 結果 |
