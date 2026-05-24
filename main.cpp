 #include <iostream>

#include <vector>

#include <algorithm>

#include <cmath>

#include <string>

#include <limits>

using namespace std;



// ==============================

// 資料結構

// ==============================

struct Point {

    int x;

    int y;

};



// ==============================

// 工具函式

// ==============================

void printPoints(const vector<Point>& pts, const string& title) {

    cout << title << "\n";

    for (const auto& p : pts) {

        cout << "(" << p.x << "," << p.y << ") ";

    }

    cout << "\n\n";

}



double distancePoints(const Point& a, const Point& b) {

    double dx = a.x - b.x;

    double dy = a.y - b.y;

    return sqrt(dx * dx + dy * dy);

}



bool cmpX(const Point& a, const Point& b) {

    if (a.x != b.x) return a.x < b.x;

    return a.y < b.y;

}



bool cmpY(const Point& a, const Point& b) {

    if (a.y != b.y) return a.y < b.y;

    return a.x < b.x;

}



// =====================================================

// Part A. 2D_Maximal Template

// =====================================================



// 判斷 p1 是否被 p2 凌駕

// 若 p2.x >= p1.x 且 p2.y >= p1.y，並且至少一項嚴格大於，則 p1 被 p2 凌駕

bool isDominated(const Point& p1, const Point& p2) {

    // TODO:

    // 依照題目中的凌駕定義完成判斷

    if(p2.x >= p1.x && p2.y >= p1.y && (p2.x > p1.x || p2.y > p1.y)){

        return true;

    }

    return false; // 請修改

}



// n <= 3 時直接暴力求極點

vector<Point> bruteForceMaximal(const vector<Point>& S) {

    vector<Point> result;

    if(S.size() == 1){

        result.push_back(S[0]);

    }

    else if(S.size() == 2){

        //bool over = false;

       

        if(S[0].x >= S[1].x && S[0].y >= S[1].y && (S[0].x > S[1].x || S[0].y > S[1].y)){result.push_back(S[0]);}

        else if(S[1].x >= S[0].x && S[1].y >= S[0].y && (S[1].x > S[0].x || S[1].y > S[0].y) ){result.push_back(S[1]);}

        else {

            result.push_back(S[0]);

            result.push_back(S[1]);

        }

    }

    else {  //size=3 =>0,1,2  //p0如果滿足其中

        bool p0_be_domain = (S[1].x >= S[0].x && S[1].y >= S[0].y && (S[1].x > S[0].x || S[1].y > S[0].y))||

                            (S[2].x >= S[0].x && S[2].y >= S[0].y && (S[2].x > S[0].x || S[2].y > S[0].y));

        bool p1_be_domain = (S[0].x >= S[1].x && S[0].y >= S[1].y && (S[0].x > S[1].x || S[0].y > S[1].y)) ||

                            (S[2].x >= S[1].x && S[2].y >= S[1].y && (S[2].x > S[1].x || S[2].y > S[1].y));

        bool p2_be_domain = (S[0].x >= S[2].x && S[0].y >= S[2].y && (S[0].x > S[2].x || S[0].y > S[2].y)) ||

                            (S[1].x >= S[2].x && S[1].y >= S[2].y && (S[1].x > S[2].x || S[1].y > S[2].y));

       

        if(!p0_be_domain)result.push_back(S[0]);

        if(!p1_be_domain)result.push_back(S[1]);

        if(!p2_be_domain)result.push_back(S[2]);

       

    }

   

    // TODO:

    // 1. 對每個點檢查是否被其他點凌駕

    // 2. 若沒有被任何點凌駕，則加入 result

    // 3. 回傳 result



    return result;

    /*

    for (size_t i = 0; i < S.size(); ++i) {

        bool is_dominated = false;

       

        // 內層迴圈：拿點 i 跟其他所有的點 j 做比較

        for (size_t j = 0; j < S.size(); ++j) {

            if (i == j) continue; // 自己不用跟自己比

           

            // 💡 這裡直接呼叫你寫好的 isDominated 函式！

            // 意思是：如果點 S[i] 被點 S[j] 凌駕了

            if (isDominated(S[i], S[j])) {

                is_dominated = true;

                break; // 只要被任何一個點壓制，i 就出局，直接檢查下一個點

            }

        }

       

        // 如果完全沒有被任何人凌駕，它就是極點！

        if (!is_dominated) {

            // 選擇性加入：如果你想順便做到「完全重疊的點完美去重（只留一個）」

            bool already_exists = false;

            for (const auto& res : result) {

                if (res.x == S[i].x && res.y == S[i].y) {

                    already_exists = true;

                    break;

                }

            }

            if (!already_exists) {

                result.push_back(S[i]);

            }

        }

    }

    */

}



// 取得 x 座標中位數

int getMedianX(const vector<Point>& S) {

    vector<int> xs;

    for (const auto& p : S) {

        xs.push_back(p.x);

    }

    sort(xs.begin(),xs.end());

    int mid_index = (xs.size()-1)/2;

    // TODO:

    // 1. 將 xs 排序

    // 2. 取中位數並回傳

    return xs[mid_index]; // 請修改



    // 2. 取中位數並回傳

    // 使用 (size - 1) / 2 的好處：

    // 如果 size 是 4 (偶數)，(4-1)/2 = 1，會精準拿到第 2 個元素（中間偏左），符合我們之前算的 index 2

    // 如果 size 是 3 (奇數)，(3-1)/2 = 1，會精準拿到正中間第 2 個元素

}



// 2D_Maximal 主遞迴

vector<Point> maximalPoints(const vector<Point>& S) {

    int n = S.size();



    if (n <= 3) {

        return bruteForceMaximal(S);

    }



    // Step 1: 找 x 座標中位數

    int medianX = getMedianX(S);



    // Step 2: 分割成 S_L 與 S_R

    vector<Point> SL, SR;



    // TODO:

    // 將 x <= medianX 的點放入 SL

    // 將 x >  medianX 的點放入 SR

    for(const auto& p:S){

        if(p.x <= medianX){SL.push_back(p);}

        else {

            SR.push_back(p);

        }

    }

    // 避免分割失敗造成無限遞迴

    if (SL.size() == S.size() || SR.size() == S.size()) {

        return bruteForceMaximal(S);

    }



    // Step 3: 遞迴求左右兩側極點

    vector<Point> leftMaximal = maximalPoints(SL);

    vector<Point> rightMaximal = maximalPoints(SR);



    // Step 4: 找出 S_R 極點中 y 最大值

    int ymax = -1;

    if(!rightMaximal.empty()){

        ymax = rightMaximal[0].y;

        for (const auto& p : rightMaximal) {

            if (p.y > ymax) {

                ymax = p.y;

            }

        }

    }

    // TODO:

    // 從 rightMaximal 中找出最大的 y 值

    // 若 rightMaximal 為空，要注意處理



    // Step 5: 刪除 S_L 中 y < ymax 的點

    vector<Point> filteredLeft;

    if(rightMaximal.empty()){

        filteredLeft = leftMaximal;

    }

    else {

        for(const auto& p : leftMaximal){

            if(p.y >=ymax){

                filteredLeft.push_back(p);

            }

        }

    }

    // TODO:

    // 若 rightMaximal 為空，leftMaximal 全保留

    // 否則只保留 y >= ymax 的左側極點



    // Step 6: 合併結果

    vector<Point> result;

    result.insert(result.end(),filteredLeft.begin(),filteredLeft.end());

    result.insert(result.end(),rightMaximal.begin(),rightMaximal.end());

   

    // TODO:

    // 將 filteredLeft 與 rightMaximal 合併到 result



    return result;

}



// =====================================================

// Part B. 2D_Closest_Pair Template

// =====================================================



// n <= 3 時直接暴力求最近距離

double bruteForceClosest(const vector<Point>& S) {

    int n=S.size();

    if(n<2){

        return numeric_limits<double>::infinity();

    }
    
    double minDist = numeric_limits<double>::infinity();

    //S.size() == 3

    for (size_t i = 0; i < n; ++i) {

        for (size_t j = i + 1; j < n; ++j) {

            // 使用 sqrt 搭配兩點距離公式計算

            double d = sqrt(pow(S[i].x - S[j].x, 2) + pow(S[i].y - S[j].y, 2));

            if (d < minDist) {

                minDist = d; // 3. 回傳最小距離

            }

        }

    }

    return minDist; // 請修改



    // TODO:

    // 1. 若點數小於 2，可回傳很大的值

    // 2. 兩兩比較所有點距離

    // 3. 回傳最小距離



}



// 2D Closest Pair 遞迴函式

double closestPairRecursive(vector<Point> Px, vector<Point> Py) {

    int n = Px.size();



    // Base case

    if (n <= 3) {

        return bruteForceClosest(Px);

    }



    // Step 1: 取 x 中位數

    int mid = n / 2;

    Point midPoint = Px[mid];

    int L = midPoint.x;



    // Step 2: 分割成左半與右半

    vector<Point> PxL(Px.begin(), Px.begin() + mid);

    vector<Point> PxR(Px.begin() + mid, Px.end());



    vector<Point> PyL, PyR;



    // TODO:

    // 依照題目中的規則，把 Py 中各點分到 PyL, PyR

    // S_L : x <= L

    // S_R : x >  L

    for(const auto& p : Py){

        if(p.x <= L){

            PyL.push_back(p);

        }

        else {

            PyR.push_back(p);

        }

    }

    // 避免分割失敗造成無限遞迴

    if (PxL.empty() || PxR.empty()) {

        return bruteForceClosest(Px);

    }



    // Step 3: 遞迴求左右最近距離

    double dL = closestPairRecursive(PxL, PyL);

    double dR = closestPairRecursive(PxR, PyR);



    double delta = min(dL, dR);



    // Step 4: 建立 strip

    vector<Point> strip;



    // TODO:

    // 將所有滿足 |x - L| < delta 的點放入 strip

    // 建議從 Py 取，因為 Py 已按 y 排序

    for(const auto& p : Py){

        if(abs(p.x - L)<delta){

            strip.push_back(p);

        }

    }

    // Step 5: 檢查 strip 中可能跨中線的最近點

    int m = strip.size();

    for (int i = 0; i < m; i++) {

        // TODO:

        // 對 strip[i] 後面有限個點進行比較

        // 若找到更小距離，更新 delta

        for(int j=i+1;j<m && (strip[j].y-strip[i].y)<delta;j++){

            double d = sqrt(pow(strip[i].x - strip[j].x, 2) + pow(strip[i].y - strip[j].y, 2));

            if(d<delta){

                delta = d;

            }

        }

    }



    return delta;

}



// 封裝主函式：先依 x 與 y 排序，再呼叫遞迴

double closestPair(vector<Point> S) {

    // TODO:

    // 1. 建立 Px 與 Py

    // 2. Px 依 x 排序

    // 3. Py 依 y 排序

    // 4. 呼叫 closestPairRecursive(Px, Py)

    vector<Point>Px = S;

    vector<Point>Py = S;



    sort(Px.begin(), Px.end(), [](const Point& a, const Point& b) {

        return a.x < b.x;

    });



    sort(Py.begin(), Py.end(), [](const Point& a, const Point& b) {

        return a.y < b.y;

    });





    return closestPairRecursive(Px, Py);; // 請修改

}



// =====================================================

// 主程式

// =====================================================

int main() {

    // 測資 1

    vector<Point> case1 = {

        {5,12}, {12,10}, {2,9}, {5,7}, {10,6},

        {9,4}, {6,3}, {11,4}, {1,3}, {6,1}

    };



    // 測資 2

    vector<Point> case2 = {

        {6,0}, {11,3}, {10,9}, {8,5}, {9,7}, {6,10},

        {4,7}, {5,4}, {3,8}, {2,3}, {2,9}, {9,4}

    };



    // ------------------------------

    // Part A: 2D_Maximal

    // ------------------------------

    printPoints(case1, "Input Case 1:");

    vector<Point> ans1 = maximalPoints(case1);

    sort(ans1.begin(), ans1.end(), cmpX);

    printPoints(ans1, "Maximal Points of Case 1:");



    printPoints(case2, "Input Case 2:");

    vector<Point> ans2 = maximalPoints(case2);

    sort(ans2.begin(), ans2.end(), cmpX);

    printPoints(ans2, "Maximal Points of Case 2:");



    // ------------------------------

    // Part B: 2D_Closest_Pair

    // ------------------------------

    cout << "Closest Pair Distance of Case 1: "

         << closestPair(case1) << "\n";



    cout << "Closest Pair Distance of Case 2: "

         << closestPair(case2) << "\n";



    return 0;

}