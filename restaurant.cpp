#include "main.h"


int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;


class RESTAURANT_Gojo{
	class Tree_BST;
private:
	vector<Tree_BST> areaTable;
public:
	RESTAURANT_Gojo():areaTable(MAXSIZE + 1){}
	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;                
		areaTable[ID].insert(result); 
	}

	void remove_KOKUSEN()
	{
		for(int i = 1; i < MAXSIZE + 1; i++) areaTable[i].remove();
 	}

	void print_LIMITLESS(int number)
	{
		if(number <= 0 || number > MAXSIZE) return; 
		areaTable[number].print();
	}
private:
	class Tree_BST{
		class Node;
	private:
		Node* root;	
		queue<int> queueTime; 
	public:
		Tree_BST():root(nullptr){}

		int size(){
			return queueTime.size();
		}

		Node* insert_recursive(Node* node, int result)
		{
			if(node == nullptr){
				queueTime.push(result);
				return new Node(result);
			}
			if(result < node->result){
				node->left = insert_recursive(node->left,result);
			}
			else if(result >= node->result){
				//cout<<"count"<<endl;
				node->right = insert_recursive(node->right,result);
			}
			
			return node;
		}
		void insert(int result){
			//cout<<"hi";
			root = insert_recursive(root, result);
		}
		Node* remove_recursive(Node* node,int result)
		{	
			if (node == nullptr){
				return nullptr;
			}
			if(result < node->result){
				node->left = remove_recursive(node->left, result);
			} else if (result > node->result){
				node->right = remove_recursive(node->right, result);
			} else {
				if(node->left == nullptr){
					Node* temp = node->right;
					delete node;
					return temp;
				} else if (node->right == nullptr){
					Node* temp = node->left;
					delete node;
					return temp;
				}
				/*Node* temp = node->left;
				while(temp->right != nullptr){
					temp = temp->right;
				}
				node->result = temp->result;
				node->left = remove_recursive(node->left, temp->result);*/
				Node* temp = node->right;
				while(temp->left != nullptr){
					temp = temp->left;
				}
				node->result = temp->result;
				node->right = remove_recursive(node->right,temp->result);
			}
			return node;
 		}
		int CountNode(Node* node)
		{
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}
		unsigned long long permutationFormula(int x, int n)
		{
			unsigned long long result = 1;
        	for (int i = 1; i <= x; ++i) {
            	result *= (n - x + i);
           		result /= i;
        	}
        return result;
		}
		unsigned long long DFS(Node* node)
		{
			if(node == NULL) return 1;
			return DFS(node->left) * DFS(node->right) * permutationFormula(CountNode(node->left), CountNode(node->right)+CountNode(node->left)) % MAXSIZE;
			
		}
		void remove(){
			if(this->size() == 0) return;
			unsigned long long number = DFS(root) % MAXSIZE;
			if(this->size() == 1) return;
			while(number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();			
				queueTime.pop(); 						
				root = remove_recursive(root ,temp);	
				number --;
			}
		}

		string print_recursive(Node* node)
		{
			if(node != NULL){
				print_recursive(node->left);
				cout << node->result << "\n";
				print_recursive(node->right);
			}
		}
		void print(){
			print_recursive(root);
		}
	
	private:
		class Node{
		private:
			int result;
			Node* left;
			Node* right;
			friend class Tree_BST;
		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};
};




class RESTAURANT_Sukuna{
	class Node;
private:
	vector<Node* > areaTable;  
	list<Node* > LRU; 		  
private:
	void ReHeap_down(int index)
	{	
		//cout<<index<<endl;
		int leftChild = index * 2 + 1;
		int rightChild = index * 2 + 2;

		if(leftChild < areaTable.size()){
			int smallest = index;
			if(areaTable[leftChild]->size() < areaTable[smallest]->size()){
				smallest = leftChild;
			}
			if(rightChild < areaTable.size() && areaTable[rightChild]->size() < areaTable[smallest]->size()){
				smallest = rightChild;
			}
			
			if(rightChild < areaTable.size() && areaTable[rightChild]->size() == areaTable[leftChild]->size()){
				int leftFind = 0;
				int rightFind = 0;
				int indexIt = 0;

				for(auto it = LRU.begin(); it != LRU.end(); it++){
					if(areaTable[leftChild]->ID == (*it)->ID){
						leftFind = indexIt;
					}
					if(areaTable[rightChild]->ID == (*it)->ID){
						rightFind = indexIt;
					}
					indexIt++;
				}
				if(leftFind > rightFind){
					smallest = leftChild;
				} else {
					smallest = rightChild;
				}
			}
			if (smallest != index){
				swap(areaTable[index], areaTable[smallest]);
				ReHeap_down(smallest);
			}
			else{
				//cout<<"hello"<<endl;
			if(areaTable[leftChild] != nullptr){
			if(areaTable[leftChild]->size() == areaTable[index]->size() ){
				//cout<<index<<endl;
				int parentFind = 0;
				int childFind = 0;
				int indexIt = 0;

			for(auto it = LRU.begin(); it != LRU.end(); it++){
				
				if(areaTable[index]->ID == (*it)->ID){
					parentFind = indexIt;
				}
				if(areaTable[leftChild]->ID == (*it)->ID){
					childFind = indexIt;
				}
				indexIt++;
			} 

			//cout<<parentFind<<endl;
			//cout<<childFind<<endl;
			if(parentFind < childFind){
					//cout<<"test2";
					swap(areaTable[index], areaTable[leftChild]);
					ReHeap_down(leftChild);
				}
			
			}
			}
			if(areaTable[rightChild] != nullptr){
			if(areaTable[rightChild]->size() == areaTable[index]->size()){
				
				int parentFind = 0;
				int childFind = 0;
				int indexIt = 0;

			for(auto it = LRU.begin(); it != LRU.end(); it++){
				if(areaTable[index]->ID == (*it)->ID){
					parentFind = indexIt;
				}
				if(areaTable[leftChild]->ID == (*it)->ID){
					childFind = indexIt;
				}
				indexIt++;
			} 
				if(parentFind < childFind){
					swap(areaTable[index], areaTable[rightChild]);
					ReHeap_down(rightChild);
				}
			}
			}
		} 
		}
		
	}

	void ReHeap_up(int index)
	{
		if(index == 0){
			return;
		}
		int parent = (index - 1) / 2;

		if(areaTable[index]->size() < areaTable[parent]->size()){
			swap(areaTable[index], areaTable[parent]);
			ReHeap_up(parent);
		} else if (areaTable[index]->size() == areaTable[parent]->size()){
			//cout<<"count"<<endl;
			int parentFind = 0;
			int indexFind = 0;
			int indexIt = 0;

			for(auto it = LRU.begin(); it != LRU.end(); it++){
				if(areaTable[parent]->ID == (*it)->ID){
					parentFind = indexIt;
				}
				if(areaTable[index]->ID == (*it)->ID){
					indexFind = indexIt;
				}
				indexIt++;
			}
			if(parentFind < indexFind){
				swap(areaTable[index],areaTable[parent]);
				ReHeap_up(parent);
			}
		}

	
	}

	void moveTop(Node* node)
	{	
		auto it = find(LRU.begin(), LRU.end(), node);
		if(it != LRU.end()){
			LRU.erase(it);
		}
		LRU.push_front(node);
	}

    void removeNode(Node* node)
	{
		 auto it = find(LRU.begin(), LRU.end(), node);
    	if (it != LRU.end()) {	
        		LRU.erase(it);
    		}
 
	}
public:
	RESTAURANT_Sukuna(){}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		int index = -1;
		for(int i = 0; i < areaTable.size(); i++){
			if(areaTable[i]->ID == ID){
				index = i;
				break;
			}
		}


		if(index == -1){
			areaTable.push_back(new Node(ID));
			index = areaTable.size() - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_up(index);
			
			//cout<<areaTable[1]->ID<<endl;
			//cout<<areaTable[2]->ID<<endl;
		}
	
		else 
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_down(index);
		}
	}

	void remove_KEITEIKEN(int number)
	{
		if(areaTable.size() <= 0) return;
		int numberRemove = number;
		while(areaTable.size() != 0 && number != 0){
			cout << "remove customers in the area ID = " << areaTable[0]->ID << ": ";
			areaTable[0]->remove(numberRemove);
			if(areaTable[0]->size() == 0)
			{
				swap(areaTable[0], areaTable[areaTable.size() - 1]);
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];
				areaTable.pop_back();
			}
			this->ReHeap_down(0);
			number --;
		}
 	}
	void print_pre_order(int index, int number)
	{	
		if(index >= this->areaTable.size()) return;

		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_LIMITLESS(int number)
	{	
		print_pre_order(0, number);
	}

private:
	class Node{
	private:
		int ID;					
		list<int> head; 		
		friend class RESTAURANT_Sukuna;
	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		
		void insert(int result){head.push_front(result);}
		
		void remove(int number)
		{
			if(head.empty()){
				return;
			}
			for(int i = 0; i < number && !head.empty(); i++){
				cout << head.back() << " ";
				head.pop_back();
			}
			cout << "\n";
			
		}
	
		void print(int number)
		{
			cout << "customers in the area ID = " << ID << ": ";
			for(list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				cout << ID << "-" << *it  << "\n";
			}
			
		}

	};

};

class HuffTree_AVL{
	class Node;
private:
	Node* root = nullptr;
public:
	int encode(string name){
		vector<pair<char, int>> freq = this->string_Processing(name);
		Node* huffmanTreeRoot = buildHuff(freq);
		return encodingHuffman(huffmanTreeRoot,name);
	}
	//void print(){}

	Node* rotateRight(Node* x) {

    Node* y = x->left;
    Node* T2 = y->right;

    y->right = x;
    x->left = T2;
    
    x->height = max(x->left ? x->left->height : 0, x->right ? x->right->height : 0) + 1;
    y->height = max(y->left ? y->left->height : 0, y->right ? y->right->height : 0) + 1;
    
    return y;
}
Node* rotateLeft(Node* y) {
   
    Node* x = y->right;
    Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(y->left ? y->left->height : 0, y->right ? y->right->height : 0) + 1;
    x->height = max(x->left ? x->left->height : 0, x->right ? x->right->height : 0) + 1;

    return x;
}
	int getBalanceFactor(Node* node) {
    return (node ? (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0) : 0);
}
	Node* balanceNode(Node* node, int& count) {
    if (!node) {
        return nullptr;
    }

    if (count >= 3) {
        return node;
    }

    if (getBalanceFactor(node) > 1) {
       // cout<<getBalanceFactor(node);
        if (getBalanceFactor(node->left) >= 0) {
            count++;
            //cout<<"right<"<<count;
            node = rotateRight(node);
        } else {
            count ++;
            node->left = rotateLeft(node->left);
            if(count < 3){
                count ++;
                node = rotateRight(node);}
        }
    } else if (getBalanceFactor(node) < -1) {
        //cout<<1;
        if (getBalanceFactor(node->right) <= 0) {
            count++;
 
            node = rotateLeft(node);
        } else {
            count ++;
            node->right = rotateRight(node->right);
            if(count < 3){
                count ++;
            node =  rotateLeft(node);}
        }
    }
    if(count < 3){
        node->left = balanceNode(node->left,count);
        node->right = balanceNode(node->right,count);
    }

    return node;
}
	Node* balanceTree(Node* node, int& count) {
    //cout<<node->weight<<endl;
    if (!node || count >= 3) {
        return node;
    }

    node->left = balanceTree(node->left, count);
    node->right = balanceTree(node->right, count);

    node = balanceNode(node, count);
    //if(node->weight == 4){ cout<< "co";}
    return node;
}
	Node* buildHuff(vector<pair<char, int>> freq)
{
    vector<Node*> build;
    for(const auto& pair : freq){
        build.push_back(new Node(pair.second, pair.first));
    }
   


    while(build.size() > 1)
    {
 
        int count = 0;

        Node* smallest1 = build.back();
        build.pop_back();

        Node* smallest2 = build.back();
        build.pop_back();
        
        Node* newNode = new Node(smallest1->weight + smallest2->weight, '\0', smallest1, smallest2);

        newNode->height = max(newNode->left ? newNode->left->height : 0, newNode->right ? newNode->right->height : 0) + 1;

        newNode = balanceTree(newNode, count);

        auto it = lower_bound(build.begin(), build.end(), newNode, [](Node* a, Node* b) {
            return a->weight > b->weight;
        });
        build.insert(it, newNode);
        
    }	
    return build[0];
}
	vector<pair<char, int>> string_Processing(string& name)
{
     unordered_map<char, int> freq_prev;
    for (char ch : name) {
        freq_prev[ch]++;
    }
    string temp2;
    for (char& ch : name) {
        char temp = ch;
        if(ch >= 'a' && ch <= 'z'){
            temp = 'a' + (ch - 'a' + freq_prev[(int)ch]) % 26;
        } else if(ch >= 'A' && ch <= 'Z'){
            temp = 'A' + (ch - 'A' + freq_prev[(int)ch]) % 26;
        }
        ch = temp;
        temp2.push_back(temp);
    }

    unordered_map<char, int> freq_prev2;
    for (char ch : temp2) {
        freq_prev2[ch]++;
    }

    vector<pair<char, int>> freq(freq_prev2.begin(), freq_prev2.end());

     sort(freq.begin(), freq.end(),[](const pair<char, int>& a, const pair<char, int>& b)
     {
        if (a.second != b.second) {
            return a.second > b.second;
        } else {
            if (isupper(a.first) && islower(b.first)) {
                return true;
            } else if (islower(a.first) && isupper(b.first)) {
                return false;
            } else {
                return a.first > b.first;
            }
        }
    });
    return freq;
}
string getLast10Bits(const string& binaryString)
{
    string reversedBinaryString = binaryString;
    reverse(reversedBinaryString.begin(), reversedBinaryString.end());

    int length = reversedBinaryString.length();

    if (length <= 10) {
        return reversedBinaryString;
    }

    return reversedBinaryString.substr(0, 10);
}
int binaryToDecimal(const string& binaryString) {
    
    bitset<64> bits(binaryString);
    return static_cast<int>(bits.to_ulong());
}
void encoding_rec(vector<string>& encoding, Node* node, string s = "")
{
    if(node == nullptr){
        return;
    }
    if(node->isChar()){
        encoding[node->c] = s;
    }
    encoding_rec(encoding, node->left, s + "0");
    encoding_rec(encoding, node->right, s + "1");
}
int encodingHuffman(Node * root,string nameCaesar)
{
    if(root->left == nullptr && root->right == nullptr) return 0;

    vector<string> encoding(256, "");
    encoding_rec(encoding, root);

    int result = 0;
    string binaryString = "";
    for(char& c : nameCaesar){
        binaryString += encoding[c];
    }
    string last10Bits = getLast10Bits(binaryString);

    result = binaryToDecimal(last10Bits);
    return result;
}
	
	void print_recursive(Node* node){
		if(node == nullptr) return;
		print_recursive(node->left);
		if(node->c == '\0') cout << node->weight << "\n";
		else cout << node->c << "\n";
		print_recursive(node->right);
	}
	void print_HAND(){print_recursive(root);}
	private:
	class Node{
	public:
		int weight;
		char c;
		int height;
		Node* left;
		Node* right;
		friend class HuffTree_AVL;
	public:
		Node(int weight, char c = '\0', Node* left = nullptr, Node* right = nullptr)
		:weight(weight), c(c), left(left), right(right) {}
		bool isChar() const {return c != '\0';}
};
};

class JJK_RESTAURANT_OPERATIONS
{
private:
	HuffTree_AVL Customers_arrive;
	RESTAURANT_Gojo hash;
	RESTAURANT_Sukuna heap;
	
public:

	void LAPSE(string name)
	{
		
		int result = Customers_arrive.encode(name);

		if(result == -1) return;

		if(result % 2 == 1) hash.insertAreaTable(result);

		else{
			heap.insertAreaTable(result);
		}
	}	


	void KOKUSEN(){hash.remove_KOKUSEN();}
	void LIMITLESS(int num){hash.print_LIMITLESS(num);}
	
	
	void KEITEIKEN(int num){heap.remove_KEITEIKEN(num);}
	void CLEAVE(int num){heap.print_LIMITLESS(num);}

	void HAND(){Customers_arrive.print_HAND();}

	

	
};


