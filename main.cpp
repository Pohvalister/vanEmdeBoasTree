#include <iostream>
#include "veb.h"
#include "veb.cpp"
#include "algorithm"
#include "ctime"

const int val =10000000;


int main() {
    std::vector<unsigned long long int> values1;
    std::vector<unsigned long long int> values2;
    std::vector<unsigned long long int> values3;
    srand(time(0));
    VEBTree<20> tree;
    tree.add(5);
    tree.add(11);
    tree.add(10);
    std::cout << tree.next(5) << std::endl;
    tree.remove(10);
    std::cout << tree.next(5) << std::endl;
    std::cout << tree.prev(40) << std::endl;
    std::cout << tree.prev(1) << std::endl;

    VEBTree<val> tree1;
    VEBTree<val> tree2;
    VEBTree<val> tree3;

    for (int i=0;i<100000;i++){
        values1.push_back(i);
        values2.push_back(val-i);
        values3.push_back((unsigned long long )rand()%val);
    }

    for (int i=0;i<100000;i++){
        tree1.add(values1[i]);
        tree2.add(values2[i]);
        tree3.add(values3[i]);
    }
    std::random_shuffle(values1.begin(),values1.end());
    std::random_shuffle(values2.begin(),values2.end());
    std::random_shuffle(values3.begin(),values3.end());
    for (int i=0;i<100000;i++){
        tree1.remove(values1[i]);
        tree2.remove(values2[i]);
        tree3.remove(values3[i]);
    }
    std::cout<<tree1.next(0)<<'\n';
    std::cout<<tree1.prev(NO)<<'\n';
    std::cout<<tree2.next(0)<<'\n';
    std::cout<<tree2.prev(NO)<<'\n';
    std::cout<<tree3.next(0)<<'\n';
    std::cout<<tree3.prev(NO)<<'\n';

}