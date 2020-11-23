// https://practice.geeksforgeeks.org/problems/maximum-path-sum/1

/*
    maxPathSum (time complexity: O(n), space complexity: O(1))
        Calculate at the same time the maximum path of the two immediate
        subnodes and the maximum maxPathSum subsolutions. Compare the
        subsolutions with the current solution, which is simply the sum of
        the two maximum paths plus the current node value.
*/

pair<int, int> maxPathSum_(Node* root) {
    if(root == nullptr)
        return make_pair(INT_MIN, INT_MIN);
    else if(root->left == nullptr && root->right == nullptr)
        return make_pair(INT_MIN, root->data);
    else if(root->left == nullptr && root->right != nullptr)
        return make_pair(INT_MIN, root->data + maxPathSum_(root->right).second);
    else if(root->left != nullptr && root->right == nullptr)
        return make_pair(INT_MIN, root->data + maxPathSum_(root->left).second);
    else {
        auto left  = maxPathSum_(root->left);
        auto right = maxPathSum_(root->right);
        return make_pair(max(max(left.first, right.first),
                             root->data + left.second + right.second),
                         root->data + max(left.second, right.second));
    }
}

int maxPathSum(Node* root) {
    return maxPathSum_(root).first;
}
