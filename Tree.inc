#include <iostream>
#include <cstdlib>
#include <string>
#include "Tree.h"
#include <sstream>


// siblings and children must be unique, return true if added, false otherwise
template <typename T>//template
Tree<T>::Tree(T value): data(value), kids(nullptr),sibs(nullptr),prev(nullptr)
{//constructor function                                                            
}
template <typename T>
Tree<T>::~Tree() {//destructor function 
  if(this->kids) {//checking if it has kids
    delete this->kids;
  }
  if(this->sibs) {//checking if it has siblings
    delete this->sibs;
  }
}

template <typename T>
Tree<T>& Tree<T>::operator^(Tree<T>& rt){  //^ operator to do the same thing as addChild                                       
  addChild(&rt);
  return *this;
}
template <typename T>
bool Tree<T>::operator==(const Tree<T> &root){ // return true if two Trees match node by node                                      
  if(root.sibs == nullptr && root.kids == nullptr && this->sibs == nullptr && this->kids == nullptr) {//in case both Trees are empty
    return true;
  }

  if(root.data == this->data) {//any cases will be checked if the data in the first node is same, else return false 
    if(((root.sibs == nullptr) && (this->sibs == nullptr)) && ((root.kids != nullptr) && (this->kids != nullptr))) {//if both trees dont have sibs, then compare equality of kids
      return (*(this->kids) == *(root.kids));
    }

    if(((root.kids == nullptr) && (this->kids == nullptr)) && ((root.sibs != nullptr) && (this->sibs != nullptr))) {//if both Trees do not have kids, then compare equality of sibs
      return (*(this->sibs) == *(root.sibs));
    }

    if(((root.sibs !=nullptr) && (this->sibs != nullptr)) && ((root.kids !=nullptr) && (this->kids != nullptr))) {//if both trees have both kids and sibs, then check equality of kids and sibs recursively
      bool kids_eq = (*(root.kids) == *(this->kids));//checking kids
      bool sibs_eq = (*(root.sibs) == *(this->sibs));//checking sibs
      return (kids_eq && sibs_eq);
    }
  }
    return false;//if none of the conditions are false, the Trees are not equal anyways, so return false
  }

template <typename T>
std::ostream& operator<<(std::ostream &os,const Tree<T>& rt)  {//does same thing as toString() function
  os<<rt.toString();
  return os;
}

template <typename T>
std::string Tree<T>::toString() const { // all characters, separated by newlines, including at the end                                   
  std::string output;   
  std::stringstream ss;//string stream storing all the output   
  ss<<this->data<<"\n";
  if(kids) {
    ss<<kids->toString();
  }
  if(sibs) {
    ss<<sibs->toString();
  }
  output=ss.str();
  return output;

}

template <typename T>
bool Tree<T>::addChild(T value){//T version of add child
  Tree<T> *to_add = new Tree(value);
  bool result = addChild(to_add);
  if(!result) {
    delete to_add;//freeing memory if addChild doesnt get executed
  }
  return result;//else normal execution and memory will be handled by destructor 
}

// add tree root for better building, root should have null prev and sibs
// returns false on any type of failure, including invalid root
template <typename T>
bool Tree<T>::addChild(Tree<T> *root){
  if(root->prev != nullptr || root->sibs != nullptr) {//checking if parameter CTree is a root node
    return false;
  }
  if(kids == nullptr) {//if kid doesnt exist the make root as the kid
    kids = root;
    kids->prev = this;
    return true;
  }
  else {//if kids exist, add root as sibling to kids 
    return kids->addSibling(root);
  }
}

template <typename T>
bool Tree<T>::addSibling(T value){//T version of addSibling 
  Tree<T> *to_add=new Tree(value);
  bool result = addSibling(to_add);
  if(!result) {
    delete to_add;//freeing memory if addSibling doesnt get executed
  }
  return result;//else normal execution and memory will be handled by destructor
  
}

template <typename T>
bool Tree<T>::addSibling(Tree<T> *root){
  if(root->prev != nullptr || root->sibs != nullptr) {//checking if parameter CTree is a root node 
    return false;
  }

  if(this->prev == nullptr && this->sibs==nullptr) {//checking that the CTree that addSibling is called on is not a root node
    return false;
  }
  else {

    Tree<T> *temp = this;
    while(temp) {//in case the value already exists                                                                                
      if((root->data) == (temp->data)) {
        return false;
      }
      temp = temp->sibs;
    }

    if((root->data) < (this->data)) {//if the value is less than the first sibling
    Tree<T> *temporary = this->prev;
      root->sibs= this;
      this->prev->kids = root;
      this->prev = root;
      root->prev = temporary;
      return true;
    }
    if(sibs == nullptr) {//if there is no sibling present
      sibs = root;
      sibs->prev = this;
      return true;
     }

    temp=this;//to get temp pointer back to the the root node of the tree to be added as a sibling
      while(temp->sibs && (temp->sibs)->data < root->data) {//checking where root needs to get added to be in order  
      temp = temp->sibs;
    }

    if(temp->sibs == nullptr) {//when root gets added as the last sibling 
      temp->sibs = root;
      root->prev = temp;
      return true;
    }
    else {//when root gets added somewhere in the sibs linked list but not in the end 
      Tree<T> *temporary = temp->sibs;
      root->sibs = temp->sibs;
      temp->sibs = root;
      temporary->prev = root;
      root->prev = temp;
      return true;
    }
  }

}



