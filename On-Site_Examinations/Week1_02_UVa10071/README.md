# Code Review Report: [UVa] [10071] - [Back to High School Physics]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10071
- **Problem Title:** Back to High School Physics
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1012
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva10071.cpp](./src/uva10071.cpp)
- **Review Date:** 2026-09-23

## 2. Problem Statement in My Own Words

- 多筆包含兩個整數的測資，分別代表粒子的速度 $v$ 與時間 $t$，直到 EOF。
- 計算並輸出該物體在 $2t$ 時間後的位移，並換行。
- 假設為等加速度運動，速度與時間的乘積在標準 `int` 範圍內。
- 找出速度、時間與位移的關係並計算解答。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 一開始想到的是先算出加速度 $a = v / t$，再代入位移公式 $s = \frac{1}{2} a (2t)^2$。
- 如果直接這樣寫，當 $t = 0$ 時會發生除以零 的執行時期錯誤。
- 且若使用浮點數計算 $v / t$，可能會產生精確度誤差，程式碼也較繁瑣。

### Final Strategy

- 將物理公式在紙上先進行代數化簡：$s = \frac{1}{2} (\frac{v}{t}) (2t)^2 = \frac{1}{2} \frac{v}{t} 4t^2 = 2vt$。
- 直接讀取 $v$ 和 $t$，輸出 `2 * v * t` 即可，完全避開浮點數運算與除以零的問題。
- 不論 $t=0$ 或 $v$ 為負數的情況皆可正常處理。

### Complexity Analysis

- **Time Complexity:** $O(1)$。單純進行一次乘法運算。
- **Space Complexity:** $O(1)$。只使用了兩個變數存放輸入。
- **解釋為何這些複雜度滿足問題限制：** 運算成本極低，僅一行數學式，能輕鬆通過時間限制。

## 4. Pseudocode
```
START
1. WHILE read v and t successfully (until EOF):
2.     PRINT 2 * v * t
3. END WHILE
END
```

## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int main() {
    int v, t;
    while (cin >> v >> t) {
        cout << 2 * v * t << "\n";
    }
    return 0;
}
```

**Why it works：**
- **關鍵條件：** 利用數學代數化簡為 $2vt$，避免了除以 0 的狀況。同時數值範圍在 `int` 內，不會有溢位問題。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `5 12` | `120` | `120` | 測試正常速度與時間相乘 |
| 邊界情況 | `0 0` | `0` | `0` | 測試靜止或時間為 0 |
| 負數情況 | `-5 12` | `-120` | `-120` | 測試具有方向性的速度 |

## 7. Reflection

- **根本原因：** 如果物理公式未經化簡就直接寫成程式碼，容易遇到除以 0 的例外錯誤，或是增加不必要的浮點數負擔。
- **解決辦法：** 將公式化簡為最乾淨的乘法關係 $2vt$。
- **改進：** 未來遇到數學或物理公式題，寫程式碼前先在紙上尋找變數之間最簡單的代數關係。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10071 / Back to High School Physics | Gemini | 幫助整理 README.md | 自行推導公式化簡並確認避開除以零錯誤 |