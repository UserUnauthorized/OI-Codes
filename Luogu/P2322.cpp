//HZ - 38.5
//Luogu - P2322
#include<bits/stdc++.h>

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

class AC {
public:
	typedef int valueType;
	typedef size_t sizeType;
	static sizeType const charSetSize = 26;
	typedef std::vector<valueType> Vector;
	
private:
	static sizeType converter(char c) {
		return c - 'A';
			
		throw std::range_error("");
	}
	
	static char reConverter(sizeType x) {
		return (char)x + 'A';
	}
	
	struct NODE{
		typedef NODE self;
		typedef self* pointer;
		
		std::array<pointer, charSetSize> trans;
		
		int endId, path;
		
		pointer fail;
		
		NODE() : trans(), endId(0), path(0), fail(nullptr) {
			trans.fill(nullptr);
		}
		
		pointer& transfer(char c) {
			return trans[converter(c)];
		}
	};
	
	typedef NODE::pointer pointer;
	
	pointer allocate() {
		return new NODE();
	}
	
	pointer root;
	
	sizeType size;
	
public:
	AC() : root(allocate()), size(0){};
	
	void insert(const std::string &data, int id) {
		++size;
		
		pointer current = this->root;
		
		for(auto const &iter : data) {
			if(current->transfer(iter) == nullptr) {
				current->transfer(iter) = allocate();
				
				current = current->transfer(iter);
			} else {
				current = current->transfer(iter);
			}
			
			current->path |= 1 << id;
		}

		current->endId |= 1 << id;
	}
	
	void build() {
		root->fail = root;
		
		std::queue<pointer> que;
		
		for(sizeType i = 0; i < charSetSize; ++i) {
			if(root->trans[i] != nullptr) {
				root->trans[i]->fail = root;
				
				que.push(root->trans[i]);
			} else {
				root->trans[i] = root;
			}
		}
		
				
		while(!que.empty()) {
			pointer current = que.front();
			que.pop();
			
			for(sizeType i = 0; i < charSetSize; ++i) {
				if(current->trans[i] != nullptr) {
					current->trans[i]->fail = current->fail->trans[i];
					
					que.push(current->trans[i]);
				} else {
					current->trans[i] = current->fail->trans[i];
				}
			}
		}
	}
	
private:
	struct STATUS {
		pointer current;
		
		int state;
		
		std::string text;
		
		STATUS() : current(nullptr), state(0), text(){};
		
		STATUS(pointer cur, int sta, std::string str) : current(std::move(cur)), state(sta), text(std::move(str)) {};
		
		friend std::ostream &operator <<(std::ostream &os, STATUS const &sta) {
			os << sta.current << ' ' << sta.state << ' ' << sta.text << std::endl;
			
			return os;
		}
	};

public:
	std::string ans() {
		int const end = (1 << size) - 1;
		
		std::queue<STATUS> que;
		
		que.emplace(root, 0, std::string());
//		debug(que.front());
		while(!que.empty()) {
			auto const now = que.front();
			
			que.pop();
			
			pointer current = now.current;
			
			for(sizeType i = 0; i < charSetSize; ++i) {
				if(current->endId == 0 && ((~now.state) & current->trans[i]->path) == 0)
					continue;
				
				STATUS next;
				
				next.current = current->trans[i];
				next.state = now.state | next.current->endId;
				next.text = now.text + reConverter(i);
				
//				debug(now, next);
				
				if(next.state == end)
					return next.text;
				else
					que.push(next);
			}
		}
	}
};

int main() {
//	freopen("P2322.err", "w", stderr);
	
	int N;
	
	std::cin >> N;
	
	AC ac;
	
	std::vector<std::string> source(N);
	
	for(int i = 0; i < N; ++i) {
		std::cin >> source[i];
		
		ac.insert(source[i], i);
	}
	
	ac.build();
	
	std::cout << ac.ans() << std::flush;
	
	return 0;
}
