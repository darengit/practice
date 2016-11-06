#ifndef TESTER_H
#define TESTER_H
#include <vector>
#include <map>
#include <unordered_map>
#include "string8.h"
#include "wordreader.h"

struct Item {
    String8 word;
    int count;
    Item(const String8 &w, int c) : word(w), count(c) {}
};

void testLinearSearch(WordReader *r);
template<template<typename...>class M, typename K, typename V> void templatedTestMap(WordReader * r);
void testMap(WordReader *r);
void testUnorderedMap(WordReader *r);
#endif
