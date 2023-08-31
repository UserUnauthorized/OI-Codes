//Checker
#include <bits/stdc++.h>
#include <windows.h>

std::string const root = R"(C:\Users\hzoi\Documents\check\)";
std::string const inputFile = root + "check.in";
std::string const outputFile = root + "check.out";
std::string const answerFile = root + "check.ans";
std::string const Generator = root + "Generator.exe";

std::string const correct = root + "std.exe";
std::string const wrong = root + "wa.exe";
std::string const correctOrder = (correct + " < " + inputFile + " > " + answerFile);
std::string const wrongOrder = (wrong + " < " + inputFile + " > " + outputFile);

//#define TESTLIB_CHECKER

#ifdef TESTLIB_CHECKER
std::string const Checker = root + "Checker.exe";
std::string const judgeOrder = (Checker + " " + inputFile + " " + answerFile + " " + outputFile);
#else
std::string const judgeOrder = ("fc " + answerFile + ' ' + outputFile + " > nul");
#endif

int const N = 100;

int run(const std::string &);

constexpr std::chrono::milliseconds TimeLimit(1000);

void color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    std::random_device rd;

    for (int t = 1; true; ++t) {
        unsigned int const seed = rd() ^ time(nullptr) ^ std::chrono::steady_clock::now().time_since_epoch().count();

        std::string genOrder = Generator;

        genOrder.append(" -N=").append(std::to_string(N));
        genOrder.append(" -seed=").append(std::to_string(seed));
        genOrder.append(" > ").append(inputFile);

        run(genOrder);

        run(correctOrder);
        std::chrono::steady_clock::time_point const start = std::chrono::steady_clock::now();
        int const code = run(wrongOrder);
        std::chrono::steady_clock::time_point const end = std::chrono::steady_clock::now();

        std::chrono::duration<double, std::milli> const time = end - start;

        if (code != 0) {
            color(13);
            char str[100];
            sprintf(str, "Runtime Error, Case #%d", t);
            std::cout << str;

            return 0;
        } else if (end - start > TimeLimit) {
            color(14);
            printf("Time Limit Exceeded, Case #%d, Time %.0lfms\n", t, time.count());

            if (end - start > TimeLimit * 10)
                return 0;
        } else if (run(judgeOrder)) {
            color(12);
            char str[100];
            sprintf(str, "Wrong Answer, Case #%d", t);
            std::cout << str;

            return 0;
        } else {
            color(10);
            char str[100];
            sprintf(str, "Accepted, Case #%d, Time %.0lfms\n\n", t, time.count());
            std::cout << str;
        }
    }
}

int run(const std::string &str) {
    return system(str.c_str());
}