#include "function.h"

    /*MAX_HEAP():Count(0){}
    virtual ~MAX_HEAP() {}
    virtual void PUSH(const int &) = 0;
    virtual int MAX() const = 0;
    virtual int POP() = 0;*/

Array_MAX_HEAP::Array_MAX_HEAP() {

}

void Array_MAX_HEAP::PUSH(const int &x) { //root node is stored at index 1.
    array[++Count] = x;
    //cout << x << '\n';
    int idx = Count, tmp;
    while(idx > 1 && array[idx] > array[idx/2]) {
        //cout << array[idx] << " " << array[idx/2] << '\n';
        tmp = array[idx];
        array[idx] = array[idx/2];
        array[idx/2] = tmp;
        idx /= 2;
    }
}

int Array_MAX_HEAP::MAX() const {
    if(!Count)
        return -1;
    /*for(int i = 1; i <= Count; i++){
        cout << "[" << i << "]" << " = " << array[i] << '\n';
    }*/
    return array[1];
}

int Array_MAX_HEAP::POP() {
    if(!Count)
        return -1;
    int result = array[1];
    array[1] = array[Count--];
    int idx = 1, tmp, child_idx;
    while(1) {
        if(Count < 2*idx)
            break;
        if(Count == 2*idx || array[2*idx] > array[2*idx+1])
            child_idx = 2*idx;
        else
            child_idx = 2*idx+1;

        if(array[child_idx] > array[idx]) {
            tmp = array[idx];
            array[idx] = array[child_idx];
            array[child_idx] = tmp;
            idx = child_idx;
        }
        else
            break;
    }
    return result;
}

List_MAX_HEAP::List_MAX_HEAP() {
    root = NULL;
}

void List_MAX_HEAP::PUSH(const int &x) {
    if(!Count) {
        root = new ListNode(x);
        Count++;
        return;
    }

    ListNode *ptr = findparent(++Count, root), *child;
    //cout << "parent is " << ptr->value << '\n';
    if(ptr->left == NULL) {
        ptr->left = new ListNode(x);
        ptr->left->parent = ptr;
        child = ptr->left;
    }
    else {
        ptr->right = new ListNode(x);
        ptr->right->parent = ptr;
        child = ptr->right;
    }
    int tmp;
    while(1) {
        if(child->parent == NULL)
            break;
        if(child->parent->value < child->value) {
            tmp = child->value;
            child->value = child->parent->value;
            child->parent->value = tmp;
            child = child->parent;
        }
        else
            break;
    }
}

int List_MAX_HEAP::MAX() const {
    if(!Count)
        return -1;
    return root->value;
}
int List_MAX_HEAP::POP() {
    if(!Count)
        return -1;

    int result = root->value, tmp;
    ListNode *ptr, *child;
    if(Count == 1) {
        delete root;
        root = NULL;
    }
    else {
        ptr = findparent(Count, root);
        if(ptr->right != NULL) {
            root->value = ptr->right->value;
            delete ptr->right;
            ptr->right = NULL;
        }
        else {
            root->value = ptr->left->value;
            delete ptr->left;
            ptr->left = NULL;
        }
        ptr = root;
        while(1) {
            if(ptr->left == NULL)
                break;
            if(ptr->right == NULL || ptr->left->value > ptr->right->value)
                child = ptr->left;
            else
                child = ptr->right;
            if(ptr->value < child->value) {
                tmp = ptr->value;
                ptr->value = child->value;
                child->value = tmp;
                ptr = child;
            }
            else
                break;
        }
    }
    Count--;
    return result;
}
void List_MAX_HEAP::deleteTree(ListNode* root) {
    if(root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}
