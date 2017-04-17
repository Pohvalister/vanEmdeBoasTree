#include <iostream>
#include <set>
#include "vebNT.h"
#include "vebNT.cpp"
#include "algorithm"
#include "ctime"

const int val =10000000;


int main() {
    std::vector<unsigned long long int> values1;
    std::vector<unsigned long long int> values2;
    std::vector<unsigned long long int> values3;
    srand(time(0));
    VEBTree tree(63);
    tree.add(5);
    tree.add(11);
    tree.add(10);
    std::cout << tree.next(5) << std::endl;
    tree.remove(10);
    std::cout << tree.next(5) << std::endl;
    std::cout << tree.prev(40) << std::endl;
    std::cout << tree.prev(1) << std::endl;

    VEBTree tree1(my_2_log(val));
    VEBTree tree2(my_2_log(val));
    VEBTree tree3(my_2_log(val));

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

    std::set<unsigned long long int> set;
    std::random_shuffle(values3.begin(),values3.end());

    VEBTree tree4(my_2_log(val));
    VEBTree tree5(my_2_log(val));

    for (int i=0;i<100000;i++){
        set.insert(values3[i]);
        tree4.add(values3[i]);
        tree5.add(values3[i]);
    }
    int tmp=values3[0];
    std::random_shuffle(values3.begin(),values3.end());
    bool flag =false;
    for (auto iter=values3.begin();iter!=values3.end();++iter){
        if (*iter==tmp)
            flag=true;
        if (flag) {
            if (tree5.prev(tree4.next(*iter)) != *iter) {
                std::cout << "NOOO\n"<<tree5.prev(tree4.next(*iter))<<' '<<*iter<<'\n';
            }
        }else{
            if (*iter!=*(++iter))
                tree5.remove(*iter);
        }

    }
    std::sort(values3.begin(),values3.end());

    for (int i=1;i<100000;i++){
        if (values3[i-1]!=values3[i]&&tree4.next(values3[i-1])!=values3[i])
            std::cout<<"NOnext "<<tree4.next(values3[i-1])<<" "<<values3[i]<<'\n';
        if (values3[i-1]!=values3[i]&&tree4.prev(values3[i])!=values3[i-1])
            std::cout<<"NOprev "<<tree4.prev(values3[i])<<" "<<values3[i-1]<<'\n';;
    }

}