
#include <vector>

#include <map>
#include <set>
#include <string>

#define DECLARE_PROPERTY_PARAMS(name, type) \
public:                                     \
    inline const type& get##name()          \
    {                                       \
        return m##name.get();               \
    }                                       \
    inline void set##name(type para)        \
    {                                       \
        m##name.set(para);                  \
    }                                       \
    inline bool is##name##Updated()         \
    {                                       \
        return m##name.updated();           \
    }                                       \
                                            \
private:                                    \
    Params<type> m##name;


template <typename T>
class Params
{
public:
    Params(T def)
        : value(def), defValue(def) {}
    void reset()
    {
        updateFlag = false;
        value      = defValue;
    };
    void resetFlag()
    {
        updateFlag = false;
    };
    void set(T& v)
    {
        value      = v;
        updateFlag = true;
    }
    T& get()
    {
        return value;
    }
    bool updated()
    {
        return updateFlag;
    }

private:
    const T defValue;
    T       value;
    bool    updateFlag = false;
};


class A
{

    using TYPE = std::map<std::string, int>;
    DECLARE_PROPERTY_PARAMS(map,TYPE);
};


int main(int argc, char* argv[]){

    

    // std::vector<int> a;
    // a.push_back(1);
    // a.push_back(1);

    // std::vector<int> b;
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);
    // b.push_back(11);


    // a = b;

    // printf("a-size: %d, b-size:%d \n", a.size(), b.size());

    return 0;
}