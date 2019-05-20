#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>

typedef unsigned char byte;

/** A class, instances of which are nodes in an HCTree.
*/
class HCNode {
  public:
    HCNode(int count, byte symbol,
           HCNode* c0 = nullptr, HCNode* c1 = nullptr, HCNode* p = nullptr);

    /** Less-than comparison, so HCNodes will work in std::priority_queue
     *  We want small counts to have high priority.
     *  And we want to break ties deterministically.
     */
    bool operator<(const HCNode& other);

    int getCount() const;
    byte getSymbol() const;
    HCNode* getZeroChild() const;
    HCNode* getOneChild() const;
    HCNode* getParent() const;
    HCNode** getZeroChildPtr();
    HCNode** getOneChildPtr();

    void setCount(int count);
    void setSymbol(byte symbol);
    void setZeroChild(HCNode* c0);
    void setOneChild(HCNode* c1);
    void setParent(HCNode* p);

  private:
    int count;
    byte symbol; // byte in the file we're keeping track of
    HCNode* c0;  // pointer to '0' child
    HCNode* c1;  // pointer to '1' child
    HCNode* p;   // pointer to parent
};

#endif // HCNODE_HPP
