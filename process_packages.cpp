#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) {
        bool drop = false;
        int new_finish_time = -1 ;
        int new_start_time = -1 ;

        while (finish_time_.size()>0 && finish_time_.front() <= request.arrival_time)
                finish_time_.pop();
        

        if (finish_time_.size()<size_){
            if (finish_time_.empty()){
                new_start_time = request.arrival_time;
                new_finish_time = request.arrival_time + request.process_time;
                finish_time_.push(new_finish_time);
            }
            else{
                new_finish_time = finish_time_.back() + request.process_time;
                new_start_time = finish_time_.back();
                finish_time_.push(new_finish_time);
            }

        }
        else drop = true;


        //std::cout<<drop<<std::endl;
        return Response( drop, new_start_time );
    }


private:
    int size_;
    std::queue <int> finish_time_;
};


//this reads the input and generates a vector of all requests
std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count; //number of requests
    std::cin >> count;
    for (int i = 0; i < count; i++) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); i++)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    if (not responses.empty()){
        for (int i = 0; i < responses.size(); i++)
            std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;

    }    
}

int main() {
    int size;
    std::cin >> size; //size of the buffer
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
