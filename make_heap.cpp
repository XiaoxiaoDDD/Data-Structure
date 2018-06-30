#include <iostream>
#include <vector>
#include <cmath>


class Make_heap{
private:
	int count;
	int index_;
	std::vector <int> the_input;
	std::vector <std::pair <int, int> > output;

public:

	Make_heap(){
		build_heap();
	}

	void process(){
		build_heap();
		generate_swaps();
		printresults();
	}


	void build_heap(){
		int size_of_input;
		std::cin >> size_of_input;
		
		the_input.resize(size_of_input);
		for (int i=0; i < size_of_input; i++){
			std::cin >> the_input[i];
		}
		std::cout<<the_input;
	}

	void printresults(){
		std::cout << output.size()<<std::endl;
		for (int i =0 ; i < output.size(); i++){
			std::cout<<output[i].first << " " << output[i].second << std::endl;
		}
	}

	void generate_swaps(){
		
		int starter = floor((the_input.size()-1)/2);
		for (int n = starter; n >=0; n--){
			index_=n;
			siftdown();
		}
	}

	void swap(int big, int small){
		int tmp;
		tmp = the_input[big];
		the_input[big] = the_input[small];
		the_input[small]=tmp;


	}

	void siftdown(){
		int child_a = -1;
		int child_b = -1;
		if (index_*2+1 < the_input.size()) child_a=index_*2+1;
		if (index_*2+2 < the_input.size()) child_b=index_*2+2;
		while (true){

			if (child_a >=0 && child_b >=0){
				if (child_a < child_b){
					output.push_back(std::make_pair(child_a,index_));
					swap(child_a, index_);
					index_=child_a;				
				}
				else {
					output.push_back(std::make_pair(child_b, index_ ));
					swap(child_b, index_);
					index_=child_b;
				}
			}

			else if (child_a>=0 && the_input[index_] > the_input[child_a]){
				output.push_back(std::make_pair(child_a, index_ ));
				swap(child_a, index_);
				index_=child_a;
			}
			else {
				break;
			}		
		}
	}
};


int main(){
	std::ios_base::sync_with_stdio(false);
	Make_heap make_heap;
	make_heap.process();

	return 0;
}

