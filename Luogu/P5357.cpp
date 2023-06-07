//Luogu - P5357
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
	static sizeType const charSetSize = 30;
	typedef std::vector<valueType> Vector;
	
private:
	static sizeType converter(char c) {
		if(c < 'a' || c > 'z')
			throw std::range_error("");
		
		return c - 'a';
	}
	
	struct NODE{
		typedef NODE self;
		typedef self* pointer;
		
		std::array<pointer, charSetSize> trans;
		
		std::list<pointer> son;
		
		valueType visitedTime;
		
		std::list<int> endId;
		
		pointer fail;
		
		NODE(valueType id = -1) : trans(), son(), visitedTime(0), endId(), fail(nullptr) {
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
	
	void insert(const std::string &data, valueType id) {
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
		
		current->endId.push_back(id);
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
	
	Vector query(const std::string &data) {
		pointer current = root;
		
		++root->visitedTime;
		
		for(auto const &iter : data) {
			current = current->transfer(iter);
			
			++current->visitedTime;
		}
		
		Vector result(size + 1, 0);
		
		calc(root, result);
		
		return result;
	}
	
	valueType calc(const pointer &current, Vector &V) {
		int result = current->visitedTime;
		
		for(auto const &iter : current->son)
			result += calc(iter, V);
			
		for(auto const &iter : current->endId)
			V[iter] = result;
		
		return result;
	}
};

int main() {
	int N;
	
	std::cin >> N;
	
	AC ac;
	
	std::vector<std::string> source(N + 1);		
	
	std::string text;
	
	for(int i = 1; i <= N; ++i) {
		std::cin >> source[i];
		
		text = text + source[i];
		
		ac.insert(source[i], i);
	}
	
	ac.build();
	
	AC::Vector result = ac.query(text);
	
	for(int i = 1; i <= N; ++i)
		std::cout << result[i] << std::endl;
	
	return 0;
}