#include "../../inc/AllHeaders.hpp"

RequestConfig::RequestConfig(HttpRequestParser &request, Listen &host_port, DB &db, Client &client) : request_(request), client_(client), host_port_(host_port), db_(db) {
}

RequestConfig::~RequestConfig() {}

void RequestConfig::setUp() {
    std::vector<KeyMapValue> callingServer = getDataByIdx(db_.serversDB, 0);
    printData(callingServer);
}


// void RequestConfig::setTarget(std::string target) {
//   target_ = target;
// }

// std::string &RequestConfig::getTarget() {
//   return target_;
// }

