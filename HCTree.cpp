#include "HCTree.hpp"

void HCTree::build(const vector<int>& freqs) {
  huffman_queue trees;

  for(unsigned int i = 0; i < freqs.size(); i++) {
    if(freqs[i] > 0) {
      this->leaves[i] = new HCNode(freqs[i], (byte)i);
      trees.push(this->leaves[i]);
    }
  }

  if(trees.empty()) {
    return;
  }

  HCNode* chZero;
  HCNode* chOne;
  HCNode* parent;
  while(trees.size > 1) {
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
  trees.pop();
}

void HCTree::encode(byte symbol, ofstream& out) const {
  this->encode(this->leaves[symbol], out);
}

int HCTree::decode(ifstream& in) const {
  int codeSym;
  HCNode* cur = root;
  while(codeSym = in.get()) {
    if(!cur)
      return -1;

    if((byte)codeSym == '0')
      cur = cur->c0;
    else
      cur = cur->c1;

    if(!cur->c0 && !cur->c1)
      return cur->symbol;
  }

  return -1;
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
    out << (node->p->c0 == node) ? '0' : '1';
    out.flush();
  }
}
