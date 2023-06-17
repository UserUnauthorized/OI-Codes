//Checker
#include <bits/stdc++.h>

std::string const root = "C:\\Users\\hzoi\\Documents\\check\\";
std::string const inputFile = root + "check.in";
std::string const outputFile = root + "check.out";
std::string const answerFile = root + "check.ans";
std::string const Generator = root + "Generator.exe";
std::string const seedFile = root + "seed.gen";
std::string const correct = root + "std.exe";
std::string const wrong = root + "wa.exe";

std::string const genOrder = (Generator + " < " + seedFile + " > " + inputFile);
std::string const correctOrder = (correct + " < " + inputFile + " > " + answerFile);
std::string const wrongOrder = (wrong + " < " + inputFile + " > " + outputFile);
std::string const fcOrder = ("fc " + answerFile + ' ' + outputFile + " > nul");

int main() {
    std::random_device rd;

    for(int t = 1; true; ++t) {
        unsigned int const seed = rd() ^ time(0) ^ std::chrono::steady_clock::now().time_since_epoch().count();

        std::ofstream sef(seedFile);
        sef << seed;
        sef.close();

        system(genOrder.c_str());

        system(correctOrder.c_str());
        double const start = clock();
        system(wrongOrder.c_str());
        double const end = clock();

        if(end - start > 1100){
            printf("Time Limit Exceeded, Case #%d, Time %.0lfms\n", t, end - start);
            if(end - start > 10000)
                return 0;
        }
        else if(system(fcOrder.c_str())){
            char str[100];
            sprintf(str, "Wrong Answer, Case #%d", t);
            std::cout << str;
            return 0;
        } else {
            char str[100];
            sprintf(str, "Accepted, Case #%d, Time %.0lfms\n\n", t, end - start);
            std::cout << str;
        }
    };
}