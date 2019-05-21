/*
 * Filename: HCTree.cpp
 * Author: Ajay Nair
 * Userid: cs100sp19bg
 * Date: May 12, 2019
 * Description: Definitions for HCTree class member functions.
 */
#include "HCTree.hpp"

/*
 * Function Name: HCTree()
 * Function Prototype: HCTree(std::vector<std::pair<byte, int>> data);
 * Description: Constructor for HCTree object. Fills HCTree with the contents of
 *              the passed vector.
 * Parameters: data - vector of pairs where each element contains the symbol of
 *                    a supposed leaf node and the height at which it should be
 *                    in the tree. contains the leaf nodes of an HCTree in the
 *                    order of left-most leaf node first leading to right-most
 *                    leaf node last.
 * Return Value: None
 */
HCTree::HCTree(std::vector<std::pair<byte, int>> data) : 
                                                        root(new HCNode(0, 0)) {
  HCNode* cur = this->root;
  HCNode** newNodePtr;
  bool done;
  int curDepth = 0;

  for(std::vector<std::pair<byte, int>>::iterator it = data.begin();
                                                     it != data.end(); it++) {
    // keep building edges till depth of current leaf node data is reached.
    while(curDepth < (*it).second) {
      // ensures we build, favoring building to the left before the right
      newNodePtr = (!cur->getZeroChild()) ? cur->getZeroChildPtr() :
                                            cur->getOneChildPtr();
      *newNodePtr = new HCNode(0, 0, nullptr, nullptr, cur);
      cur = *newNodePtr;
      curDepth++;
    }

    // once position of current leaf node has been found, assign its symbol to
    //   the new leaf node
    cur->setSymbol((*it).first);
    done = false;

    // traverse back up the tree until the root is reached or we found the next
    //   unfinished branch of the tree
    while(cur != this->root && !done) {
      done = !cur->getParent()->getOneChild();
      cur = cur->getParent();
      curDepth--;
    }
  }
}

/*
 * Function Name: build()
 * Function Prototype: build(const vector<int>& freqs);
 * Description: Builds this HCTree using the frequencies in passed vector. Each
 *              vector index is the integer value of an ASCII character. Tree
 *              is built using huffman encoding algorithm
 * Parameters: freqs - vector of frequencies, each element is the frequency of
 *                     its index value as a character
 * Return Value: None
 */
void HCTree::build(const vector<int>& freqs) {
  huffman_queue trees;
  HCNode* tree;

  // populate the queue of leaf nodes
  for(unsigned int i = 0; i < freqs.size(); i++) {
    if(freqs[i] != 0) {
      tree = new HCNode(freqs[i], i);
      this->leaves[i] = tree;
      trees.push(tree);
    }
  }

  HCNode* chZero;
  HCNode* chOne;
  HCNode* parent;

  // keep processing queue of trees as long as there is more than 1 tree in the
  //   queue
  while(trees.size() > 1) {
    // pop two minimum frequency nodes off queue to combine into one tree
    chZero = trees.top();
    trees.pop();

    chOne = trees.top();
    trees.pop();

    
    parent = new HCNode(chZero->getCount() + chOne->getCount(),
                                             chOne->getSymbol(), chZero, chOne);

    chZero->setParent(parent);
    chOne->setParent(parent);

    // push newly created tree's root back into stack
    trees.push(parent);
  }

  // the last remaining node is the root of the completed tree
  this->root = trees.top();
}

/*
 * Function Name: encode()
 * Function Prototype: void encode(byte symbol, ofstream& out) const;
 * Description: Writes the huffman code of the given byte to the output stream.
 *              No compression is used to print the huffman code.
 * Parameters: symbol - the symbol to be encoded and written to the output
 *                      stream
 *             out - reference to the output stream to print the encoded symbol
 *                   to
 * Return Value: None
 */
void HCTree::encode(byte symbol, ofstream& out) const {
  this->encode(this->leaves[symbol], out);
}

/*
 * Function Name: encode()
 * Function Prototype: void encode(byte symbol, BitOutputStream& out) const;
 * Description: Writes the huffman code of the given byte to the output stream.
 *              Compresses code by writing each element of the huffman code as a
 *              literal bit.
 * Parameters: symbol - the symbol to be encoded and written to the output
 *                      stream
 *             out - reference to the BitOutputStream that will print the
 *                   encoded symbol to the output stream as a literal bit
 * Return Value: None
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
  this->encode(this->leaves[symbol], out);
}

/*
 * Function Name: decode()
 * Function Prototype: int decode(ifstream& in) const;
 * Description: Reads and decodes the next symbol in an input stream containing
 *              data encoded using this huffman tree.
 * Parameters: in - reference to the input stream to read the huffman code from
 * Return Value: int cast of decoded symbol
 */
int HCTree::decode(ifstream& in) const {
  unsigned char codeSym = 0;
  HCNode* cur = this->root;
  while(cur->getZeroChild() && cur->getOneChild()) {
    in >> codeSym;
    cur = (codeSym == '0') ? cur->getZeroChild() : cur->getOneChild();
  }

  return cur->getSymbol();
}

/*
 * Function Name: decode()
 * Function Prototype: int decode(BitInputStream& in) const;
 * Description: Reads and decodes the next symbol in an input stream containing
 *              data encoded using this huffman tree. The input stream here
 *              contains the huffman codes as literal bits, instead of char
 *              representations of bit values.
 * Parameters: in - reference to BitInputStream containing the huffman code as
 *                  a stream of literal bits
 * Return Value: int cast of decoded symbol
 */
int HCTree::decode(BitInputStream& in) const {
  HCNode* cur = this->root;

  // traverse till leaf node reached
  while(cur->getZeroChild() && cur->getOneChild()) {
    cur = (in.readBit() == 0) ? cur->getZeroChild() : cur->getOneChild();
  }

  return cur->getSymbol();
}

/*
 * Function Name: saveTree()
 * Function Prototype: void saveTree(BitOutputStream* out);
 * Description: Saves contents of this tree object by storing each leaf node's
 *              data in order from left to right
 * Parameters: out - pointer to BitOutputStream containing output stream to
 *                   write HCTree data to
 * Return Value: None
 */
void HCTree::saveTree(BitOutputStream* out) {
  this->saveHelper(this->root, out, 0);
}

/*
 * Function Name: ~HCTree()
 * Function Prototype: ~HCTree();
 * Description: Destructor for this HCTree object. Deletes memory allocated for
 *              every node in this tree object.
 * Parameters: None
 * Return Value: None
 */
HCTree::~HCTree() {
  this->deleteAll(this->root);
  this->root = nullptr;
}

/*
 * Function Name: deleteAll()
 * Function Prototype: void deleteAll(HCNode* node);
 * Description: Helper function for destructor. Recursively traverses and
 *              deletes all nodes in the tree
 * Parameters: node - pointer to root node of subtree to delete.
 * Return Value: None
 */
void HCTree::deleteAll(HCNode* node) {
  if(!node)
    return;

  this->deleteAll(node->getZeroChild());
  node->setZeroChild(nullptr);

  this->deleteAll(node->getOneChild());
  node->setOneChild(nullptr);

  node->setParent(nullptr);

  delete node;
}

/*
 * Function Name: encode()
 * Function Prototype: void encode(HCNode* node, ofstream& out) const;
 * Description: Helper function for public encode function. Recursively
 *              traverses up from leaf node containing symbol to be encoded,
 *              then unwinds recursion stack once root node is reached to print
 *              each element of huffman code as a char
 * Parameters: node - pointer to current node in recursive traversal
 *             out - reference to output stream to print the huffman code to
 * Return Value: None
 */
void HCTree::encode(HCNode* node, ofstream& out) const {
  if(!node)
    return;

  this->encode(node->getParent(), out);
  if(node->getParent()) {
    out.put((node->getParent()->getZeroChild() == node) ? '0' : '1');
    out.flush();
  }
}

/*
 * Function Name: encode()
 * Function Prototype: void encode(HCNode* node, BitOutputStream& out) const;
 * Description: Helper function for public encode function. Recursively
 *              traverses up from leaf node containing symbol to be encoded,
 *              then unwinds recursion stack once root node is reached to print
 *              each element of huffman code as a literal bit
 * Parameters: node - pointer to current node in recursive traversal
 *             out - reference to BitOutputStream containing output stream to
 *                   print the encoded bits to
 * Return Value: None
 */
void HCTree::encode(HCNode* node, BitOutputStream& out) const {
  if(!node)
    return;
  this->encode(node->getParent(), out);
  // this check ensures we skip to next down in recursion stack when at root
  if(node->getParent()) {
    out.writeBit((node->getParent()->getZeroChild() == node) ? 0 : 1);
  }
}

/*
 * Function Name: saveHelper()
 * Function Prototype: void saveHelper(
 *                                   HCNode* node, BitOutputStream* out, int d);
 * Description: Helper function for saveTree function. Recursively traverses to
 *              each leaf node in tree and writes its data to the output stream.
 *              Writes leaf node data in order from left-most leaf node, to
 *              right-most leaf node. Data stored on each leaf-node includes
 *              node's symbol and depth at which it is found in the HC-tree.
 * Parameters: node - pointer to current node in recursive traversal
 *             out - pointer to BitOutputStream containing output stream to
 *                   print leaf node data to
 *             d - current traversal depth in tree
 * Return Value: None
 */
void HCTree::saveHelper(HCNode* node, BitOutputStream* out, int d) {
  if(node) {
    if(!(node->getZeroChild() || node->getOneChild())) { // found leaf node
      // write leaf-node's symbol and depth in tree to output stream
      out->writeByte(node->getSymbol());
      out->writeByte(d);
    }
    else { // traverse recursively, favoring left traversal before right
      this->saveHelper(node->getZeroChild(), out, d + 1);
      this->saveHelper(node->getOneChild(), out, d + 1);
    }
  }
}
