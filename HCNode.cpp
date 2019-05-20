/*
 * Filename: HCNode.cpp
 * Author: Ajay Nair
 * Email: ajnair@ucsd.edu
 * Date: May 20, 2019
 */

#include "HCNode.hpp"

HCNode::HCNode(int count, byte symbol, HCNode* c0, HCNode* c1, HCNode* p) :
                           count(count), symbol(symbol), c0(c0), c1(c1), p(p) {}

bool HCNode::operator<(const HCNode& other) {
  return (this->count != other.count) ? this->count > other.count :
                                        this->symbol > other.symbol;
}

int HCNode::getCount() const {
  return this->count;
}

byte HCNode::getSymbol() const {
  return this->symbol;
}

HCNode* HCNode::getZeroChild() const {
  return this->c0;
}

HCNode* HCNode::getOneChild() const {
  return this->c1;
}

HCNode* HCNode::getParent() const {
  return this->p;
}

HCNode** HCNode::getZeroChildPtr() {
  return &this->c0;
}

HCNode** HCNode::getOneChildPtr() {
  return &this->c1;
}

void HCNode::setCount(int count) {
  this->count = count;
}

void HCNode::setSymbol(byte symbol) {
  this->symbol = symbol;
}

void HCNode::setZeroChild(HCNode* c0) {
  this->c0 = c0;
}

void HCNode::setOneChild(HCNode* c1) {
  this->c1 = c1;
}

void HCNode::setParent(HCNode* p) {
  this->p = p;
}
