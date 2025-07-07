
#include <chrono>
#include <cstdint>
#include <string>
class StatTime
{
public:
    //阈值，单位毫秒 默认60秒
    StatTime(int32_t threshold = 60000) : threshold(threshold){}
    ~StatTime(){}

    void start(){
        start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        if(origin_time == 0){
            origin_time = start_time;
        }
    }
    void end(){
        end_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        int32_t duration = end_time - start_time;
        peak_value = std::max(peak_value, duration);
        average_value = (average_value + duration) / 2;
        if(end_time - origin_time > threshold){
            needReport = true;
        }
    }

    //是否超过阈值，超过阈值则返回true
    bool needReport(){
        return needReport;
    }

    std::string getStatInfo(){
        return "peak_value: " + std::to_string(peak_value) + " average_value: " + std::to_string(average_value);
    }

    void reset(){
        peak_value = 0;
        average_value = 0;
        needReport = false;
    }

private:
    bool needReport {false};

    int64_t start_time  {0};
    int64_t origin_time {0};    //记录最开始时间
    int64_t end_time {0};

    int32_t threshold {0};   //阈值，单位毫秒
    int32_t peak_value {0};  //峰值
    int32_t average_value {0}; //平均值
};
