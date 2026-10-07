# Code Review Report: [UVa] [11461] - [Square Numbers]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11461
- **Problem Title:** Square Numbers
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2456
- **Language / Version:** C++
- **Submission Result:** Accepted
- **Source Code (Final/Accepted):** [src/uva11461.cpp](./src/uva11461.cpp)
- **Review Date:** 2026-10-07

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 每行包含兩個整數 `a` 和 `b` ($0 < a \le b \le 100000$)。當讀取到 `0 0` 時結束輸入。
- **預期的輸出是什麼？** 輸出在區間 $[a, b]$ 之間（包含端點）有多少個完全平方數 (Square numbers)，並換行。
- **主要的規則與限制是什麼？** 數值範圍介於 1 到 100000 之間，包含多組測試資料。
- **必須解決的核心任務是什麼？** 計算區間內的完全平方數數量，並確保演算法效率足夠通過大量測資。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 直覺的想法是使用 `for` 迴圈從 `a` 跑到 `b`，逐一檢查每個整數 `i` 是否能開根號得到整數（例如 `isSquare(i)`）。
- 每次檢查計算 `sqrt(i)` 並驗證平方是否等於原數。雖然在測資上限 $100000$ 內通常能通過，但若測資筆數非常多，對區間內每個數字做逐一開根號會產生重複且不必要的運算開銷。

### Final Strategy

- 依然使用迴圈走訪區間 $[a, b]$，利用 `sqrt` 搭配四捨五入或取整數平方根：`long long r = round(sqrt(n))`，判斷 `r * r == n` 來累加計數。
- 當遇到輸入 `a == 0 && b == 0` 時跳出迴圈終止程式。

### Complexity Analysis

- **Time Complexity:** $O(b - a)$ 每筆測資。迴圈共執行 $b - a + 1$ 次，每次進行一次浮點數開根號與乘法比較。
- **Space Complexity:** $O(1)$。僅使用少數整數變數儲存邊界與計數結果。
- **解釋為何這些複雜度滿足問題限制：** 題目給定的範圍最大為 $100000$，單次迴圈最多執行十萬次基本運算，在 UVa 限制時間內足以通過。

## 4. Pseudocode
```
START
FUNCTION isSquare(n):
    IF n < 0 THEN RETURN False
    SET r = round(sqrt(n))
    RETURN (r * r == n)

WHILE read a, b successfully:
    IF a == 0 AND b == 0 THEN BREAK
    SET ans = 0
    FOR i = a TO b:
        IF isSquare(i) THEN
            ans = ans + 1
    PRINT ans
END
```
## 5. Correct Code
```cpp
#include <iostream>
#include <cmath>

using namespace std;

bool isSquare(long long n){
    if(n < 0)false;
    long long r = round(sqrt(n));
    return (r* r == n);

}


int main()
{
    int a,b;
    while(cin >> a >> b ){
            int ans = 0;
        if(a == 0 && b == 0)break;
        for(long long i = a; i <= b; i++){
            bool s = isSquare(i);
            if(s){
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```
**Why it works：**
- **關鍵條件：** 透過 `round(sqrt(n))` 取得最接近的整數根，再以 `r * r == n` 驗證其平方是否恰好等於原數，精準判定了完全平方數，避免浮點數精度微小偏差造成的誤判。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般區間 | `1 4` | `2` | `2` | 測試包含 1 和 4 兩個平方數 |
| 無平方數 | `2 3` | `0` | `0` | 測試區間內不存在完全平方數 |
| 端點皆為平方數 | `4 9` | `2` | `2` | 測試端點是否正確被計入 (4 和 9) |
| 極大區間 | `1 100000` | `316` | `316` | 測試全範圍上限下的計算正確性 ($\lfloor\sqrt{100000}\rfloor = 316$) |

## 7. Reflection

- **根本原因：** 雖然使用迴圈一個個檢查很直觀且正確，但對於範圍極大的區間，逐一開根號運算會增加執行時間。
- **解決辦法：** 目前透過逐個檢查並驗證平方可正確 AC。
- **改進：** 在數學上，$[a, b]$ 之間的平方數個數可直接利用上下界公式化簡為 $\lfloor\sqrt{b}\rfloor - \lceil\sqrt{a}\rceil + 1$（或 $\lfloor\sqrt{b}\rfloor - \lfloor\sqrt{a - 1}\rfloor$），將時間複雜度進一步最佳化至 $O(1)$。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 114