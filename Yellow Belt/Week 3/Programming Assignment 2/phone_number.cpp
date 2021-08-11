#include "phone_number.h"
#include <stdexcept>
#include <sstream>

using namespace std;


PhoneNumber::PhoneNumber(const string& international_number){
    if(international_number.empty() || international_number[0] != '+'){
        throw invalid_argument("Wrong input. Please make sure you're entering a valid string.");
    }
    stringstream ss;
    ss << international_number;
    ss.ignore(1);
    getline(ss, country_code_, '-');
    getline(ss, city_code_, '-');
    getline(ss, local_number_);

    if(country_code_.empty()){
        throw invalid_argument("country code can't be empty");
    } if(city_code_.empty()){
        throw invalid_argument("city code can't be empty");
    } if(local_number_.empty()){
        throw invalid_argument("local number can't be empty");
    }
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
