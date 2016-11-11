#include <bits/stdc++.h>

using namespace std;
template <typename IteratorType>
 class deque_iterator : public iterator<random_access_iterator_tag, IteratorType>
 {
 private:

    IteratorType *it_, *begin_;
    int len_, size_, ind_;
    void make_step(int t)
    {
        len_ += t;
        ind_ += t;
        while (len_ < 0)
        {
            len_ += size_;
        }
        len_ %= size_;
        it_ = begin_ + len_;
    }

 public:

    deque_iterator(IteratorType* a, int position, int ind, int size) : it_(a + position), begin_(a), len_(position), ind_(ind), size_(size) {}
    deque_iterator(const deque_iterator &it) : it_(it.it_), begin_(it.begin_), len_(it.len_), size_(it.size_), ind_(it.ind_) {}
    deque_iterator& operator =(const deque_iterator& it) {
        it_ = it.it_;
        begin_ = it.begin_;
        len_ = it.len_;
        size_ = it.len_;
        ind_ = it.ind_;
        return *this;
    }
    IteratorType& operator *() {
        return *it_;
    }
    const IteratorType& operator *() const {
        return *it_;
    }
    IteratorType* operator ->() {
        return it_;
    }
    const IteratorType* operator ->() const {
        return it_;
    }
    deque_iterator& operator ++() {
        make_step(1);
        return *this;
    }
    deque_iterator& operator --() {
        make_step(-1);
        return *this;
    }
    const deque_iterator operator ++(int) {
        deque_iterator it = *this;
        ++(*this);
        return it;
    }
    const deque_iterator operator --(int) {
        deque_iterator it = *this;
        --(*this);
        return it;
    }
    const deque_iterator operator +(const int a) const {
        deque_iterator it = *this;
        it.make_step(a);
        return it;
    }
    const deque_iterator operator -(const int a) const {
        deque_iterator it = *this;
        it.make_step(-a);
        return it;
    }
    const int operator -(const deque_iterator& it) const {
        return it_ - it.it_;
    }
    const deque_iterator& operator +=(const int a) {
        make_step(a);
        return *this;
    }
    const deque_iterator& operator -=(const int a) {
        make_step(-a);
        return *this;
    }
    IteratorType& operator [](const int f) {
        deque_iterator it = *this;
        it.make_step(f);
        return *(it.it_);
    }
    bool operator != (const deque_iterator &it) const {
        return it_ != it.it_;
    }

    bool operator == (const deque_iterator &it) const {
        return it_ == it.it_;
    }

    bool operator < (const deque_iterator &it) const {
        return ind_ < it.ind_;
    }
    bool operator > (const deque_iterator &it) const {
        return it < (*this);
    }
    bool operator >= (const deque_iterator &it) const {
        return (*this > it || *this == it);
    }
    bool operator <= (const deque_iterator &it) const {
        return (*this < it || *this == it);
    }
 };
 /////////////////////////////////////////////////////////////////////////////////////////
template <class T>
 class Deque {
    int N_, size_;
    T *a_;
    int begin_, end_;
    void reallocator() {
        T *b = new T [2 * N_];
        for (int i = begin_, j = 0; j < N_; ++j, ++i)  {
            i %= N_;
            b[j] = a_[i];
        }
        delete[] a_;
        a_ = b;
        end_ = N_;
        begin_ = 0;
        N_*=2;
    }
    void deletememory() {
        T *b = new T [N_ / 2];
        int j = 0;
        for (int i = begin_; j < N_ / 2 && i % N_ != end_; ++j, ++i)  {
            i %= N_;
            b[j] = a_[i];
        }
        delete[] a_;
        a_ = b;
        N_/=2;
        end_ = j;
        begin_ = 0;
    }
public:
    typedef deque_iterator<T> iterator;
    typedef deque_iterator<const T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    Deque() : N_(1), a_(new T [N_]), begin_(0), end_(0), size_(0) {}
    Deque(const Deque &b) {
        N_ = b.N_;
        a_ = new T [N_];
        begin_ = b.begin_;
        end_ = b.end_;
        size_ = b.size_;
        for (int i = 0; i < N_; ++i) {
            a_[i] = b.a_[i];
        }
    }
    Deque& operator = (const Deque& b)
    {
        N_ = b.N_;
        a_ = new T [N_];
        begin_ = b.begin_;
        end_ = b.end_;
        size_ = b.size_;
        for (int i = 0; i < N_; ++i) {
            a_[i] = b.a_[i];
        }
        return *this;
    }
    T &operator [](const int i) {
        return a_[(begin_ + i) % N_];
    }
    T &back() {
        return a_[(end_ - 1 + N_) % N_];
    }
    T &front() {
        return a_[begin_];
    }
    T &operator [](const int i) const{
        return (*this)[i];
    }
    T &front() const {
        return (*this).front();
    }
    T &back() const {
        return (*this).back();
    }
    void push_back(const T &a) {
        a_[end_] = a;
        end_ = (end_ + 1) % N_;
        ++size_;
        if (end_ == begin_) {
            reallocator();
        }
    }
    void push_front(const T &a) {
        begin_ = (begin_ - 1 + N_) % N_;
        a_[begin_] = a;
        ++size_;
        if (end_ == begin_) {
            reallocator();
        }
    }
    void pop_back() {
        if (end_ == begin_) {
            size_ = 0;
            return;
        }
        --size_;
        end_ = (end_  - 1 + N_) % N_;
        if (size_ < N_ / 4 && N_ > 1)
            deletememory();
    }
    void pop_front() {
        if (end_ == begin_) {
            size_ = 0;
            return;
        }
        --size_;
        begin_ = (begin_ + 1) % N_;
        if (size_ < N_ / 4 && N_ > 1)
            deletememory();
    }
    int size() const {
        return size_;
    }
    bool empty() const {
        return size_ ? false : true;
    }
    iterator begin()
    {
        return iterator(a_, begin_, 0, N_);
    }
    const_iterator begin() const
    {
        return const_iterator(a_, begin_, 0, N_);
    }
    const_iterator cbegin() const
    {
        return const_iterator(a_, begin_, 0, N_);
    }
    iterator end()
    {
        return iterator(a_, end_, size_, N_);
    }
    const_iterator end() const
    {
        return const_iterator(a_, end_, size_, N_);
    }
    const_iterator cend() const
    {
        return const_iterator(a_, end_, size_, N_);
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator(iterator(a_, end_, size_, N_));
    }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(iterator(a_, end_, size_, N_));
    }
    const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator(const_iterator(a_, end_, size_, N_));
    }
    reverse_iterator rend()
    {
        return reverse_iterator(iterator(a_, begin_, 0, N_));
    }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(iterator(a_, begin_, 0, N_));
    }
    const_reverse_iterator crend() const
    {
        return const_reverse_iterator(const_iterator(a_, begin_, 0, N_));
    }

 };
