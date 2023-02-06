#pragma once

using namespace eosio;
using namespace std;

namespace utils {

    bool ends_with(string const & value, string const & ending)
    {
        return value.size() >= ending.size() && equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    void rule_check(bool conditonal, const char* message){
      if(!conditonal){
        check(false, message);
      }
    }
}