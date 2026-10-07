# Code Review Report: [UVa] [11827] - [Maximum GCD]

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 11827
- **Problem Title:** Maximum GCD
- **Problem Link:** https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2927
- **Language / Version:** C++
- **Submission Result:** Wrong Answer / Need Revision
- **Source Code (Initial/Fail):** [src/uva11827_fail.cpp](./src/uva11827_fail.cpp)
- **Source Code (Final/Accepted):** [src/uva11827.cpp](./src/uva11827.cpp)
- **Review Date:** 2026-10-07

## 2. Problem Statement in My Own Words

- **輸入是什麼？** 第一行包含測資筆數 $N$。接下來每一行給定若干個由空白分隔的正整數（個數不固定，至少 2 個且最多 100 個）。
- **預期的輸出是什麼？** 找出該行中所有任意兩數配對的最大公因數（GCD）之最大值，並換行輸出。
- **主要的規則與限制是什麼？** 題目每一行沒有預先給定該行數字的數量，且行尾可能包含多餘的空白或換行符號。
- **必須解決的核心任務是什麼？** 正確讀取不固定個數的單行整數輸入，並雙重枚舉所有數對求出最大 GCD。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- 看到輸入每行數字個數不固定，一開始嘗試使用 `cin >> n` 搭配 `scanf("%c", &c)` 來檢查是否遇到 `\n`。
- 但 `cin >> n` 會自動略過前置空白和換行，如果數字與換行之間存在多個空白，`scanf` 讀到空白鍵而非換行時，下一次的 `cin` 就會跨行讀取到下一筆測資，造成資料錯位與邏輯混亂。

### Final Strategy

- 改用標準字串串流處理解法：先用 `getline(cin, line)` 吃掉測資筆數後的換行。
- 對於每筆測資，使用 `getline(cin, line)` 將整行資料完整讀入，避免跨行干擾。
- 建立 `stringstream ss(line)`，透過 `while (ss >> n)` 將該行所有數字依序解析存入陣列。
- 使用雙層迴圈枚舉所有 $0 \le j < k < i$ 的數對，透過輾轉相除法計算 GCD，並維護最大值 `m`。

### Complexity Analysis

- **Time Complexity:** $O(M^2 \log(\max(A)))$ 每筆測資。其中 $M$ 為該行的數字個數（$M \le 100$）。雙層迴圈最多執行約 $\frac{100 \times 99}{2} \approx 4950$ 次 GCD 運算，效率極高。
- **Space Complexity:** $O(M)$。需要陣列儲存單行解析出的數字，最多僅 100 個元素。
- **解釋為何這些複雜度滿足問題限制：** 運算規模非常小，遠低於時間限制要求。

## 4. Pseudocode
```
START
FUNCTION getgcd(a, b):
    WHILE b != 0:
        remainder = a % b
        a = b
        b = remainder
    RETURN abs(a)

READ cases
CONSUME newline after cases

WHILE cases > 0:
    READ entire line as string
    INITIALIZE stringstream with line
    INITIALIZE array a and count i = 0
    
    WHILE read n from stringstream:
        a[i] = n
        i = i + 1
        
    SET m = 0
    FOR j = 0 TO i - 2:
        FOR k = j + 1 TO i - 1:
            t = getgcd(a[j], a[k])
            IF t > m THEN
                m = t
                
    PRINT m
    cases = cases - 1
END
```
## 5. Fail Code vs Correct Code

### Fail Code
```cpp
#include <iostream>
#include <cmath>

using namespace std;

long long getgcd(long long a, long long b){
    while(b != 0){
        long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return abs(a);
}

int main(){
    int cases;
    cin >> cases;
    while(cases--){
        int n;
        char c = ' ';
        int i = 0;
        int a[101] = {};
        while(c != '\n'){
            cin >> n;
            a[i] = n;
            scanf("%c", &c);
            i++;
        }
        int m = 0;
        for(int j = 0; j < i - 1; j++){
            for(int k = j + 1; k < i; k++){
                int t = getgcd(a[j], a[k]);
                if(m < t){
                    m = t;
                }
            }
        }
        cout << m << endl;
    }
    return 0;
}
```
**Why it failed:**
- **技術原因：** `cin >> n` 與 `scanf("%c", &c)` 混用處理字元結尾，當行尾有多餘空白或換行符號殘留時，無法準確以 `c == '\n'` 作為行結束判斷，導致迴圈跨行讀取下一組測資，發生錯位或無窮迴圈。
- **暴露問題的測資：** 行尾含有多個連續空白（例如 `"10 20   \n"`）或數字間有非單一空白隔開時，會讀錯測資邊界。

### Correct Code
```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

long long getgcd(long long a, long long b){
    while(b != 0){
        long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return abs(a);
}

int main(){
    int cases;
    if (cin >> cases) {
        string line;
        getline(cin, line);

        while(cases--){
            getline(cin, line);
            stringstream ss(line);

            int a[101] = {};
            int i = 0;
            int n;

            while(ss >> n){
                a[i++] = n;
            }

            int m = 0;
            for(int j = 0; j < i - 1; j++){
                for(int k = j + 1; k < i; k++){
                    int t = getgcd(a[j], a[k]);
                    if(m < t){
                        m = t;
                    }
                }
            }
            cout << m << "\n";
        }
    }
    return 0;
}
```
**Why it works:**
- **關鍵條件：** 透過 `getline` 將整行字串完整封閉讀取，再由 `stringstream` 自動處理任意長度的空白與縮排，確保單行邊界絕對切分正確，不會發生跨行誤讀。

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
|---|---|---|---|---|
| 一般情況 | `10 20 30 40` | `20` | `20` | 測試多數字配對最大 GCD (gcd(20, 40)=20) |
| 多重空白情況 | `10   20  40   ` | `20` | `20` | 驗證 `stringstream` 能正確忽略多餘空白 |
| 最小個數 | `7 13` | `1` | `1` | 測試只有兩個互質數字的情況 |

## 7. Reflection

- **根本原因：** 依賴逐字元讀取換行符號來判定行結尾過於脆弱，容易受連續空白與緩衝區殘留字元影響。
- **解決辦法：** 遇到「未告知該行數量」的不定長度輸入時，一律採用 `getline` 搭配 `stringstream` 進行解析。
- **改進：** 養成在讀取混合型態輸入時（如先讀整數再讀整行），立即使用 `cin.ignore()` 或空讀 `getline` 清除緩衝區換行符號的習慣。

## 8. AI Usage Disclaimer

- 若有使用 AI 工具，僅用於輔助學習，例如釐清概念或檢查解釋。
- 本報告中的解決方案與反思皆由本人獨立理解、驗證並完成。

### AI Usage Record

| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
|---|---|---|---|
| 11827 / Maximum GCD | Gemini | 幫助分析輸入錯位原因與整理 README.md | 獨立確認 stringstream 解析流程與雙層枚舉邏輯 |