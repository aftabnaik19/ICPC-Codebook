// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set =
tree<T, null_type, std::less<T>, rb_tree_tag,
     tree_order_statistics_node_update>;
ordered_set<int> os;
os.insert(5);
os.erase(5);
os.find_by_order(k); // iterator to k-th element (0-indexed)
os.order_of_key(x);  // number of elements < x
template <typename T>
using ordered_multiset_base =
tree<pair<T, int>, null_type, less<pair<T, int>>,
     rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> struct ordered_multiset {
  ordered_multiset_base<T> os;
  int timer = 0;
  void insert(T x) { os.insert({x, timer++}); }
  void erase_one(T x) {
    auto it = os.lower_bound({x, -1});
    if (it != os.end() && it->first == x) os.erase(it);
  }
  int order_of_key(T x) { return os.order_of_key({x, -1}); }
  T find_by_order(int k) {
    return os.find_by_order(k)->first;
  }
  int size() { return (int)os.size(); }
};
