#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int main() {
    shared_ptr<vector<int>> sp(new vector<int>({1,2,3}));
    cout << "before weak ptr, shared_ptr's reference count: " << sp.use_count() << endl;
    weak_ptr<vector<int>> wp = sp;
    cout << "after weak ptr, shared_ptr's reference count: " << sp.use_count() << endl;
    shared_ptr<vector<int>> sp_copy = wp.lock();
    cout << "primary shared_ptr object address: " << &sp << ", size: " << sizeof(sp) << endl;
    cout << "primary weak_ptr object address: " << &wp << ", size: " << sizeof(wp) << endl;
    cout << "lock() generated shared_ptr object address: " << &sp_copy << ", size: " << sizeof(sp_copy) << endl;
    cout << "after weak ptr.lock(), shared_ptr's reference count: " << sp.use_count() << endl;

    cout << "before shared_ptr operation: vector size: " << sp->size() << endl;
    sp->push_back(4);
    cout << "after shared_ptr operation: vector size: " << sp->size() << endl;

    cout << "before weak_ptr operation: vector size: " << sp->size() << endl;
    wp.lock()->push_back(5); // wp不可直接操作
    cout << "after  weak_ptr operation: vector size: " << sp->size() << endl;

    cout << "before reset, weak_ptr's expire: " << wp.expired() << endl;
    sp.reset();
    sp_copy.reset();
    cout << "before reset, weak_ptr's expire: " << wp.expired() << endl;

}