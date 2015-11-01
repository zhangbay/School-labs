/*#include "TreeDB.h"
#include <iostream>

using namespace std;

TreeDB::TreeDB()
{
    root=NULL;
    probesCount=1;
    storedCount=0;
}

TreeDB::~TreeDB()
{
   if(root==NULL)
    return;
   delete_tree(root);
   root=NULL;
}

void TreeDB::delete_tree(TreeNode * myroot)
{
    if (myroot == NULL)
    {
        return;
    }
    delete_tree(myroot->getLeft());
    delete_tree(myroot->getRight());
    delete myroot;

}

bool TreeDB::insert(DBentry* newEntry)
{
        TreeNode *ins=new TreeNode(newEntry);
        if (root == NULL) { // Basis
            root = ins;
            root->setLeft(NULL);
            root->setRight(NULL);
            return true;
        }
        return insert_bst(ins, root);

}

bool TreeDB::insert_bst(TreeNode *ins, TreeNode *curr)
{
    if(ins->getEntry()->getName()==curr->getEntry()->getName())
        return false;
    if(ins->getEntry()->getName()<curr->getEntry()->getName())//Go Left
    {
        if(curr->getLeft()==NULL)
            {
                curr->setLeft(ins);
                return true;
            }
        else
            {
                insert_bst(ins, curr->getLeft());
            }
    }
    else{
        if (curr->getRight() == NULL)
        {
            curr->setRight(ins);
            return true;
        }
        else{
                insert_bst (ins, curr->getRight());
        }
    }
    return false;
}

DBentry* TreeDB::find(string name)
{
    if(root==NULL)
    {
        return NULL;
    }
    return searchTree(root, name);
}
DBentry * TreeDB::searchTree(TreeNode *curr ,string name)
{
    if(curr->getEntry()->getName()==name)
    {   storedCount=probesCount;
        probesCount=1;
        return curr->getEntry();
    }

    if(name<curr->getEntry()->getName())//Go Left
    {
        if(curr->getLeft()==NULL)
            {
                return NULL;
            }
        probesCount++;
        return searchTree(curr->getLeft(),name);
    }
    else//go right
        {
            if(curr->getRight()==NULL)
            {
                return NULL;
            }
            probesCount++;//updates count
            return searchTree(curr->getRight(),name);
        }
}

bool TreeDB::remove(string name)
{
    if (root==NULL)
        return false;
    else if(find(name)==NULL)
        return false;
    else{
        root->removing(root,name);
        return true;
    }
}

void TreeDB::clear()
{
   if(root==NULL)
    return;
   delete_tree(root);
   root=NULL;
}

void TreeDB::printProbes() const
{
    cout<<storedCount<<endl;
}

void TreeDB::countActive() const
{   int activeCount=0;
    activesearch(root, activeCount);
    cout<<activeCount<<endl;
}

void TreeDB::activesearch(TreeNode * searchnode, int & counts) const
{
        if (searchnode != NULL)
            {
                if(searchnode->getEntry()->getActive()==true)
                {
                    counts++;
                }
                activesearch(searchnode->getLeft(),counts);
                activesearch(searchnode->getRight(),counts);
            }
}

void TreeDB::printall(TreeNode *node) const
{
    if(node!=NULL)
    {
        if(node->getLeft()!=NULL)
        {
            printall(node->getLeft());//go left
        }
        string status;
        if(node->getEntry()->getActive()==true)
            status="active";
        else status="inactive";
        cout<<node->getEntry()->getName()<<" : "<<node->getEntry()->getIPaddress()<<" : "<<status<<endl;
        if(node->getRight()!=NULL)
        {
            printall(node->getRight());//go right
        }
    }
}

*/
#include "TreeDB.h"
#include <iostream>

using namespace std;

TreeDB::TreeDB()
{
    root=NULL;
    probesCount=1;
    storedCount=0;
}

TreeDB::~TreeDB()
{
   if(root==NULL)
    return;
   delete_tree(root);
   root=NULL;
}

void TreeDB::delete_tree(TreeNode * myroot)
{
    if (myroot == NULL)
    {
        return;
    }
    delete_tree(myroot->getLeft());
    delete_tree(myroot->getRight());
    delete myroot;

}

bool TreeDB::insert(DBentry* newEntry)
{
        TreeNode *ins=new TreeNode(newEntry);
        if (root == NULL) { // Basis
            root = ins;
            root->setLeft(NULL);
            root->setRight(NULL);
            return true;
        }
        return insert_bst(ins, root);

}

bool TreeDB::insert_bst(TreeNode *ins, TreeNode *curr)
{
    if(ins->getEntry()->getName()==curr->getEntry()->getName())
        return false;
    if(ins->getEntry()->getName()<curr->getEntry()->getName())//Go Left
    {
        if(curr->getLeft()==NULL)
            {
                curr->setLeft(ins);
                return true;
            }
        else
            {
                insert_bst(ins, curr->getLeft());
            }
    }
    else{
        if (curr->getRight() == NULL)
        {
            curr->setRight(ins);
            return true;
        }
        else{
                insert_bst (ins, curr->getRight());
        }
    }
    return false;
}

DBentry* TreeDB::find(string name)
{
    if(root==NULL)
    {
        return NULL;
    }
    return searchTree(root, name);
}
DBentry * TreeDB::searchTree(TreeNode *curr ,string name)
{
    if(curr->getEntry()->getName()==name)
    {   storedCount=probesCount;
        probesCount=1;
        return curr->getEntry();
    }

    if(name<curr->getEntry()->getName())//Go Left
    {
        if(curr->getLeft()==NULL)
            {
                return NULL;
            }
        probesCount++;
        return searchTree(curr->getLeft(),name);
    }
    else
        {
            if(curr->getRight()==NULL)
            {
                return NULL;
            }
            probesCount++;//updates count
            return searchTree(curr->getRight(),name);
        }
}

bool TreeDB::remove(string name)
{
    if (root==NULL)
        return false;
    else if(find(name)==NULL)
        return false;
    else{
        removing(root,name);
        return true;
    }
}

void TreeDB::clear()
{
   if(root==NULL)
    return;
   delete_tree(root);
   root=NULL;
}

void TreeDB::printProbes() const
{
    cout<<storedCount<<endl;
}

void TreeDB::countActive() const
{   int activeCount=0;
    activesearch(root, activeCount);
    cout<<activeCount<<endl;
}

void TreeDB::activesearch(TreeNode * searchnode, int & counts) const
{
        if (searchnode != NULL)
            {
                if(searchnode->getEntry()->getActive()==true)
                {
                    counts++;
                }
                activesearch(searchnode->getLeft(),counts);
                activesearch(searchnode->getRight(),counts);
            }
}

void TreeDB::printall(TreeNode *node) const
{
    if(node!=NULL)
    {
        if(node->getLeft()!=NULL)
        {
            printall(node->getLeft());
        }
        string status;
        if(node->getEntry()->getActive()==true)
            status="active";
        else status="inactive";
        cout<<node->getEntry()->getName()<<" : "<<node->getEntry()->getIPaddress()<<" : "<<status<<endl;
        if(node->getRight()!=NULL)
        {
            printall(node->getRight());
        }
    }
}

 DBentry* TreeDB::Maximum(TreeNode *curr)
{
    if(curr->getRight()==NULL)
        return curr->getEntry();
    else return Maximum(curr->getRight()) ;
}


 void TreeDB::removing(TreeNode * & curr, string name)
 {
      if(name<curr->getEntry()->getName())
        {
            if(curr->getLeft()==NULL)
            {
                return;
            }
        TreeNode * left=curr->getLeft();
       
        removing(left,name);
        curr->setLeft(left);
        return;
        }
    if(name>curr->getEntry()->getName())
        {
            if(curr->getRight()==NULL)
                {
                        return;
                }
            TreeNode * right= curr->getRight();
            removing(right,name);
            curr->setRight(right);
            return;
        }

 //value found
    if((curr->getLeft()==NULL) && (curr->getRight()==NULL))//no children
        {   
            delete curr;
            curr=NULL;
            return;
        }
 //1 child
    else if((curr->getLeft()==NULL) && (curr->getRight()!=NULL))
        {
            TreeNode *right=curr->getRight();
            delete curr;
            curr=right;
            return;
        }
      else if((curr->getLeft()!=NULL) && (curr->getRight()==NULL))
        {
            TreeNode *left=curr->getLeft();
            delete curr;
            curr=left;
            return;
        }
 // node has two children

    else
    {
      
        TreeNode * left=curr->getLeft();
        DBentry *replacedDB = Maximum(curr->getLeft());
        removing(left,replacedDB->getName());
        curr->setLeft(left);
         
        
        curr->getEntry()->setName(replacedDB->getName());
        curr->getEntry()->setActive(replacedDB->getActive());
        curr->getEntry()->setIPaddress(replacedDB->getIPaddress());
        delete replacedDB;
    }
 }


