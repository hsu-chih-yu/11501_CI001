# Code Review Report: [UVa] [10300] - [Ecological Premium]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10300
- **Problem Title:** Ecological Premium
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1241
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva10300.cpp](./src/uva10300.cpp)
- **Review Date:** 2026-09-24

## 2. Problem Statement in My Own Words

- 第一行是測資筆數 `n`。每筆測資包含農夫數量 `f`，接著 `f` 行，每行有三個整數：農場面積、動物數量、環保等級。
- 輸出每筆測資中所有農夫獲得的「生態獎金總和」，並換行。
- 每位農夫的獎金計算公式為：`(農場面積 / 動物數量) * 環保等級 * 動物數量`。
- 準確計算每位農夫的獎金並加總，同時避免整數除法造成的小數誤差。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 一開始的想法是照著公式直接寫：`sum += (size / animals) * friendliness * animals`。
- 但立刻發現兩個問題：第一，C++ 的整數除法 `size / animals` 會直接無條件捨去小數部分，導致後續乘法結果完全錯誤。第二，如果 `animals` 為 0，會發生除以零的錯誤。

### Final Strategy

- 將計算公式在紙上進行代數化簡：`(size / animals) * friendliness * animals = size * friendliness`。
- 我們發現「動物數量」這個變數在數學上被完全消去了！因此讀取三個變數後，只需要把「農場面積」與「環保等級」相乘即可。
- 將所有農夫的 `size * friendliness` 累加起來。為防止總和過大，累加變數使用 `long long` 型態。

### Complexity Analysis

- **Time Complexity:** $O(N \times F)$。其中 $N$ 為測資筆數，$F$ 為農夫數量。每一位農夫的資料只需要常數時間的乘法與加法。
- **Space Complexity:** $O(1)$。只使用了幾個常數變數來儲存輸入和總和。
- **解釋為何這些複雜度滿足問題限制：** 運算步驟僅包含基本的乘法與加法，完全沒有使用額外的資料結構或複雜迴圈，時間與空間都非常精簡。

## 4. Pseudocode
```
START
1. READ number of test cases 'n'
2. WHILE n > 0:
3.     READ number of farmers 'f'
4.     SET total_premium = 0
5.     WHILE f > 0:
6.         READ size, animals, friendliness
7.         total_premium = total_premium + (size * friendliness)
8.         f = f - 1
9.     PRINT total_premium
10.    n = n - 1
END
```
## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        while (n--) {
            int f;
            cin >> f;
            long long total_premium = 0;
            while (f--) {
                long long size, animals, friendliness;
                cin >> size >> animals >> friendliness;
                total_premium += size * friendliness;
            }
            cout << total_premium << "\n";
        }
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 透過數學代數化簡為 `size * friendliness`，徹底解決了整數除法帶來的精確度流失問題，也完全避開了除以 0 的潛在風險。使用 `long long` 避免總和溢位。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `1`<br>`3`<br>`10 20 5`<br>`...` | `50` | `50` | 測試多位農夫的總和計算 |
| 邊界情況 | 包含動物數量為 0 的測資 | 照常運算不報錯 | 正常輸出 | 測試化簡後的公式是否成功避開除以零錯誤 |
| 大數情況 | 面積與環保等級極大 | 正確的大數值 | 正確的大數值 | 測試 `long long` 是否防止了整數溢位 |

## 7. Reflection

- **根本原因：** 若死板地將題目文字直接轉譯為程式碼，會因為整數除法的特性而得到錯誤答案。
- **解決辦法：** 先從數學層面化簡公式，消去不必要的變數，讓運算變得更安全、更快速。
- **改進：** 遇到包含乘除法的複雜公式時，先在紙上約分、化簡，確定最終型態後再撰寫程式碼。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10300 / Ecological Premium | Gemini | 幫助整理 README.md | 自行推導公式約分並確認整數溢位風險 |
