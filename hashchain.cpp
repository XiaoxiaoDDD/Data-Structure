#include <iostream>
#include <vector>
#include <string>

using std::string;


class Hash_chain{
public:
	int m; //number of buckets
	int n; //number of queries
	std::vector< std::vector <string> > hash_table;

	std::vector<int> converter(string phrase){
		std::vector <int> ascii;
		for (char x: phrase){
			int a;
			a = x;
			ascii.push_back(x);
		}
		return ascii;
	}

	int get_hash(string input){
		std::vector<int> list_of_int;
		list_of_int= converter(input);
		long long intermediate;
		intermediate = 0;
		for (int i = list_of_int.size()-1; i >= 0; i--){
			intermediate = ((intermediate * 263 + list_of_int[i]) % 1000000007);
			while (intermediate < 0){
				intermediate = intermediate + m;
		}
		int hash;
		hash = int(intermediate % m);
		while (hash < 0){
			hash = hash + m;
		}
		//std::cout << "***the hash for "<< input << "is " << hash;
		return hash;
	}

	void add(int hash, string input){
		if (find(hash, input) == ""){
			hash_table[hash].insert(hash_table[hash].begin(), input);
		}
	}

	void del(int hash, string input){
		if (find(hash, input) != ""){
			int index;
			for (int i = 0; i < hash_table[hash].size(); i++){
				if (hash_table[hash][i] == input){
					index = i;
					break;
				}
			}
			hash_table[hash].erase(hash_table[hash].begin()+index);
		}
	}

	string find(int hash, string input){
		if (hash_table[hash].empty()){
			return "";
		}
		else{
			for (string one: hash_table[hash]){
				if (one == input){
					return input;
				}
			}
			return "";
		}
		
	}

	void check(int line){
		if (hash_table[line].empty()){
			std::cout << "\n";
		}
		else{
			for (string one: hash_table[line]){
				std::cout<< one << " ";
			}
			std::cout<<std::endl;
		}

	}

	void Solver(){
		std::cin >> m >> n;
		hash_table.resize(m);
		for (int i = 0; i < n; i++){
			string type;
			string content;
			int hash;
			std::cin >> type >>content;
			hash = get_hash(content);

			if (type=="add") {
				add(hash, content);
			}
			if (type=="del") {
				del(hash, content);
			}
			if (type=="find") {
				if (find(hash, content) ==""){
					std::cout << "no" <<std::endl;
				}
				else{
					std::cout <<"yes"<< std::endl;
				}
			}
			if (type=="check") {
				int line;
				line = std::stoi(content);
				check(line);
			}
			// std::cout <<"--------"<<"\n";
			// for (int i = 0; i < m; i++){
				
			// 	std::cout <<i<<": ";
			// 	check(i);
			// }
			// std::cout <<"--------"<<"\n";
		}

	}

};

int main(){
	std::ios_base::sync_with_stdio(false);
	Hash_chain hash_chain;
	hash_chain.Solver();
}