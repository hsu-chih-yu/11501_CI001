# Code Review Report: [UVa] [11677] - [Automatic Alarm Clock]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11677
- **Problem Title:** Automatic Alarm Clock
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2724
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11677.cpp](./src/uva11677.cpp)
- **Review Date:** 2026-09-30

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 每行給定四個整數 `H1, M1, H2, M2`，分別代表目前的時與分，以及鬧鐘設定的時與分。當四個數字皆為 0 時結束。
- **預期的輸出是什麼？** 計算從目前時間到鬧鐘響起所需經過的分鐘數，並換行輸出。
- **主要的規則與限制是什麼？** 鬧鐘可能在當天響起，也可能在跨夜的隔天響起。一天固定有 24 小時（1440 分鐘）。
- **必須解決的核心任務是什麼？** 將時間統一轉換為當天的總分鐘數，計算差值並正確處理「跨日」的循環問題。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 直接分開算小時差與分鐘差容易遇到需要借位、或是跨過午夜 00:00 的情況，條件判斷會變得很繁瑣。
- 如果先把所有時間點換算成「從當天 00:00 開始起算的總分鐘數」，計算就會簡化成單純的整數減法。

### Final Strategy

- 將目前時間換算成自午夜起的總分鐘數：`now = H1 * 60 + M1`。
- 將鬧鐘時間同樣換算成分鐘數：`alarm = H2 * 60 + M2`。
- 兩者相減得到分鐘差 `d = alarm - now`。
- 若 `d < 0`，代表鬧鐘設定的時間在隔天，加上一整天的分鐘數 `1440` (24 * 60) 補正。

### Complexity Analysis

- **Time Complexity:** $O(1)$ 每筆測資。僅執行簡單的乘除與加減運算。
- **Space Complexity:** $O(1)$。只使用四個輸入變數與計算差值的變數。
- **解釋為何這些複雜度滿足問題限制：** 運算次數極少且無多層迴圈，能輕易在時限內通過大量輸入。

## 4. Pseudocode
```
START
1. WHILE read nh, nt, ah, att successfully:
2.     IF nh == 0 AND nt == 0 AND ah == 0 AND att == 0 THEN BREAK
3.     SET now = nh * 60 + nt
4.     SET al = ah * 60 + att
5.     SET d = al - now
6.     IF d < 0 THEN
7.         d = d + 1440
8.     PRINT d
END
```

## 5. Correct Code
```cpp
#include <iostream>

using namespace std;

int main() {
    int nh, nt, ah, att;
    while (cin >> nh >> nt >> ah >> att) {
        if (nh == 0 && nt == 0 && ah == 0 && att == 0) break;
        int now = nh * 60 + nt;
        int al = ah * 60 + att;
        int d = al - now;
        if (d < 0) {
            d += 1440;
        }
        cout << d << endl;
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 透過把時間維度降至單一單位（分鐘），避免了 60 進位與 24 進位的混淆；利用 `d < 0` 加上 `1440` 的操作，在數學上等價於在模數（Modulo 1440）空間下進行非負差值計算，精確涵蓋了跨夜的情境。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 當天同日 | `1 5 3 5` | `120` | `120` | 測試同一天內單純的時間增加 |
| 跨日情況 | `23 59 0 34` | `35` | `35` | 測試跨過午夜 00:00 的情形 |
| 相同時間 | `21 33 21 33` | `0` | `0` | 測試目前時間與鬧鐘時間完全相同 |

## 7. Reflection

- **根本原因：** 多單位（時、分）的時間差計算容易因借位與跨日造成邏輯混亂。
- **解決辦法：** 先統一度量衡，將全部時間換算成「分」再做運算。
- **改進：** 未來遇到角度、時間等具循環性質的題目時，善用最小度量單位轉換與模數概念來簡化邊界判斷。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11677 / Automatic Alarm Clock | Gemini | 幫助整理 README.md | 獨立完成時間度量轉換與跨日補正邏輯 |
