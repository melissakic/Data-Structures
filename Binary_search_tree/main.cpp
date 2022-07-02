#include <iostream>
#include "stablo.hpp"


int main(void)
{
   Tree<int> moj_tree;
    moj_tree.insert(6);
  moj_tree.insert(4);
  moj_tree.insert(5);
  moj_tree.insert(3);
  moj_tree.insert(8);
  moj_tree.insert(11);
  moj_tree.insert(9);


  moj_tree.incorder();
  std::cout << std::endl;
  
    return 0;
}
