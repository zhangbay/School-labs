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
    delete_tree(myroot->getLeft());//delete leftside
    delete_tree(myroot->getRight());//delete rightside
    delete myroot;

}

bool TreeDB::insert(DBentry* newEntry)
{
        TreeNode *ins=new TreeNode(newEntry);
        if (root == NULL) { // set all to null first if there's nothing there
            root = ins;
            root->setLeft(NULL);
            root->setRight(NULL);
            return true;
        }
        return insert_bst(ins, root);//recurse if root is filled

}

bool TreeDB::insert_bst(TreeNode *ins, TreeNode *curr)
{
    if(ins->getEntry()->getName()==curr->getEntry()->getName())//exists, no insert
        return false;
    if(ins->getEntry()->getName()<curr->getEntry()->getName())//Go Left
    {
        if(curr->getLeft()==NULL)//reached the end can insert
            {
                curr->setLeft(ins);
                return true;
            }
        else
            {
                insert_bst(ins, curr->getLeft());
            }
    }
    else{//go right
        if (curr->getRight() == NULL)//reached end can insert
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
    if(curr->getEntry()->getName()==name)//find and the probescount is stored in another count to be printed, then probescount reset
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
                if(searchnode->getEntry()->getActive()==true)//for every active counts goes up
                {
                    counts++;
                }
                activesearch(searchnode->getLeft(),counts);//go left
                activesearch(searchnode->getRight(),counts);//go right
            }
}

void TreeDB::printall(TreeNode *node) const
{//post-order print
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
        TreeNode * lefttree=curr->getLeft();
        removing(lefttree,name);
        curr->setLeft(lefttree);
        return;
        }
    if(name>curr->getEntry()->getName())
        {
            if(curr->getRight()==NULL)
                {
                        return;
                }
            TreeNode * righttree= curr->getRight();
            removing(righttree,name);
            curr->setRight(righttree);
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
            TreeNode *righttree=curr->getRight();
            delete curr;
            curr=righttree;
            return;
        }
      else if((curr->getLeft()!=NULL) && (curr->getRight()==NULL))
        {
            TreeNode *lefttree=curr->getLeft();
            delete curr;
            curr=lefttree;
            return;
        }
 // node has two children

    else
    {
        TreeNode * left=curr->getLeft();
        DBentry *replacedDB = Maximum(left);
        //updates the node 
        curr->getEntry()->setName(replacedDB->getName());
        curr->getEntry()->setActive(replacedDB->getActive());
        curr->getEntry()->setIPaddress(replacedDB->getIPaddress());
        //removes the maximum
        removing(left,replacedDB->getName());
        curr->setLeft(left);

    }
 }


