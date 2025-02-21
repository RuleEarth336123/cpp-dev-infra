#include <bits/stdc++.h>
#include <atomic>

template<typename T>
class shared_ptr
{
    using namespace std;
private:
    T* m_data;
    atomic<int>* m_count;
public:
    shared_ptr() : m_data(nullptr), m_count(new atomic<int>(0)) { }
    shared_ptr(T* data) : m_data(data), m_count(new atomic<int>(1)) {
        if(m_data != nullptr){
            (*m_count)++;
        }
    }
    shared_ptr(shared_ptr& other) : m_data(other.m_data), m_count(other.m_count) {
        if(m_data != nullptr){
            (*m_count)++;
        }
    }
    shared_ptr(shared_ptr&& other) : m_data(other.m_data), m_count(other.m_count) {
        other.m_data = nullptr;
        other.m_count = nullptr;
    }
    shared_ptr& operator = (const shared_ptr<T>& other) {
        if(this == &other){
            return *this;
        }
        if(m_data != nullptr && --(*m_count) == 0) {
            delete m_data;
            delete m_count;
        }
        m_data = other.m_data;
        m_count = other.m_count;
        (*m_count)++;
        return *this;
    }
    shared_ptr& operator = (shared_ptr<T>&& other) noexcept {
        if(this == &other){
            return *this;
        }
        if(m_data != nullptr && --(*m_count) == 0) {
            delete m_data;
            delete m_count;
        }
        m_data = other.m_data;
        m_count = other.m_count;
        other.m_count = nullptr;
        other.m_data = nullptr;
        (*m_count)++;
        return *this;
    }
    ~shared_ptr() {
        if(m_data != nullptr && --(*m_count) == 0) {
            delete m_data;
            delete m_count;
        }
    }

    T* operator -> (){
        return m_data;
    }
    T& operator * (){
        return *m_data;
    }
    
    T& operator [] (int i) const{
        return m_data[i];
    }

    T* get() const{
        return m_data;
    }

    T* release(){
        auto data = m_data;
        m_data = nullptr;
        return data;
    }
    void reset(T* data = nullptr){
        if(m_data == data){
            return;
        }
        if(m_data == nullptr){
            m_data = data;
            m_count = new atomic<int>(1);
            return;
        }
        m_data = data;
    }
    int use_count() const{
        if(m_data == nullptr){
            return 0;
        }
        return (*m_count);
    }

    bool unique() const{
        if(m_data == nullptr){
            return false;
        }
        return (*m_count) == 1;
    }

    void swap(shared_ptr<T>& other){
        auto data = m_data;
        auto count = m_count;

        m_data = other.m_data;
        m_count = other.m_count;

        other.m_data = data;
        other.m_count = count;
    }
};

