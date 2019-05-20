#include "HCTree.hpp"

HCTree::HCTree(std::vector<std::pair<byte, int>> data) : 
                                                        root(new HCNode(0, 0)) {
  HCNode* cur = this->root;
  HCNode** newNodePtr;
  bool done;
  int curDepth = 0;

  for(std::vector<std::pair<byte, int>>::iterator it = data.begin();
                                                     it != data.end(); it++) {
    while(curDepth < (*it).second) {
      newNodePtr = (!cur->getZeroChild()) ? cur->getZeroChildPtr() :
                                            cur->getOneChildPtr();
      *newNodePtr = new HCNode(0, 0, nullptr, nullptr, cur);
      cur = *newNodePtr;
      curDepth++;
    }

    cur->setSymbol((*it).first);
    done = false;

    while(cur != this->root && !done) {
      done = !cur->getParent()->getOneChild();
      cur = cur->getParent();
      curDepth--;
    }
  }
}

void HCTree::build(const vector<int>& freqs) {
  huffman_queue trees;
  HCNode* tree;
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
  while(trees.size() > 1) {
    chZero = trees.top();
    trees.pop();

    chOne = trees.top();
    trees.pop();

    parent = new HCNode(chZero->getCount() + chOne->getCount(),
                                             chOne->getSymbol(), chZero, chOne);

    chZero->setParent(parent);
    chOne->setParent(parent);

    trees.push(parent);
  }

  this->root = trees.top();
}

void HCTree::encode(byte symbol, ofstream& out) const {
  this->encode(this->leaves[symbol], out);
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
  this->encode(this->leaves[symbol], out);
}

int HCTree::decode(ifstream& in) const {
  unsigned char codeSym = 0;
  HCNode* cur = this->root;
  while(cur->getZeroChild() && cur->getOneChild()) {
    in >> codeSym;
    cur = (codeSym == '0') ? cur->getZeroChild() : cur->getOneChild();
  }

  return cur->getSymbol();
}

int HCTree::decode(BitInputStream& in) const {
  HCNode* cur = this->root;

  while(cur->getZeroChild() && cur->getOneChild()) {
    cur = (in.readBit() == 0) ? cur->getZeroChild() : cur->getOneChild();
  }

  return cur->getSymbol();
}

void HCTree::saveTree(BitOutputStream* out) {
  this->saveHelper(this->root, out, 0);
}

HCTree::~HCTree() {
  this->deleteAll(this->root);
  this->root = nullptr;
}

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

void HCTree::encode(HCNode* node, ofstream& out) const {
  if(!node)
    return;

  this->encode(node->getParent(), out);
  if(node->getParent()) {
    out.put((node->getParent()->getZeroChild() == node) ? '0' : '1');
    out.flush();
  }
}

void HCTree::encode(HCNode* node, BitOutputStream& out) const {
  if(!node)
    return;
  this->encode(node->getParent(), out);
  if(node->getParent()) {
    out.writeBit((node->getParent()->getZeroChild() == node) ? 0 : 1);
  }
}

void HCTree::saveHelper(HCNode* node, BitOutputStream* out, int d) {
  if(node) {
    if(!(node->getZeroChild() || node->getOneChild())) {
      out->writeByte(node->getSymbol());
      out->writeByte(d);
    }
    else {
      this->saveHelper(node->getZeroChild(), out, d + 1);
      this->saveHelper(node->getOneChild(), out, d + 1);
    }
  }
}
