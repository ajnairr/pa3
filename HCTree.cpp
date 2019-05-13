#include "HCTree.hpp"

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

int HCTree::decode(ifstream& in) const {
  unsigned char codeSym = 0;
  HCNode* cur = this->root;
  while(cur->c0 && cur->c1) {
    in >> codeSym;
    cur = (codeSym == '0') ? cur->c0 : cur->c1;
  }

  return cur->symbol;
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
    out << ((node->p->c0 == node) ? '0' : '1');
    out.flush();
  }
}
