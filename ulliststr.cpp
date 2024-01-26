#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
 /**
   * Adds a new value to the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::push_back(const std::string& val){
  if (tail_!=nullptr && tail_->last != ARRSIZE) { // if tail is not null and not full
    tail_->val[tail_->last] = val; // store val in last as last before push_back is exclusive
    tail_->last++; // increment last
  } 
  else{// if tail is null or full
    Item* newNode = new Item(); // need to make new node
    newNode->val[0] = val; //store val in first index of the new node
    newNode->first = 0;
    newNode->last = 1;
    newNode->next = nullptr;

    if (tail_!=nullptr) { //if tail is full not null
      tail_->next = newNode;
      newNode->prev = tail_;
    } 
    else { // tail is null meaning the list is empty 
      head_ = newNode;
    }
    tail_ = newNode; // updates tail pointer to point to the new node
  }
  size_++; // increment size of ull 
}

  /**
   * Removes a value from the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_back(){
  tail_->last--; // pop_back 

  if(tail_->first==tail_->last){ // if tail node is empty after pop_back
    Item* temp=tail_; 
    tail_=tail_->prev; 
    if(tail_!=nullptr){ // if list not empty meaning there are more than one node in the ull
      tail_->next=nullptr; // update the tail 
    }
    else{ // if list is now empty
      head_=nullptr; // head is also nullptr now
    }
    delete temp; 
  }
  size_--; 
}
  
  /**
   * Adds a new value to the front of the list.
   * If there is room before the 'first' value in
   * the head node add it there, otherwise, 
   * allocate a new head node.
   *   - MUST RUN in O(1)
   */
void ULListStr::push_front(const std::string& val){
  if(head_!=nullptr&&head_->first!=0){ // if head is not null and not full
    head_->first--; // need to decrement first
    head_->val[head_->first]=val; // so val is inserted in the right first
    
  }
  else{ //if head is null or full
    Item* newNode=new Item();
    newNode->val[ARRSIZE-1]=val; // put val in new node's last index
    newNode->first=ARRSIZE-1; // first in new node should be in the last index
    newNode->last=ARRSIZE; 
    newNode->prev=nullptr; 
    
    if(head_!=nullptr){ // if ull is not empty 
      head_->prev=newNode; 
      newNode->next=head_; 
    }
    else{
      tail_=newNode; 
    }
    head_=newNode; // update head with new node 
  }
  size_++; 
}

  /**
   * Removes a value from the front of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_front(){
  head_->first++; // decrement first as the first thing 

  if (head_->first == head_->last) { // Check if the head item is empty after pop_front
    Item* temp = head_; // create a temp pointer than points to head
    head_ = head_->next; // make the second node the new head
    if (head_!=nullptr) { // meaning there are more than one node in the ull
      head_->prev = nullptr; // make the second node the official head by making its prev point to null
    } 
    else { // list is empty because there is only one node and it has been pop 
      tail_ = nullptr; // make tail point to null too 
    }
    delete temp; // deallocate temp
  }
  size_--; // decrement size 
}
  
  /**
   * Returns a const reference to the back element
   *   - MUST RUN in O(1)
   */
std::string const & ULListStr::back() const{
  return tail_->val[tail_->last-1]; 
}

  /**
   * Returns a const reference to the front element
   *   - MUST RUN in O(1)
   */
std::string const & ULListStr::front() const{
  return head_->val[head_->first]; 
}

/** 
   * Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */
std::string* ULListStr::getValAtLoc(size_t loc) const{
  if (loc >= size_) { // if loc is not in ull
    return nullptr;
  }
  Item* current = head_; 
  size_t globalIndex = 0; // start at head node's index 0 

  while (current != nullptr) {
    size_t nodeSize = current->last - current->first; // calculate the size of the current node
    if (loc < globalIndex + nodeSize) { // if loc is in this current node 
      size_t nodeIndex = loc - globalIndex; // creates the index of the where loc is this current node  
      return &current->val[current->first + nodeIndex];
    }
    globalIndex += nodeSize; // update the global index for the next iteration 
    current = current->next; // update the current node for the next iteration 
  }
  return nullptr;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
