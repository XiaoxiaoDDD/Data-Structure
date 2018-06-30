#include <iostream>
#include <vector>
#include <string>

using std::string;

struct Contact
{
    Contact(string name, long long number):
    name(name),
    number(number)
    {
    }
    string name;
    long long number;

};

class Phone_Book
{

private:
    std::vector <std::vector < Contact * > > contacts;
    int n;  // n is the number of requests


public:

    void add_numbers(long long number){
        string name;
        std::cin >> name;
        Contact * find;
        find = find_numbers(number);
        if (find == NULL){
            Contact * tmp;
            tmp = new Contact(name, number);
            contacts[get_hash(number)].push_back(tmp);
        }
        else{
            find->name =name;
        }
        
    }     
      
    int get_hash(long long number){
        return number % n;
    }  


    void del_numbers(long long number){
        Contact * find;
        find = find_numbers(number);
        int index;
        int hash;
        hash=get_hash(number);
        if (find!= NULL){
            for (int i=0; i < contacts[hash].size(); i++){
                if (find == contacts[hash][i]){
                    index =i;
                }
            }
            contacts[get_hash(number)].erase(contacts[get_hash(number)].begin()+index);
        }
    }

    Contact * find_numbers(long long number){
        int hash;
        hash = get_hash(number);
        if (contacts[hash].size() >0){
            for (Contact * ptr: contacts[hash]){
                if (ptr->number == number){
                    return ptr;
                }
            }
            return NULL;
        }
        return NULL;
    }


    void process_requests(){      
        std::cin >> n ;
        contacts.resize(n);
        for (int i = 0; i < n; i++){
            string input;
            std::cin >> input;
            long long read_number;
            std::cin >> read_number;
            if (input =="add") add_numbers(read_number);
            if (input =="del") del_numbers(read_number);
            if (input == "find") {
                Contact * result;
                result = find_numbers(read_number);
                if (result!= NULL) std::cout << result->name <<std::endl;
                else std::cout << "not found" <<std::endl;

            }

        }
    }
    
};

int main(){
    std::ios_base::sync_with_stdio(false);
    Phone_Book phone_book;
    phone_book.process_requests();
    return 0;
}