

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

//#include "dsexceptions.h"
#include <algorithm>
#include <cassert>
#include <stack>
#include "Vector.h"
using namespace std;       


template <typename T>
class BinarySearchTree
{
 private:

    struct BinaryNode
    {
        T element;
        BinaryNode *left;
        BinaryNode *right;
		BinaryNode *parent;

        BinaryNode( const T & theElement, BinaryNode *lt, BinaryNode *rt,
			BinaryNode *par)
		  : element(theElement ), left( lt ), right( rt ), parent(par) { }
    };

 public:
	 
    BinarySearchTree( ) : root(0) {}

    BinarySearchTree( const BinarySearchTree & rhs ) : root( 0 )
    {
        root = clone( rhs.root );
    }
    
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    const T & findMin( ) const
    {
		assert(!isEmpty());
        return findMin( root )->element;
    }

    const T & findMax( ) const
    {
		assert(!isEmpty());
        return findMax( root )->element;
    }

    bool contains( const T & x ) const
    {
        return contains( x, root );
    }

    bool isEmpty( ) const
    {
        return root == 0;
    }

    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

	void printInternal() const
	{
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printInternal(root, 0);
	}
	
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    
    void insert( const T & x )
    {
		//cout << "Outer insert: " << x << endl;
	    insert( x, root, root);
    }
    
    void remove( const T & x )
    {
        remove( x, root );
    }

	void parent_check() 
	{
		parent_check(root);
	}

    // NEW FOR HW5 
    // depth is the number of levels in the 
    // bst from the root to the deepest leaf;
   
    int depth() const
    {
        return depth(root);  // HW5: DEFINE this member fct below
    }

    // NEW; provided for HW5;
    // fully defined; 
    void collect(Vector<T>& coll)
    {
        collect(root, coll);
    }

    int cardinality() const
    {
        return cardinality(root);
    }


  private:
    
    BinaryNode *root;

    /**
     INTERNAL METHODS in private ... 
     */
    void insert( const T & x, BinaryNode * & t, BinaryNode * & par)
    {
	   if( t == 0 )
		{
            t = new BinaryNode( x, 0, 0, par );
		}
        else if( x < t->element )
            insert( x, t->left, t );
        else if( t->element < x )
            insert( x, t->right, t );
        else
            ;  // Duplicate; do nothing
    }
 
    void remove( const T & x, BinaryNode * & t )
    {
        if( t == 0 )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != 0 && t->right != 0 ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            //t = ( t->left != 0 ) ? t->left : t->right;
			if (t->left != 0)
			{
				t->left->parent = t->parent;
				t = t->left;
			}
			else
			{
				if (t->right != 0)
					t->right->parent = t->parent;
				t = t->right;
			}
            delete oldNode;
        }
    }

	void parent_check(BinaryNode *t)
	{
		if (t == 0)
			return;
		if (t->parent == 0)
			cout << t->element << " has parent null" << endl;
		else
			cout << t->element << " has parent " << t->parent->element << endl;
		parent_check(t->left);
		parent_check(t->right);
		return;
	}

    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == 0 )
            return 0;
        if( t->left == 0 )
            return t;
        return findMin( t->left );
    }

    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != 0 )
            while( t->right != 0 )
                t = t->right;
        return t;
    }

    bool contains( const T & x, BinaryNode *t ) const
    {
        if( t == 0 )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    void makeEmpty( BinaryNode * & t )
    {
        if( t != 0 )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = 0;
    }

    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != 0 )
        {
            printTree( t->left, out );
            out << t->element << " ";
            printTree( t->right, out );
        }
    }

	void printInternal(BinaryNode *t, int offset) const
	{
		for (int i = 1; i <= offset; i++)
			cout << "..";
		if (t == 0)
		{
			cout << "#" << endl;
			return;
		}
		cout << t->element << endl;
		printInternal(t->left, offset + 1);
		printInternal(t->right, offset + 1);
		return;
	}

    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == 0 )
            return 0;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ),
		clone(t->parent) };
    }

    // TO BE COMPLETED FOR HW5 Task 1:
    // the depth of the bst rooted in the BinaryNode pointed to by t
    int depth(BinaryNode* t) const
    {
        if (t == nullptr)
            return 0;       // t is null pointer, empty tree, depth 0; 

        // case: tree connsists of just one node pointed to by t;
        // that is: not left and right subtrees exist; what 
        // is the appropriate depth for a tree with single node?
        // ... 
        if(t->left == nullptr && t->right == nullptr)
            return 1;

          
        // case:  node under t has left or subtree, or both; 
        // which subtree has the larger depth; total depth
        // is 1 + that larger depth
        // ...
        return 1 + max(depth(t->left), depth(t->right));
    }

    void collect(BinaryNode* t, Vector<T>& vec)
    {
        if (t == nullptr)
            return;
        if (t->left == nullptr && t->right == nullptr)
        {
            vec.push_back(t->element);
            return;
        }
        collect(t->left, vec);
        vec.push_back(t->element);
        collect(t->right, vec);
        return;
    }     

    int cardinality(BinaryNode *t) const
    {
        if(t == nullptr)
            return 0;
        if (t->left == nullptr and t->right == nullptr)
            return 1;
        return 1 + cardinality(t->left) + cardinality(t->right);
    }
};




#endif
