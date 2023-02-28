
/*
						**************************************************

									STORE   MANAGEMENT SYSTEM


					**********************************************************



							(		GROUP  MEMBERS   )

						>>>>>>>>		Tallhah-Rajpoot





						  *****************************************
						  ALL FOUR DATA STRUCTURES ARE IMPLEMENTED
						  *****************************************
						  NO USE OF ANY PREDEFINED DATA STRUCTURE LIBRARY
						  *********************************************
						  ALL ARE SELF IMPLEMENTED DATA STRUCTURE
						  **************************************************

*/

/////////////////////////////
#include<iostream>// IOSTREAM LIBARAY
#include<string>   // STRING LIBARRY
using namespace std; // COUT/CIN STANDARS
//------------<< Node Class >>------------
//------>> This Class is the building block of the tree, which is going
//to store the provided data in the system. The node have all the data members
//that can be provided to store 
class Node
{
public:
	//------------<< Data Members >>------------
	string Name;//This is used for Storing Values in objects
	int price;
	int quantity;

	///////////////////////////////////////////
//----->> Pointer to left child
	Node* Left;
	//----->> Pointer to right child
	Node* Right;
	//------------<< Constructor >>------------
	//This will initialize all the data members with there default values
	Node();
};
/////////////////////////////////////
//-----<< AVL Tree >>------
/////////////////////////////////////
//This class is the main class,means all the functionality and the operations 
//that are to be performed by the respective user of the program are in this class
class AVL
{
private:
	/////////////////////////////
	//------------<< Data Members >>------------
	//This Pointer will act as Root, means this will act as the base address
	//holder
	Node* Root;
public:
	//////////////////////////////
	//------>> Member Methods
	/////////////////////////////
	//------>> Insertion
	//This function will Insert the Values in thee tree
	bool Insert(string Info, int price, int quantity);
	/////////////////////////////
	//-------->> This function will check whether data exist in 
	//the tree or not. Also If the match exist it will call last function
	//in the series of function calls for deletions
	void GetNode(string Key, Node*& ProvidedNode);
	//-------->> This function will take the node and after managing the 
	//links, it will delete the node from the tree
	void MakeDeletion(Node*& ProvidedNode);

	//------>> Search
	//This function will Search the provided data in the tree
	Node* SearchNode(string InfoProvided);
	/////////////////////////////
	/////////////////////////////
	//------>> Delete
	//This function will delete the node from the tree
	void DeleteNode(string Key);
	//-------->> This function will check whether data exist in 
	//the tree or not. Also If the match exist it will call last function
	//in the series of function calls for deletions
	////------>> Inorder
	////This function will traverse the tree in Left Root Right Order<inorder>
	void InOrder(Node* ProvidedNode);
	/////////////////////////////
	//------>> Height
	//This function will Calculate the height of the tree
	int TreeHeight(Node* ProvideNode);
	/////////////////////////////
	//------>> TreeNodes
	//This function will Calculate the Nodes in the Tree
	int TreeNodes();
	void NodeCounter(Node* ProvidedNode, int& Count);
	/////////////////////////////
	//------>> Leaf Node Count
	//This function will Calculate the number of leaf nodes in the tree
	int LeafCounter(Node* ProvideNode);
	/////////////////////////////
	//------>> Node Level
	//This function will Calculate Level of Node in the tree
	int LevelofNode(string Info);
	/////////////////////////////////
	//------>> Auxiliary Functions 
	////////////////////////////////
	//------>> Constructor
	//This function will initialize the tree by making the root null
	AVL();
	/////////////////////////////
	//------>> Balancing Factor
	//This function will Calculate the Balancing factor for tree
	int BalanceFactor(Node* ProvidedNode);
	/////////////////////////////
	//------>> Right Right Rotation
	//This function will Rotate towards left side to balance
	void RightRotate(Node*& ProvidedNode);
	/////////////////////////////
	//------>> Left Left Rotation
	//This function will Rotate towards right side to balance
	void LeftRotate(Node*& ProvidedNode);
	/////////////////////////////////
	//------>> Balance Checker
	//This function will maintain the balance of Tree
	void BalanceIt(Node*& ProvidedNode);
	/////////////////////////////
	//------>> Display
	//This function will traverse the tree Print it On Console
	void Display();
	/////////////////////////////
	//------>> GetRoot
	//This function will return the address of root pointer
	Node* GetRoot();
	/////////////////////////////
	//------>> SetRoot
	//This function will the address to root pointer
	void SetRoot(Node* Paased);
	/////////////////////////////
	//------>> Destructor
	//This function will free all the memory occupied by tree
	~AVL();
	/////////////////////////////
	//------>> Sub Ordinate for Destructor
	//This function will free all the memory occupied by tree
	void FreeNodes(Node* ProvidedNode);
};
//This will initialize all the data members with there default values
Node::Node()
{
	Name = "";
	Left = Right = NULL;
}
/////////////////////////////////////
//-----<< AVLTree >>------
////////////////////////////////////
//------>> Insertion
bool AVL::Insert(string Info, int price, int qty)
{
	Node* NewNode = new Node();//Creating New Node
	bool AlreadyExist = false;
	NewNode->Name = Info;//Setting it Data
	NewNode->price = price;//Setting it Data
	NewNode->quantity = qty;//Setting it Data

	if (!Root)//If the Node is the Very First
		//Insert it at Node
	{
		Root = NewNode;
		return true;
	}
	else
	{
		Node* CurrentNode = Root;
		//Get the Right Position for the Data
		//If it is greater than root in right subtree
		//else in left subtree
		while (true)
		{
			if (Info < CurrentNode->Name)//checking condition
			{
				if (CurrentNode->Left)//if there exist a child
				{
					CurrentNode = CurrentNode->Left;//moving forward
				}
				else
				{
					CurrentNode->Left = NewNode;//Placing the Node
					AlreadyExist = false;
					break;
				}
			}
			else if (Info > CurrentNode->Name)//Checking the condition
			{
				if (CurrentNode->Right)//if there exist a child
				{
					CurrentNode = CurrentNode->Right;//moving forward
				}
				else
				{
					CurrentNode->Right = NewNode;//Placing the Node
					AlreadyExist = false;
					break;
				}
			}
			//if Duplication is taking place no insertion takes place
			else
			{
				AlreadyExist = true;
				break;
			}
		}
	}
	if (AlreadyExist)//if insert didn't occured not need to
		//balance the tree
	{
		return false;
	}
	else
		//maintain the balance
	{
		BalanceIt(Root);
		return true;
	}
}
//------>> Inorder
void AVL::InOrder(Node* ProvidedNode)
{
	if (ProvidedNode)
	{
		InOrder(ProvidedNode->Left);//left Most child then move backward
		cout << "  ==>     product name is : " << ProvidedNode->Name << "\t::  price is : " << ProvidedNode->price << "\t::  quantity is : " << ProvidedNode->quantity << endl;
		InOrder(ProvidedNode->Right);
	}
}
///////////////////////////////
/////////////////////////////
//------>> Height
int AVL::TreeHeight(Node* ProvideNode)
{
	int LeftHeight, RightHeight;
	if (!ProvideNode)
	{
		//Base Condition
		return -1;
	}
	else
	{
		LeftHeight = TreeHeight(ProvideNode->Left);//getting left subtree height
		RightHeight = TreeHeight(ProvideNode->Right);//getting right subtree height
		if (LeftHeight > RightHeight)//if left subtree has more height than right
			//then the tree height will be the higher and vice versa
		{
			return LeftHeight + 1;
		}
		else
		{
			return RightHeight + 1;
		}
	}
}
/////////////////////////////
//------>> TreeNodes
int AVL::TreeNodes()
{
	int NumberofNodes = 0;
	NodeCounter(Root, NumberofNodes);
	return NumberofNodes;
}
//////////////////////////////////
void AVL::NodeCounter(Node* ProvidedNode, int& Count)
{
	if (ProvidedNode)
	{
		Count++;
		//left Most child then move backward
		NodeCounter(ProvidedNode->Left, Count);
		NodeCounter(ProvidedNode->Right, Count);
	}
}
/////////////////////////////
//------>> Leaf Node Count
int AVL::LeafCounter(Node* ProvideNode)
{
	if (!ProvideNode)//Base Condition
	{
		return 0;
	}
	else if (!ProvideNode->Left && !ProvideNode->Right)
	{
		return 1;//if the node has no child
	}
	else
	{
		//getting the number of leaves from left as well as right sub tree
		return LeafCounter(ProvideNode->Left) + LeafCounter(ProvideNode->Right);
	}
}
/////////////////////////////
//------>> Node Level
int AVL::LevelofNode(string Info)
{
	int TotalHeight = TreeHeight(Root);
	Node* ProvidedNode = SearchNode(Info);
	int HeightofNode = TreeHeight(ProvidedNode);
	return (TotalHeight - HeightofNode);
}
/////////////////////////////////
//------>> Auxiliary Functions 
////////////////////////////////
//------>> Constructor
AVL::AVL()
{
	Root = NULL;
}
/////////////////////////////
//------>> Balancing Factor
int AVL::BalanceFactor(Node* ProvidedNode)
{
	if (ProvidedNode == NULL)
	{
		return 0;
	}
	//BFactor = LeftSubtree Height-Right Subtree Height
	return TreeHeight(ProvidedNode->Left) - TreeHeight(ProvidedNode->Right);
}
/////////////////////////////
//------>> Right Right Rotation
//This function will Rotate towards left side to balance
void AVL::RightRotate(Node*& ProvidedNode)
{
	Node* AuxiliaryNode = ProvidedNode->Left;
	ProvidedNode->Left = AuxiliaryNode->Right;
	AuxiliaryNode->Right = ProvidedNode;
	ProvidedNode = AuxiliaryNode;
}
/////////////////////////////
//------>> Left Left Rotation
//This function will Rotate towards right side to balance
void AVL::LeftRotate(Node*& ProvidedNode)
{
	Node* AuxiliaryNode = ProvidedNode->Right;
	ProvidedNode->Right = AuxiliaryNode->Left;
	AuxiliaryNode->Left = ProvidedNode;
	ProvidedNode = AuxiliaryNode;
}
/////////////////////////////////
//------>> Balance Checker
//This function will maintain the balance of Tree
void AVL::BalanceIt(Node*& ProvidedNode)
{
	if (ProvidedNode)
	{
		int B_Factor;
		BalanceIt(ProvidedNode->Left);
		BalanceIt(ProvidedNode->Right);
		B_Factor = BalanceFactor(ProvidedNode);
		// Left Left Case
		if (B_Factor > 1)
		{
			if (BalanceFactor(ProvidedNode->Left) >= 0)
			{
				RightRotate(ProvidedNode);
			}
			else
			{
				LeftRotate(ProvidedNode->Left);
				RightRotate(ProvidedNode);
			}
		}
		//Right Right case
		if (B_Factor < -1)
		{
			if (BalanceFactor(ProvidedNode->Right) > 0)
			{
				RightRotate(ProvidedNode->Right);
				LeftRotate(ProvidedNode);
			}
			else
			{
				LeftRotate(ProvidedNode);
			}
		}
	}
}
/////////////
//------>> Search
Node* AVL::SearchNode(string InfoProvided)
{

	Node* CurrentNode = Root;//Starting from root
	while (CurrentNode)//Until last child is not reached
	{
		if (CurrentNode->Name == InfoProvided)//if match found
		{
			return CurrentNode;
		}
		else if (CurrentNode->Name < InfoProvided)//if the data is in right sub tree
		{
			CurrentNode = CurrentNode->Right;//moving forward
		}
		else//else it wil be in left sub tree
		{
			CurrentNode = CurrentNode->Left;
		}
	}
	return NULL;//no match found
}
/////////////////////////////

/////////////////////////////
void AVL::DeleteNode(string Key)
{
	//Since recursion is being used multiple functions are created
	//inorder to perform recursion efficiently
	GetNode(Key, Root);
}


//------>> Display
void AVL::Display()
{
	cout << "\n\t------------<< Available Products Are >>------------\n";
	if (!Root)
	{
		cout << "\n\tshop is Empty!";
	}
	else
	{
		InOrder(Root);

	}
	cout << "\n\n\t----------------------------------\n";
}
/////////////////////////////
// 
void AVL::GetNode(string Key, Node*& ProvidedNode)
{
	if (ProvidedNode == NULL)//if last child is reached or root is null
	{
		cout << "\n\t" << Key << " Does not Exist in the List!\n";
	}
	//moving towards respective node
	else if (Key < ProvidedNode->Name)
	{
		GetNode(Key, ProvidedNode->Left);
	}
	else if (Key > ProvidedNode->Name)
	{
		GetNode(Key, ProvidedNode->Right);
	}
	else
		//if the match is found .... then deleting the node
	{
		if (!ProvidedNode->Left && !ProvidedNode->Right)
		{
			delete ProvidedNode;
			ProvidedNode = nullptr;
		}
		else
		{
			MakeDeletion(ProvidedNode);
		}
		if (Root)//if Deletion Occurred re balance the tree
		{
			BalanceIt(Root);
		}
		return;
	}
}
/////////////////
void AVL::MakeDeletion(Node*& ProvidedNode)
{
	Node* NodetoDelete;
	if (ProvidedNode->Right == NULL)//if only right child is present
	{
		NodetoDelete = ProvidedNode;
		ProvidedNode = ProvidedNode->Left;//moving right
		delete NodetoDelete;//deleting node
	}
	else if (ProvidedNode->Left == NULL)//if only left child is present
	{
		NodetoDelete = ProvidedNode;
		ProvidedNode = ProvidedNode->Right;//moving left
		delete NodetoDelete;//deleting node
	}
	else
	{
		//if the node is full
		//then finding the successor
		NodetoDelete = ProvidedNode->Right;
		while (NodetoDelete->Left)
		{
			NodetoDelete = NodetoDelete->Left;
		}
		//making he link between the successor and provided node
		NodetoDelete->Left = ProvidedNode->Left;
		//the successor may have a right child
		NodetoDelete = ProvidedNode;
		ProvidedNode = ProvidedNode->Right;
		delete NodetoDelete;

	}
}
//------>> GetRoot
Node* AVL::GetRoot()
{
	return Root;
}
/////////////////////////////
//------>> SetRoot
void AVL::SetRoot(Node* Passed)
{
	this->Root = Passed;
}
/////////////////////////////
//------>> Destructor
AVL::~AVL()
{
	FreeNodes(Root);
	Root = nullptr;
}
/////////////////////////////
void AVL::FreeNodes(Node* ProvidedNode)
{
	if (ProvidedNode)
	{
		//deleting the children first and then the parent
		FreeNodes(ProvidedNode->Left);
		FreeNodes(ProvidedNode->Right);
		delete ProvidedNode;
	}
}
/////////////////////////////////
// ////////////////////////////////////    queue ////////////////////
struct queue_node  /// node
{
	string data;
	string name;
	string complaint;
	queue_node* next;
	queue_node(string d)
	{
		data = d;
		next = NULL;
	}
	queue_node(string nam, string comp)
	{
		name = nam;
		complaint = comp;
		next = NULL;
	}

};

class Queue_link  /////linking
{
public:
	queue_node* front, * rear;
	Queue_link()
	{
		front = rear = NULL;
	}
	void en_queue(string name, string complaint)// enquee
	{
		queue_node* temp = new queue_node(name, complaint);
		if (rear == NULL) {
			front = rear = temp;
			return;
		}
		rear->next = temp;
		rear = temp;
	}
	void en_queue(string x)// enquee
	{
		queue_node* temp = new queue_node(x);
		if (rear == NULL) {
			front = rear = temp;
			return;
		}
		rear->next = temp;
		rear = temp;
	}
	string get_complaint()
	{
		return front->complaint;
	}
	string get_name()
	{
		return front->name;
	}
	string de_queue()/// dequee
	{
		string tmp;
		if (front == NULL)
			return "";
		queue_node* temp = front;
		front = front->next;
		if (front == NULL)
			rear = NULL;
		tmp = temp->data;
		delete (temp);
		return tmp;
	}
	bool isempty() //// checking empty  or not
	{
		if (front == NULL)
			return true;
		else
			return false;
	}
	void display_comp() /// display
	{
		cout << "\n\t---------------<< List >>------------------\n\n";
		queue_node* CurrentNode;
		int NodeCounter = 0;
		CurrentNode = front;//Starting form first Node to last Node
		cout << "\n\t   ------>>>>>      customer complaints  are      <<<<----------  \n\n";
		while (CurrentNode)//until null is not found
		{
			cout << "\t  ***   Customer Name : " << CurrentNode->name << "  ***   Complaint is  : " << CurrentNode->complaint << "\n";
			CurrentNode = CurrentNode->next;
			NodeCounter++;
		}
		cout << "\n\tNumber of complaints in the List = " << NodeCounter << endl;
	}
	void display() /// display
	{
		cout << "\n\t---------------<< List >>------------------\n\n";
		queue_node* CurrentNode;
		int NodeCounter = 0;
		CurrentNode = front;//Starting form first Node to last Node
		cout << "\n\t   ------>>>>>      your favourite products are      <<<<----------  \n\n";
		while (CurrentNode)//until null is not found
		{
			cout << "\t  ***   " << CurrentNode->data << "\n";
			CurrentNode = CurrentNode->next;
			NodeCounter++;
		}
		cout << "\n\tNumber of products in the List = " << NodeCounter << endl;
	}
};
////////stack node
//------------<< Node Class >>------------
//------>> This Class is the building block of the link list, which is going
//to store the provided data in the system. The node have all the data members
//that can be provided to store 
class Stack_Node
{
public:
	//------------<< Data Members >>------------
	string customer_name;//This is used for Storing Values in objects
	///////////////////////////////////////////
	string product_name;
	string time;
	int product_price;
	int payment;
	int exchange;
	int qty;
	int total;
	//----->> Pointer to next node
	Stack_Node* Next;
	//------------<< Constructor >>------------
	//This will initialize all the data members with there default values
	Stack_Node()
	{
		customer_name = "\0";
		product_name = "\0";
		product_price = 0;
		total = 0;
		qty = 0;
		payment = 0;
		exchange = 0;
		Next = NULL;
	}

};
//------------<< Stack Class >>------------
//This class is the main class,means all the functionality and the operations 
//that are to be performed by the respective user of the program are in this class
class Stack
{
private:
	//////////////////////////////
	//------>> Data Members
	/////////////////////////////
	//------------<< Data Members >>------------
	//This Pointer will act as the name of Array, means this will act as the base address
	//holder for the link list ADT implemented
	Stack_Node* Head;
public:
	//////////////////////////////
	//------>> Member Methods
	/////////////////////////////
	//------>> Constructor

	//------>> Constructor
	Stack()
	{
		Head = NULL;
	}
	/////////////////////////////
	//------>> Push
	bool Push(string a, string b, int c, int d, int e, int qty, int total)
	{
		//If all the Conditions are meet and insertion is possible
		//creating the new node
		Stack_Node* NewNode = new Stack_Node;
		NewNode->customer_name = a;//Data is inserted in the new node
		//insertion in begining is handled
		NewNode->product_name = b;//Data is inserted in the new node
		NewNode->product_price = c;//Data is inserted in the new node
		NewNode->payment = d;//Data is inserted in the new node
		NewNode->exchange = e;//Data is inserted in the new node
		NewNode->qty = qty;//Data is inserted in the new node
		NewNode->total = total;//Data is inserted in the new node

		NewNode->Next = Head;
		Head = NewNode;
		return true;
	}
	/////////////////////////////
	//------>> POP Function
	void POP()
	{
		//	string TobeReturned = "\0";
		if (Head != NULL)
		{
			Stack_Node* TobeDeleted;
			TobeDeleted = Head;
			//	TobeReturned = Head->name;//get the value and move backward
			Head = Head->Next;
			delete TobeDeleted;
		}
		//	return TobeReturned;
	}
	/////////////////////////////
	void Display()
	{
		int i = 1;
		if (Head == NULL)//if head is null
		{
			cout << "Empty!";
		}
		else
		{
			//if head is not null
			for (Stack_Node* Current = Head; Current != NULL; Current = Current->Next)//moving forward from first to last
			{
				cout << "\n \t\t  ---->  customer # " << i << endl << endl; i++;
				cout << " \t  ---->  customer name : " << Current->customer_name << " \n";
				cout << " \t  ---->  product name : " << Current->product_name << " \n";
				cout << " \t  ---->  prodcut price  : " << Current->product_price << " \n";
				cout << " \t  ---->  quantity : " << Current->qty << " \n";
				cout << " \t  ---->  total : " << Current->total << " \n";
				cout << " \t  ---->  payment  : " << Current->payment << " \n";
				cout << " \t  ---->  exchange : " << Current->exchange << " \n";
			}
		}
	}
	int return_qty(string tmp)
	{
		int i = 1;
		if (Head == NULL)//if head is null
		{
			return 0;
		}
		else
		{
			//if head is not null
			for (Stack_Node* Current = Head; Current != NULL; Current = Current->Next)//moving forward from first to last
			{
				if (Current->product_name == tmp)
				{
					return Current->qty;
				}

			}
			return 0;
		}
	}
	int search_product(string tmp)
	{
		int i = 1;
		if (Head == NULL)//if head is null
		{
			return 0;
		}
		else
		{
			//if head is not null
			for (Stack_Node* Current = Head; Current != NULL; Current = Current->Next)//moving forward from first to last
			{
				if (Current->product_name == tmp)
				{
					return Current->total;
				}

			}
			return 0;
		}
	}
	bool search_name(string tmp)
	{
		int i = 1;
		if (Head == NULL)//if head is null
		{
			return false;
		}
		else
		{
			//if head is not null
			for (Stack_Node* Current = Head; Current != NULL; Current = Current->Next)//moving forward from first to last
			{
				if (Current->customer_name == tmp)
				{
					return true;
				}
			}

			return false;
		}
	}
	/////////////////////////////
	//------>> Destructor
	~Stack()
	{
		Stack_Node* CurrentNode = Head;
		Stack_Node* NextNode = NULL;
		while (CurrentNode)//until Last node is not reached
		{
			NextNode = CurrentNode->Next;//having address of next node
			delete CurrentNode;//deleting current node
			CurrentNode = NextNode;//moving forward
		}
		Head = NULL;//head is null list is empty
	}
};

/////////////  link list     //////////////
struct link_list_node {
	string data;
	link_list_node* next;

};
class link_list {
public:
	link_list_node* head;
	link_list()
	{
		head = NULL;
	}
	///////////////
	void insert_at_end(string num)
	{
		link_list_node* newNode = new link_list_node();
		newNode->data = num;
		newNode->next = NULL;
		if (head == NULL) {
			head = newNode;
		}
		else {
			link_list_node* temp = head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = newNode;
		}
	}
	bool Search_name(string searchValue) {

		//1. create a temp node pointing to head
		link_list_node* temp = head;

		//2. create two variables: found - to track
		//   search, idx - to track current index
		int found = 0;
		int i = 0;

		//3. if the temp node is not null check the
		//   node value with searchValue, if found 
		//   update variables and break the loop, else
		//   continue searching till temp node is not null 
		if (temp != NULL) {
			while (temp != NULL) {
				i++;
				if (temp->data == searchValue) {
					found++;
					break;
				}
				temp = temp->next;
			}
			if (found == 1) {
				return true;
				//cout << searchValue << " is found at index = " << i << ".\n";
			}
			else {
				return false;
				//				cout << searchValue << " is not found in the list.\n";
			}
		}
		else {

			//4. If the temp node is null at the start, 
			//   the list is empty
			cout << "The list is empty.\n";
			return false;
		}
	}
	void display()
	{
		int i = 1;
		link_list_node* ptr;
		ptr = head;
		while (ptr != NULL)
		{
			cout << "  \n  =>>>>>>> customer #  " << i << "\n";
			cout << "     >>>>    " << ptr->data << " ";
			ptr = ptr->next;

			i++;
		}
	}

};
//////////  functions ///////////////

///     checking availability of favourite product //////
void fav_product_availability(Queue_link& passed_obj, AVL& pass_obj)
{
	bool ch = true;
	string tmp;
	while (!passed_obj.isempty())
	{
		if (ch == true)
		{
			cout << "    ==>> your favourite product are :\n\n";
			ch = false;
		}

		tmp = passed_obj.de_queue();
		cout << "  =>  " << tmp << "  status : ";
		if (pass_obj.SearchNode(tmp) == NULL)
		{
			cout << "  ==>> not avaiable\n";
		}
		else
		{
			cout << "  ==>>  avaiable\n";

		}
	}
}
///   this function is used to buy product 
void buy_product(AVL& pass_obj, Stack& obj, link_list& link_obj)
{
	Node* temp;
	int qty;
	int money;
	string pname;
	bool product_check = true;
	bool qty_check = true;
	bool price_check = true;
	string customer_name;
	while (product_check == true)
	{
		cout << "   ==>> plz enter product name to buy \n";
		cin.ignore();
		getline(cin, pname);
		temp = pass_obj.SearchNode(pname);
		if (temp == NULL)
		{
			cout << "  ==>> not avaiable\n";
		}
		else
		{
			product_check = false;
			while (qty_check == true)
			{
				cout << " plz enter quantity \n";
				cin >> qty;
				if (qty <= temp->quantity)
				{
					qty_check = false;
					while (price_check == true)
					{
						cout << " plz enter money \n";
						cin >> money;
						if (money >= temp->price * qty)
						{
							cout << "\n    kindly enter your good name : ";
							cin.ignore();
							getline(cin, customer_name);
							price_check = false;
							temp->quantity -= qty;
							cout << "  your change is : " << money - temp->price * qty;
							cout << "    ==>>>>>>>  successfully bought";
							obj.Push(customer_name, pname, temp->price, money, money - (temp->price * qty), qty, temp->price * qty);
							link_obj.insert_at_end(customer_name);
						}
						else
						{
							cout << "  too low money plz enter money again\n";
						}
					}

				}
				else
				{
					cout << "  no enough stock enter again quantity";
				}
			}

		}
	}
}
///    add favourite product in list ///////
void  fav_product(AVL& pass_obj, Stack& obj, link_list& link_obj)
{
	Queue_link ListCreated;
	//In the Begining we have to have a link list inorder to peform the given functions on it
	//so a dummy doubly link list is created with the help of following function
	bool MenuBreak = false;//this variable is for quiting the menu
	int Option;//Variable to Take menu Option from user
	string InputValue = "";//Variable used to take Input From user
	//to perform the required task before or after that Node
	do
	{
		cout << "\n\tPlease Select one of the following Function\n\n"
			<< "\n\tPress 1 ===>> enquee product"
			<< "\n\tPress 2 ===>> dequee product"
			<< "\n\tPress 3 ===>> buy product"
			<< "\n\tPress 4 ===>> Exit Program\n\n"
			<< "\n\tSelect Any Provided Option = ";
		cin >> Option;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n\n\tSelect Option = ";
			cin >> Option;
		}

		system("cls");
		switch (Option)
		{
		case 1:
			cout << "\n\tBefore enquee\n";
			ListCreated.display();
			cout << "\n\t---------------<< performing enquee operation >>------------------\n\n\t";
			cout << "\n\tPlease Enter product name  to Insert in the List = ";
			cin.ignore();
			getline(cin, InputValue);
			ListCreated.en_queue(InputValue);
			cout << "\n\tAfter enquee operation\n";
			ListCreated.display();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 2:
			cout << "\n\tBefore Dequee\n";
			ListCreated.display();
			cout << "\n\t---------------<< performing dequee operation >>------------------\n\n\t";
			ListCreated.de_queue();
			cout << "\n\tAfter dequee\n";
			ListCreated.display();
			cout << "\n\n\t";
			system("pause");
			system("cls");

			break;
		case 3:
			fav_product_availability(ListCreated, pass_obj);
			pass_obj.Display();
			buy_product(pass_obj, obj, link_obj);
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 4:
			MenuBreak = true;
			break;
		default:
			cout << "\n\tPlease Select \"Valid\" Option\n\tPlease Input Again!\n\n";
			break;
		}
	} while (!MenuBreak);

}
///   giving discounts on different productrs /////////
void discounts()
{
	cout << "\n  7% discount on coke"
		<< "\n  15 % discount on lays"
		<< "\n  25 % discount on dairy milk"
		<< "\n  70 % discount on biscuits";
}
///     dequeue customer on behalf of cojmplaintys //////
void customer_dequeue(Queue_link& obj)
{
	bool MenuBreak = false;
	int Option;
	do
	{
		cout << "\n\tPlease Select an Option from Following!"
			<< "\n\tPress 1 ===>> complaints list"
			<< "\n\tPress 2 ===>> dequeue complaints/"
			<< "\n\tPress 3 ===>> go back"
			<< "\n\n\tSelect Option = ";
		cin >> Option;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n\n\tSelect Option = ";
			cin >> Option;
		}
		system("cls");
		switch (Option)
		{
		case 1:
			obj.display_comp();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 2:
			obj.de_queue();
			cout << "\n  -------->>> successfully dequeued  <<-------\n";
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 3:
			MenuBreak = true;
			break;
		default:
			cout << "\n\tPlease Select a Valid Option!\n\tTry Again!\n";
			break;
		}
	} while (!MenuBreak);

}
///    this adding complaints of user in queue list////////////////
void complaints(Queue_link& PassedObject)
{
	string name;
	string comp;
	cout << "\n\n      ==>>  enter your name : ";
	cin.ignore();
	getline(cin, name);
	cout << " \n      ==>>  enter your complaint : ";
	getline(cin, comp);
	PassedObject.en_queue(name, comp);
	cout << "\n      ------>>>  your complaint is successfully submited    ------<<<<<<< \n";
}
///  this function return the products bought by users 
void return_prodduct(Stack& obj, AVL& object)
{
	string name;
	cout << "\n\n  ==>> plz enter your name to verify that u really bought this productg from us :";
	cin.ignore();
	getline(cin, name);
	if (obj.search_name(name) == true)
	{
		cout << "  kindly enter product name you want to return ";
		getline(cin, name);
		int tmp = obj.search_product(name);
		if (tmp == 0)
		{
			cout << "\n      you did not buy this product from us !!!!!!!";
		}
		else
		{
			Node* ptr = object.SearchNode(name);
			ptr->quantity += obj.return_qty(name);
			cout << "\n   =>>>>      product is successfully returned ";
			cout << "\n    =>>>>      kindly take your money :" << tmp;

		}
	}
	else
	{
		cout << "\n      you did not buy any product from us !!!!!!!";

	}

}
///  this functions is actually driver function to display customer menu /////////////
void customer_Menu(Queue_link& PassedObject, AVL& passed_obj, Stack& obj, link_list& link_obj)
{
	bool MenuBreak = false;
	string product_name = "";
	int product_price = 0;
	int product_qty = 0;
	int Option = 0;
	do
	{
		cout << "\n\tPlease Select an Option from Following!"
			<< "\n\tPress 1 ===>> buying history"
			<< "\n\tPress 2 ===>> buy/favourite products"
			<< "\n\tPress 3 ===>> complaints"
			<< "\n\tPress 4 ===>> return product "
			<< "\n\tPress 5 ===>> discount "
			<< "\n\tPress 6 ===>> exit"
			<< "\n\n\tSelect Option = ";
		cin >> Option;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n\n\tSelect Option = ";
			cin >> Option;
		}
		system("cls");
		switch (Option)
		{
		case 1:
			obj.Display();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 2:
			fav_product(passed_obj, obj, link_obj);
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 3:
			complaints(PassedObject);
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;

		case 4:
			return_prodduct(obj, passed_obj);
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 5:
			discounts();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 6:
			MenuBreak = true;
			break;
		default:
			cout << "\n\tPlease Select a Valid Option!\n\tTry Again!\n";
			break;
		}
	} while (!MenuBreak);
}
/////////  this fumctions is driver code of admin mode ///////////////////
void admin_Menu(AVL& PassedObject, Queue_link& passed_obj, link_list link_obj)
{
	bool MenuBreak = false;
	string product_name = "";
	int product_price = 0;
	int product_qty = 0;
	int Option = 0;
	Node* CurrentNode = NULL;
	do
	{
		cout << "\n\tPlease Select an Option from Following!"
			<< "\n\tPress 1 ===>> Add Product"
			<< "\n\tPress 2 ===>> Delete Product"
			<< "\n\tPress 3 ===>> Modify Product"
			<< "\n\tPress 4 ===>> customer list"
			<< "\n\tPress 5 ===>> dequeue customer "
			<< "\n\tPress 6 ===>> Exit"
			<< "\n\n\tSelect Option = ";
		cin >> Option;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n\n\tSelect Option = ";
			cin >> Option;
		}
		system("cls");
		switch (Option)
		{
		case 1:
			cout << "\n\tBefore Insertion";
			PassedObject.Display();
			cout << "\n\tPlease Enter the Name of product = ";
			cin.ignore();
			getline(cin, product_name);
			cout << "\n\tPlease Enter the price of product = ";
			cin >> product_price;
			cout << "\n\tPlease Enter the quantity of product = ";
			cin >> product_qty;

			if (!PassedObject.Insert(product_name, product_price, product_qty))
			{
				cout << "\n\tInsertion is not Possible!\n";
			}
			PassedObject.Display();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 2:
			cout << "\n\tBefore Deletion";
			PassedObject.Display();
			cout << "\n\tPlease Enter the product name to Delete = ";
			cin >> product_name;
			PassedObject.DeleteNode(product_name);
			PassedObject.Display();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 3:
			PassedObject.Display();
			cout << "\n\tPlease Enter the product name  to Search = ";
			cin >> product_name;
			CurrentNode = PassedObject.SearchNode(product_name);
			if (CurrentNode == NULL)
			{
				cout << "\n\tData Does not Exist in the Tree\n";
			}
			else
			{
				cout << "\n  ==> product found !!!!!\n\n";
				cout << "  ==>> product Name is : " << CurrentNode->Name << "  ::  price is : " << CurrentNode->price;
				cout << "\n\n  ==>> enter product Name to modify : ";
				cin >> CurrentNode->Name;
				cout << "  \n==>> enter product price to modify : ";
				cin >> CurrentNode->price;
				cout << "  \n==>> enter product quantity to modify : ";
				cin >> CurrentNode->quantity;
				cout << " \n\n   !!!   successfully modified   !!!\n\n";

				//cout << "\n\tData Exists in the Tree\n";
			}
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;

		case 4:
			link_obj.display();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 5:
			//PassedObject.Display();
			customer_dequeue(passed_obj);
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 6:
			MenuBreak = true;
			break;
		default:
			cout << "\n\tPlease Select a Valid Option!\n\tTry Again!\n";
			break;
		}
	} while (!MenuBreak);
}

//		 Driver Code		 
void main_head_controller_of_program()
{
	AVL TreeCreated;          // creating object of AVL tree
	Queue_link queue_list;    // creating object of queue data structure
	Stack obj;                // creating object of stack data structure
	link_list link_list_obj;  // creating object of link list data structure
	bool MenuBreak = false;
	int Input = 0;
	Node* GotRoot = TreeCreated.GetRoot();
	int Option;
	//// driver 
	do
	{
		cout << "\n\tPlease Select an Option from Following!"
			<< "\n\tPress 1 ===>> for administration mode"
			<< "\n\tPress 2 ===>> for customer mode"
			<< "\n\tPress 3 ===>> Exit"
			<< "\n\n\tSelect Option = ";
		cin >> Option;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n\n\tSelect Option = ";
			cin >> Option;
		}
		system("cls");
		switch (Option)
		{
		case 1:
			admin_Menu(TreeCreated, queue_list, link_list_obj);
			//TreeCreated.~AVL();
			break;
		case 2:
			customer_Menu(queue_list, TreeCreated, obj, link_list_obj);
			break;
		case 3:
			MenuBreak = true;
			break;
		default:
			cout << "\n\tPlease Select a Valid Option!\n\tTry Again!\n";
			break;
		}
	} while (!MenuBreak);

}
int main()////   main function
{
	// calling head / main conrroller of program 
	///  which actually displaying all starting menu modules to user 
	main_head_controller_of_program();
	system("pause>0");
	return 0;
}