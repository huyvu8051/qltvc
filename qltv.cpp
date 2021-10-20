#include<iostream>
#include <string.h>
using namespace std;

struct Customer {
	char name[50];
	char address[50];
	char phoneNum[11];
	char returnDate[11];// ngay tra sach
};

struct Book {
	char id[50];
	char category[50];// the loai
	Customer *customer;
};

struct Node {
	Book data;
	Node *next;
};
typedef struct Node *Stack;

void init(Stack &top);
bool isEmpty(Stack top);
Node *createNode(Book data);
bool push(Stack &top, Book newItem);
void deleteTop(Stack &top);
bool pop(Stack &top, Book &outItem);
bool top(Stack top, Book &outItem);

void init(Stack &top) {
	top = NULL;
}

bool isEmpty(Stack top) {
	return (top == NULL);
}


Node *createNode(Book data) {
	Node *p = new Node();
	p->data = data;
	p->next = NULL;
	p->data.customer = NULL;

	return p;
}


/**
*	add element at the top of stack
*
*/
bool push(Stack &top, Book newItem) {

	Node *ptr = createNode(newItem);

	if (isEmpty(top)) {
		top = ptr;
	}

	else {
		ptr->next = top;
		top = ptr;
	}


	return true;
}


/**
*	get the top node of stack and remove it
*
*/
bool pop(Stack &top, Book &outItem) {
	if (!isEmpty(top)) {
		outItem = top->data;
		Node *x = top;
		top = top->next;
		delete(x);
		return true;
	} else {
		return false;
	}
}

/**
*	remove the top node of stack
*
*/
void deleteTop(Stack &top) {
	if (!isEmpty(top)) {
		Book data = top->data;
		Node *x = top;
		top = top->next;
		delete(x);
	}
}

/**
*	peek stack
*
*/
bool top(Stack top, Book &outItem) {
	if (!isEmpty(top)) {
		outItem = top->data;
		return true;
	} else {
		return false;
	}
}

/**
*	input book infomation
*
*/
void inputBookInfo(Book &book) {
	printf("\n++++++++Nhap thong tin sach+++++++++++");

	printf("\nNhap id: ");
	scanf("%s", &book.id);

	printf("\nNhap the loai: ");
	scanf("%s", &book.category);

}

/**
*	add one book to stack
*
*/
void addBook(Stack &top) {
	Book newItem ;
	inputBookInfo(newItem);

	push(top, newItem);
}

void printOneCustomerInfo(Customer *customer) {
	printf("\nname: %s", customer->name);
	printf("\naddress: %s", customer->address);
	printf("\nphoneNum: %s", customer->phoneNum);
	printf("\nreturnDate: %s", customer->returnDate);
}

/**
*	print one book infomation
*
*/
void printOneBookInfo(Book book) {
	printf("\nid: %s", book.id);
	printf("\ncategory: %s", book.category);
	if(book.customer->name != NULL) {
		printf("\n========>This book is borrowed by customer:");
		printOneCustomerInfo(book.customer);
	} else {
		printf("\n========>This book isn't borrowed");
	}


}

/**
*	print all book in stack
*	show the quantity left
*/
void printListBook(Stack top) {
	int index = 0;
	while(top != NULL) {
		index ++;
		printf("\n\nXuat thong tin sach thu %d:", index);
		printOneBookInfo(top->data);
		top = top->next;
	}
	printf("\n========>So sach con lai la: %d", index);
}




/**
*	get book index in stack by book id
*	if the id not exist in stack, return -1
*
*
*/
int searchBookIndexById(Stack top, char id[50]) {
	int position = 0;
	for(Stack p = top; p != NULL; p = p->next) {
		if(strcmp(p->data.id,id) == 0) { // found a correct book id
			return position;
		}
		++position;
	}
	return -1;
}

/**
*	delete one node in stack by index
*
*/
void DelAt(Stack &top, int index) {

	// if the index equals 0 -> try to delete the top of stack
	if(index == 0) {
		deleteTop(top);
	}

	int position = 0;
	for(Stack p = top; p != NULL; p = p->next) {
		if(position == index - 1) {
			Stack x = p->next;

			p->next = x->next;

			delete(x);
			return;
		}
		++position;
	}

}

/**
*	sell one book
*	get the book index in stack
*	use the index to delete the node in stack
*
*/
void sellBook(Stack &top) {
	printf("\nNhap id sach can ban: ");
	char id[50];
	scanf("%s", &id);

	int index = searchBookIndexById(top, id);

	if(index < 0) {
		printf("\nKhong tim thay sach!");
		return;
	}

	DelAt(top, index);

	printf("\nBan thanh cong!");



}



/**
*	input customer infomation
*
*
*
*/
void inputCustomerInfo(Customer *customer) {
	printf("\n++++++++Nhap thong tin khach hang+++++++++++");
	printf("\nNhap ten: ");
	scanf("%s", &customer->name);
	printf("Nhap dia chi: ");
	scanf("%s", &customer->address);
	printf("Nhap sdt: ");
	scanf("%s", &customer->phoneNum);
	printf("Nhap ngay tra: ");
	scanf("%s", &customer->returnDate);
}



/**
*	borrow a book
*	create a customer in book by id
*
*
*/
void borrowBook(Stack &top) {
	printf("\nNhap id sach can thue: ");
	char id[50];
	scanf("%s", &id);

	int index = searchBookIndexById(top, id);

	if(index < 0) {
		printf("\nKhong tim thay sach!");
		return;
	}
	int i = 0;
	for(Stack p = top ; p != NULL; p = p->next, i++) {
		if(i == index) {
			Customer *customer = new Customer();
			p->data.customer = customer;
			inputCustomerInfo(customer);
			break;
		}
	}

	printf("\nBorrow book successful!");

}

/**
*	customer return a book
*	set customer = NULL
*
*
*/
void returnBook(Stack &top) {
	printf("\nNhap id sach can tra: ");
	char id[50];
	scanf("%s", &id);

	int index = searchBookIndexById(top, id);

	if(index < 0) {
		printf("\nKhong tim thay sach!");
		return;
	}
	int i = 0;
	for(Stack p = top ; p != NULL; p = p->next, i++) {
		if(i == index) {
			Customer *x = p->data.customer;
			p->data.customer = NULL;
			delete(x);
			break;
		}
	}

	printf("\nReturn book successful!");
}


int main() {

	Stack s;

	init(s);

	int soSachDaBan = 0;

	int lc = 0;
	do {
		cout << "\n\n\t\t ============== Menu ==============";
		cout << "\n\t1. Them sach";
		cout << "\n\t2. Ban sach(xoa sach)";
		cout << "\n\t3. So sach con";
		cout << "\n\t4. So sach da ban";
		cout << "\n\t5. Dang ky muon sach";
		cout << "\n\t5. Tra sach";
		cout << "\n\t0. Ket thuc";
		cout << "\n\n\t\t ============== End ==============";
		cout<<"\nNhap lua chon: ";
		cin>> lc;


		switch(lc) {
			case 0:
				return 0;
				break;
			case 1:
				addBook(s);
				break;
			case 2:
				sellBook(s);
				soSachDaBan ++;
				break;
			case 3:
				printListBook(s);
				break;
			case 4:
				printf("\nSo sach da ban: %d", soSachDaBan);
				break;
			case 5:
				borrowBook(s);
				break;
			case 6:
				returnBook(s);
				break;
			default:
				cout<<"\nNhap sai, vui long nhap lai!";
		}
	} while(lc != 0);
}
