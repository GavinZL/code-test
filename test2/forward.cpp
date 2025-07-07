

#include <stdio.h>
#include <utility>
#include <vector>

#include <forward_list>
#include <list>
#include <queue>

class A
{
public:
    A(int aa, int bb):a(aa), b(bb){}

    void print()
    {
        printf("a=%d, b=%d\n", a, b);
    }
private:
    int a;
    int b;
};


int main(int argc, char* argv[])
{

    std::unique_ptr<A> a1(new A(1, 0));
    std::unique_ptr<A> a2(new A(2, 0));
    std::unique_ptr<A> a3(new A(3, 0));
    std::unique_ptr<A> a4(new A(4, 0));

    std::vector<std::unique_ptr<A>> ve(4);
    ve[0] = std::move(a1);
    ve[1] = std::move(a2);
    ve[2] = std::move(a3);
    ve[3] = std::move(a4);
    
    std::vector<std::unique_ptr<A>> v;
    printf("ve:%d, v:%d\n", ve.size(), v.size());

    v = std::forward<std::vector<std::unique_ptr<A>>>(ve);

    printf("ve:%d, v:%d\n", ve.size(), v.size());


    std::forward_list<int> forwardlist {1, 2, 3 , 4, 5};

    printf("front: %d", forwardlist.front());
    for(auto &it : forwardlist)
    {
        printf("%d-", it);
    }
    printf("\n");
    std::list<int> list{1,2,3,4,5,6};
    printf("-->front: %d, back: %d\n", list.front(), list.back());


    std::queue<int> queue ;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    printf("queue: front: %d, back: %d\n", queue.front(), queue.back());
}