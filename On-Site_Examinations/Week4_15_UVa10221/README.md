# Code Review Report: [UVa] [10221] - [Satellites]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10221
- **Problem Title:** Satellites
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1162
- **Language / Version:** C++
- **Submission Result:** Wrong Answer / Incomplete
- **Source Code (Initial/Fail):** [src/uva10221_fail.cpp](./src/uva10221_fail.cpp)
- **Source Code (Final/Accepted):** [src/uva10221.cpp](./src/uva10221.cpp)
- **Review Date:** 2026-09-30

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 多行輸入，每行包含衛星離地表高度 `s`、兩衛星夾角 `a`、以及角度單位字串 `b` (`"deg"` 度 或 `"min"` 分)。
- **預期的輸出是什麼？** 輸出兩顆衛星之間的「弧長 (arc distance)」與「弦長 (chord distance)」，以空白分隔並保留至小數點後六位。
- **主要的規則與限制是什麼？** 地球半徑固定為 6440 公里，因此軌道半徑為 $r = s + 6440$。若角度大於 180 度，需取兩者之間的劣弧/劣角（$360^\circ - a$）。
- **必須解決的核心任務是什麼？** 正確將「分 (min)」換算為「度 (deg)」，處理大於 180 度的角，並依據圓的幾何公式計算弧長與弦長。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 地球半徑需加上衛星高度 $r = 6440 + s$。
- 弧長公式為 $r \times \theta$（其中 $\theta$ 為弧度）。
- 檢視原本的程式碼，發現缺漏了「弦長計算」、漏掉了「大於 180 度時需取 $360 - a$ 的規則」，且在角度為分時直接除以 60 在部分變數型態上易遺漏，此外殘留了除錯用的 `cout`。

### Final Strategy

- 讀取 `s`、`a` 與字串 `b`。軌道半徑為 $r = s + 6440.0$。
- 單位轉換：若 `b == "min"`，則將角度轉換為度數：$a = a / 60.0$。
- 角度調整：若角度 $a > 180^\circ$，則令 $a = 360^\circ - a$。
- 將角度轉為弧度：$\text{rad} = a \times \frac{\pi}{180}$。使用較高精度的圓周率 $\pi = 2 \times \arccos(0.0)$。
- 計算弧長：$\text{arc} = r \times \text{rad}$。
- 計算弦長：$\text{chord} = 2.0 \times r \times \sin(\text{rad} / 2.0)$。
- 格式化輸出小數點後六位。

### Complexity Analysis

- **Time Complexity:** $O(1)$ 每筆測資。僅執行三角函數與基本浮點數四則運算。
- **Space Complexity:** $O(1)$。僅使用少數 double 變數存放計算結果。
- **解釋為何這些複雜度滿足問題限制：** 運算量為極低的常數級別，能在時限內迅速完成所有測試。

## 4. Pseudocode
```
START
1. SET PI = 2 * acos(0.0)
2. WHILE read s, a, b successfully:
3.     SET r = s + 6440.0
4.     IF b == "min" THEN
5.         a = a / 60.0
6.     IF a > 180.0 THEN
7.         a = 360.0 - a
8.     SET rad = a * PI / 180.0
9.     SET arc = r * rad
10.    SET chord = 2.0 * r * sin(rad / 2.0)
11.    PRINT arc and chord with 6 decimal places
END
```
## 5. Fail Code vs Correct Code

### Fail Code
```cpp
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int s, a;
    string b;
    cout <<  3592.408346 / 6940 * 180 /3.1415926 << endl <<  124.616509 / 7140 * 360 / 3.1415926 *30 << endl;
    while(cin >> s >> a >> b){
        s += 6440;
        float o = 180 / 3.1415926;
        double ans = s * a * 3.1415926536 / 180;
        if(b == "min"){
            ans /= 60;
        }
        
        printf("%.6f %.6f\n", ans);
        }
    return 0;
}
```

**Why it failed:**
- **技術原因：** 輸出完全遺漏了第二個數值「弦長」，且未考慮到題目要求的幾何限制（角度超過 180 度時應走短弧 $360 - a$）；另外程式碼開頭殘留了 debug 輸出行，且變數精度使用 `float` 易產生誤差。
- **暴露問題的測資：** 任何題目範例測資（例如 `500 30 deg`）皆因缺少弦長輸出而判定 Wrong Answer；輸入角度大於 180 度時（例如 `500 200 deg`）弧長計算錯誤。

### Correct Code
```cpp
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    double s, a;
    string b;
    const double PI = 2.0 * acos(0.0);

    while (cin >> s >> a >> b) {
        double r = s + 6440.0;
        
        if (b == "min") {
            a /= 60.0;
        }
        
        if (a > 180.0) {
            a = 360.0 - a;
        }
        
        double rad = a * PI / 180.0;
        double arc = r * rad;
        double chord = 2.0 * r * sin(rad / 2.0);
        
        cout << fixed << setprecision(6) << arc << " " << chord << "\n";
    }
    return 0;
}
```
**Why it works:**
- **關鍵條件：** 補齊了弦長的三角函數計算公式 $2r\sin(\theta / 2)$；在計算前加入 `a > 180` 的劣角修正；使用 `const double PI = 2.0 * acos(0.0)` 與 `double` 型態確保精確度，並移除了多餘的除錯輸出。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般角度 (度) | `500 30 deg` | `3633.775503 3592.408346` | `3633.775503 3592.408346` | 驗證標準角度之弧長與弦長運算 |
| 分單位轉換 | `500 60 min` | 等同 1 度的結果 | 與計算值一致 | 驗證 `min` 正確除以 60 轉換為度 |
| 超過 180 度 | `500 200 deg` | 等同 160 度的結果 | 與計算值一致 | 驗證 $a > 180$ 時取劣角 $360 - a$ 的邏輯 |

## 7. Reflection

- **根本原因：** 撰寫時未完整閱讀輸出規格（漏看了弦長需求），且在測試時殘留了非必要的打印語句。
- **解決辦法：** 補齊弦長三角函數公式，並落實題目對於角度大於 180 度走短邊的幾何限制。
- **改進：** 遇到輸出多個數值的題目，提交前務必再次對照題目要求的輸出數量、格式與變數範圍，並養成提交前清除所有 debug 輸出的習慣。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 10221 / Satellites | Gemini | 幫助整理 README.md 與比對錯誤原因 | 獨立推導弦長三角函數與邊界角度修正 |