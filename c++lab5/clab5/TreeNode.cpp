#include "TreeNode.h"
#include <iostream>

using namespace std;

TreeNode::TreeNode(DBentry* _entryPtr)
{
    entryPtr=_entryPtr;
    left=NULL;
    right=NULL;
}

TreeNode::~TreeNode()
{
    delete entryPtr;
    left=NULL;
    right=NULL;
}

    // sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft)
{
    left=newLeft;
}

    // sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight)
{
    right=newRight;
}

    // gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const
{
    return left;
}

    // gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const
{
    return right;
}
/*
void TreeNode::removing(TreeNode* & curr, string name)
{
 if(name<entryPtr->getName())
 {
     if(left==NULL)
        {
            return;
        }
     left->removing(left,name);
     return;
 }
  if(name>entryPtr->getName())
 {
     if(right==NULL)
        return;
     right->removing(right,name);
     return;
 }

 //value found
 if((left==NULL) && (right==NULL))//no children
 {
     curr=NULL;
     delete this;

 }
 //1 child
 else if((left==NULL) && (right!=NULL))
 {
     curr=right;
     right=NULL;
     delete this;

 }
 else if((left!=NULL) && (right==NULL))
 {
     curr=left;
     left=NULL;
     delete this;

 }
 // node has two children

else
 {
     DBentry *replacedDB=left->getMaximum();
     left->removing(left,replacedDB->getName());
     entryPtr->setActive(replacedDB->getActive());
     entryPtr->setIPaddress(replacedDB->getIPaddress());
     entryPtr->setName(replacedDB->getName());
     delete replacedDB;
 }
}

DBentry* TreeNode::getMaximum()
{
    if(right==NULL)
        return entryPtr;
    else return right->getMaximum() ;
}
*/
    // returns a pointer to the DBentry the TreeNode contains.
DBentry* TreeNode::getEntry() const
{
    return entryPtr;
}
