#include <iostream>
#include <map>

using namespace std;

void addOrInsert(map<u_int64_t, u_int64_t, greater<u_int64_t>>& Map, u_int64_t x, u_int64_t ile){
	auto it = Map.find(x);
	if(it == Map.end()){
		Map.emplace(x, ile);
	}else{
		it->second += ile;
	}
}


int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	map<u_int64_t, u_int64_t, greater<u_int64_t>> Map;

	u_int64_t n;
	cin >> n;


	for(u_int64_t i = 1; i<=n; i++){
		u_int64_t x;
		cin >> x;
		addOrInsert(Map, x, 1);
	}

	u_int64_t m;
	cin >>m;

	for(u_int64_t i=1; i<=m; i++){
		u_int64_t x;
		cin >> x;

		while(x > 0){
			auto it = Map.begin();
			if(it->second <= x){
				x -= it->second;

				if(it->first%2 == 0){
					addOrInsert(Map, it->first/2, 2*it->second);
				}else{
					addOrInsert(Map, it->first/2, it->second);
					addOrInsert(Map, it->first/2 + 1, it->second);
				}
				Map.erase(it);
			}else{
				it->second -= x;
				if(it->first%2 == 0){
					addOrInsert(Map, it->first/2, 2*x);
				}else{
					addOrInsert(Map, it->first/2, x);
					addOrInsert(Map, it->first/2 + 1, x);
				}
				x = 0;
			}

		}


		cout << Map.size() << "\n";


	}




	//cout <<;
	return 0;
}
