#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set =
tree<T, null_type, std::less<T>, rb_tree_tag,
     tree_order_statistics_node_update>;
ordered_set<int> os;
os.insert(5);
os.erase(5);
// iterator to k-th element (0-indexed)
os.find_by_order(k);
// number of elements < x
os.order_of_key(x);
