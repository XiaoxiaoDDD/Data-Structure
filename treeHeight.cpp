#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

int search_children(Node * parent, int & height, int & maxHeight)
{
  height+=1;
  if (parent->children.empty())
  {
    maxHeight= (height > maxHeight ? height: maxHeight);
    //std::cout<<height<<std::endl;
    return 0;
  }
  for (int i=0; i < parent->children.size();i++)
  {
    if (search_children(parent->children[i],height,maxHeight)==0)
      height-=1;
  }
  return 0;
}





int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  int root_index;
  std::cin >> n;

  std::vector <Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    nodes[child_index].key = child_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
      root_index = child_index;
  }


  // Replace this code with a faster implementation


  int maxHeight = 0;
  int height=0;
  search_children(&nodes[root_index],height, maxHeight);
  std::cout<<maxHeight<<std::endl;

  return 0;
}


int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
