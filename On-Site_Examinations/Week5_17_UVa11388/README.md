# Code Review Report: [UVa] [11388] - [GCD LCM]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11388
- **Problem Title:** GCD LCM
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2383
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11388.cpp](./src/uva11388.cpp)
- **Review Date:** 2026-10-07

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 第一行為測資筆數 `cases`，接著每行包含兩個正整數 `G` 與 `L`，分別代表給定的最大公因數 (GCD) 與最小公倍數 (LCM)。
- **預期的輸出是什麼？** 尋找兩個正整數 $a$ 和 $b$，滿足 $\gcd(a, b) = G$ 且 $\text{lcm}(a, b) = L$。若存在多組解，輸出使 $a$ 最小的一組；若無解則輸出 `-1`。
- **主要的規則與限制是什麼？** 輸出的數對需滿足 $a \le b$ 且 $a$ 盡可能小。
- **必須解決的核心任務是什麼？** 判斷是否存在符合條件的整數對，並利用數論性質直接找出最佳解。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 看到 GCD 與 LCM，可能會想嘗試列舉所有因數或用迴圈尋找數對。
- 但從數論基本性質來看：任何兩數的 $\gcd(a, b)$ 必然是其 $\text{lcm}(a, b)$ 的因數。
- 如果 $L$ 不能被 $G$ 整除（即 `L % G != 0`），代表在數學上根本不可能存在這樣的數對，直接輸出 `-1`。

### Final Strategy

- 若 $L$ 能被 $G$ 整除（`b % a == 0`）：
  - 我們直接取 $a = G$ 以及 $b = L$。
  - 驗證：$\gcd(G, L) = G$（因為 $G$ 整除 $L$），且 $\text{lcm}(G, L) = L$。
  - 因為任何符合條件的數都必須是 $G$ 的倍數，所以最小的正整數可能值就是 $G$ 本身，這組解自然保證了 $a$ 是所有可能解中最小的。
- 檢查 `b % a == 0`：若成立輸出 `a b`，否則輸出 `-1`。

### Complexity Analysis

- **Time Complexity:** $O(1)$ 每筆測資。只進行一次模除運算與條件判斷。
- **Space Complexity:** $O(1)$。僅使用儲存輸入的變數。
- **解釋為何這些複雜度滿足問題限制：** 運算次數極少，無任何迴圈窮舉，能瞬間處理所有測資。

## 4. Pseudocode
```markdown
START
1. READ cases
2. WHILE cases > 0:
3.     READ a, b
4.     IF b % a == 0 THEN
5.         PRINT a, b
6.     ELSE
7.         PRINT -1
8.     cases = cases - 1
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
        int a, b;
        cin >> a >> b;
        if(b % a == 0){
            cout << a << " " << b << endl;
        }else{
            cout << "-1\n";
        }
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 數論性質保證了 $\gcd(a, b)$ 必定能整除 $\text{lcm}(a, b)$。當 $b \pmod a == 0$ 時，數對 $(a, b)$ 本身就直接滿足最大公因數為 $a$、最小公倍數為 $b$，且 $a$ 是可能範圍內的最小值。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般整除情況 | `12 24` | `12 24` | `12 24` | 測試 LCM 可被 GCD 整除 |
| 無法整除情況 | `12 18` | `-1` | `-1` | 測試 LCM 無法被 GCD 整除 (18 % 12 != 0) |
| 兩數相同情況 | `5 5` | `5 5` | `5 5` | 測試 GCD 等於 LCM 的邊界情況 |

## 7. Reflection

- **根本原因：** 若沒有先推導數論性質而直接暴力窮舉因數，會造成不必要的時間與程式碼複雜度。
- **解決辦法：** 利用「GCD 必整除 LCM」與「$(G, L)$ 即為使第一數最小的解」這兩項定理，將問題降為 $O(1)$。
- **改進：** 遇到因數、倍數相關的題目，優先從整除性質切入，往往能省去繁瑣的演算法實作。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11388 / GCD LCM | Gemini | 幫助整理 README.md | 獨立確認數論整除性質與最佳解選取邏輯 |