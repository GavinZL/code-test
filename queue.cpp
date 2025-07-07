

#include <queue>
#include <stdio.h>


struct A{
    int a;
    int b;
};

int main()
{

    A ta[2];

    ta[0].a = 11;
    ta[0].b = 12;

    ta[1].a = 13;
    ta[1].b = 14;

    std::queue<A*> que;
    que.push(&ta[0]);
    que.push(&ta[1]);



    printf("%d , size: %d\n", que.front()->a, que.size());
    que.pop();

    que.push(&ta[0]);

    printf("%d , size: %d \n", que.front()->a, que.size());
    que.pop();


printf("%d , size: %d \n", que.front()->a, que.size());
    return 0;
}