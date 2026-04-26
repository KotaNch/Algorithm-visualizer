#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>
#include <bits/stdc++.h>
#include <queue>  

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;



void clearScreen(){
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void sleepMs(int ms){
this_thread::sleep_for(chrono::milliseconds(ms));

}
int delay = 500;





void visualize(const vector<int>& arr, int maxHeight, const string& message = ""){
    clearScreen();
    if (!message.empty()){
        cout << message << endl;
    }
    cout << endl;

    for (int lvl = maxHeight; lvl >=1;lvl--){
        for (int val : arr){
            if (val >= lvl)
                cout << " ██ ";
            else
                cout << "    ";
        }
        cout << endl;
    }

    cout << " " << string(arr.size() * 4, '-') << endl;

    for (size_t i = 0; i < arr.size(); i++){
        cout << "  " << i << " ";
    }
    cout << endl << endl;

    cout << "Values: ";
    for (int val:arr) cout << val << " ";
    cout << endl;
    sleepMs(delay);
}
/////////////////////////////////////////////////////////////
//                  SORTS
/////////////////////////////////////////////////////////////
void bubbleSort(vector<int> arr, int maxHeight){
    visualize(arr,maxHeight,"Bubble sort: start");
    int n = arr.size()-1;
    for (int i= 0; i<n;i++){
        for (int j = 0; j < n - i; j++){
            if (arr[j] > arr[j+1]){
                swap(arr[j],arr[j+1]);
                visualize(arr,maxHeight, "Bobble sort: swap " + to_string(arr[j+1]) + " and " + to_string(arr[j]));
            }
        }
    }
    visualize(arr,maxHeight,"Bubble sort: end");
}

void selectionSort(vector<int> arr, int maxHeight){
    visualize(arr, maxHeight, "Selection sort: start");
    int n = arr.size();
    for (int i = 0;i<n-1;i++){
        int minIdx = i;
        for(int j = i +1;j<n;j++){
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i){
            swap(arr[i],arr[minIdx]);
            visualize(arr,maxHeight,"Selection sort: swap " + to_string(arr[i]) + " to " + to_string(i));
        }
    }
    visualize(arr, maxHeight, "Selection sort: end");
    
}

void insertSort(vector<int> arr, int maxHeight){
    visualize(arr,maxHeight,"Insertion sort: start");
    int n = arr.size();
    for(int i = 1; i<n;i++){
        int k = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] >k){
            arr[j+1] = arr[j];
            j--;
            visualize(arr,maxHeight,"Insertion sort: spread");

        }
        arr[j+1] = k;
        visualize(arr,maxHeight, "Insertion sort: inserted" + to_string(k));
        
        
    }
    visualize(arr,maxHeight,"Insertion sort: end");
    
}

int partition(vector<int> &vec, int low, int high, int maxHeight){
    int pivot = vec[high];
    int i = (low-1);
    
    for (int j = low; j <= high -1; j++){
        if (vec[j] <= pivot){
            i++;
            swap(vec[i],vec[j]);
            visualize(vec, maxHeight,"Quick sort: partition (pivot=" + to_string(pivot) + ") swap " + to_string(vec[i]) + " and " + to_string(vec[j]) );
        }
    }
    swap(vec[i+1], vec[high]);
    visualize(vec, maxHeight, "Quick sort: partition — pivot placed at position " + to_string(i+1));

    
    return (i+1);
}



void quickSort(vector<int> &arr, int low,int high, int maxHeight){
    if (low < high){
        int pi = partition(arr, low, high, maxHeight);
        quickSort(arr, low, pi -1, maxHeight);
        quickSort(arr,pi +1, high,maxHeight);
    }
}

void quickSortWrapper(vector<int> arr, int maxHeight){
    visualize(arr, maxHeight, "Quick sort: start");
    quickSort(arr,0,arr.size()-1, maxHeight);
    visualize(arr, maxHeight,"Quick sort: end" );
}
void twodirectionalBubbleSort(vector<int> arr, int maxHeight){
    visualize(arr,maxHeight,"Twodirectional Bubble sort: start");
    int n = arr.size()-1;
    for (int i= 0; i<n;i++){
        for (int j = 0; j < n - i; j++){
            if (arr[j] > arr[j+1]){
                swap(arr[j],arr[j+1]);
                visualize(arr,maxHeight, "Twodirectional Bobble sort: swap " + to_string(arr[j+1]) + " and " + to_string(arr[j]));
            }
        }
    }
    visualize(arr,maxHeight,"Twodirectional Bubble sort: end");
}

///////////////////////////////////////////////////////
//                  TREES
///////////////////////////////////////////////////////

struct TreeNode{
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val): value(val), left(nullptr), right(nullptr) {}
};


void printTree(TreeNode* root,int highlight, int space = 0, int indent = 4){
    if (root == nullptr) return;
    space += indent;
    printTree(root->right,highlight,space);
    cout << endl;
    for (int i = indent; i <space; i++) cout << " ";
    if(root->value == highlight)cout << "(" << root -> value << ")" << endl;
    else cout << "[" << root -> value << "]" << endl;
    printTree(root->left,highlight,space);
    
}

void bfs(TreeNode* root) {
    if (!root) return; 
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()){
        TreeNode* cur = q.front(); q.pop();
        clearScreen();
        cout <<  "BFS: visiting node " << cur->value << endl << endl;
        printTree(root, cur->value);
        sleepMs(delay);
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}



void dfs(TreeNode* node, TreeNode* root){
    if (!node) return;
    clearScreen();
    cout << "DFS: visiting note " << node->value<<endl;
    sleepMs(delay);
    dfs(node->left, root);
    dfs(node->right,root);
}

TreeNode* generateRandomTreeDepth(int maxDepth, int maxValue, double probability = 0.7){
    if (maxDepth == 0) return nullptr;
    if ((double)rand()/ RAND_MAX > probability) return nullptr;
    TreeNode* node = new TreeNode(rand()% maxValue + 1);
    node ->left = generateRandomTreeDepth(maxDepth-1,maxValue,probability);

    node ->right = generateRandomTreeDepth(maxDepth-1,maxValue,probability);
    return node;
}

TreeNode* insertRandom(TreeNode* root,int value){
    if (!root) return  new TreeNode(value);
    if (rand()% 2 == 0) root ->left = insertRandom(root->left, value);
    else root->right = insertRandom(root->right,value);
    return root;
}

TreeNode* generateRandomTreeNodes(int nodeCount, int maxValue){
    TreeNode* root = nullptr;
    for (int i = 0; i < nodeCount; i++){
        int val = rand() % maxValue  +1;
        root = insertRandom(root, val);

    }
    return root;
}


void deleteTree(TreeNode* root){
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
int main(){
    srand(time(nullptr));
    cout << "=== Visualizing Sorting Algorithms in the Terminal (C++) ===" << endl;

    cout << "\nAvailable algorithms:\n";
    cout << "1. Bubble sort \n";
    cout << "2. Selection sort \n";
    cout << "3. Insertion sort \n";
    cout << "4. Quick sort\n";
    cout << "5. BFS on binary tree\n";
    cout << "6. DFS on binary tree\n";


    int algoChoice;
    while (true){
        cout << "Enter the algorithm number (1-6):";
        cin >> algoChoice;
        if (cin.fail() || algoChoice<1 || algoChoice >6){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Please enter a number between 1 and 4.\n";
        }else break;
    }


    int n;
    if (algoChoice <= 4){
    while (true){
        cout <<"Enter the number of items (5-25): ";
        cin >> n;
        if (cin.fail() || n<5 || n>25){
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "Error: number must be between 5 and 20.\n";
        }else break;
    }
    int maxHeight;
    while (true){
        cout << "Enter the maximum height of columns (e.g. 10): ";
        cin >> maxHeight;
        if (cin.fail() || maxHeight < 1){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Height must be positive.\n";
        }else break;
    }
   
    while (true){
        cout << "Enter the delay in milliseconds ";
        cin >> delay;
        if (cin.fail() || delay <0){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: delay must be positive.\n";
        }else break;
    }

    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        arr[i] = rand() % maxHeight +1;
    }
    cout << "\nSource array: ";
    for (int v:arr) cout << v << " ";
    cout << endl;
    cout << "Press Enter to start sorting...";
    cin.ignore();
    cin.get();

    switch (algoChoice){
        case 1:
            bubbleSort(arr,maxHeight);
            break;
    
    case 2:
        selectionSort(arr,maxHeight);
        break;
    case 3:
    insertSort(arr, maxHeight);
    break;
    case 4:
    quickSortWrapper(arr,maxHeight);
    break;
    }
}
    else{
        int treeType, depthOrNodes,maxValue;
        cout << "\nTree generation:\n";
        cout << "1. By depth (random shape)\n";
        cout << "1. By number of nodes\n";
        cin >> treeType;

        if (treeType ==1){
            cout << "Max depth (2-5): ";
            cin >> depthOrNodes;
            cout << "Max value (10-50): ";
            cin >> maxValue;
            cout << "Probability of node (0.5-1.0): ";
            double prob;
            cin >> prob;
            TreeNode* root = generateRandomTreeDepth(depthOrNodes,maxValue,prob);
            if (!root) { cout << "Empty tree!\n"; return 0;}
            cout <<  "\nGenerated tree:\n";
            printTree(root, -1);
            cout << "\nPress Enter to start " << (algoChoice == 5 ? "BFS": "DFS") << "...";
            cin.ignore();
            cin.get();
            if (algoChoice == 5) bfs(root);
            else dfs(root,root);
            deleteTree(root);
        }
        else{
            cout << "Number of nodes (5-15) ";
            cin >> depthOrNodes;
            cout << "Max value (10-50): "; cin >> maxValue;
            TreeNode* root = generateRandomTreeNodes(depthOrNodes,maxValue);
            cout <<  "\nGenerated tree:\n";
            printTree(root, -1);
            cout << "\nPress Enter to start " << (algoChoice == 5 ? "BFS": "DFS") << "...";
            cin.ignore();
            cin.get();
            if (algoChoice == 5) bfs(root);
            else dfs(root,root);
            deleteTree(root);
        }
    }
    cout << "\nPress Enter to exit...";
    cin.get();
    return 0;
 
}
          



 
                 