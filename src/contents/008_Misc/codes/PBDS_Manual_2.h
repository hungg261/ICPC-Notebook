/* Hash: 7FAEB7C7 */
ordered_set<int> st;

// 1. Insert elements normally
st.insert(1); st.insert(4); st.insert(8);

// 2. find_by_order(k): Returns an iterator to the k-th smallest element (0-indexed)
auto it = st.find_by_order(1); // Points to '4'
int val = *it;

// 3. order_of_key(x): Returns the number of elements strictly smaller than x
int cnt = st.order_of_key(5); // Returns 2 (elements 1 and 4 are smaller)

// 4. Erase element in ordered_multiset (MUST use iterator to avoid removing all duplicates)
ordered_multiset<int> mst;
mst.insert(4); mst.insert(4);
mst.erase(mst.find_by_order(mst.order_of_key(4))); // Safely erases only one '4'