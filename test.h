#include <windows.h>
#include <bits/stdc++.h>
#include "deque.h"
#include "gtest/gtest.h"

class PushPopSizeEmptyTest : public testing::TestWithParam<int> {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
    const int a_ = 2, mod_ = 1e7 + 7;
    int x_ = 0;
    int Random() {
        x_ = (a_ * x_ + rand() % mod_) % mod_;
        return x_;
    }
    template<class DequeReference>
    void fullDeque(DequeReference& dq, int n, bool makePop) {
        for(int i = 0; i < n; i++) {
            int x = rand() % 100;
            if(!dq.empty() && makePop) {
                if (x % 4 == 0) {
                    int x = Random();
                    dq.push_back(x);
                } else if (x % 4 == 1) {
                    int x = Random();
                    dq.push_front(x);
                } else if (x % 4 == 2) {
                    dq.pop_back();
                } else if (x % 4 == 3) {
                    dq.pop_front();
                }
            } else {
                if (x % 2 == 0) {
                    int x = Random();
                    dq.push_back(x);
                } else {
                    int x = Random();
                    dq.push_front(x);
                }
            }
        }
    }
    template<class DequeReference>
    void clearDeque(DequeReference& dq) {
        while(!dq.empty()) {
            dq.pop_front();
        }
    }
    Deque<int> testing;
    deque<int> tester;
};
void printDeque(Deque<int> &testing, deque<int> &tester) {
    cout << "size testing: " << testing.size() <<"\n";
    for (int i = 0; i < testing.size(); ++i) {
        cout << testing[i] << " ";
    }
    cout <<"\n";
    cout << "size tester: " << tester.size() << "\n";
    for (int i = 0; i < tester.size(); ++i) {
        cout << tester[i] << " ";
    }
    cout <<"\n";
}
TEST_P(PushPopSizeEmptyTest, DequeueWorks) {
    srand(time(NULL));
    int n = GetParam();
    for (int i = 0; i < n; i++) {
        if (tester.size() != testing.size() || tester.empty() != testing.empty()) {
            printDeque(testing, tester);
        }
        ASSERT_EQ(tester.size(), testing.size());
        ASSERT_EQ(tester.empty(), testing.empty());
        int x = rand() % 100;
        if (!tester.empty()) {
            ASSERT_EQ(tester.back(), testing.back());
            ASSERT_EQ(tester.front(), testing.front());
            if (x % 4 == 0) {
                int x = Random();
                testing.push_back(x);
                tester.push_back(x);
            } else if (x % 4 == 1) {
                int x = Random();
                testing.push_front(x);
                tester.push_front(x);
            } else if (x % 4 == 2) {
                tester.pop_back();
                testing.pop_back();
            } else if (x % 4 == 3) {
                tester.pop_front();
                testing.pop_front();
            }
        } else {
            if (x % 2 == 0) {
                int x = Random();
                testing.push_back(x);
                tester.push_back(x);
            } else {
                int x = Random();
                testing.push_front(x);
                tester.push_front(x);
            }
        }
    }
    if (tester.size() != testing.size() || tester.empty() != testing.empty()) {
            printDeque(testing, tester);
    }
    ASSERT_EQ(tester.size(), testing.size());
    ASSERT_EQ(tester.empty(), testing.empty());
    for (int i = 0; i < tester.size(); ++i) {

        EXPECT_EQ(tester[i], testing[i]);
        if (tester[i] != testing[i])
            printDeque(testing, tester);
        ASSERT_EQ(tester[i], testing[i]);
        ASSERT_EQ((tester.begin())[i], (testing.begin())[i]);
        ASSERT_EQ((tester.rbegin())[i], (testing.rbegin())[i]);
    }
    deque<int>::reverse_iterator it1 = tester.rbegin();
    Deque<int>::reverse_iterator it2 = testing.rbegin();
    for (; it1 < tester.rend() && it2 < testing.rend(); it1 += 3, it2 +=3) {
         ASSERT_EQ(*it1, *it2);
    }
    deque<int>::iterator it3 = tester.begin();
    Deque<int>::iterator it4 = testing.begin();
    for (; it3 != tester.end() && it4 != testing.end(); ++it3, ++it4) {
         ASSERT_EQ(*it3, *it4);
    }
    while (!testing.empty()) {
        ASSERT_EQ(tester.back(), testing.back());
        ASSERT_EQ(tester.front(), testing.front());
        testing.pop_front();
        tester.pop_front();
    }
    ASSERT_EQ(tester.size(), testing.size());
    ASSERT_EQ(tester.empty(), testing.empty());
}
TEST_F(PushPopSizeEmptyTest, TimeAnalys) {
    srand(time(NULL));
    int n = 65536;
    for(; n < 16777350; n *= 2) {
        double t1 = clock();
        fullDeque(testing, n, 1);
        double t2 = clock();
        double testTime = (t2 - t1) / CLOCKS_PER_SEC;
        printf("size: %d; time for Deque with using pop: %lfs\n", n, testTime);
        clearDeque(testing);
        t1 = clock();
        fullDeque(testing, n, 0);
        t2 = clock();
        testTime = (t2 - t1) / CLOCKS_PER_SEC;
        printf("size: %d; time for Deque without using pop: %lfs\n--------\n", n, testTime);
        clearDeque(testing);
        t1 = clock();
        fullDeque(tester, n, 1);
        t2 = clock();
        testTime = (t2 - t1) / CLOCKS_PER_SEC;
        printf("size: %d; time for std::deque with using pop: %lfs\n", n, testTime);
        clearDeque(tester);
        t1 = clock();
        fullDeque(tester, n, 0);
        t2 = clock();
        testTime = (t2 - t1) / CLOCKS_PER_SEC;
        printf("size: %d; time for std::deque without using pop: %lfs\n===============================================\n", n, testTime);
        clearDeque(tester);
    }
    cout <<"Here you can see that usually Deque works faster, than std::deque, that is why every operation has accounting time O(1)\n";
}


INSTANTIATE_TEST_CASE_P(PushPopSizeEmptyTest, PushPopSizeEmptyTest, testing::Values(10, 100, 1000, 5000, 10000, 100000, 1000000, 10000000, 50000000));
