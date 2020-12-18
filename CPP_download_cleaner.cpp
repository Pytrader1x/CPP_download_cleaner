// download cleaner cpp app

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std::chrono_literals;
using namespace std::chrono;





int main()
{
    std::string path = "path/";
    int i = 0;
    int deletions = 0;
    // std::vector <std::string> vect;

    auto now = fs::file_time_type::clock::now();
    std::time_t now_time = decltype(now)::clock::to_time_t(now);

    std::cout << "Current date: " << std::asctime(std::localtime(&now_time)) << std::endl;

    for (const auto & entry : fs::directory_iterator(path)){

        typedef duration<int, std::ratio<86400>> days;

        auto ftime = fs::last_write_time(entry.path());
        std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);

        std::cout << i << ") " << entry.path()<< " ++ File write time of " << std::asctime(std::localtime(&cftime));

        auto now = fs::file_time_type::clock::now();
        std::time_t now_time = decltype(now)::clock::to_time_t(now);

        int days_difference = duration_cast<days>(now - fs::last_write_time(entry.path())).count();

        std::cout << i << ") " <<"Days since last modification time: " << days_difference << std::endl << '\n';;
       
       char choice = 'x';
       bool user_mode = false;
       if(days_difference > 240){
           if(user_mode == true){

                std::cin >> choice;
            if(choice == 'y'){
                std::cout << "Deleting: " << entry.path() << std::endl;
            }
            else{
                std::cout << "Not Deleting: " << entry.path() << std::endl;
            }
           }
           else if(user_mode == false){
               std::cout << "Deleting: " << entry.path() << std::endl;
               entry.path();

               if(remove(entry.path()) != 0){
                   perror("File deletion failed");
               }
               else{
                   std::cout<< "File deleted succesfully " << std::endl;
               }
               deletions++;
               
           }
           
           
       }

        i++;
    
    }
        
     
    std::cout << deletions << " Deletions" << std::endl; 
        
}