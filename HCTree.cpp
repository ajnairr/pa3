#include "HCTree.hpp"

HCTree::HCTree(std::vector<std::pair<byte, int>> data) : 
                                                        root(new HCNode(0, 0)) {
  HCNode* cur = this->root;
  HCNode** newNodePtr;
  bool done;
  int d = 0;

  for(std::vector<std::pair<byte, int>>::iterator it = data.begin();
                                                     it != data.end(); it++) {
    while(d < (*it).second) {
      newNodePtr = (!cur->c0) ? &cur->c0 : &cur->c1;
      *newNodePtr = new HCNode(0, 0, nullptr, nullptr, cur);
      cur = *newNodePtr;
      d++;
    }
    cur->symbol = (*it).first;
    done = false;
    while(cur != this->root && !done) {
      done = !cur->p->c1;
      cur = cur->p;
      d--;
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

    parent = new HCNode(chZero->count + chOne->count, chOne->symbol,
                                                                 chZero, chOne);

    chZero->p = chOne->p = parent;

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
  while(cur->c0 && cur->c1) {
    in >> codeSym;
    cur = (codeSym == '0') ? cur->c0 : cur->c1;
  }

  return cur->symbol;
}

int HCTree::decode(BitInputStream& in) const {
  HCNode* cur = this->root;

  while(cur->c0 && cur->c1) {
    cur = (in.readBit() == 0) ? cur->c0 : cur->c1;
  }

  return cur->symbol;
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

  this->deleteAll(node->c0);
  node->c0 = nullptr;

  this->deleteAll(node->c1);
  node->c1 = nullptr;

  node->p = nullptr;

  delete node;
}

void HCTree::encode(HCNode* node, ofstream& out) const {
  if(!node)
    return;

  this->encode(node->p, out);
  if(node->p) {
    out.put((node->p->c0 == node) ? '0' : '1');
    out.flush();
  }
}

void HCTree::encode(HCNode* node, BitOutputStream& out) const {
  if(!node)
    return;
  this->encode(node->p, out);
  if(node->p) {
    out.writeBit((node->p->c0 == node) ? 0 : 1);
  }
}

void HCTree::saveHelper(HCNode* node, BitOutputStream* out, int d) {
  if(node) {
    if(!(node->c0 || node->c1)) {
      out->writeByte(node->symbol);
      out->writeByte(d);
    }
    else {
      this->saveHelper(node->c0, out, d + 1);
      this->saveHelper(node->c1, out, d + 1);
    }
  }
}
