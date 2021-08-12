#include "query.h"
using namespace std;

istream& operator >> (istream& is, Query& q){
    string str;
    is >> str;
    if (str == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count = 0;
    is >> stop_count;
    q.stops.resize(stop_count);
    for (auto& stop : q.stops) {
      is >> stop;
    }
  } else if (str == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (str == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (str == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }

  return is;
}

