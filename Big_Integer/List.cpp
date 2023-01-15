#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Class Constructors & Destructors

// Private Constructors
List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Constructors
List::List(){
	Node *N = new Node(-1);
	frontDummy = N ;
	backDummy = N;
	beforeCursor = N;
	afterCursor = N;
	pos_cursor = 0;
	num_elements = 0;
}

// Copy Constructors
List::List(const List& L){
	Node *N = new Node(-1);
	frontDummy = N;
	backDummy = N;
	beforeCursor = N;
	afterCursor = N;
	pos_cursor = 0;
	num_elements = 0;
	
	if(L.length() > 0){
		Node *M = L.List::backDummy->prev;
		while(M != L.List::frontDummy){
			insertAfter(M->data);
			M = M->prev;
		}
	}
}

// Destructor
List::~List(){
	clear();
	if(frontDummy == backDummy){
		delete frontDummy;
	}else{
		delete frontDummy;
		delete backDummy;
	}
}

// Class Access Function
int List::length() const{
	return num_elements;
}

ListElement List::front() const{
	if(length() > 0){
		return frontDummy->next->data;
	}
	throw std::length_error("List: front(): empty list");	
}

ListElement List::back() const{
	if(length() > 0){
		return backDummy->prev->data;
	}
	throw std::length_error("List: back(): empty list");
}

int List::position() const{
	return pos_cursor;
}

ListElement List::peekNext() const{
	if(position() < length()){
		return afterCursor->data;
	}
	throw std::range_error("List: peekNext(): cursor at back");
}

ListElement List::peekPrev() const{
	if(position() > 0){
		return beforeCursor->data;
	}
	throw std::range_error("List: peekPrev: cursor at front");
}

// Class Manipulation procedures
void List::clear(){
	moveBack();
	while(length() > 0){
		eraseBefore();
	}
}

void List::moveFront(){
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
}

void List::moveBack(){
	pos_cursor = length();
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
}

ListElement List::moveNext(){
	if(position() < length()){
		beforeCursor = afterCursor;
		afterCursor = afterCursor->next;
		pos_cursor++;
		return beforeCursor->data;
	}
	throw std::range_error("List: moveNext(): cursor at back");
}

ListElement List::movePrev(){
	if(position() > 0){
		afterCursor = beforeCursor;
		beforeCursor = beforeCursor->prev;
		pos_cursor--;
		return afterCursor->data;
	}
	throw std::range_error("List: movePrev(): cursor at front");
}

void List::insertAfter(ListElement x){
	Node *N = new Node(x);
	if(length() == 0){
		frontDummy->next = backDummy->prev = N;
		N->next = backDummy;
		N->prev = frontDummy;

		beforeCursor = frontDummy;
		afterCursor = N;

		num_elements++;
		pos_cursor = 0;
	}else{
		beforeCursor->next = afterCursor->prev = N;
		N->prev = beforeCursor;
		N->next = afterCursor;

		afterCursor = N;

		num_elements++;
	}

}

void List::insertBefore(ListElement x){
	Node *N = new Node(x);
	if(length() == 0){
		frontDummy->next = backDummy->prev = N;
		N->next = backDummy;
		N->prev = frontDummy;

		afterCursor = backDummy;
		beforeCursor = N;

		num_elements++;
		pos_cursor = 1;
	}else{
		beforeCursor->next = afterCursor->prev = N;
		N->prev = beforeCursor;
		N->next = afterCursor;

		beforeCursor = N;

		num_elements++;
		pos_cursor++;
	}
}

void List::setAfter(ListElement x){
	if(position() < length()){
		afterCursor->data = x;
	}else{
		throw std::range_error("List: setAtfer(): cursor at front");
	}
}

void List::setBefore(ListElement x){
	if(position() > 0){
		beforeCursor->data = x;
	}else{
		throw std::range_error("List: setBefore(): cursor at front");
	}
}

void List::eraseAfter(){
	if(position() < length()){
		Node *del = afterCursor;
		afterCursor = afterCursor->next;

		beforeCursor->next = afterCursor;
		afterCursor->prev = beforeCursor;
	
		num_elements--;
		delete del;
	}else{
		throw std::range_error("List: eraseAfter(): cursor at back");
	}
}

void List::eraseBefore(){
	if(position() > 0){
		Node *del = beforeCursor;
		beforeCursor = beforeCursor->prev;

		beforeCursor->next = afterCursor;
		afterCursor->prev = beforeCursor;

		pos_cursor--;
		num_elements--;
		delete del;
	}else{
		throw std::range_error("List: eraseBefore(): cursor at front");
	}
}

// Other Functions
int List::findNext(ListElement x){
	if(afterCursor->data == x){
		moveNext();
		return position();
	}else{
		while(moveNext() != x){
			if(afterCursor == backDummy){
				moveBack();
				return -1;
			}
		}
		return position();
	}
}	

int List::findPrev(ListElement x){
	if(beforeCursor->data == x){
		movePrev();
		return position();
	}else{
		while(movePrev() != x){
			if(beforeCursor == frontDummy){
				moveFront();
				return -1;
			}
		}
		return position();
	}
}

void List::cleanup(){
	int check_pos = 1, curr_pos;
	Node *check = frontDummy->next;
	Node *prev = nullptr;
	Node *curr = nullptr;
	
	while(check_pos <= length()){
		bool pass_cursor = false;
		curr = check->next;
		curr_pos = check_pos + 1;
		if(check_pos > position()){
			pass_cursor = true;
		}
		while(curr_pos <= length()){
			if(curr_pos > position()){
				pass_cursor = true;
			}

			if(curr->data == check->data){
				num_elements--;

				Node *del = curr;
				prev = curr->prev;
				curr = curr->next;

				prev->next = curr;
				curr->prev = prev;

				if(pass_cursor == false){
					pos_cursor--;
					if(beforeCursor == del){
						beforeCursor = beforeCursor->prev;
					}
				}

				delete del;
			}else{
				curr = curr->next;
				curr_pos++;
			}
		}
		check_pos++;
		check = check->next;
	}
}

List List::concat(const List& L) const{
	List out;
	Node *N = this->frontDummy->next;
	Node *M = L.frontDummy->next;
	while(N != this->backDummy){
		out.insertBefore(N->data);
		N = N->next;
	}
	while(M != L.backDummy){
		out.insertBefore(M->data);
		M = M->next;
	}
	out.moveFront();
	return out;
}

std::string List::to_string() const{
	Node * N = nullptr;
	std::string s ="(";

	for(N=frontDummy->next; N!=nullptr;N=N->next){
		if(N != backDummy->prev){
			s += std::to_string(N->data)+", ";
		}else{
			s += std::to_string(N->data);
			break;
		}
	}
	s+= ")";
	return s;
}

bool List::equals(const List& R) const{
	bool eq =false;
	eq = (length() == R.List::length());
	Node *N = frontDummy->next;
	Node *M = R.List::frontDummy->next;

	while(eq && N != backDummy){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

// Overriden Operators
std::ostream& operator<<(std::ostream& stream, const List& L){
	return stream << L.List::to_string();
}

bool operator==(const List& A, const List& B){
	return A.List::equals(B);
}

List& List::operator=(const List& L){
	if(this != &L){
	List temp = L;
	std::swap(frontDummy,temp.frontDummy);
	std::swap(backDummy,temp.backDummy);
	std::swap(num_elements,temp.num_elements);
	std::swap(pos_cursor,temp.pos_cursor);
	}
	return *this;
}

