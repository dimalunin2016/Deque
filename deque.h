//https://github.com/dimalunin2016/Deque
#include <iostream>
#include <iterator>

template <class IteratorType, class IteratorType2, class IteratorType3>
class deque_iterator : public std::iterator<std::random_access_iterator_tag, IteratorType>
{
private:
    IteratorType2 begin_;
    int len_, size_, ind_;
    void make_step(int t) {
        if(size_ == 0) {
            len_ = 0;
            ind_ = 0;
            return;
        }
        len_ += t;
        ind_ += t;
        if (len_ < 0) {
            int k = 0;
            k = (0 - len_)/size_ + 1;
            len_ += k * size_;
        }
        len_ %= size_;
    }

public:
    deque_iterator() {}
    deque_iterator(IteratorType2 a, int position, int ind, int size) {
        begin_ = a;
        len_ = position;
        ind_ = ind;
        size_ = size;
    }
    deque_iterator(const deque_iterator &it) {
        begin_ = it.begin_;
        len_ = it.len_;
        size_ = it.size_;
        ind_ = it.ind_;
    }
    deque_iterator& operator =(const deque_iterator& it) {
        begin_ = it.begin_;
        len_ = it.len_;
        size_ = it.size_;
        ind_ = it.ind_;
        return *this;
    }
    IteratorType3 operator *() {
        return *(begin_ + len_);
    }
    IteratorType2 operator ->() {
        return &**this;
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
    deque_iterator operator +(const int a) const {
        deque_iterator it = *this;
        it.make_step(a);
        return it;
    }
    deque_iterator operator -(const int a) const {
        deque_iterator it = *this;
        it.make_step(-a);
        return it;
    }
    int operator -(const deque_iterator& it) const {
        return ind_ - it.ind_;
    }
    deque_iterator& operator +=(const int a) {
        make_step(a);
        return *this;
    }
    deque_iterator& operator -=(const int a) {
        make_step(-a);
        return *this;
    }
    IteratorType3 operator [](const int a) {
        return *(*this + a);
    }
    bool operator != (const deque_iterator &it) const {
        return !(*this == it);
    }
    bool operator == (const deque_iterator &it) const {
        return (begin_ + len_) == (it.begin_ + it.len_);
    }
    bool operator < (const deque_iterator &it) const {
        return ind_ < it.ind_;
    }
    bool operator > (const deque_iterator &it) const {
        return ind_ > it.ind_;
    }
    bool operator >= (const deque_iterator &it) const {
        return ind_ >= it.ind_;
    }
    bool operator <= (const deque_iterator &it) const {
        return ind_ <= it.ind_;
    }
};/////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class Deque {
    int N_, size_;
    T *a_ = nullptr;
    int begin_, end_;
    void reallocator() {
        T *b = new T [2 * N_];
        for (int j = 0; j < size_; ++j)  {
            b[j] = (*this)[j];
        }
        delete[] a_;
        a_ = b;
        end_ = size_;
        begin_ = 0;
        N_*=2;
    }
    void deletememory() {
        T *b = new T [N_ / 2];
        for (int j = 0; j < size_; ++j)  {
            b[j] = (*this)[j];
        }
        delete[] a_;
        a_ = b;
        N_/=2;
        end_ = size_;
        begin_ = 0;
    }
    int make_move(const int ch,const int a) const {
        return (ch + a + N_) % N_;
    }
public:
    typedef deque_iterator<T, T*, T&> iterator;
    typedef deque_iterator<const T, const T*, const T&> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    Deque() {
        N_ = 8;
        a_ = new T [N_];
        begin_ = 0;
        end_ = 0;
        size_ = 0;
    }
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
    Deque& operator = (const Deque& b) {
        if (a_ == b.a_) {
            return *this;
        }
        N_ = b.N_;
        delete[] a_;
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
        return a_[make_move(begin_, i)];
    }
    T &back() {
        return a_[make_move(end_, -1)];
    }
    T &front() {
        return a_[begin_];
    }
    const T &operator [](const int i) const{
        return a_[make_move(begin_, i)];
    }
    const T &front() const {
        return a_[begin_];
    }
    const T &back() const {
        return a_[make_move(end_, -1)];
    }
    void push_back(const T &a) {
        a_[end_] = a;
        end_ = make_move(end_, 1);
        ++size_;
        if (end_ == begin_) {
            reallocator();
        }
    }
    void push_front(const T &a) {
        begin_ = make_move(begin_, -1);
        a_[begin_] = a;
        ++size_;
        if (end_ == begin_) {
            reallocator();
        }
    }
    void pop_back() {
        --size_;
        end_ = make_move(end_, -1);
        if (size_ < N_ / 3 && N_ / 2 > 8)
            deletememory();
    }
    void pop_front() {
        --size_;
        begin_ = make_move(begin_, 1);
        if (size_ < N_ / 3 && N_ / 2 > 8)
            deletememory();
    }
    int size() const {
        return size_;
    }
    bool empty() const {
        return size_ ? false : true;
    }
    void clear() {
        begin_ = end_ = 0;
        size_ = 0;
        N_ = 8;
    }
    ~Deque() {
        delete[] a_;
    }
    iterator begin() {
        return iterator(a_, begin_, 0, N_);
    }
    const_iterator begin() const {
        return const_iterator(a_, begin_, 0, N_);
    }
    const_iterator cbegin() const {
        return const_iterator(a_, begin_, 0, N_);
    }
    iterator end() {
        return iterator(a_, end_, size_, N_);
    }
    const_iterator end() const {
        return const_iterator(a_, end_, size_, N_);
    }
    const_iterator cend() const {
        return const_iterator(a_, end_, size_, N_);
    }
    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(cend());
    }
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(cend());
    }
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(cbegin());
    }
    const_reverse_iterator crend() const {
        return const_reverse_iterator(cbegin());
    }

};
