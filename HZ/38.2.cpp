//HZ - 38.2
//Luogu - P5231
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
	static sizeType const charSetSize = 4;
	typedef std::vector<valueType> Vector;
	
private:
	static sizeType converter(char c) {
		if(c == 'E')
			return 0;
			
		if(c == 'S')
			return 1;
			
		if(c == 'W')
			return 2;
			
		if(c =='N')
			return 3;
			
			
		throw std::range_error("");
	}
	
	struct NODE{
		typedef NODE self;
		typedef self* pointer;
		
		std::array<pointer, charSetSize> trans;
		
		std::list<pointer> son;
		
		bool visited;
		
		pointer fail;
		
		NODE(valueType id = -1) : trans(), son(), visited(false), fail(nullptr) {
			trans.fill(nullptr);
		}
		
		pointer& transfer(char c) {
			return trans[converter(c)];
		}
	};
	
	typedef NODE::pointer pointer;
	
	pointer allocate(valueType v = -1) {
		return new NODE(v);
	}
	
	pointer root;
	
	sizeType size;
	
public:
	AC() : root(allocate()), size(0) {};
	
	void insert(const std::string &data) {
		++size;

		pointer current = this->root;
		
		for(auto const &iter : data) {
			if(current->transfer(iter) == nullptr) {
				current->transfer(iter) = allocate();
				
				current = current->transfer(iter);
			} else {
				current = current->transfer(iter);
			}
		}
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
			
			current->fail->son.push_back(current);
			
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
	
	void query(const std::string &data) {
		pointer current = root;
		
		for(auto const &iter : data) {
			current = current->transfer(iter);
			
			for(pointer i = current; i != nullptr && !i->visited; i = i->fail)
				i->visited = true;
		}
	}
	
	valueType calc(const std::string &data) {
		valueType result = 0, depth = 0;
		
		pointer current = root;
		
		for(auto const &iter : data) {
			current = current->transfer(iter);
			
			++depth;
			
			if(current->visited)
				result = depth;
		}
		
		return result;
	}
};

int main() {
	int N, t;
	
	std::cin >> t >> N;
	
	std::string text;
	
	std::cin >> text;
	
	AC ac;
	
	std::vector<std::string> source(N + 1);		
	
	for(int i = 1; i <= N; ++i) {
		std::cin >> source[i];
		
		ac.insert(source[i]);
	}
	
	ac.build();
	
	ac.query(text);
	
	for(int i = 1; i <= N; ++i)
		std::cout << ac.calc(source[i]) << std::endl;
	
	return 0;
}
