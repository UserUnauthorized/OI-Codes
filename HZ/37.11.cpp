//HZ - 37.11
//Luogu - UVA11362
//Luogu - SP4033
#include<bits/stdc++.h>

#include <iostream>
#include <vector>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

class Trie {
public:
	static int const charSetSize = 10;
	
private:
	struct NODE{
		typedef NODE self;
		typedef self* pointer;
		
		bool isEnd;
		std::array<pointer, Trie::charSetSize> son;
		
		NODE() : isEnd(false) , son(){
			son.fill(nullptr);
		};
	};
	
	typedef NODE::pointer pointer;
	
	static pointer allocate() {
		return new NODE();
	}
	
	
	static void freeNode(pointer &p) {
		delete p;
	}
	
	pointer root;

public:
	Trie():root(allocate()){};
	
	static int convert(char x) {
		return x - '0';
	}
	
	bool insert(const std::string &data) {
		bool passEnd = false, createdNode = false;
		
		pointer current = this->root;
		
		for(auto const &iter : data) {
			if(current->son[convert(iter)] == nullptr) {
				createdNode = true;
				
				current->son[convert(iter)] = allocate();
				
				current = current->son[convert(iter)];
			} else {
				current = current->son[convert(iter)];
				
				if(current->isEnd) {
					passEnd = true;
					break;
				}
			}
		}
		
		current->isEnd = true;
		
		return passEnd || !createdNode;
	}
	
	void clear() {
		for(auto &iter : this->root->son) {
			if(iter != nullptr) {
				clear(iter);
				iter = nullptr;
			}
		}
	}
	
protected:
	void clear(pointer &current) {
		for(auto &iter : current->son) {
			if(iter != nullptr) {
				clear(iter);
				iter = nullptr;
			}
		}
				
		freeNode(current);
	}
} tree;

int main() {
	int T;
	
	std::cin >> T;
	
	for(int t = 0; t < T; ++t) {
		int n;
		
		std::cin >> n;
		
		bool success = false;
		
		for(int i = 0; i < n; ++i) {
			std::string data;
			
			std::cin >> data;
			
			if(success)
				continue;
				
			if(tree.insert(data))
				success = true;
		}
		
		tree.clear();
		
		std::cout << (success ? "NO" : "YES") << '\n';
	}
	
	std::cout << std::flush;
	
	return 0;
}
