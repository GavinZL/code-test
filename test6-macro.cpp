
#include <vector>
#include <string>

#define DECLARE_PROPERTY(type, name) \
    public:                             \
        inline type get##name(){       \
            return m##name;             \
        }                               \
        inline void set##name(type para){\
            m##name = para;                 \
        }                                   \
    private:                                \
        type  m##name;                       \


#define DECLARE_PROPERTY_VECTOR(type, name) \
    public:                             \
        inline type get##name(){       \
            return m##name;             \
        }                               \
        inline void set##name(type para){\
            m##name = para;                 \
        }                                   \
    private:                                \
        type  m##name;                       \



class A{

    //DECLARE_PROPERTY(int , Age);
    DECLARE_PROPERTY_VECTOR(std::vector<std::string>, DeviceId);

};

int main(){

    reutrn 0;
}