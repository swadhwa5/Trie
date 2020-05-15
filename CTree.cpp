#include <iostream>
#include <cstdlib>
#include <string>
#include "CTree.h"
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::ostream;

// siblings and children must be unique, return true if added, false otherwise                                                                                                                    
CTree::CTree(char ch): data(ch), kids(nullptr),sibs(nullptr),prev(nullptr) {//constructor function
}

CTree::~CTree() {//destructor function
  if(this->kids) {//checking if it has kids                                                                                                                 
    delete this->kids;
  }
  if(this->sibs) {//checking if it has siblings                                                                                                             
    delete this->sibs;
  }
}


CTree& CTree::operator^(CTree& rt){  //^ operator to do the same thing as addChild
  addChild(&rt);
  return *this;
}

bool CTree::operator==(const CTree &root){ // return true if two CTrees match node by node    
  if(root.sibs == nullptr && root.kids == nullptr && this->sibs == nullptr && this->kids == nullptr) {//in case both the CTrees are empty
    return true;
  }

  if(root.data == this->data) {//any cases will be checked if the data in the first node is same, else return false
    if(((root.sibs == nullptr) && (this->sibs == nullptr)) && ((root.kids != nullptr) && (this->kids != nullptr))) {//when both CTrees dont have siblings, but have kids
      return (*(this->kids) == *(root.kids));
    }
    
    if(((root.kids == nullptr) && (this->kids == nullptr)) && ((root.sibs != nullptr) && (this->sibs != nullptr))) {//when both CTrees have kids, but not siblings
      return (*(this->sibs) == *(root.sibs));
    }
    
    if(((root.sibs !=nullptr) && (this->sibs != nullptr)) && ((root.kids !=nullptr) && (this->kids != nullptr))) {//when both CTress have kids as well as siblings
      bool kids_eq = (*(root.kids) == *(this->kids));//comparing kids recursively
      bool sibs_eq = (*(root.sibs) == *(this->sibs));//comparing sibs recursively
      return (kids_eq && sibs_eq);
    }
  }
  return false;//if none of the above conditions are present then they are not equal anyway so return false
  }


std::ostream& operator<<(ostream &os,const CTree& rt) {//does same thing as toString() function
  os<<rt.toString();
  return os;
}


std::string CTree::toString() const { // all characters, separated by newlines, including at the end    
  string output;
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

bool CTree::addChild(char ch){//character version of add child
  CTree *to_add = new CTree(ch);
  bool result = addChild(to_add);
    if(!result) {
      delete to_add;//freeing memory if addChild doesnt get executed
    }
    return result;//else normal execution and memory will be handled by destructor		 
}

// add tree root for better building, root should have null prev and sibs

// returns false on any type of failure, including invalid root

bool CTree::addChild(CTree *root){
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


bool CTree::addSibling(char ch){//character version of addSibling
  CTree *to_add=new CTree(ch);
  bool result = addSibling(to_add);
  if(!result) {//freeing memory if addSibling doesnt get executed
    delete to_add;
  }
  return result;//else normal execution and memory will be handled by destructor 

}
bool CTree::addSibling(CTree *root){
  if(root->prev != nullptr || root->sibs != nullptr) {//checking if parameter CTree is a root node
    return false;
  }

  if(this->prev == nullptr && this->sibs==nullptr) {//checking that the CTree that addSibling is called on is not a root node
    return false;
  }
  else {

    CTree *temp = this;
    while(temp) {//in case the value already exists                                                                                                                                                         
      if((root->data) == (temp->data)) {
	return false;
      }
      temp = temp->sibs;
    }
    
    if((root->data) < (this->data)) {//if the value is less than the first sibling
      CTree *temporary = this->prev;
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
      CTree *temporary = temp->sibs;
      root->sibs = temp->sibs;
      temp->sibs = root;
      temporary->prev = root;
      root->prev = temp;
      return true;
    }
  }      
  
}
