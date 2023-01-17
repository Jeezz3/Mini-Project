//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT. List is a double ended queue with a vertical
// cursor standing between elements. The cursor position is always defined
// to be an int in the range 0 (at front) to length of List (at back).
// An empty list consists of the vertical cursor only, with no elements.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>

#ifndef List_H_INCLUDE_
#define List_H_INCLUDE_

// Exported types -------------------------------------------------------------
typedef int64_t ListElement;

class List{

private:

   // private Node struct
   struct Node{
      // Node fields
      ListElement data;
      Node* next;
      Node* prev;
      // Node constructor
      Node(ListElement x);
   };

   // List fields
   Node* frontDummy;
   Node* backDummy;
   Node* beforeCursor;
   Node* afterCursor;
   int pos_cursor;
   int num_elements;

public:

   // Class Constructors & Destructors ----------------------------------------
   
   // Creates new List in the empty state.
   List();

   // Copy constructor.
   List(const List& L);

   // Destructor
   ~List();


   // Access functions --------------------------------------------------------

   // length()
   // param: None
   // return: Int-length of this List.
   int length() const;

   // front()
   // param: None
   // return: ListElement-front element in this List.
   // pre: length() > 0
   ListElement front() const;

   // back()
   // param: None
   // return: ListElement-back element in this List.
   // pre: length() > 0
   ListElement back() const;

   // position()
   // param: None
   // return: Int-position of cursor in the List: 0 <= position() <= length().
   int position() const;

   // peekNext()
   // param: None
   // return: ListElement-element after the cursor.
   // pre: position() < length()
   ListElement peekNext() const;

   // peekPrev()
   // param: None
   // return: ListElement-element before the cursor.
   // pre: position() > 0
   ListElement peekPrev() const;


   // Manipulation procedures -------------------------------------------------

   // clear()
   // param: None
   // return: None
   // func: Deletes all elements in this List, setting it to the empty state.
   void clear();

   // moveFront()
   // param: None
   // return: None
   // func: Moves cursor to position 0 in this List.
   void moveFront();

   // moveBack()
   // param: None
   // return: None
   // func: Moves cursor to position length() in this List.
   void moveBack();

   // moveNext()
   // param: None
   // return: None
   // func: Advances cursor to next higher position. Returns the List element that
   //       was passed over. 
   // pre: position() < length() 
   ListElement moveNext();

   // movePrev()
   // param: None
   // return: None
   // func: Advances cursor to next lower position. Returns the List element that
   //       was passed over. 
   // pre: position() > 0
   ListElement movePrev();

   // insertAfter()
   // param: None
   // return: None
   // func: Inserts x after cursor.
   void insertAfter(ListElement x);

   // insertBefore()
   // param: None
   // return: None
   // func: Inserts x before cursor.
   void insertBefore(ListElement x);

   // setAfter()
   // param: None
   // return: None
   // func: Overwrites the List element after the cursor with x.
   // pre: position() < length()
   void setAfter(ListElement x);

   // setBefore()
   // param: None
   // return: None
   // func: Overwrites the List element before the cursor with x.
   // pre: position() > 0
   void setBefore(ListElement x);

   // eraseAfter()
   // param: None
   // return: None
   // func: Deletes element after cursor.
   // pre: position() < length()
   void eraseAfter();

   // eraseBefore()
   // param:
   // return:
   // Deletes element before cursor.
   // pre: position()>0
   void eraseBefore();

   // Other Functions ---------------------------------------------------------

   // findNext()
   // param: ListElement- target element
   // return: Int- find the first occurrence (front to back) of element x relative to cursor position, return -1 if not found

   int findNext(ListElement x);

   // findPrev()
   // param: ListElement- target element
   // return: Int- find the first occurrence (back to front) of element x relative to cursor position, return -1 if not found
   int findPrev(ListElement x);

   // cleanup()
   // param: None
   // return: None
   // func: remove reapeated element, while retaining frontmost occurrance of each element 
   void cleanup();
 
   // concat()
   // param: List-
   // return: List-
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
   List concat(const List& L) const;

   // to_string()
   // param: None
   // return: string-
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   std::string to_string() const;

   // equals()
   // param:
   // return: Bool-
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool equals(const List& R) const;


   // Overriden Operators -----------------------------------------------------
   // operator<<()
   // Inserts string representation of L into stream.
   friend std::ostream& operator<<( std::ostream& stream, const List& L );

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
   friend bool operator==( const List& A, const List& B );

   // operator=()
   // Overwrites the state of this List with state of L.
   List& operator=( const List& L );

};


#endif

