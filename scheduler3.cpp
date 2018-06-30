#include <iostream>
#include <vector>
#include <queue>


struct Response{
	Response(int thread, long long start_time):
		thread(thread),
		start_time(start_time)
		{}

	int thread;
	long long start_time;
};

struct Buffer{
	Buffer(int number, long long finish_time):
	number(number),
	finish_time(finish_time)
	{}

	int number;
	long long finish_time;
};



class Scheduler{
public:
	Scheduler(){
		build_threads();
		read_tasks();
	}


	void build_threads(){
		std::cin >> n; //n is the number of threads		
		for (int i = 0; i < n; i++){
			buffers.push_back(Buffer(i,0));
		}

	}

	void read_tasks(){
		std::cin >> m; //m is the number of tasks
		//responses.resize(m);
		
		for (int i = 0; i < m; i++ ){
			long long task;
			std::cin >> task;
			tasks.push(task);
		}
	}

	void swap(int a, int b){
		Buffer tmp(buffers[a].number, buffers[a].finish_time);
		buffers[a]=Buffer(buffers[b].number, buffers[b].finish_time);
		buffers[b]=Buffer(tmp.number, tmp.finish_time);

	}

	void sift_down(int n){
		int left;
    	int right;
    	int min_index;
    	min_index = n;
    	left = n * 2 +1;
    	if (left < buffers.size()){
    		if (buffers[left].finish_time < buffers[min_index].finish_time){
    			min_index = left;
    		}
    		if (buffers[left].finish_time == buffers[min_index].finish_time && buffers[left].number < buffers[min_index].number){
    			min_index = left;
    		}     		
    	}

    	right = n * 2 + 2;
    	if (right< buffers.size()){
    		if (buffers[right].finish_time < buffers[min_index].finish_time){
    			min_index = right;
    		}
    		if (buffers[right].finish_time ==buffers[min_index].finish_time && buffers[right].number < buffers[min_index].number){
    			min_index = right;
    		}
      		
    	}
    	if (min_index != n){
    		if (right< buffers.size() && buffers[left].finish_time == buffers[right].finish_time){
    			if (buffers[left].number <buffers[right].number){
    				min_index=left;
    			}
    			else min_index=right;
    		}
    		swap(min_index, n);
      		sift_down(min_index);
      		
      	}
	}


	void assign_tasks(){
		while (tasks.size()>0){
			long long new_start_time = buffers.front().finish_time;
			int which_buffer = buffers.front().number;
			//std::cout << which_buffer<< ";"<< new_start_time<<std::endl;
			responses.push_back(Response(which_buffer,new_start_time));
			buffers.front().finish_time=new_start_time+tasks.front();
			tasks.pop();
			sift_down(0);
		}

	}

	void print_results(){
		for (int i = 0; i < m; i++){
			std::cout<<responses[i].thread<<" "<<responses[i].start_time<<"\n";
		}

	}


private:
	int n; //number of threads
	int m; //number of tasks
	int time;
	std::vector <Response> responses;
	std::queue <long long> tasks;
	std::vector <Buffer> buffers;  //saves the finish times


};

int main(){
	std::ios_base::sync_with_stdio(false);

	Scheduler scheduler;
	scheduler.assign_tasks();
	scheduler.print_results();

	return 0;
}