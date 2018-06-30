#include <iostream>
#include <vector>

struct Table {
	Table (int size, int id):
	size(size),
	id(id)	
	{}

	int size; 
	int id;
	
};

class Merge
{
public:
	Merge(){
		max = 0;
		read_input();
	}

	void read_input(){
		std::cin >> num_tables;
		std::cin >> num_mergers;
		for (int i=0; i < num_tables; i++){
			int tmp;
			std::cin >> tmp;
			if (tmp > max) max =tmp;
			tables.push_back(Table(tmp,i));
		}
	}

	void Sovler(){
		for (int i = 0; i < num_mergers; i++){
			int a;
			int b;
			std::cin >> a;
			std::cin >> b;
			merge_tables(a-1, b-1); // a and b are indeces
		}
	}

	int get_destination(int n){ //to get which set it belongs to
		if (tables[n].id != n){
			tables[n].id = get_destination(tables[n].id);
			return tables[n].id;
		}
		else return n;
	}

	void merge_tables(int a, int b){
		if (get_destination(a)!= get_destination(b)){
			int size_sum;
			size_sum = tables[get_destination(a)].size + tables[get_destination(b)].size;
			tables[get_destination(b)].id = get_destination(a);
			tables[get_destination(a)].size = size_sum;
			if (size_sum > max) max = size_sum;
		}
		std::cout << max <<std::endl;
	}

private:
	int num_tables;
	int num_mergers;
	int max;
	std::vector <Table> tables;

};


int main(){
	std::ios_base::sync_with_stdio(false);
	Merge merge;
	merge.Sovler();
	return 0;
}