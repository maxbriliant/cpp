#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <numeric>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

auto stat() {
    ifstream f("/proc/stat");
    string l;
    getline(f, l);
    istringstream iss(l);
    vector<long long> n;
    string w;
    iss >> w;
    while (iss >> w) try { n.push_back(stoll(w)); } catch (...) {}
    return n;
}

int main() {
    auto a = stat();
    this_thread::sleep_for(3s);
    auto b = stat();
    if (a.size() < 4 || b.size() < 4) return cerr << "Zu wenig Stats!\n", 1;
    auto tot = [&](const auto& v){ return accumulate(v.begin(), v.end(), 0LL); };
    auto dt = tot(b) - tot(a);
    auto di = b[3] - a[3];
    cout << fixed << setprecision(2) << "CPU: " << (dt > 0 ? 100.0 * (dt - di) / dt : 0.0) << "%\n";
    return 0;
}